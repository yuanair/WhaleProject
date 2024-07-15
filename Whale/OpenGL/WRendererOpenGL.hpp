//
// Created by admin on 2024/7/13.
//

#pragma once

#include "Whale/Render/WRenderer.hpp"

namespace Whale
{
	
	///
	/// OpenGL渲染器
	class WHALE_API WRendererOpenGL : public WRenderer
	{
	public:
		
		inline static std::string GetStaticNameA() { return "OpenGL"; }
		
		inline static std::wstring GetStaticNameW() { return L"OpenGL"; }
	
	public: // override
		
		void Create() override;
		
		void Render() override;
	
	public:
		
		[[nodiscard]]
		inline std::string GetNameA() const override { return GetStaticNameA(); }
		
		[[nodiscard]]
		inline std::wstring GetNameW() const override { return GetStaticNameW(); }
		
	};
	
} // Whale
