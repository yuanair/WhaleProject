//
// Created by admin on 2024/7/11.
//

#include "WStaticMesh.hpp"

namespace Whale
{
	
	void WStaticMesh::SetVertexes(const std::vector<Vertex> &vertexesArg)
	{
		WStaticMesh::vertexes = vertexesArg;
	}
	
	SizeT WStaticMesh::GetByteSize() const
	{
		return sizeof(Vertex) * this->vertexes.size();
	}
	
	
} // Whale