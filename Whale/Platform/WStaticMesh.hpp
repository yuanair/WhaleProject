//
// Created by admin on 2024/7/11.
//

#pragma once

#include "WRenderObject.hpp"
#include "Whale/Core/TFMath.hpp"
#include "Whale/Core/Memory.hpp"
#include "Whale/Core/Container/TFArray.hpp"
#include "WShader.hpp"

namespace Whale
{
	///
	/// 顶点
	struct WHALE_API FVertex
	{
		float4 positionOS;
		float4 color;
	};
	
	///
	/// 静态网格体
	class WHALE_API WStaticMesh : public WRenderObject
	{
	public:
		
		using Vertex = FVertex;
	
	public:
		
		///
		/// \return 获取网格体数据字节大小
		[[nodiscard]]
		SizeT GetByteSize() const { return sizeof(Vertex) * this->vertexes.GetLength(); }
		
		///
		/// 加载网格体
		virtual void Load() = 0;
	
	protected:
		
		void OnRender() override = 0;
	
	public:
		
		[[nodiscard]]
		const Container::TFArray<Vertex> &GetVertexes() const { return this->vertexes; }
		
		void SetVertexes(const Container::TFArray<Vertex> &vertexesArg) { this->vertexes = vertexesArg; }
		
		[[nodiscard]]
		const Container::TFArray<TFWeakPtr<WShader>> &GetPShaders() const { return this->pShaders; }
		
		void SetPShader(const Container::TFArray<TFWeakPtr<WShader>> &pShadersArg) { this->pShaders = pShadersArg; }
	
	private:
		
		Container::TFArray<Vertex> vertexes;
		
		Container::TFArray<TFWeakPtr<WShader>> pShaders;
		
	};
	
	
} // Whale
