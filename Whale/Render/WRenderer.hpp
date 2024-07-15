//
// Created by admin on 2024/7/9.
//

#pragma once

#include "Whale/Core/WObject.hpp"
#include "WRenderTarget.hpp"

#include "Whale/Core/FDebug.hpp"

namespace Whale
{
	
	///
	/// 渲染器
	class WHALE_API WRenderer : public WObject
	{
	public:
		
		///
		/// 渲染器类型
		enum Type
		{
			None = 0,
			DirectX,
			OpenGL
		};
	
	public:
		
		WRenderer();
		
		~WRenderer() override;
	
	public:
		
		///
		/// 创建渲染器
		/// \param type 类型
		static WRenderer *NewRenderer(Type type);
		
		///
		/// \param type
		/// \return
		static std::string ToStringA(Type type);
		
		///
		/// \param type
		/// \return
		static std::wstring ToStringW(Type type);
		
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
				(
					L"The renderer should be " + T::GetStaticNameW() + L", but it is " +
					WRenderer::GetPRenderer()->GetNameW()
				).c_str()
			);
			throw;
		}
	
	public:
		
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
		/// 渲染
		virtual void Render() = 0;
	
	public:
		
		std::vector<std::weak_ptr<WRenderTarget>> renderTargets;
	
	private:
		
		static WRenderer *pRenderer;
		
	};
	
	
} // Whale
