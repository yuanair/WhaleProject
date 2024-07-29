//
// Created by admin on 2024/7/9.
//

#pragma once

#include "Whale/Core/WObject.hpp"
#include "WProgram.hpp"
#include "Whale/Core/FDebug.hpp"
#include "Whale/Core/Memory.hpp"
#include "TIGPUResource.hpp"

namespace Whale
{
	class WRenderTarget;
	
	class WWindowRenderTarget;
	
	class WShader;
	
	class WRenderingPipeline;
	
	class WMaterial;
	
	class WStaticMesh;
	
	class WImage;
	
	class WBitmap;
	
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
	class WHALE_API WRenderer : public WObject, public TIGPUResource<void>
	{
	public:
		
		WRenderer() = default;
		
		WRenderer(const WRenderer &) = delete;
		
		~WRenderer() override = default;
	
	public:
		
		WRenderer &operator=(const WRenderer &) = delete;
	
	public:
		
		///
		/// 创建渲染器
		/// \param type 类型
		static TFUniquePtr<WRenderer> CreateRenderer(ERendererType type);
		
		///
		/// \param type
		/// \return
		static StringA ToStringA(ERendererType type);
		
		///
		/// \param type
		/// \return
		static StringW ToStringW(ERendererType type);
	
	public:
		
		///
		/// \return 类型
		[[nodiscard]]
		virtual ERendererType GetType() const = 0;
		
		///
		/// 创建窗口渲染目标
		TFWeakPtr<WWindowRenderTarget> MakeWindowRenderTarget();
		
		///
		/// 创建着色器
		TFWeakPtr<WShader> MakeShader();
		
		///
		/// 创建渲染管线
		TFWeakPtr<WRenderingPipeline> MakeRenderingPipeline();
		
		///
		/// 创建材质
		TFWeakPtr<WMaterial> MakeMaterial();
		
		///
		/// 创建网格体
		TFWeakPtr<WStaticMesh> MakeStaticMesh();
		
		///
		/// 创建图片
		TFWeakPtr<WBitmap> MakeBitmap();
		
		///
		/// 渲染
		void Render() { if (this->IsEnabled()) OnRender(); }
	
	private:
		
		virtual void OnRender() = 0;
		
		virtual TFUniquePtr<WWindowRenderTarget> OnMakeWindowRenderTarget() = 0;
		
		virtual TFUniquePtr<WShader> OnMakeShader() = 0;
		
		virtual TFUniquePtr<WRenderingPipeline> OnMakeRenderingPipeline() = 0;
		
		virtual TFUniquePtr<WMaterial> OnMakeMaterial() = 0;
		
		virtual TFUniquePtr<WStaticMesh> OnMakeStaticMesh() = 0;
		
		virtual TFUniquePtr<WBitmap> OnMakeBitmap() = 0;
	
	public:
		
		// 渲染目标
		Container::TFArray<TFSharedPtr<WRenderTarget>> m_pRenderTargets;
		
		// 着色器
		Container::TFArray<TFSharedPtr<WShader>> m_pShaders;
		
		// 渲染管线
		Container::TFArray<TFSharedPtr<WRenderingPipeline>> m_pRenderingPipelines;
		
		// 材质
		Container::TFArray<TFSharedPtr<WMaterial>> m_pMaterials;
		
		// 静态网格体
		Container::TFArray<TFSharedPtr<WStaticMesh>> m_pStaticMeshes;
		
		// 图片
		Container::TFArray<TFSharedPtr<WImage>> m_pImages;
		
	};
	
	
} // Whale
