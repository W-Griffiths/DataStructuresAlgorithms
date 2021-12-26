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
