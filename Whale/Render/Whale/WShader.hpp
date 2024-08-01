//
// Created by admin on 2024/7/11.
//

#pragma once

#include <Whale/WObject.hpp>
#include <Whale/Container/TFString.hpp>
#include "TIGPUResource.hpp"

namespace Whale
{
	
	///
	/// 着色器类型
	enum EShaderType
	{
		EShaderTypeUnknown  = 0,
		EShaderTypeVertex   = 1,
		EShaderTypePixel    = 2,
		EShaderTypeFragment = EShaderTypePixel
	};
	
	///
	/// 着色器参数
	struct WHALE_API FShaderArg
	{
		/// 着色器文件名
		StringW     m_fileName;
		/// 着色器类型
		EShaderType m_type     = EShaderTypeUnknown;
		/// 入口点
		StringA     entryPoint = "main";
	};
	
	
	template<>
	void WHALE_API ToString(StringA &target, EShaderType arg) noexcept;
	
	template<>
	void WHALE_API ToString(StringW &target, EShaderType arg) noexcept;
	
	///
	/// 着色器
	class WHALE_API WShader : public WObject, public TIGPUResource
	{
	public:
		
		virtual Bool CreateFromFile(const FShaderArg &arg) noexcept = 0;
		
	};
	
	
} // Whale
