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

		T& data() noexcept
		{
			return m_node->data;
		}

		const T& data() const noexcept
		{
			return m_node->data;
		}

		[[nodiscard]] node parent() const noexcept
		{
			return m_node->m_parent;
		}

		[[nodiscard]] node left_son() const noexcept
		{
			return m_node->m_left_son;
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

		node insert_left_son(const node& node)
		{
			node.m_node->m_parent = m_node;
			node.m_node->m_right_brother = m_node->m_left_son;
			m_node->m_left_son = node.m_node;
			return node;
		}

		node insert_right_brother(const node& node)
		{
			if (m_node->m_parent == nullptr)
				throw std::runtime_error("Cannot insert right brother to root");

			node.m_node->m_parent = m_node->m_parent;
			node.m_node->m_right_brother = m_node->m_right_brother;
			m_node->m_right_brother = node.m_node;
			return node;
		}
	};

	general_tree() noexcept
		: m_root(nullptr) {}

	general_tree(const T& root_value) noexcept
		: m_root(new private_node(root_value)) {}
};