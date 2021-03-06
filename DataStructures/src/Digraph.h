#pragma once
#include "Array.h"
#include "List.h"

namespace ds {

	using uint = unsigned int;

	class Digraph {
	public:
		Digraph(const uint vertices);
		
		virtual void AddEdge(uint from, uint to);

		uint NumVertices() const;
		uint NumEdges() const;

		bool PathExists(const uint source, const uint destination) const;

		Array<uint> DFS(const uint source, const uint destination) const;
		Array<uint> BFS(const uint source, const uint destination) const;

	protected:
		const uint numVertices;
		uint numEdges;
		Array<List<uint>> edges;
	};

}
