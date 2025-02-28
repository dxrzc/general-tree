#pragma once

#include <queue>

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
	std::size_t m_size;

public:
	// public node interface
	class node
	{
	private:
		private_node* m_node;

		// in order to allow the general_tree class to access the private constructor
		friend class general_tree;

		node(private_node* node) noexcept
			: m_node(node) {}

	public:
		node(const T& data)
			: m_node(new private_node(data)) {}

		[[nodiscard]] node left_son() const noexcept
		{
			return m_node->m_left_son;
		}

		[[nodiscard]] node parent() const noexcept
		{
			return m_node->m_parent;
		}

		[[nodiscard]] node right_brother() const noexcept
		{
			return m_node->m_right_brother;
		}

		bool is_root() const noexcept
		{
			return m_node->m_parent == nullptr;
		}

		bool is_leaf() const noexcept
		{
			return m_node->m_left_son == nullptr;
		}

		bool has_right_brother() const noexcept
		{
			return m_node->m_right_brother != nullptr;
		}

		bool has_left_son() const noexcept
		{
			return m_node->m_left_son != nullptr;
		}
	};

	general_tree() noexcept
		: m_root(nullptr), m_size(0) {}

	general_tree(const T& root_value) noexcept
		: m_root(new private_node(root_value)), m_size(1) {}

	void insert_left_son(const node& tree, node new_node)
	{
		if (tree.m_node == nullptr)
			throw std::runtime_error("Cannot insert left son to nullptr");
		new_node.m_node->m_parent = tree.m_node;
		new_node.m_node->m_right_brother = tree.m_node->m_left_son;
		tree.m_node->m_left_son = new_node.m_node;
		++m_size;		
	}

	void insert_right_brother(const node& tree, node new_node)
	{
		if (tree.m_node == nullptr)
			throw std::runtime_error("Cannot insert left son to nullptr");
		if (tree.m_node->m_parent == nullptr)
			throw std::runtime_error("Cannot insert right brother to root");
		new_node.m_node->m_parent = tree.m_node->m_parent;
		new_node.m_node->m_right_brother = tree.m_node->m_right_brother;
		tree.m_node->m_right_brother = new_node.m_node;
		++m_size;
	}

	[[nodiscard]] const T& data(node node) const noexcept
	{
		return node.m_node->data;
	}

	[[nodiscard]] T& data(node node) noexcept
	{
		return node.m_node->data;
	}	

	node create_root(const T& data)
	{
		if (m_root != nullptr)
			throw std::runtime_error("Root already exists");
		m_root = new private_node(data);
		return m_root;
	}

	[[nodiscard]] node root() const noexcept
	{
		return m_root;
	}

	bool empty() const noexcept
	{
		return m_root == nullptr;
	}

	[[nodiscard]] std::size_t size() const noexcept
	{
		return m_size;
	}
};