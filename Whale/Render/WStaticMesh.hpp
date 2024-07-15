//
// Created by admin on 2024/7/11.
//

#pragma once

#include <vector>
#include <memory>

#include "WRenderObject.hpp"
#include "Whale/Core/TMath.hpp"
#include "Whale/Core/FUndefinedData.hpp"
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
	
	///
	/// DirectX12静态网格体
	class WHALE_API WStaticMeshDirectX12 : public WStaticMesh
	{
	public:
		
		WStaticMeshDirectX12();
	
	public:
		
		void Load() override;
	
	protected:
		
		void OnRender() override;
	
	public:
		
		[[nodiscard]]
		const FUndefinedData<class WStaticMeshDirectX12Data> &GetData() const { return data; }
	
	private:
		
		FUndefinedData<class WStaticMeshDirectX12Data> data;
		
	};
	
} // Whale
