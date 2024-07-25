//
// Created by admin on 2024/7/16.
//

#pragma once

#include "Whale/Platform/WShader.hpp"
#include "HDirectXHeader.hpp"
#include "WRendererDirectX.hpp"

namespace Whale::DirectX
{
	
	///
	/// DirectX着色器(HLSL)
	class WHALE_API WShaderDirectX : public WShader
	{
	public:
		
		explicit WShaderDirectX(WRendererDirectX *pRenderer) : m_pRenderer(pRenderer) {}
	
	public:
		
		static Bool GetTarget(StringA &target, EShaderType type)
		{
			switch (type)
			{
				case EShaderTypeVertex:
					target = "vs_5_0";
					return true;
				case EShaderTypePixel:
					target = "ps_5_0";
					return true;
				case EShaderTypeUnknown:
				default:
					target = "unknown";
					return false;
			}
		}
	
	public:
		
		[[nodiscard]] Bool IsGPUResourceCreated() const noexcept override;
	
	private:
		
		Bool OnGPUCreate(const FShaderArg &arg) noexcept override;
		
		void OnGPUDestroy() noexcept override;
		
		void OnEnable() noexcept override;
		
		void OnDisable() noexcept override;
	
	public:
		
		[[nodiscard]] const Microsoft::WRL::ComPtr<ID3DBlob> &GetPShader() const noexcept { return m_pShader; }
	
	private:
		
		WRendererDirectX *m_pRenderer;
		
		Microsoft::WRL::ComPtr<ID3DBlob> m_pShader;
		
	};
	
} // Whale
