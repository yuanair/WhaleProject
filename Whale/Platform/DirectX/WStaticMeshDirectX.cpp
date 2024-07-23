//
// Created by admin on 2024/7/16.
//

#include "WStaticMeshDirectX.hpp"
#include "Whale/Platform/WRenderer.hpp"
#include "WRendererDirectX.hpp"

namespace Whale::DirectX
{
	
	void WStaticMeshDirectX::Load()
	{
		auto &renderer = WRenderer::GetRenderer<WRendererDirectX>();
		
		auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(GetByteSize());
		THROW_IF_FAILED(
			renderer.pID3D12Device->CreateCommittedResource(
				&heapProperties,
				D3D12_HEAP_FLAG_NONE,
				&resourceDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&this->pID3D12VertexBuffer)));
		
		UINT8 *pVertexDataBegin = nullptr;
		CD3DX12_RANGE readRange(0, 0);
		THROW_IF_FAILED(this->pID3D12VertexBuffer->Map(0, &readRange, reinterpret_cast<void **>(&pVertexDataBegin)));
		memcpy(pVertexDataBegin, GetVertexes().GetPtr(), GetByteSize());
		this->pID3D12VertexBuffer->Unmap(0, nullptr);
		
		this->vertexBufferView.BufferLocation = this->pID3D12VertexBuffer->GetGPUVirtualAddress();
		this->vertexBufferView.StrideInBytes = sizeof(WStaticMesh::Vertex);
		this->vertexBufferView.SizeInBytes = (uint32) GetByteSize();
	}
	
	void WStaticMeshDirectX::OnRender()
	{
		auto &renderer = WRenderer::GetRenderer<WRendererDirectX>();
		for (auto &shader: this->GetPShaders())
		{
			shader.Lock()->Use();
			renderer.pID3D12CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			renderer.pID3D12CommandList->IASetVertexBuffers(0, 1, &this->vertexBufferView);
			renderer.pID3D12CommandList->DrawInstanced(
				this->vertexBufferView.SizeInBytes / this->vertexBufferView.StrideInBytes, 1, 0, 0
			);
		}
	}
} // Whale