//
// Created by admin on 2024/7/25.
//

#pragma once

#include "Whale/Core/TypeDef.hpp"
#include "Whale/Tool/IEnable.hpp"

namespace Whale
{
	
	///
	/// GPU资源
	template<class CreateArg, class Result = void>
	class WHALE_API TIGPUResource : public Tool::IEnable
	{
	public:
		
		/// 创建GPU资源
		Result GPUCreate(CreateArg &arg) noexcept { return OnGPUCreate(arg); }
		
		/// 释放GPU资源
		void GPUDestroy() noexcept { OnGPUDestroy(); }
		
		/// 启用并创建GPU资源
		Result GPUCreateAndEnable(CreateArg &arg) noexcept
		{
			Enable();
			return OnGPUCreate(arg);
		}
		
		/// 释放GPU资源并禁用
		void GPUDisableAndDisable() noexcept
		{
			OnGPUDestroy();
			Disable();
		}
		
		/// GPU资源是否已创建
		[[nodiscard]] virtual Bool IsGPUResourceCreated() const noexcept = 0;
	
	private:
		
		virtual Result OnGPUCreate(CreateArg &arg) noexcept = 0;
		
		virtual void OnGPUDestroy() noexcept = 0;
	
	public:
		
		[[nodiscard]] Bool IsEnabled() const noexcept override
		{
			return Tool::IEnable::IsEnabled() && IsGPUResourceCreated();
		}
		
	};
	
	template<>
	class WHALE_API TIGPUResource<void, void> : public Tool::IEnable
	{
	public:
		
		/// 创建GPU资源
		void GPUCreate() noexcept { return OnGPUCreate(); }
		
		/// 释放GPU资源
		void GPUDestroy() noexcept { OnGPUDestroy(); }
		
		/// 启用并创建GPU资源
		void GPUCreateAndEnable() noexcept
		{
			Enable();
			return OnGPUCreate();
		}
		
		/// 释放GPU资源并禁用
		void GPUDisableAndDisable() noexcept
		{
			OnGPUDestroy();
			Disable();
		}
		
		/// GPU资源是否已创建
		[[nodiscard]] virtual Bool IsGPUResourceCreated() const noexcept = 0;
	
	private:
		
		virtual void OnGPUCreate() noexcept = 0;
		
		virtual void OnGPUDestroy() noexcept = 0;
	
	public:
		
		[[nodiscard]] Bool IsEnabled() const noexcept override
		{
			return Tool::IEnable::IsEnabled() && IsGPUResourceCreated();
		}
		
	};
	
} // Whale
