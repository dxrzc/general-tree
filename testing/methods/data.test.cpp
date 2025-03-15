#include <gtest/gtest.h>
#include "general-tree.h"

TEST(data, throwInvalidArgumentExceptionIfNodeIsNull)
{
    general_tree<int> tree;
	// using a block to avoid the warning caused by nodiscard
    EXPECT_THROW({        
        auto data = tree.data(tree.root());
        }, 
		std::invalid_argument
	);
}

TEST(data, returnTheDataStoredInTheNode)
{
	const int root_value = 1;
	general_tree<int> tree(root_value);	
	EXPECT_EQ(tree.data(tree.root()), root_value);
}

// const T& data overload
TEST(dataConst, throwInvalidArgumentExceptionIfNodeIsNull)
{
    const general_tree<int> tree;
	// using a block to avoid the warning caused by nodiscard
    EXPECT_THROW({        
        auto data = tree.data(tree.root());
        }, 
		std::invalid_argument
	);
}

// const T& data overload
TEST(dataConst, returnTheDataStoredInTheNode)
{
	const int root_value = 1;
	const general_tree<int> tree(root_value);	
	EXPECT_EQ(tree.data(tree.root()), root_value);
}
