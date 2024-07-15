//
// Created by admin on 2024/7/9.
//

#pragma once

#include "Whale/Core/FUndefinedData.hpp"
#include "Whale/DirectX/FDirectXHeader.hpp"

namespace Whale
{
	class WStaticMeshDirectX12Data : public WObject
	{
	public:
		
		Microsoft::WRL::ComPtr<ID3D12Resource> pID3D12VertexBuffer;
		
		D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
		
	};
}