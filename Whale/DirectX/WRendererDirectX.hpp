//
// Created by admin on 2024/7/13.
//

#pragma once

#include "Whale/Render/WRenderer.hpp"
#include "Whale/Core/FUndefinedData.hpp"

namespace Whale
{
	
	///
	/// DirectX渲染器
	class WHALE_API WRendererDirectX : public WRenderer
	{
	public:
		
		WRendererDirectX();
	
	public:
		
		inline static std::string GetStaticNameA() { return "DirectX"; }
		
		inline static std::wstring GetStaticNameW() { return L"DirectX"; }
	
	public:
		
		void Create() override;
		
		void Render() override;
	
	public:
		
		[[nodiscard]]
		inline const FUndefinedData<class WDirectX12Data> &GetData() const { return data; }
	
	private:
		
		// 开启DirectX调试层
		void EnableDebugLayer() const;
	
	public:
		
		[[nodiscard]]
		inline std::string GetNameA() const override { return GetStaticNameA(); }
		
		[[nodiscard]]
		inline std::wstring GetNameW() const override { return GetStaticNameW(); }
	
	private:
		
		FUndefinedData<class WDirectX12Data> data;
	};
	
} // Whale
