#pragma once
#include <general-tree.h>
#include <vector>

class populated_tree
{
public:
	static inline general_tree<int> tree;
	static inline std::vector<int> preorder_vector = { 1, 30, 33, 32, 31, 311, 20, 203, 202, 201, 10, 102, 101 };
	static inline std::vector<int> postorder_vector = { 33, 32, 311, 31, 30, 203, 202, 201, 20, 102, 101, 10, 1 };	

	class builder
	{
	public:
		builder()
		{
			tree.create_root(1);

			auto n10 = tree.insert_left_child(tree.root(), 10);
			auto n20 = tree.insert_left_child(tree.root(), 20);
			auto n30 = tree.insert_left_child(tree.root(), 30);

			auto n31 = tree.insert_left_child(n30, 31);
			auto n32 = tree.insert_left_child(n30, 32);
			auto n33 = tree.insert_left_child(n30, 33);

			auto n201 = tree.insert_left_child(n20, 201);
			auto n202 = tree.insert_left_child(n20, 202);
			auto n203 = tree.insert_left_child(n20, 203);

			auto n101 = tree.insert_left_child(n10, 101);
			auto n102 = tree.insert_left_child(n10, 102);

			auto n311 = tree.insert_left_child(n31, 311);
		}
	};

private:
	static inline builder tree_builder;
};

// Render it: dreampuf.github.io/GraphvizOnline
/*
digraph GeneralTree {
	node [shape=circle];

	1 -> 30;
	1 -> 20;
	1 -> 10;

	30 -> 33;
	30 -> 32;
	30 -> 31;

	31 -> 311;

	20 -> 203;
	20 -> 202;
	20 -> 201;

	10 -> 102;
	10 -> 101;
}
*/