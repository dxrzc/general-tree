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
		T m_data;
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
			m_data(std::forward<Args>(args)...) {}

		private_node(
			const T& data,
			private_node* parent = nullptr,
			private_node* right_sibling = nullptr,
			private_node* left_child = nullptr
		) : m_data(data),
			m_parent(parent),
			m_left_child(left_child),
			m_right_sibling(right_sibling) {}
	};

	private_node* m_root;

	void deep_copy(node n)
	{
		if (n.m_node == nullptr)
			return;

		private_node* copy_root = new private_node(n.m_node->m_data);
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
				private_node* child_copy = new private_node(child_original->m_data);

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

		/**
		 * @brief Retrieves the left child of the current node.
		 * @return The left child node, or a null node if the current node has no left child.
		 */
		[[nodiscard]] node left_child() const noexcept
		{
			return m_node->m_left_child;
		}

		/**
		 * @brief Retrieves the parent of the current node.
		 * @return The parent node, or a null node if the current node has no parent.
		 */
		[[nodiscard]] node parent() const noexcept
		{
			return m_node->m_parent;
		}

		/**
		 * @brief Retrieves the right sibling of the current node.
		 * @return The right sibling node, or a null node if the current node has no right sibling.
		 */
		[[nodiscard]] node right_sibling() const noexcept
		{
			return m_node->m_right_sibling;
		}

		/**
		 * @brief Retrieves the child node at the specified index.
		 * @param index The zero-based index of the child to retrieve.
		 * @return The child node at the specified index, or a null node if the index is out of range.
		 * @throws std::invalid_argument If the current node is null.
		 */
		[[nodiscard]] node child(std::size_t index) const
		{
			if (m_node == nullptr)
				throw std::invalid_argument("Cannot get child of null node");

			node child = m_node->m_left_child;

			for (std::size_t i = 0; i < index; i++)
			{
				if (child.m_node == nullptr)
					return nullptr;
				child = child.m_node->m_right_sibling;
			}

			return child;
		}

		/**
		 * @brief Counts the number of children of the current node.
		 * @return The total number of children of the current node.
		 * @throws std::invalid_argument If the current node is null.
		 */
		[[nodiscard]] std::size_t children_count() const
		{
			if (m_node == nullptr)
				throw std::invalid_argument("Cannot count children of null node");

			std::size_t count = 0;
			for (const private_node* child = m_node->m_left_child; child != nullptr; child = child->m_right_sibling)
				++count;

			return count;
		}

		/**
		 * @brief Computes the height of the current node in the tree.
		 * @return The height of the current node's subtree.
		 * @throws std::invalid_argument If the current node is null.
		 */
		[[nodiscard]] std::size_t height() const
		{
			// Breadth First Algorithm

			if (m_node == nullptr)
				throw std::invalid_argument("Cannot get height of null node");

			std::queue<private_node*> q;
			q.push(m_node);

			std::size_t height = 0;
			while (!q.empty())
			{
				std::size_t current_level_size = q.size();

				// Process every node of the current level
				for (std::size_t i = 0; i < current_level_size; ++i)
				{
					private_node* current_node = q.front();
					q.pop();

					// Add children of the current node to the queue
					private_node* current_node_left_child = current_node->m_left_child;
					if (current_node_left_child != nullptr)
					{
						q.push(current_node_left_child);
						private_node* right_sibling = current_node_left_child->m_right_sibling;
						while (right_sibling != nullptr)
						{
							q.push(right_sibling);
							right_sibling = right_sibling->m_right_sibling;
						}
					}
				}

				++height;
			}

			return height - 1;
		}

		/**
		 * @brief Computes the total number of descendants of the current node.		 
		 * @return The total number of descendants of the current node.
		 * @throws std::invalid_argument If the current node is null.
		 */
		[[nodiscard]] std::size_t descendants_count() const
		{
			if (m_node == nullptr)
				throw std::invalid_argument("Cannot get height of null node");

			std::size_t count = 0;
			std::queue<private_node*> q;
			q.push(m_node);

			while (!q.empty())
			{
				private_node* current_node = q.front();
				q.pop();

				for (private_node* left_child = current_node->m_left_child; left_child != nullptr; left_child = left_child->m_right_sibling)
				{
					q.push(left_child);
					++count;
				}
			}

			return count;
		}

		/*
		 * @brief Checks if the node is the root of the tree.
		 * @return true if the node is the root, false otherwise.
		 */
		bool is_root() const noexcept
		{
			return m_node->m_parent == nullptr;
		}

		/**
		 * @brief Checks if the node is a leaf in the tree.
		 * @return true if the node is a leaf, false otherwise.
		 */
		bool is_leaf() const noexcept
		{
			return m_node->m_left_child == nullptr;
		}

		/**
		 * @brief Checks if the node has a right sibling.
		 * @return true if the node has a right sibling, false otherwise.
		 */
		bool has_right_sibling() const noexcept
		{
			return m_node->m_right_sibling != nullptr;
		}

		/**
		 * @brief Checks if the node has a left child.
		 * @return true if the node has a left child, false otherwise.
		 */
		bool has_left_child() const noexcept
		{
			return m_node->m_left_child != nullptr;
		}

		/**
		 * @brief Checks if the node is null.
		 * @return true if the node is null, false otherwise.
		 */
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

	/**
	 * @brief Creates and emplaces a new left child node for the given destination node.
	 * @tparam Args Variadic template parameters for the new node constructor.
	 * @param destiny The node to which the new left child will be attached.
	 * @param args Arguments to forward to the new node's constructor.
	 * @return node A handle to the newly created left child node.	 
	 * @throws std::invalid_argument If the destination node is null.
	 */
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

	/**
	 * @brief Inserts an entire subtree as the left child of the given destination node.
	 * @param destiny The node to which the tree will be inserted as a left child.
	 * @param tree The tree to insert as a left child. After insertion, this tree will be empty.
	 * @return node A handle to the newly inserted left child node, or a null node if the tree is empty.
	 * @throws std::invalid_argument If the destination node is null or if attempting to insert the tree as a child of its own root.
	 */
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

	/**
	 * @brief Inserts a new left child node for the given destination node, with the provided value.	 
	 * @param destiny The node to which the left child will be inserted.
	 * @param new_node_value The value to store in the newly created left child node.
	 * @return node A handle to the newly created left child node.	 
	 * @throws std::invalid_argument If the destination node is null.
	 */
	template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
	node insert_left_child(node destiny, U&& new_node_value)
	{
		return emplace_left_child(destiny, std::forward<U>(new_node_value));
	}

	/**
	 * @brief Creates and emplaces a new right sibling for the given destination node.	 
	 * @tparam Args Variadic template parameters for the new node constructor.
	 * @param destiny The node to which the new right sibling will be attached.
	 * @param args Arguments to forward to the new node's constructor.
	 * @return node A handle to the newly created right sibling node.	 
	 * @throws std::invalid_argument If the destination node is null or is the root (cannot have a sibling).
	 */
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

	/**
	 * @brief Inserts an entire subtree as the right sibling of the given destination node.	 
	 * @param destiny The node to which the tree will be inserted as a right sibling.
	 * @param tree The tree to insert as a right sibling. After insertion, this tree will be empty.
	 * @return node A handle to the newly inserted right sibling node, or a null node if the tree is empty.	 
	 * @throws std::invalid_argument If the destination node is null, is the root (cannot have siblings),
	 *                               or if attempting to insert the tree as its own sibling.
	 */
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

	/**
	 * @brief Inserts a new right sibling node for the given destination node, with the provided value.	 
	 * @param destiny The node to which the right sibling will be inserted.
	 * @param new_node_value The value to store in the newly created right sibling node.
	 * @return node A handle to the newly created right sibling node.	 
	 * @throws std::invalid_argument If the destination node is null or is the root (cannot have a sibling).
	 */
	template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
	node insert_right_sibling(node destiny, U&& new_node_value)
	{
		return emplace_right_sibling(destiny, std::forward<U>(new_node_value));
	}

	[[nodiscard]] const T& data(node node) const
	{
		if (node.m_node == nullptr)
			throw std::invalid_argument("Cannot get data from null node");

		return node.m_node->m_data;
	}

	/**
	 * @brief Accesses the data stored in the given node.	 
	 * @param node The node from which to retrieve the data.
	 * @return T& Reference to the data stored in the node.
	 * @throws std::invalid_argument If the given node is null.
	 */
	[[nodiscard]] T& data(node node)
	{
		if (node.m_node == nullptr)
			throw std::invalid_argument("Cannot get data from null node");

		return node.m_node->m_data;
	}

	/**
	 * @brief Creates and emplaces the root node of the tree with the given arguments.
	 * @tparam Args Variadic template parameters representing the types of arguments to be forwarded to the root node constructor.
	 * @param args Arguments to forward to the root node constructor.
	 * @return node A handle to the newly created root node.	 
	 * @throws std::runtime_error If a root node already exists.
	 */
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

	/**
	 * @brief Creates the root node of the tree 
	 * @param data The value to store in the root node.
	 * @return node A handle to the newly created root node.
	 * @throws std::runtime_error If a root node already exists.
	 */	
	template<typename U, typename = std::enable_if_t<std::is_convertible_v<U, T>>>
	node create_root(U&& data)
	{
		return emplace_root(std::forward<U>(data));
	}

	/**
	 * @brief Retrieves the root node of the tree.	 
	 */
	[[nodiscard]] node root() const noexcept
	{
		return m_root;
	}

	/**
	 * @brief Clears all nodes from the tree.	 
	 */
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


	/**
	 * @brief Checks whether the tree is empty.	 	 
	 */
	bool empty() const noexcept
	{
		return m_root == nullptr;
	}
};