//
// Created by admin on 2024/7/11.
//

#include "WShader.hpp"


namespace Whale
{
	
	template<>
	void ToString(StringA &target, EShaderType arg) noexcept
	{
		switch (arg)
		{
			case EShaderTypeVertex:
				target = "vertex";
				break;
			case EShaderTypePixel: // case EShaderTypeFragment:
				target = "pixel";
				break;
			case EShaderTypeUnknown:
			default:
				target = "unknown";
				break;
		}
	}
	
	template<>
	void ToString(StringW &target, EShaderType arg) noexcept
	{
		switch (arg)
		{
			case EShaderTypeVertex:
				target = L"vertex";
				break;
			case EShaderTypePixel: // case EShaderTypeFragment:
				target = L"pixel";
				break;
			case EShaderTypeUnknown:
			default:
				target = L"unknown";
				break;
		}
	}
	
} // Whale