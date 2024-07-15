//
// Created by admin on 2024/7/5.
//

#pragma once

#include "WObject.hpp"
#include "TTimer.hpp"

namespace Whale
{
	
	///
	/// 程序
	///
	class WHALE_API WProgram : public WObject
	{
	public:
		
		///
		/// 运行
		/// \return 程序返回值
		int32 Run();
	
	protected:
		
		///
		/// 开始
		virtual void OnBeginPlay();
		
		///
		/// 每帧
		/// \param deltaTime 帧间隔时间（秒）
		virtual void OnTick(Float deltaTime);
		
		///
		/// 结束
		virtual void OnEndPlay();
	
	public:
		
		[[nodiscard]]
		inline const TTimer<std::chrono::system_clock> &GetTimer() const { return this->timer; }
		
		inline TTimer<std::chrono::system_clock> &GetTimer() { return this->timer; }
	
	public:
		
		static const Char AppNameA[];
		
		static const WChar AppNameW[];
		
		static const Char VersionA[];
		
		static const WChar VersionW[];
		
		static const Char BuildDataA[];
		
		static const WChar BuildDataW[];
	
	private:
		
		TTimer<std::chrono::system_clock> timer;
		
	};
	
} // Whale
