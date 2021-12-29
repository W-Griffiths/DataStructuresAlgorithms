#include "CppUnitTest.h"
#include "Digraph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Digraph {

	TEST_CLASS(Construction)
	{
	public:
		TEST_METHOD(ConstructWithVertices)
		{
			ds::Digraph graph(5);
			Assert::AreEqual(ds::uint{ 5 }, graph.NumVertices());
		}
		TEST_METHOD(ConstructWithNoVertices)
		{
			ds::Digraph graph(0);
			Assert::AreEqual(ds::uint{ 0 }, graph.NumVertices());
		}
		TEST_METHOD(NoEdgesOnConstruction)
		{
			ds::Digraph graph(5);
			Assert::AreEqual(ds::uint{ 0 }, graph.NumEdges());
		}
	};

	TEST_CLASS(AddEdges)
	{
	public:
		TEST_METHOD(AddingEdgesIncreasesNumEdges)
		{
			ds::Digraph graph(5);
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
			ds::Digraph graph(6);
			graph.AddEdge(0, 2);
			graph.AddEdge(5, 0);
			graph.AddEdge(2, 1);
			graph.AddEdge(1, 0);
			graph.AddEdge(2, 3);
			graph.AddEdge(3, 4);
			graph.AddEdge(4, 2);
			graph.AddEdge(3, 5);

			auto path = graph.DFS(0, 5);

			Assert::AreEqual(ds::uint{ 4 }, path.Size());
			Assert::AreEqual(ds::uint{ 0 }, path[0]);
			Assert::AreEqual(ds::uint{ 2 }, path[1]);
			Assert::AreEqual(ds::uint{ 3 }, path[2]);
			Assert::AreEqual(ds::uint{ 5 }, path[3]);
		}

		TEST_METHOD(DFSReturnsEmptyIfNoPath)
		{
			ds::Digraph graph(7);
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

			auto path = graph.DFS(0, 6);

			Assert::AreEqual(size_t{ 0 }, path.Size());
		}

		TEST_METHOD(BreadthFirstSearch)
		{
			ds::Digraph graph(6);
			graph.AddEdge(0, 2);
			graph.AddEdge(5, 0);
			graph.AddEdge(2, 1);
			graph.AddEdge(1, 0);
			graph.AddEdge(2, 3);
			graph.AddEdge(3, 4);
			graph.AddEdge(4, 2);
			graph.AddEdge(3, 5);

			auto path = graph.BFS(0, 5);

			Assert::AreEqual(ds::uint{ 4 }, path.Size());
			Assert::AreEqual(ds::uint{ 0 }, path[0]);
			Assert::AreEqual(ds::uint{ 2 }, path[1]);
			Assert::AreEqual(ds::uint{ 3 }, path[2]);
			Assert::AreEqual(ds::uint{ 5 }, path[3]);
		}

		TEST_METHOD(BFSFindsShortestPath)
		{
			ds::Digraph graph(10);
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
			ds::Digraph graph(7);
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

			auto path = graph.BFS(0, 6);

			Assert::AreEqual(size_t{ 0 }, path.Size());
		}
	};

	TEST_CLASS(Exceptions)
	{
	public:
		TEST_METHOD(AddingEdgeToNonExistentVertexThrows)
		{
			ds::Digraph graph(5);
			graph.AddEdge(0, 1);
			graph.AddEdge(1, 2);

			Assert::ExpectException<std::out_of_range>([&] { graph.AddEdge(1, 10); });
			Assert::ExpectException<std::out_of_range>([&] { graph.AddEdge(10, 2); });
		}
	};

}
