//
// Created by admin on 2024/7/22.
//

#pragma once

#include "TypeDef.hpp"

namespace Whale
{
	
	///
	/// 好坏接口
	class IGoodAndBad
	{
	public:
		
		///
		/// \return 坏的
		virtual Bool operator!() const noexcept { return Bad(); }
		
		///
		/// \return 好的
		virtual explicit operator Bool() const noexcept { return Good(); }
	
	public:
		
		///
		/// \return 好的
		[[nodiscard]] virtual Bool Good() const noexcept = 0;
		
		///
		/// \return 坏的
		[[nodiscard]] virtual Bool Bad() const noexcept = 0;
		
	};
	
} // Whale
