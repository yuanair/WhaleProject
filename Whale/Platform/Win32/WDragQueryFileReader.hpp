//
// Created by admin on 2024/7/31.
//

#pragma once

#include "Whale/Core/Stream.hpp"
#include "Whale/Core/Container/TFString.hpp"
#include "HWinDef.hpp"

namespace Whale::Win32
{
	
	/// 拖放文件读取
	class WHALE_API WDragQueryFileReader
	{
	public:
		
		WDragQueryFileReader() : m_fileCount(0) {}
	
	public:
		
		
		/// 初始化
		/// \param hDrop
		/// \return 是否成功
		template<class ElemT>
		void Init(HDrop hDrop) noexcept
		{
			static_assert("unimplemented");
		}
		
		/// 销毁HDrop
		void Destroy() noexcept;
		
		/// 获取文件名
		/// \param fileName 文件名
		/// \param index 索引
		/// \return 是否成功
		template<class ElemT>
		Bool Get(Container::TFString<ElemT> &fileName, uint32 index) noexcept
		{
			static_assert("unimplemented");
		}
	
	public:
		
		///
		[[nodiscard]] const HDrop &GetHDrop() const noexcept { return m_hDrop; }
		
		/// \return 文件数量
		[[nodiscard]] uint32 GetFileCount() const noexcept { return this->m_fileCount; }
	
	private:
		
		HDrop m_hDrop;
		
		uint32 m_fileCount;
		
	};
	
	template<>
	void WHALE_API WDragQueryFileReader::Init<CharA>(HDrop hDrop) noexcept;
	
	template<>
	void WHALE_API WDragQueryFileReader::Init<CharW>(HDrop hDrop) noexcept;
	
	template<>
	Bool WHALE_API WDragQueryFileReader::Get(StringA &fileName, uint32 index) noexcept;
	
	template<>
	Bool WHALE_API WDragQueryFileReader::Get(StringW &fileName, uint32 index) noexcept;
	
} // Whale
