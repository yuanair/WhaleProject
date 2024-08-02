//
// Created by admin on 2024/7/31.
//

#pragma once

#include <Whale/Stream.hpp>
#include <Whale/Container/TFString.hpp>
#include "HWinDef.hpp"

namespace Whale::Windows
{
	
	/// 拖放文件读取
	class WHALE_API WDragQueryFileReader
	{
	public:
		
		constexpr WDragQueryFileReader() noexcept: m_fileCount(0) {}
		
		inline ~WDragQueryFileReader() noexcept { Destroy(); }
	
	public:
		
		
		/// 初始化
		/// \param hDrop
		/// \return 是否成功
		template<class ElemT>
		void Init(HDrop hDrop) noexcept;
		
		/// 销毁HDrop
		void Destroy() noexcept;
		
		/// 获取文件名
		/// \param fileName 文件名
		/// \param index 索引
		/// \return 是否成功
		template<class ElemT>
		Bool Get(Container::TFString<ElemT> &fileName, uint32 index) noexcept;
	
	public:
		
		///
		[[nodiscard]] const HDrop &GetHDrop() const noexcept { return m_hDrop; }
		
		/// \return 文件数量
		[[nodiscard]] uint32 GetFileCount() const noexcept { return this->m_fileCount; }
	
	private:
		
		HDrop m_hDrop;
		
		uint32 m_fileCount;
		
	};
	
} // Whale
