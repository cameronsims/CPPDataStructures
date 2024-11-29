#include "Test.h" 
#include "BinarySearchTree.h" 

#include <stdio.h>
#include <string.h>

namespace cslib {

    BinarySearchTree<int> BST_testBasicTestTree() {
        //    4
        //  2   6
        // 1 3 5 7
        //         8
        BinarySearchTree<int> bst;

        constexpr size_t n = 8;
        const int arr[n] = { 4, 2, 6, 1, 3, 5, 7, 8 };

        for (size_t i = 0; i < n; i++) {
            bst.insert(arr[i]);
        }

        return bst;
    }

    // Test insertion / search
    int BST_test1() {
        BinarySearchTree<int> bst = BST_testBasicTestTree();

        //    4
        //  2   6
        // 1 3 5 7
        //         8
        constexpr size_t n = 8;
        const int arr[n] = { 4, 2, 6, 1, 3, 5, 7, 8 };

        for (size_t i = 0; i < n; i++) {
            if (arr[i] != bst.search(arr[i])) {
                return false;
            }
        }

        CS_RANGE_TEST(bst.search(0), BSTNodeNotFound);
        CS_RANGE_TEST(bst.search(9), BSTNodeNotFound);

        return true;
    }
    
    // Deletion Test
    int BST_test2() {
        constexpr size_t n = 7;
        const int arr[n] = { 1, 3, 4, 5, 6, 7, 8 };

        BinarySearchTree<int> bst = BST_testBasicTestTree();
        bst.remove(2);

        
        for (size_t i = 0; i < n; i++) {
            try {
                bst.search(arr[i]);
            } catch (const BSTNodeNotFound& err) {
                return false;
            }
        }

        return true;
    }

    // Depth Test
    int BST_test3() { 
        constexpr size_t n = 8;
        const size_t depth = 3; 
        BinarySearchTree<int> bst = BST_testBasicTestTree();

        return (bst.depth() == depth); 
    }

    // In order
    int BST_test4() { 
        constexpr size_t n = 8;
        const int inorder[n] = { 1, 2, 3, 4, 5, 6, 7, 8 };
        bool correct = true;

        BinarySearchTree<int> bst = BST_testBasicTestTree();
        size_t i = 0;
        bst.inorder([&](const int& a) {
            // If not...
            if (inorder[i] != a) {
                correct = false;
            }
            i++;
        });

        return correct;
    }

    // Pre order
    int BST_test5() { 
        constexpr size_t n = 8;
        
        BinarySearchTree<int> bst = BST_testBasicTestTree();
        const int preorder[n] = { 4, 2, 1, 3, 6, 5, 7, 8 };
        bool correct = true;
        size_t i = 0;

        auto f = [&](const int& a) {
            if (preorder[i] != a) {
                correct = false;
            }
            i++;
        };

        bst.preorder(f);

        return correct;
    }
    
    // Post order
    int BST_test6() { 
        constexpr size_t n = 8;
        const int postorder[n] = { 1, 3, 2, 5, 8, 7, 6, 4 };
        BinarySearchTree<int> bst = BST_testBasicTestTree();
        
        bool correct = true;
        size_t i = 0;

        auto f = [&](const int& a) {
            if (postorder[i] != a) {
                correct = false;
            }
            i++;
        };

        bst.postorder(f);

        return correct;
    }

    // Depth First
    int BST_test7() {
        constexpr size_t n = 8;
        const int depthfirst[n] = { 4, 2, 1, 3, 6, 5, 7, 8 };
        BinarySearchTree<int> bst = BST_testBasicTestTree();
        bool correct = true;

        bst.depthFirst([&](const int& a) {
            static size_t i = 0;
            if (depthfirst[i] != a) {
                correct = false;
            }

            i++;
        });

        return correct;
    }

    // Breadth First
    int BST_test8() {
        constexpr size_t n = 8;
        const int breadthfirst[n] = { 4, 2, 6, 1, 3, 5, 7, 8 };
        BinarySearchTree<int> bst = BST_testBasicTestTree();
        bool correct = true;

        bst.breadthFirst([&](const int& a) {
            static size_t i = 0;
            if (breadthfirst[i] != a) {
                correct = false;
            }

            i++;
        });

        return correct;
    }

    // Depth testing
    int BST_test9() {
        // Try values up to this depth
        constexpr size_t n = 1024;
        BinarySearchTree<int> bst;

        int arr[n];
        for (size_t i = 0; i < n; i++) {
            arr[i] = i + 1;
        }

        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < i + 1; j++) {
                bst.insert(arr[j]);
            }

            if (bst.depth() != i) {
                return false;
            }

            // Kill all nodes
            bst.clear();
        }

        return true;
    }

    // Amount of nodes test
    int BST_test10() {
        constexpr size_t n = 1024;
        BinarySearchTree<int> bst;
        for (size_t i = 1; i < n; i++) {
            for (size_t j = 0; j < i; j++) {
                bst.insert(j);
            }

            if (bst.amount() != i) {
                return false;
            }

            bst.clear();
        }
        return true;
    }
}



typedef int(*testf_t)(void);

int main() {
    using namespace cslib;

    constexpr size_t TEST_SIZE = 10;
    testf_t test[TEST_SIZE] = {
        BST_test1,
        BST_test2,
        BST_test3,
        BST_test4,
        BST_test5,
        BST_test6,
        BST_test7,
        BST_test8,
        BST_test9,
        BST_test10
    };

    for (int i = 0; i < TEST_SIZE; i++) {
        int result = test[i]();
        cslib::Datastructure_test(i + 1, result);
        if (!result) {
            return i + 1;
        }
    }

    return 0;
}