//
// Created by admin on 2024/7/11.
//

#pragma once

#include "WRenderObject.hpp"
#include <Whale/TFMath.hpp>
#include <Whale/Memory.hpp>
#include <Whale/Container/TFArray.hpp>
#include "WMaterial.hpp"
#include "TIGPUResource.hpp"

#include <Eigen/Core>

namespace Whale
{
	///
	/// 顶点
	struct WHALE_API FVertex
	{
		Eigen::Vector4f positionOS{};
		Eigen::Vector4f color{};
		Eigen::Vector3f normalOS{};
		Eigen::Vector2f texcoord{};
	};
	
	/// 静态网格体参数
	struct WHALE_API StaticMeshArg
	{
	
	};
	
	///
	/// 静态网格体
	class WHALE_API WStaticMesh : public WRenderObject
	{
	public:
		
		using Vertex = FVertex;
	
	public:
		
		/// 创建资源
		virtual Bool Create(const StaticMeshArg &arg) noexcept = 0;
	
	private:
		
		void OnRender() override = 0;
	
	public:
		
		///
		/// \return 获取网格体数据字节大小
		[[nodiscard]]
		SizeT GetByteSize() const { return sizeof(Vertex) * this->m_vertexes.GetLength(); }
		
		[[nodiscard]]
		const Container::TFArray<Vertex> &GetVertexes() const { return this->m_vertexes; }
		
		void SetVertexes(Container::TFArray<Vertex> vertexesArg)
		{
			this->m_vertexes = Whale::Move(vertexesArg);
		}
		
		[[nodiscard]]
		const Container::TFArray<TFWeakPtr<WMaterial>> &GetPMaterials() const { return this->m_pMaterials; }
		
		void SetPMaterials(Container::TFArray<TFWeakPtr<WMaterial>> pMaterials)
		{
			this->m_pMaterials = Whale::Move(pMaterials);
		}
	
	private:
		
		Container::TFArray<Vertex> m_vertexes;
		
		Container::TFArray<TFWeakPtr<WMaterial>> m_pMaterials;
		
	};
	
	
} // Whale
