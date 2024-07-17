//
// Created by admin on 2024/7/9.
//

#pragma once

#include "Whale/Core/Object/WObject.hpp"
#include "Whale/Core/Object/WProgram.hpp"
#include "Whale/Core/Debug/FDebug.hpp"
#include "Whale/Core/Container/FMemory.hpp"
#include "WRenderTarget.hpp"
#include "WShader.hpp"
#include "WStaticMesh.hpp"

namespace Whale
{
	
	///
	/// 渲染器类型
	enum ERendererType
	{
		ERendererTypeNone = 0,
		ERendererTypeDirectX,
		ERendererTypeOpenGL
	};
	
	///
	/// 渲染器
	class WHALE_API WRenderer : public WObject
	{
	public:
		
		WRenderer();
		
		~WRenderer() override;
	
	public:
		
		///
		/// 创建渲染器
		/// \param type 类型
		static FTUniquePtr<WRenderer> CreateRenderer(ERendererType type);
		
		///
		/// \param type
		/// \return
		static FTStringA ToStringA(ERendererType type);
		
		///
		/// \param type
		/// \return
		static FTStringW ToStringW(ERendererType type);
		
		///
		/// 获取渲染器
		/// \tparam T
		/// \return
		template<class T = WRenderer>
		inline static T *GetPRenderer()
		{
			return dynamic_cast<T *>(pRenderer);
		}
		
		///
		/// 获取渲染器
		/// \tparam T
		/// \return
		template<class T = WRenderer>
		inline static T &GetRenderer()
		{
			if (auto ptr = GetPRenderer<T>()) return *ptr;
			FDebug::Fatal(
				WProgram::GetAppNameW(),
				(
					L"The renderer should be " + T::GetStaticNameW() + L", but it is " +
					WRenderer::GetPRenderer()->GetNameW()
				).c_str()
			);
			throw;
		}
	
	public:
		
		///
		/// \return 类型
		[[nodiscard]]
		virtual ERendererType GetType() const = 0;
		
		///
		/// \return 名称
		[[nodiscard]]
		virtual std::string GetNameA() const = 0;
		
		///
		/// \return 名称
		[[nodiscard]]
		virtual std::wstring GetNameW() const = 0;
		
		///
		/// 创建渲染器
		virtual void Create() = 0;
		
		///
		/// 创建窗口渲染目标
		virtual FTUniquePtr<WWindowRenderTarget> CreateWindowRenderTarget() = 0;
		
		///
		/// 创建着色器
		virtual FTUniquePtr<WShader> CreateShader() = 0;
		
		///
		/// 创建网格体
		virtual FTUniquePtr<WStaticMesh> CreateStaticMesh() = 0;
		
		///
		/// 渲染
		virtual void Render() = 0;
	
	public:
		
		std::vector<FTWeakPtr<WRenderTarget>> renderTargets;
	
	private:
		
		static WRenderer *pRenderer;
		
	};
	
	
} // Whale
