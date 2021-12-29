#include "Graph.h"
#include <stdexcept>

namespace ds {

	Graph::Graph(const uint vertices) : Digraph(vertices) { }

	void Graph::AddEdge(uint from, uint to) {
		if (from >= numVertices || to >= numVertices) {
			throw std::out_of_range("Vertex doesn't exist in the graph");
		}

		edges[from].Add(to);
		if (from != to) {
			// Don't add duplicate edge for self-loops
			edges[to].Add(from);
		}
		numEdges++;
	}

}
