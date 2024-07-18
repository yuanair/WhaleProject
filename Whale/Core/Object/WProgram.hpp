//
// Created by admin on 2024/7/5.
//

#pragma once

#include "WObject.hpp"
#include "Whale/Core/Tool/TFTimer.hpp"

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
		int32 RunA();
		
		///
		/// 运行
		/// \return 程序返回值
		int32 RunW();
	
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
	
	private:
		
		void BeginPlay();
		
		void Tick();
		
		void EndPlay();
	
	public:
		
		[[nodiscard]]
		inline const TFTimer<std::chrono::system_clock> &GetTimer() const { return this->timer; }
		
		inline TFTimer<std::chrono::system_clock> &GetTimer() { return this->timer; }
	
	public:
		
		static const Char *GetAppNameA();
		
		static const WChar *GetAppNameW();
		
		static const Char *GetVersionA();
		
		static const WChar *GetVersionW();
		
		static const Char *GetBuildDataA();
		
		static const WChar *GetBuildDataW();
	
	private:
		
		TFTimer<std::chrono::system_clock> timer;
		
	};
	
} // Whale
