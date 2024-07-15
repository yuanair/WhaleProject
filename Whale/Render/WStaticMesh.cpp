//
// Created by admin on 2024/7/11.
//

#include "WStaticMesh.hpp"
#include "Whale/DirectX/WStaticMeshDirectX12Data.hpp"
#include "Whale/DirectX/WDirectX12Data.hpp"
#include "WRenderer.hpp"
#include "Whale/DirectX/WRendererDirectX.hpp"

namespace Whale
{
	
	void WStaticMesh::SetVertexes(const std::vector<Vertex> &vertexesArg)
	{
		WStaticMesh::vertexes = vertexesArg;
	}
	
	SizeT WStaticMesh::GetByteSize() const
	{
		return sizeof(Vertex) * this->vertexes.size();
	}
	
	WStaticMeshDirectX12::WStaticMeshDirectX12()
	{
		this->data.New();
	}
	
	void WStaticMeshDirectX12::Load()
	{
		auto &renderer = WRenderer::GetRenderer<WRendererDirectX>();
		
		auto heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
		auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(GetByteSize());
		THROW_IF_FAILED(
			renderer.GetData()->pID3D12Device->CreateCommittedResource(
				&heapProperties,
				D3D12_HEAP_FLAG_NONE,
				&resourceDesc,
				D3D12_RESOURCE_STATE_GENERIC_READ,
				nullptr,
				IID_PPV_ARGS(&data->pID3D12VertexBuffer)));
		
		UINT8 *pVertexDataBegin = nullptr;
		CD3DX12_RANGE readRange(0, 0);
		THROW_IF_FAILED(data->pID3D12VertexBuffer->Map(0, &readRange, reinterpret_cast<void **>(&pVertexDataBegin)));
		memcpy(pVertexDataBegin, GetVertexes().data(), GetByteSize());
		data->pID3D12VertexBuffer->Unmap(0, nullptr);
		
		data->vertexBufferView.BufferLocation = data->pID3D12VertexBuffer->GetGPUVirtualAddress();
		data->vertexBufferView.StrideInBytes = sizeof(WStaticMesh::Vertex);
		data->vertexBufferView.SizeInBytes = (uint32) GetByteSize();
	}
	
	void WStaticMeshDirectX12::OnRender()
	{
		auto &renderer = WRenderer::GetRenderer<WRendererDirectX>();
		for (auto &shader: this->GetPShaders())
		{
			shader.lock()->Use();
			renderer.GetData()->pID3D12CommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			renderer.GetData()->pID3D12CommandList->IASetVertexBuffers(0, 1, &data->vertexBufferView);
			renderer.GetData()->pID3D12CommandList->DrawInstanced(
				data->vertexBufferView.SizeInBytes / data->vertexBufferView.StrideInBytes, 1, 0, 0
			);
		}
	}
} // Whale