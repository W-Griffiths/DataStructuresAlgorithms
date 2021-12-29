#include "CppUnitTest.h"
#include "Graph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Graph {

	TEST_CLASS(Construction)
	{
	public:
		TEST_METHOD(ConstructWithVertices)
		{
			ds::Graph graph(5);
			Assert::AreEqual(ds::uint{ 5 }, graph.NumVertices());
		}
		TEST_METHOD(ConstructWithNoVertices)
		{
			ds::Graph graph(0);
			Assert::AreEqual(ds::uint{ 0 }, graph.NumVertices());
		}
		TEST_METHOD(NoEdgesOnConstruction)
		{
			ds::Graph graph(5);
			Assert::AreEqual(ds::uint{ 0 }, graph.NumEdges());
		}
	};

	TEST_CLASS(AddEdges)
	{
	public:
		TEST_METHOD(AddingEdgesIncreasesNumEdges)
		{
			ds::Graph graph(5);
			graph.AddEdge(0, 1);
			graph.AddEdge(1, 2);
			graph.AddEdge(2, 3);

			Assert::AreEqual(ds::uint{ 3 }, graph.NumEdges());
		}
	};

	TEST_CLASS(Search)
	{
	public:
		TEST_METHOD(DepthFirstSearch)
		{
			ds::Graph graph(9);
			graph.AddEdge(0, 8);
			graph.AddEdge(8, 2);
			graph.AddEdge(0, 1);
			graph.AddEdge(1, 4);
			graph.AddEdge(1, 3);
			graph.AddEdge(3, 4);
			graph.AddEdge(4, 5);
			graph.AddEdge(5, 6);
			graph.AddEdge(5, 2);
			graph.AddEdge(6, 7);

			auto path = graph.DFS(0, 2);

			Assert::AreEqual(ds::uint{ 5 }, path.Size());
			Assert::AreEqual(ds::uint{ 0 }, path[0]);
			Assert::AreEqual(ds::uint{ 1 }, path[1]);
			Assert::AreEqual(ds::uint{ 4 }, path[2]);
			Assert::AreEqual(ds::uint{ 5 }, path[3]);
			Assert::AreEqual(ds::uint{ 2 }, path[4]);
		}

		TEST_METHOD(DFSReturnsEmptyIfNoPath)
		{
			ds::Graph graph(10);
			graph.AddEdge(0, 2);
			graph.AddEdge(0, 5);
			graph.AddEdge(2, 1);
			graph.AddEdge(1, 0);
			graph.AddEdge(2, 3);
			graph.AddEdge(3, 4);
			graph.AddEdge(4, 2);
			graph.AddEdge(3, 5);
			graph.AddEdge(6, 1);
			graph.AddEdge(6, 5);

			graph.AddEdge(7, 8);
			graph.AddEdge(8, 9);
			graph.AddEdge(9, 7);

			auto path = graph.DFS(0, 9);

			Assert::AreEqual(size_t{ 0 }, path.Size());
		}

		TEST_METHOD(BreadthFirstSearch)
		{
			ds::Graph graph(9);
			graph.AddEdge(0, 8);
			graph.AddEdge(8, 2);
			graph.AddEdge(0, 1);
			graph.AddEdge(1, 4);
			graph.AddEdge(1, 3);
			graph.AddEdge(3, 4);
			graph.AddEdge(4, 5);
			graph.AddEdge(5, 6);
			graph.AddEdge(5, 2);
			graph.AddEdge(6, 7);

			auto path = graph.BFS(0, 2);

			Assert::AreEqual(ds::uint{ 3 }, path.Size());
			Assert::AreEqual(ds::uint{ 0 }, path[0]);
			Assert::AreEqual(ds::uint{ 8 }, path[1]);
			Assert::AreEqual(ds::uint{ 2 }, path[2]);
		}

		TEST_METHOD(BFSFindsShortestPath)
		{
			ds::Graph graph(10);
			graph.AddEdge(0, 1);
			graph.AddEdge(1, 2);
			graph.AddEdge(2, 3);
			graph.AddEdge(0, 4);
			graph.AddEdge(4, 5);
			graph.AddEdge(5, 6);
			graph.AddEdge(6, 7);
			graph.AddEdge(7, 2);
			graph.AddEdge(0, 8);
			graph.AddEdge(8, 9);
			graph.AddEdge(9, 4);

			auto path = graph.BFS(0, 2);

			Assert::AreEqual(ds::uint{ 3 }, path.Size());
			Assert::AreEqual(ds::uint{ 0 }, path[0]);
			Assert::AreEqual(ds::uint{ 1 }, path[1]);
			Assert::AreEqual(ds::uint{ 2 }, path[2]);
		}

		TEST_METHOD(BFSReturnsEmptyIfNoPath)
		{
			ds::Graph graph(10);
			graph.AddEdge(0, 2);
			graph.AddEdge(0, 5);
			graph.AddEdge(2, 1);
			graph.AddEdge(1, 0);
			graph.AddEdge(2, 3);
			graph.AddEdge(3, 4);
			graph.AddEdge(4, 2);
			graph.AddEdge(3, 5);
			graph.AddEdge(6, 1);
			graph.AddEdge(6, 5);

			graph.AddEdge(7, 8);
			graph.AddEdge(8, 9);
			graph.AddEdge(9, 7);

			auto path = graph.BFS(0, 8);

			Assert::AreEqual(size_t{ 0 }, path.Size());
		}
	};

	TEST_CLASS(Exceptions)
	{
	public:
		TEST_METHOD(AddingEdgeToNonExistentVertexThrows)
		{
			ds::Graph graph(5);
			graph.AddEdge(0, 1);
			graph.AddEdge(1, 2);

			Assert::ExpectException<std::out_of_range>([&] { graph.AddEdge(1, 10); });
			Assert::ExpectException<std::out_of_range>([&] { graph.AddEdge(10, 2); });

			Assert::ExpectException<std::out_of_range>([&] { graph.AddEdge(0, 5); });
		}
	};

}
