//
// Created by admin on 2024/7/16.
//

#include "WStaticMeshDirectX.hpp"
#include "WRendererDirectX.hpp"

namespace Whale::DirectX
{
	
	void WStaticMeshDirectX::OnRender()
	{
		for (auto &shader: this->GetPMaterials())
		{
			auto locked = shader.Lock();
			if (!locked || !locked->IsEnabled()) continue;
			locked->Use();
			m_pRenderer->pID3D12CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			m_pRenderer->pID3D12CommandList->IASetVertexBuffers(0, 1, &this->vertexBufferView);
			m_pRenderer->pID3D12CommandList->DrawInstanced(
				GetVertexes().GetLength(), 1, 0, 0
			);
		}
	}
	
	void WStaticMeshDirectX::OnGPUCreate() noexcept
	{
		if (m_pRenderer == nullptr || !m_pRenderer->IsGPUResourceCreated())
		{
			FDebug::LogError(TagA, "m_pRenderer isn't create");
			return;
		}
		
		auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		auto resourceDesc   = CD3DX12_RESOURCE_DESC::Buffer(GetByteSize());
		THROW_IF_FAILED(
			m_pRenderer->pID3D12Device->CreateCommittedResource(
				&heapProperties,
				D3D12_HEAP_FLAG_NONE,
				&resourceDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(this->pID3D12VertexBuffer.ReleaseAndGetAddressOf())));
		
		UINT8         *pVertexDataBegin = nullptr;
		CD3DX12_RANGE readRange(0, 0);
		THROW_IF_FAILED(this->pID3D12VertexBuffer->Map(0, &readRange, reinterpret_cast<void **>(&pVertexDataBegin)));
		memcpy(pVertexDataBegin, GetVertexes().GetPtr(), GetByteSize());
		this->pID3D12VertexBuffer->Unmap(0, nullptr);
		
		this->vertexBufferView.BufferLocation = this->pID3D12VertexBuffer->GetGPUVirtualAddress();
		this->vertexBufferView.StrideInBytes  = sizeof(WStaticMesh::Vertex);
		this->vertexBufferView.SizeInBytes    = (uint32) GetByteSize();
	}
	
	void WStaticMeshDirectX::OnGPUDestroy() noexcept
	{
		pID3D12VertexBuffer = nullptr;
		vertexBufferView    = {};
	}
	
	Bool WStaticMeshDirectX::IsGPUResourceCreated() const noexcept
	{
		return pID3D12VertexBuffer;
	}
	
	void WStaticMeshDirectX::OnEnable() noexcept
	{
	
	}
	
	void WStaticMeshDirectX::OnDisable() noexcept
	{
	
	}
} // Whale