#pragma once

#include <utility>
#include <queue>
#include <stdexcept>
#include <optional>

template <typename T>
class general_tree
{
public:
	class node;

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

	void deep_copy(node n)
	{
		if (n.m_node == nullptr)
			return;

		private_node* copy_root = new private_node(n.m_node->data);
		m_root = copy_root;

		// keeps track of nodes whose children still need to be copied
		std::queue<std::pair<private_node*, private_node*>> org_copy_relation_queue;
		org_copy_relation_queue.push({ n.m_node, copy_root });

		while (!org_copy_relation_queue.empty())
		{
			private_node* original_node = org_copy_relation_queue.front().first;
			private_node* copied_node = org_copy_relation_queue.front().second;
			org_copy_relation_queue.pop();

			private_node* child_original = original_node->m_left_child;
			private_node* prev_copied_child = nullptr;

			// children copy algorithm
			while (child_original != nullptr)
			{
				private_node* child_copy = new private_node(child_original->data);

				// if it is the first copied child, it goes as left child
				if (prev_copied_child == nullptr)
					copied_node->m_left_child = child_copy;
				else					
					prev_copied_child->m_right_sibling = child_copy;

				org_copy_relation_queue.push({ child_original, child_copy });

				prev_copied_child = child_copy;
				child_original = child_original->m_right_sibling;
			}
		}
	}

public:
	// public node interface
	class node
	{
		friend class general_tree;

	private:
		private_node* m_node;

	public:
		node(private_node* node = nullptr) noexcept
			: m_node(node) {}

		bool operator==(const node& other) const noexcept
		{
			return m_node == other.m_node;
		}

		explicit operator bool() const
		{
			return m_node != nullptr;
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

		/**
		 * @brief Retrieves the child node at the specified index.
		 * @param index The index of the child node to retrieve.
		 * @return The child node at the specified index. It can return a null node.
		 * @throws std::out_of_range Index is out of range.
		 * @throws std::invalid_argument Current node is null.
		 */
		[[nodiscard]] node child(std::size_t index) const
		{
			if (m_node == nullptr)
				throw std::invalid_argument("Cannot get child of null node");

			node child = m_node->m_left_child;

			for (std::size_t i = 0; i < index; i++)
			{
				if (child.m_node == nullptr)
					throw std::out_of_range("Index out of range");
				child = child.m_node->m_right_sibling;
			}

			return child;
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

	general_tree(const general_tree<T>& rhs) : general_tree()
	{
		deep_copy(rhs.root());
	}

	template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
	general_tree(U&& root_value) : general_tree()
	{
		m_root = new private_node(
			nullptr,
			nullptr,
			nullptr,
			std::forward<U>(root_value)
		);
	}

	~general_tree()
	{
		clear();
	}

	template<typename ...Args>
	node emplace_left_child(node destiny, Args&& ...args)
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

		return new_node;
	}

	node insert_left_child(node destiny, general_tree<T>& tree)
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
			return destiny.m_node->m_left_child;
		}

		return node(nullptr);
	}

	template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
	node insert_left_child(node destiny, U&& new_node_value)
	{
		return emplace_left_child(destiny, std::forward<U>(new_node_value));
	}

	template<typename ...Args>
	node emplace_right_sibling(node destiny, Args&& ...args)
	{
		if (destiny.m_node == nullptr)
			throw std::invalid_argument("Cannot insert right sibling to null node");

		if (destiny.m_node->m_parent == nullptr)
			throw std::invalid_argument("Cannot insert right sibling to root");

		private_node* new_node = new private_node(
			destiny.m_node->m_parent,
			destiny.m_node->m_right_sibling,
			nullptr,
			std::forward<Args>(args)...
		);

		destiny.m_node->m_right_sibling = new_node;

		return new_node;
	}

	node insert_right_sibling(node destiny, general_tree<T>& tree)
	{
		if (destiny.m_node == nullptr)
			throw std::invalid_argument("Cannot insert right sibling to null node");

		if (destiny.m_node->m_parent == nullptr)
			throw std::invalid_argument("Cannot insert right sibling to root");

		if (destiny.m_node == tree.m_root)
			throw std::invalid_argument("Cannot insert a tree as its own sibling");

		if (tree.m_root)
		{
			tree.m_root->m_parent = destiny.m_node->m_parent;
			tree.m_root->m_right_sibling = destiny.m_node->m_right_sibling;
			destiny.m_node->m_right_sibling = tree.m_root;
			tree.m_root = nullptr;
			return destiny.m_node->m_right_sibling;
		}

		return node(nullptr);
	}

	template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
	node insert_right_sibling(node destiny, U&& new_node_value)
	{
		return emplace_right_sibling(destiny, std::forward<U>(new_node_value));
	}

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

	template<typename ...Args>
	node emplace_root(Args&& ...args)
	{
		if (m_root != nullptr)
			throw std::runtime_error("Root already exists");

		m_root = new private_node(
			nullptr,
			nullptr,
			nullptr,
			std::forward<Args>(args)...
		);

		return m_root;
	}

	template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
	node create_root(U&& data)
	{
		return emplace_root(std::forward<U>(data));
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

	// TODO: test
	[[nodiscard]] std::size_t descendants_count(node n) const
	{
		if (n.m_node == nullptr)
			throw std::invalid_argument("Cannot get descendants count of null node");

		std::size_t total = 0;

		for (n.m_node = n.m_node->m_left_child; n.m_node != nullptr; n.m_node = n.m_node->m_right_sibling)
			total += descendants_count(n) + 1;

		return total;
	}

	[[nodiscard]] node root() const noexcept
	{
		return m_root;
	}

	void clear()
	{
		if (m_root == nullptr)
			return;

		std::queue<private_node*> queue;
		queue.push(m_root);

		private_node* current = nullptr;
		while (!queue.empty())
		{
			// Add the children to the stack and delete the parent
			current = queue.front();
			queue.pop();

			for (private_node* child = current->m_left_child; child != nullptr; child = child->m_right_sibling)
				queue.push(child);

			delete current;
		}

		m_root = nullptr;
	}

	bool empty() const noexcept
	{
		return m_root == nullptr;
	}
};