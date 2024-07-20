//
// Created by admin on 2024/7/16.
//

#pragma once

#include "Whale/Platform/WStaticMesh.hpp"
#include "HDirectXHeader.hpp"

namespace Whale::DirectX
{
	
	///
	/// DirectX12静态网格体
	class WHALE_API WStaticMeshDirectX : public WStaticMesh
	{
	public:
		
		void Load() override;
	
	protected:
		
		void OnRender() override;
	
	private:
		
		Microsoft::WRL::ComPtr<ID3D12Resource> pID3D12VertexBuffer;
		
		D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
		
	};
	
} // Whale
