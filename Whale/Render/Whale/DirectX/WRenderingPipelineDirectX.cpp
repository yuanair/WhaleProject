//
// Created by admin on 2024/7/25.
//

#include "WRenderingPipelineDirectX.hpp"
#include "WShaderDirectX.hpp"
#include "WCommandListDirectX.hpp"

namespace Whale
{
	Bool DirectX::WRenderingPipelineDirectX::IsGPUResourceCreated() const noexcept
	{
		return m_pID3D12PipelineState;
	}
	
	Bool DirectX::WRenderingPipelineDirectX::CreateFromShader(const WRenderingPipelineArg &arg) noexcept
	{
		if (m_pRenderer == nullptr || !m_pRenderer->IsGPUResourceCreated())
		{
			FDebug::Log<CharA>(Error, TagA, "m_pRenderer isn't create");
			return false;
		}
		TFSharedPtr<WShaderDirectX> pVertexShader = DynamicPointerCast<WShaderDirectX>(arg.m_pVertexShader.Lock());
		TFSharedPtr<WShaderDirectX> pPixelShader  = DynamicPointerCast<WShaderDirectX>(arg.m_pPixelShader.Lock());
		if (!pVertexShader)
		{
			FDebug::Log<CharA>(Error, TagA, "pVertexShader isn't cast to WShaderDirectX");
		}
		if (!pPixelShader)
		{
			FDebug::Log<CharA>(Error, TagA, "pPixelShader isn't cast to WShaderDirectX");
		}
		if (!(pVertexShader && pPixelShader)) return false;
		
		D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
			                         {
				                         {
					                         "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT,
					                         D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
				                         },
				                         {
					                         "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT,
					                         D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
				                         },
				                         {
					                         "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D12_APPEND_ALIGNED_ELEMENT,
					                         D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
				                         },
				                         {
					                         "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D12_APPEND_ALIGNED_ELEMENT,
					                         D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
				                         }
			                         };
		
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
		
		psoDesc.InputLayout                     = {inputElementDescs, _countof(inputElementDescs)};
		psoDesc.pRootSignature                  = m_pRenderer->GetPid3D12RootSignature().Get();
		psoDesc.VS                              = CD3DX12_SHADER_BYTECODE(pVertexShader->GetPShader().Get());
		psoDesc.PS                              = CD3DX12_SHADER_BYTECODE(pPixelShader->GetPShader().Get());
		psoDesc.RasterizerState                 = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.BlendState                      = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState.DepthEnable   = FALSE;
		psoDesc.DepthStencilState.StencilEnable = FALSE;
		psoDesc.SampleMask                      = UINT_MAX;
		psoDesc.PrimitiveTopologyType           = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		psoDesc.NumRenderTargets                = 1;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		psoDesc.SampleDesc.Count = 1;
		
		THROW_IF_FAILED(
			m_pRenderer->GetPid3D12Device()->CreateGraphicsPipelineState(
				&psoDesc, IID_PPV_ARGS(this->m_pID3D12PipelineState.ReleaseAndGetAddressOf()))
		);
		return true;
	}
	
	void DirectX::WRenderingPipelineDirectX::OnUse() noexcept
	{
		m_pRenderer->GetPCommandList()->GetPID3D12CommandList()->SetPipelineState(this->m_pID3D12PipelineState.Get());
	}
	
	void DirectX::WRenderingPipelineDirectX::OnEnable() noexcept
	{
	
	}
	
	void DirectX::WRenderingPipelineDirectX::OnDisable() noexcept
	{
	
	}
	
	void DirectX::WRenderingPipelineDirectX::OnResourceDestroy() noexcept
	{
		m_pID3D12PipelineState.Reset();
	}
} // Whale