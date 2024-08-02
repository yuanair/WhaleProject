//
// Created by admin on 2024/7/5.
//

#pragma once

#include <Whale/WObject.hpp>
#include <Whale/TFTimer.hpp>
#include <Whale/Container/TFString.hpp>

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
	
	private:
		
		void BeginPlay();
		
		void Tick();
		
		void EndPlay();
	
	public:
		
		[[nodiscard]]
		inline const TFTimer<std::chrono::system_clock> &GetTimer() const { return this->timer; }
		
		inline TFTimer<std::chrono::system_clock> &GetTimer() { return this->timer; }
	
	private:
		
		TFTimer<std::chrono::system_clock> timer;
		
	};
	
} // Whale
