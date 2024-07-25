//
// Created by admin on 2024/7/16.
//

#pragma once

#include "Whale/Platform/WStaticMesh.hpp"
#include "HDirectXHeader.hpp"
#include "WRendererDirectX.hpp"

namespace Whale::DirectX
{
	
	///
	/// DirectX12静态网格体
	class WHALE_API WStaticMeshDirectX : public WStaticMesh
	{
	public:
		
		explicit WStaticMeshDirectX(WRendererDirectX *pRenderer) : m_pRenderer(pRenderer) {}
	
	private:
		
		void OnRender() override;
	
	public:
		
		void OnGPUCreate() noexcept override;
		
		void OnGPUDestroy() noexcept override;
		
		[[nodiscard]] Bool IsGPUResourceCreated() const noexcept override;
	
	private:
		
		void OnEnable() noexcept override;
		
		void OnDisable() noexcept override;
	
	private:
		
		WRendererDirectX *m_pRenderer;
		
		Microsoft::WRL::ComPtr<ID3D12Resource> pID3D12VertexBuffer;
		
		D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
		
	};
	
} // Whale
