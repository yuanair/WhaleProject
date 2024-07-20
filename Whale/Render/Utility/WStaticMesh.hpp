//
// Created by admin on 2024/7/11.
//

#pragma once

#include <vector>

#include "WRenderObject.hpp"
#include "Whale/Tool/Math/TFMath.hpp"
#include "Whale/Core/Memory.hpp"
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
		SizeT GetByteSize() const { return sizeof(Vertex) * this->vertexes.size(); }
		
		///
		/// 加载网格体
		virtual void Load() = 0;
	
	protected:
		
		void OnRender() override = 0;
	
	public:
		
		[[nodiscard]]
		const std::vector<Vertex> &GetVertexes() const { return this->vertexes; }
		
		void SetVertexes(const std::vector<Vertex> &vertexesArg) { this->vertexes = vertexesArg; }
		
		[[nodiscard]]
		const std::vector<TFWeakPtr<WShader>> &GetPShaders() const { return this->pShaders; }
		
		void SetPShader(const std::vector<TFWeakPtr<WShader>> &pShadersArg) { this->pShaders = pShadersArg; }
	
	private:
		
		std::vector<Vertex> vertexes;
		
		std::vector<TFWeakPtr<WShader>> pShaders;
		
	};
	
	
} // Whale
