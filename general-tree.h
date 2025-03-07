#pragma once

#include <utility>
#include <queue>
#include <stdexcept>
#include <optional>

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

		template<typename... Args>
		private_node(
			private_node* parent,
			private_node* right_sibling,
			private_node* left_child,
			Args&&...args
		) : m_parent(parent),
			m_left_child(left_child),
			m_right_sibling(right_sibling),
			data(std::forward<Args>(args)...) {}

		private_node(
			const T& data,
			private_node* parent = nullptr,
			private_node* right_sibling = nullptr,
			private_node* left_child = nullptr
		) : data(data),
			m_parent(parent),
			m_left_child(left_child),
			m_right_sibling(right_sibling) {}
	};

	private_node* m_root;

public:
	// public node interface
	class node
	{
		friend class general_tree;

	private:
		private_node* m_node;

	public:
		// TODO: forwarding or a stdmove version
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

		bool is_null() const noexcept
		{
			return m_node == nullptr;
		}
	};

	general_tree() noexcept
		: m_root(nullptr) {}

	// TODO: forwarding or a stdmove version
	general_tree(const T& root_value)
		: m_root(new private_node(root_value)) {}

	template<typename ...Args>
	void emplace_left_child(node destiny, Args&& ...args)
	{
		if (destiny.m_node == nullptr)
			throw std::invalid_argument("Cannot insert left child to null node");

		private_node* new_node = new private_node(
			destiny.m_node,
			destiny.m_node->m_left_child,
			nullptr,
			std::forward<Args>(args)...
		);

		destiny.m_node->m_left_child = new_node;
	}

	void insert_left_child(node destiny, general_tree<T>& tree)
	{
		if (!destiny.m_node)
			throw std::invalid_argument("Cannot insert left child to null node");

		if (destiny.m_node == tree.m_root)
			throw std::invalid_argument("Cannot insert a tree as its own child");

		if (tree.m_root)
		{
			tree.m_root->m_parent = destiny.m_node;
			tree.m_root->m_right_sibling = destiny.m_node->m_left_child;
			destiny.m_node->m_left_child = tree.m_root;
			tree.m_root = nullptr;
		}
	}

	template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
	void insert_left_child(node destiny, U&& new_node_value)
	{
		emplace_left_child(destiny, std::forward<U>(new_node_value));
	}

	//template<typename ...Args>
	//node emplace_right_sibling(node destiny, Args&& ...args)
	//{
	//	if (destiny.m_node == nullptr)
	//		throw std::invalid_argument("Cannot insert right sibling to null node");

	//	if (destiny.m_node->m_parent == nullptr)
	//		throw std::invalid_argument("Cannot insert right sibling to root");

	//	private_node* new_node = new private_node(
	//		destiny.m_node->m_parent,
	//		destiny.m_node->m_right_sibling,
	//		nullptr,
	//		std::forward<Args>(args)...
	//	);
	//	destiny.m_node->m_right_sibling = new_node;

	//	return new_node;
	//}

	 //node insert_right_sibling(node destiny, node& child_node)
	 //{
	 //	if (destiny.m_node == nullptr)
	 //		throw std::invalid_argument("Cannot insert right sibling to nullptr");
	 //
	 //	if (destiny.m_node->m_parent == nullptr)
	 //		throw std::invalid_argument("Cannot insert right sibling to root");
	 //
	 //	child_node.m_node->m_parent = destiny.m_node->m_parent;
	 //	child_node.m_node->m_right_sibling = destiny.m_node->m_right_sibling;
	 //	destiny.m_node->m_right_sibling = child_node.m_node;
	 //	child_node.m_node = nullptr;
	 //
	 //	return child_node;
	 //}
	 //
	 //template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
	 //node insert_right_sibling(node destiny, U&& new_node_value)
	 //{
	 //	return emplace_right_sibling(destiny, std::forward<U>(new_node_value));
	 //}

	[[nodiscard]] const T& data(node node) const
	{
		if (node.m_node == nullptr)
			throw std::invalid_argument("Cannot get data from null node");

		return node.m_node->data;
	}

	[[nodiscard]] T& data(node node)
	{
		if (node.m_node == nullptr)
			throw std::invalid_argument("Cannot get data from null node");

		return node.m_node->data;
	}

	// TODO: forwarding
	void create_root(const T& data)
	{
		if (m_root != nullptr)
			throw std::runtime_error("Root already exists");

		m_root = new private_node(data);
	}

	[[nodiscard]] std::size_t children_count(node n) const
	{
		if (n.m_node == nullptr)
			throw std::invalid_argument("Cannot count children of null node");

		std::size_t count = 0;
		for (auto child = n.left_child(); !child.is_null(); child = child.right_sibling())
			++count;
		return count;
	}

	[[nodiscard]] std::size_t height(node n) const
	{
		if (n.m_node == nullptr)
			throw std::invalid_argument("Cannot get height of null node");

		std::size_t max_height = 0;
		for (private_node* ptr = n.m_node->m_left_child; ptr != nullptr; ptr = ptr->m_right_sibling)
		{
			if (ptr != nullptr)
			{
				std::size_t child_height = height(ptr);
				if (child_height > max_height)
					max_height = child_height;
			}
		}

		return (n.m_node->m_left_child ? 1 + max_height : 0);
	}

	[[nodiscard]] node root() const noexcept
	{
		return m_root;
	}

	bool empty() const noexcept
	{
		return m_root == nullptr;
	}
};