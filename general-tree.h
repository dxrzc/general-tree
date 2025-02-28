#pragma once

template <typename T>
class general_tree
{
private:
	struct private_node
	{
		T data;
		private_node* m_parent;
		private_node* m_left_son;
		private_node* m_right_brother;

		private_node(const T& data, private_node* parent = nullptr, private_node* right_brother = nullptr, private_node* left_son = nullptr)
			: data(data), m_parent(parent), m_left_son(left_son), m_right_brother(right_brother) {}
	};

	private_node* m_root;

public:
		
};