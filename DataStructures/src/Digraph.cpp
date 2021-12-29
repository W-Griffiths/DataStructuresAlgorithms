#include "Digraph.h"
#include "Stack.h"
#include "Queue.h"
#include <stdexcept>

namespace ds {

	Digraph::Digraph(const uint vertices) : edges(Array<List<uint>>(vertices)), numVertices(vertices), numEdges(0) { }

	void Digraph::AddEdge(uint from, uint to) {
		if (from >= numVertices || to >= numVertices) {
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

	/// <summary>
	/// A Depth-First Search which exhausts a path before backtracking.
	/// </summary>
	/// <param name="source">Index of source vertex</param>
	/// <param name="destination">Index of destination vertex</param>
	/// <returns>Returns an array of vertices which form a
	/// connecting path between source and destination. 
	/// Returns an empty array if no path exists.</returns>
	Array<uint> Digraph::DFS(const uint source, const uint destination) const {
		Array<bool> marked(numVertices);
		marked.SetAll(false);

		Array<uint> visitedFrom(numVertices);

		Stack<uint> vertices;
		vertices.Push(source);
		marked[source] = true;

		while (!vertices.IsEmpty()) {
			uint vertex = vertices.Pop();
			if (vertex == destination) {
				// Trace back steps taken to reach destination
				Stack<uint> backTrace;
				backTrace.Push(destination);
				uint step = destination;
				while (step != source) {
					step = visitedFrom[step];
					backTrace.Push(step);
				}

				// Unwind the stack to create the forward path
				Array<uint> path(backTrace.Size());
				for (size_t i = 0; i < path.Size(); i++)
				{
					path[i] = backTrace.Pop();
				}
				return path;
			}
			else {
				for (uint edge : edges[vertex]) {
					if (!marked[edge]) {
						vertices.Push(edge);
						marked[edge] = true;
						visitedFrom[edge] = vertex;
					}
				}
			}
		}
		// All reachable vertices visited - path doesn't exist
		return Array<uint>::Empty();
	}

	/// <summary>
	/// A Breadth-First Search which guarantees the shortest path if one exists.
	/// </summary>
	/// <param name="source">Index of source vertex</param>
	/// <param name="destination">Index of destination vertex</param>
	/// <returns>Returns an array of vertices which form the shortest
	/// connecting path between source and destination. 
	/// Returns an empty array if no path exists.</returns>
	Array<uint> Digraph::BFS(const uint source, const uint destination) const {
		Array<bool> marked(numVertices);
		marked.SetAll(false);

		Array<uint> visitedFrom(numVertices);

		Queue<uint> vertices;
		vertices.Enqueue(source);
		marked[source] = true;

		while (!vertices.IsEmpty()) {
			uint vertex = vertices.Dequeue();
			if (vertex == destination) {
				// Trace back steps taken to reach destination
				Stack<uint> backTrace;
				backTrace.Push(destination);
				uint step = destination;
				while (step != source) {
					step = visitedFrom[step];
					backTrace.Push(step);
				}

				// Unwind the stack to create the forward path
				Array<uint> path(backTrace.Size());
				for (size_t i = 0; i < path.Size(); i++)
				{
					path[i] = backTrace.Pop();
				}
				return path;
			}
			else {
				for (uint edge : edges[vertex]) {
					if (!marked[edge]) {
						vertices.Enqueue(edge);
						marked[edge] = true;
						visitedFrom[edge] = vertex;
					}
				}
			}
		}
		// All reachable vertices visited - path doesn't exist
		return Array<uint>::Empty();
	}

}
