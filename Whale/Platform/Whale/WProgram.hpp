//
// Created by admin on 2024/7/5.
//

#pragma once

#include <Whale/WObject.hpp>
#include <Whale/Container/TFString.hpp>

#include "WGenericTimer.hpp"

namespace Whale
{
	
	///
	/// 程序
	///
	class WHALE_API WProgram : public WObject
	{
	public:
		
		explicit WProgram(WGenericTimer *pTimer);
		
		~WProgram() override;
	
	public:
		
		void BeginPlay();
		
		void Tick();
		
		void EndPlay();
	
	protected:
		
		///
		/// 开始
		virtual void OnBeginPlay();
		
		///
		/// 每帧
		/// \param deltaTime 帧间隔时间（秒）
		virtual void OnTick(Double deltaTime);
		
		///
		/// 结束
		virtual void OnEndPlay();
	
	public:
		
		[[nodiscard]]
		inline WGenericTimer *const &GetTimer() const { return this->pTimer; }
		
		inline WGenericTimer *&GetTimer() { return this->pTimer; }
	
	private:
		
		WGenericTimer *pTimer;
		
	};
	
} // Whale
