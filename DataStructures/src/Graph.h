#pragma once
#include "Digraph.h"

namespace ds {

	class Graph : public Digraph {
	public:
		Graph(const uint vertices);
		void AddEdge(uint from, uint to) override;
	};

}
