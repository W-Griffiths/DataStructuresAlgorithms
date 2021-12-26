#include "Digraph.h"
#include <stdexcept>

namespace ds {

	Digraph::Digraph(const uint vertices) : edges(Array<List<uint>>(vertices)), numVertices(vertices), numEdges(0) { }

	void Digraph::AddEdge(uint from, uint to) {
		if (from > numVertices || to > numVertices) {
			throw std::out_of_range("Vertex doesn't exist in the graph");
		}

		edges[from].Add(to);
		numEdges++;
	}

	uint Digraph::NumVertices() const {
		return numVertices;
	}

	uint Digraph::NumEdges() const {
		return numEdges;
	}

}
