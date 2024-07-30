//
// Created by admin on 2024/7/16.
//

#include "WStaticMeshDirectX.hpp"
#include "WRendererDirectX.hpp"
#include "WCommandListDirectX.hpp"

namespace Whale::DirectX
{
	
	void WStaticMeshDirectX::OnRender()
	{
		for (auto &shader: this->GetPMaterials())
		{
			auto locked = shader.Lock();
			if (!locked || !locked->IsEnabled()) continue;
			locked->Use();
			for (auto &pRenderingPipeline: locked->GetPRenderingPipelines())
			{
				auto rp = pRenderingPipeline.Lock();
				if (!rp || !rp->IsEnabled()) continue;
				rp->Use();
				m_pRenderer->GetPCommandList()->GetPID3D12CommandList()->IASetPrimitiveTopology(
					D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST
				);
				m_pRenderer->GetPCommandList()->GetPID3D12CommandList()->IASetVertexBuffers(
					0, 1, &this->m_vertexBufferView
				);
				m_pRenderer->GetPCommandList()->GetPID3D12CommandList()->DrawInstanced(
					GetVertexes().GetLength(), 1, 0, 0
				);
			}
		}
	}
	
	Bool WStaticMeshDirectX::Create(const Whale::StaticMeshArg &arg) noexcept
	{
		if (m_pRenderer == nullptr || !m_pRenderer->IsGPUResourceCreated())
		{
			FDebug::LogError(TagA, "m_pRenderer isn't create");
			return false;
		}
		
		auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		auto resourceDesc   = CD3DX12_RESOURCE_DESC::Buffer(GetByteSize());
		THROW_IF_FAILED(
			m_pRenderer->GetPid3D12Device()->CreateCommittedResource(
				&heapProperties,
				D3D12_HEAP_FLAG_NONE,
				&resourceDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(this->m_pID3D12VertexBuffer.ReleaseAndGetAddressOf())));
		
		void *pVertexDataBegin = nullptr;
		
		CD3DX12_RANGE readRange(0, 0);
		THROW_IF_FAILED(this->m_pID3D12VertexBuffer->Map(0, &readRange, reinterpret_cast<void **>(&pVertexDataBegin)));
		memcpy(pVertexDataBegin, GetVertexes().GetPtr(), GetByteSize());
		this->m_pID3D12VertexBuffer->Unmap(0, nullptr);
		
		this->m_vertexBufferView.BufferLocation = this->m_pID3D12VertexBuffer->GetGPUVirtualAddress();
		this->m_vertexBufferView.StrideInBytes  = sizeof(WStaticMesh::Vertex);
		this->m_vertexBufferView.SizeInBytes    = (uint32) GetByteSize();
		return true;
	}
	
	Bool WStaticMeshDirectX::IsGPUResourceCreated() const noexcept
	{
		return m_pID3D12VertexBuffer;
	}
	
	void WStaticMeshDirectX::OnEnable() noexcept
	{
	
	}
	
	void WStaticMeshDirectX::OnDisable() noexcept
	{
	
	}
	
	void WStaticMeshDirectX::OnResourceDestroy() noexcept
	{
		m_pID3D12VertexBuffer.Reset();
		m_vertexBufferView = {};
	}
} // Whale