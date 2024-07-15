//
// Created by admin on 2024/7/12.
//

#pragma once

#include "Whale/Core/WObject.hpp"
#include "Whale/Core/FUndefinedData.hpp"


namespace Whale
{
	///
	/// 位图
	class WBitmap : public WObject
	{
	public:
		
		///
		/// 从文件加载
		/// \param fileName 文件名
		virtual void LoadFromFile(const std::wstring &fileName) = 0;
		
	};
	
	///
	/// 位图
	class WBitmapDirectX12 : public WBitmap
	{
	public:
		
		void LoadFromFile(const std::wstring &fileName) override;
	
	public:
		
		[[nodiscard]]
		const FUndefinedData<class WBitmapDirectX12Data> &GetData() const { return data; }
	
	private:
		
		FUndefinedData<class WBitmapDirectX12Data> data;
		
	};
	
} // Whale
