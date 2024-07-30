//
// Created by admin on 2024/7/16.
//

#include "WBitmapDirectX.hpp"
#include "WRendererDirectX.hpp"
#include "WCommandListDirectX.hpp"

namespace Whale::DirectX
{
	
	void WBitmapDirectX::OnEnable() noexcept
	{
	
	}
	
	void WBitmapDirectX::OnDisable() noexcept
	{
	
	}
	
	Bool WBitmapDirectX::IsGPUResourceCreated() const noexcept
	{
		return m_pResource;
	}
	
	Bool WBitmapDirectX::CreateFromFile(const Whale::WBitmapArg &arg) noexcept
	{
		// 定义一个位图格式的图片数据对象接口
		Microsoft::WRL::ComPtr<IWICBitmapSource>    pIBMP;
		Microsoft::WRL::ComPtr<IWICPixelFormatInfo> pIWICPixelInfo;
		DXGI_FORMAT                                 targetFormat;
		m_pRenderer->GetPWICForDirectX()->LoadFromFile(arg.m_fileName, pIBMP, pIWICPixelInfo, targetFormat);
		
		//获得图片大小（单位：像素）
		THROW_IF_FAILED(pIBMP->GetSize(&this->m_width, &this->m_height));
		
		// 到这里终于可以得到BPP了，这也是我看的比较吐血的地方，为了BPP居然饶了这么多环节
		THROW_IF_FAILED(pIWICPixelInfo->GetBitsPerPixel(&this->m_BPP));
		
		// 计算图片实际的行大小（单位：字节），这里使用了一个上取整除法即（A+B-1）/B ，
		// 这曾经被传说是微软的面试题,希望你已经对它了如指掌
		uint32 nPicRowPitch = (uint64_t(this->m_width) * uint64_t(this->m_BPP) + 7u) / 8u;
		
		D3D12_RESOURCE_DESC stTextureDesc = {};
		stTextureDesc.Dimension          = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		stTextureDesc.MipLevels          = 1;
		stTextureDesc.Format             = targetFormat; //DXGI_FORMAT_R8G8B8A8_UNORM;
		stTextureDesc.Width              = m_width;
		stTextureDesc.Height             = m_height;
		stTextureDesc.Flags              = D3D12_RESOURCE_FLAG_NONE;
		stTextureDesc.DepthOrArraySize   = 1;
		stTextureDesc.SampleDesc.Count   = 1;
		stTextureDesc.SampleDesc.Quality = 0;
		
		
		// 创建默认堆上的资源，类型是Texture2D，GPU对默认堆资源的访问速度是最快的
		// 因为纹理资源一般是不易变的资源，所以我们通常使用上传堆复制到默认堆中
		// 在传统的D3D11及以前的D3D接口中，这些过程都被封装了，我们只能指定创建时的类型为默认堆
		auto properties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);
		THROW_IF_FAILED(
			m_pRenderer->GetPid3D12Device()->CreateCommittedResource(
				&properties, D3D12_HEAP_FLAG_NONE,
				&stTextureDesc                // 可以使用CD3DX12_RESOURCE_DESC::Tex2D来简化结构体的初始化
				, D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(m_pResource.ReleaseAndGetAddressOf())));
		
		// 获取上传堆资源缓冲的大小，这个尺寸通常大于实际图片的尺寸
		const UINT64 n64UploadBufferSize = GetRequiredIntermediateSize(m_pResource.Get(), 0, 1);
		
		// 创建用于上传纹理的资源,注意其类型是Buffer
		// 上传堆对于GPU访问来说性能是很差的，
		// 所以对于几乎不变的数据尤其像纹理都是
		// 通过它来上传至GPU访问更高效的默认堆中
		
		properties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		auto buffer = CD3DX12_RESOURCE_DESC::Buffer(n64UploadBufferSize);
		THROW_IF_FAILED(
			m_pRenderer->GetPid3D12Device()->CreateCommittedResource(
				&properties,
				D3D12_HEAP_FLAG_NONE,
				&buffer,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(m_pUpload.ReleaseAndGetAddressOf())));
		
		//按照资源缓冲大小来分配实际图片数据存储的内存大小
		void *pbPicData = ::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, n64UploadBufferSize);
		if (nullptr == pbPicData)
		{
			if (Win32::FResult(HRESULT_FROM_WIN32(GetLastError())).IsFailed()) return false;
		}
		
		UINT8 *pData = nullptr;
		
		#if true
		
		//从图片中读取出数据
		THROW_IF_FAILED(pIBMP->CopyPixels(
			nullptr, nPicRowPitch, static_cast<UINT>(nPicRowPitch * m_width)   //注意这里才是图片数据真实的大小，这个值通常小于缓冲的大小
			, reinterpret_cast<BYTE *>(pbPicData)));//{//下面这段代码来自DX12的示例，直接通过填充缓冲绘制了一个黑白方格的纹理
		
		#else
		{
			//还原这段代码，然后注释上面的CopyPixels调用可以看到黑白方格纹理的效果
			const UINT rowPitch          = nPicRowPitch; //nTextureW * 4; //static_cast<UINT>(n64UploadBufferSize / nTextureH);
			const UINT cellPitch         = rowPitch >> 3;        // The width of a cell in the checkboard texture.
			const UINT cellHeight        = m_width >> 3;    // The height of a cell in the checkerboard texture.
			const UINT textureSize       = static_cast<UINT>(n64UploadBufferSize);
			UINT       nTexturePixelSize = static_cast<UINT>(n64UploadBufferSize / m_height / m_width);
			
			pData = reinterpret_cast<UINT8 *>(pbPicData);
			
			for (UINT n = 0; n < textureSize; n += nTexturePixelSize)
			{
				UINT x = n % rowPitch;
				UINT y = n / rowPitch;
				UINT i = x / cellPitch;
				UINT j = y / cellHeight;
				
				if (i % 2 == j % 2)
				{
					pData[n]     = 0x00;        // R
					pData[n + 1] = 0x00;    // G
					pData[n + 2] = 0x00;    // B
					pData[n + 3] = 0xff;    // A
				}
				else
				{
					pData[n]     = 0xff;        // R
					pData[n + 1] = 0xff;    // G
					pData[n + 2] = 0xff;    // B
					pData[n + 3] = 0xff;    // A
				}
			}
		}
		#endif
		
		//获取向上传堆拷贝纹理数据的一些纹理转换尺寸信息
		//对于复杂的DDS纹理这是非常必要的过程
		UINT64 n64RequiredSize    = 0u;
		UINT   nNumSubresources   = 1u;  //我们只有一副图片，即子资源个数为1
		UINT64 n64TextureRowSizes = 0u;
		UINT   nTextureRowNum     = 0u;
		
		D3D12_RESOURCE_DESC stDestDesc = m_pResource->GetDesc();
		
		m_pRenderer->GetPid3D12Device()->GetCopyableFootprints(
			&stDestDesc, 0, nNumSubresources, 0, &m_stTxtLayouts, &nTextureRowNum, &n64TextureRowSizes, &n64RequiredSize
		);
		
		// 因为上传堆实际就是CPU传递数据到GPU的中介
		// 所以我们可以使用熟悉的Map方法将它先映射到CPU内存地址中
		// 然后我们按行将数据复制到上传堆中
		// 需要注意的是之所以按行拷贝是因为GPU资源的行大小
		// 与实际图片的行大小是有差异的,二者的内存边界对齐要求是不一样的
		pData = nullptr;
		THROW_IF_FAILED(m_pUpload->Map(0, nullptr, reinterpret_cast<void **>(&pData)));
		
		BYTE       *pDestSlice = reinterpret_cast<BYTE *>(pData) + m_stTxtLayouts.Offset;
		const BYTE *pSrcSlice  = reinterpret_cast<const BYTE *>(pbPicData);
		for (UINT  y           = 0; y < nTextureRowNum; ++y)
		{
			memcpy(
				pDestSlice + static_cast<SIZE_T>(m_stTxtLayouts.Footprint.RowPitch) * y,
				pSrcSlice + static_cast<SIZE_T>(nPicRowPitch) * y, nPicRowPitch
			);
		}
		// 取消映射 对于易变的数据如每帧的变换矩阵等数据，可以撒懒不用Unmap了，
		// 让它常驻内存,以提高整体性能，因为每次Map和Unmap是很耗时的操作
		// 因为现在起码都是64位系统和应用了，地址空间是足够的，被长期占用不会影响什么
		m_pUpload->Unmap(0, nullptr);
		
		// 释放图片数据，做一个干净的程序员
		::HeapFree(::GetProcessHeap(), 0, pbPicData);
		
		
		//向命令队列发出从上传堆复制纹理数据到默认堆的命令
		CD3DX12_TEXTURE_COPY_LOCATION Dst(m_pResource.Get(), 0);
		CD3DX12_TEXTURE_COPY_LOCATION Src(m_pUpload.Get(), m_stTxtLayouts);
		m_pRenderer->GetPCommandList()->GetPID3D12CommandList()->CopyTextureRegion(&Dst, 0, 0, 0, &Src, nullptr);
		
		//设置一个资源屏障，同步并确认复制操作完成
		//直接使用结构体然后调用的形式
		D3D12_RESOURCE_BARRIER stResBar = {};
		stResBar.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		stResBar.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		stResBar.Transition.pResource   = m_pResource.Get();
		stResBar.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
		stResBar.Transition.StateAfter  = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
		stResBar.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
		
		m_pRenderer->GetPCommandList()->GetPID3D12CommandList()->ResourceBarrier(1, &stResBar);
		
		
		//10、创建SRV堆 (Shader Resource View Heap)
		D3D12_DESCRIPTOR_HEAP_DESC stSRVHeapDesc = {};
		stSRVHeapDesc.NumDescriptors = 1;
		stSRVHeapDesc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		stSRVHeapDesc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		THROW_IF_FAILED(
			m_pRenderer->GetPid3D12Device()->CreateDescriptorHeap(
				&stSRVHeapDesc, IID_PPV_ARGS(m_pSRVHeap.ReleaseAndGetAddressOf())));
		
		//......
		
		// 最终创建SRV描述符
		D3D12_SHADER_RESOURCE_VIEW_DESC stSRVDesc = {};
		stSRVDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		stSRVDesc.Format                  = stTextureDesc.Format;
		stSRVDesc.ViewDimension           = D3D12_SRV_DIMENSION_TEXTURE2D;
		stSRVDesc.Texture2D.MipLevels     = 1;
		m_pRenderer->GetPid3D12Device()->CreateShaderResourceView(
			m_pResource.Get(), &stSRVDesc, m_pSRVHeap->GetCPUDescriptorHandleForHeapStart());
		
		m_pRenderer->GetPCommandList()->Run();
		m_pRenderer->GetPCommandList()->Wait();
		m_pRenderer->GetPCommandList()->Reset();
		
		return true;
	}
	
	void WBitmapDirectX::OnUse() noexcept
	{
//		//向命令队列发出从上传堆复制纹理数据到默认堆的命令
//		CD3DX12_TEXTURE_COPY_LOCATION Dst(m_pResource.Get(), 0);
//		CD3DX12_TEXTURE_COPY_LOCATION Src(m_pUpload.Get(), m_stTxtLayouts);
//		m_pRenderer->GetPCommandList()->GetPID3D12CommandList()->CopyTextureRegion(&Dst, 0, 0, 0, &Src, nullptr);
//
//		//设置一个资源屏障，同步并确认复制操作完成
//		//直接使用结构体然后调用的形式
//		D3D12_RESOURCE_BARRIER stResBar = {};
//		stResBar.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
//		stResBar.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
//		stResBar.Transition.pResource   = m_pResource.Get();
//		stResBar.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
//		stResBar.Transition.StateAfter  = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
//		stResBar.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
//
//		m_pRenderer->GetPCommandList()->GetPID3D12CommandList()->ResourceBarrier(1, &stResBar);
//
//		m_pRenderer->GetPCommandList()->Run();
//		m_pRenderer->GetPCommandList()->Wait();
		// m_pRenderer->GetPCommandList()->Reset();
		
	}
	
	void WBitmapDirectX::OnResourceDestroy() noexcept
	{
		m_pResource       = nullptr;
		m_pUpload         = nullptr;
		m_stTextureFormat = {};
		m_stTxtLayouts    = {};
		m_width           = 0;
		m_height          = 0;
		m_BPP             = 0;
	}
} // Whale