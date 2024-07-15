//
// Created by admin on 2024/7/11.
//

#pragma once

#include "Whale/Core/WObject.hpp"
#include "WRenderer.hpp"

namespace Whale
{
	///
	/// 着色器
	class WHALE_API WShader : public WObject
	{
	public:
		
		///
		/// \param fileName 文件名
		/// \returns 是否成功
		virtual bool CreateFromFile(const std::wstring &fileName) = 0;
		
		///
		/// 使用着色器
		virtual void Use() = 0;
		
	};
	
	///
	/// DirectX12着色器(HLSL)
	class WHALE_API WShaderDirectX12 : public WShader
	{
	public:
		
		WShaderDirectX12();
	
	public:
		
		bool CreateFromFile(const std::wstring &fileName) override;
		
		void Use() override;
	
	public:
		
		[[nodiscard]]
		inline const FUndefinedData<class WShaderDirectX12Data> &GetData() const { return data; }
	
	private:
		
		FUndefinedData<class WShaderDirectX12Data> data;
		
	};
	
} // Whale
