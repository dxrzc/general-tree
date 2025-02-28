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
		private_node* m_left_child;
		private_node* m_right_sibling;

		private_node(const T& data, private_node* parent = nullptr, private_node* right_sibling = nullptr, private_node* left_child = nullptr)
			: data(data), m_parent(parent), m_left_child(left_child), m_right_sibling(right_sibling) {}
	};

	private_node* m_root;
	std::size_t m_size;

public:
	// public node interface
	class node
	{
		friend class general_tree;

	private:
		private_node* m_node;				

	public:
		node(const T& data)
			: m_node(new private_node(data)) {}

		node(private_node* node = nullptr) noexcept
			: m_node(node) {}
		
		bool operator==(const node& other) const noexcept
		{
			return m_node == other.m_node;
		}

		[[nodiscard]] node left_child() const noexcept
		{
			return m_node->m_left_child;
		}

		[[nodiscard]] node parent() const noexcept
		{
			return m_node->m_parent;
		}

		[[nodiscard]] node right_sibling() const noexcept
		{
			return m_node->m_right_sibling;
		}

		bool is_root() const noexcept
		{
			return m_node->m_parent == nullptr;
		}

		bool is_leaf() const noexcept
		{
			return m_node->m_left_child == nullptr;
		}

		bool has_right_sibling() const noexcept
		{
			return m_node->m_right_sibling != nullptr;
		}

		bool has_left_child() const noexcept
		{
			return m_node->m_left_child != nullptr;
		}

		bool isNull() const noexcept
		{
			return m_node == nullptr;
		}		

		std::size_t children_count() const noexcept
		{
			std::size_t count = 0;
			for (auto child = m_node->m_left_child; child != nullptr; child = child->m_right_sibling)
				++count;
			return count;
		}		
	};

	general_tree() noexcept
		: m_root(nullptr), m_size(0) {}

	general_tree(const T& root_value) noexcept
		: m_root(new private_node(root_value)), m_size(1) {}

	node insert_left_child(const node& tree, node new_node)
	{
		if (tree.m_node == nullptr)
			throw std::runtime_error("Cannot insert left child to nullptr");
		new_node.m_node->m_parent = tree.m_node;
		new_node.m_node->m_right_sibling = tree.m_node->m_left_child;
		tree.m_node->m_left_child = new_node.m_node;
		++m_size;		
		return new_node;
	}

	node insert_right_sibling(const node& tree, node new_node)
	{
		if (tree.m_node == nullptr)
			throw std::runtime_error("Cannot insert right sibling to nullptr");
		if (tree.m_node->m_parent == nullptr)
			throw std::runtime_error("Cannot insert right sibling to root");
		new_node.m_node->m_parent = tree.m_node->m_parent;
		new_node.m_node->m_right_sibling = tree.m_node->m_right_sibling;
		tree.m_node->m_right_sibling = new_node.m_node;
		++m_size;
		return new_node;
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