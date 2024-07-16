//
// Created by admin on 2024/7/11.
//

#pragma once

#include <vector>
#include <memory>

#include "WRenderObject.hpp"
#include "Whale/Tool/Math/TMath.hpp"
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
		SizeT GetByteSize() const;
		
		///
		/// 加载网格体
		virtual void Load() = 0;
	
	protected:
		
		void OnRender() override = 0;
	
	public:
		
		[[nodiscard]]
		const std::vector<Vertex> &GetVertexes() const { return vertexes; }
		
		void SetVertexes(const std::vector<Vertex> &vertexesArg);
		
		[[nodiscard]]
		const std::vector<std::weak_ptr<WShader>> &GetPShaders() const { return pShaders; }
		
		void SetPShader(const std::vector<std::weak_ptr<WShader>> &pShadersArg) { this->pShaders = pShadersArg; }
	
	private:
		
		std::vector<Vertex> vertexes;
		
		std::vector<std::weak_ptr<WShader>> pShaders;
		
	};
	
	
} // Whale
