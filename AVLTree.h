/**
 * @file AVLTree.h
 * @brief Holds the AVL BSTree structure.
 **/

#ifndef CSAVLTREE_H
#define CSAVLTREE_H

#include "Universal.h"
#include "BSTree.h"

namespace cslib {

    /**
     * @class AVLTree
     * @tparam T The type of the data structure
     * @brief A balanced binary tree structure
     **/
    template<typename T>
    class AVLTree : public BSTree<T> {
    public:
        /**
         * @param p_key The data we're looking to delete
         * @brief Searches for the key, deletes it and returns it
         * @return Returns the value when we delete it
         */
        T  remove(const T& p_key);

        /**
         * @param p_key The data we're looking to insert
         * @brief Finds the appropirate place to put the value in the tree
         * @return Returns the value when we insert it
         */
        const T& insert(const T& p_key);

    protected:
        /// The BinaryNode of the tree
        typedef BSTree<T>::BinaryNode BinaryNode;

        /**
         * @param p_node Gets the depth of the node
         * @brief Gets the depth of a node in relation to the root
         * @return Returns the value of depth
         */
        size_t m_depth(const BinaryNode* p_node) const;

        /**
         * @param p_avl The other tree we're adding
         * @brief Adds a subtree to this binary tree
         */
        void m_addSubtree(const AVLTree<T>& p_avl);

        /**
         * @param p_subtree The subtree we're balancing
         * @brief Balances a subtree
         */
        static BinaryNode* ms_balance(BinaryNode* p_subtree);
        
        /**
         * @param p_data The data we're adding
         * @brief Adds node, doesn't balance.
         * @return Returns the data we've just inserted
         */
        const T& m_insert(const T& p_data);
    
    private:
        /**
         * @param p_subtree The subtree we're balancing
         * @brief Balances a subtree deciding a rotation
         * @return Returns the new root of the subtree
         */
        static BinaryNode* ms_balanceHelper(BinaryNode* p_subtree);

        /**
         * @param p_subtree The subtree we're balancing
         * @brief Balances a subtree using a left rotation
         * @return Returns the new root of the subtree
         */
        static BinaryNode* ms_balance_LeftRotation(BinaryNode* p_subtree);

        /**
         * @param p_subtree The subtree we're balancing
         * @brief Balances a subtree using a right rotation
         * @return Returns the new root of the subtree
         */
        static BinaryNode* ms_balance_RightRotation(BinaryNode* p_subtree);

        /**
         * @param p_subtree The subtree we're balancing
         * @brief Balances a subtree using a left-right rotation
         * @return Returns the new root of the subtree
         */
        static BinaryNode* ms_balance_LeftRightRotation(BinaryNode* p_subtree);

        /**
         * @param p_subtree The subtree we're balancing
         * @brief Balances a subtree using a right-left rotation
         * @return Returns the new root of the subtree
         */
        static BinaryNode* ms_balance_RightLeftRotation(BinaryNode* p_subtree);

    };
}


template<typename T>
T cslib::AVLTree<T>::remove(const T& p_key) {
    // Call parent
    T temp = cslib::BSTree<T>::remove(p_key);
    this->m_root = ms_balance(this->m_root);
    return temp;
}

template<typename T>
const T& cslib::AVLTree<T>::insert(const T& p_key) {
    // Call parent
    const T& temp = m_insert(p_key);
    this->m_root = ms_balance(this->m_root);
    return temp;
}

template<typename T>
const T& cslib::AVLTree<T>::m_insert(const T& p_data) {
    return BSTree<T>::insert(p_data);
}

template<typename T>
size_t cslib::AVLTree<T>::m_depth(const BinaryNode* p_node) const {
    // Loop until we find 
    size_t i = 0;
    BinaryNode* node = this->m_root;
    while (node != p_node) {
        // Check
        if (node->data < p_node->data) {
            if (node->right == nullptr) {
                throw BSTNodeNotFound();
            }
            node = node->right;
        } else if (node->data > p_node->data) {
            if (node->left == nullptr) {
                throw BSTNodeNotFound();
            }
            node = node->left;
        } 
        // If it is equal
        else {
            break;
        }
    }

    return i;
}

template<typename T>
void cslib::AVLTree<T>::m_addSubtree(const AVLTree<T>& p_avl) {
    // We're adding the binary tree
    BSTree<T>::m_addSubtree(p_avl);
    this->m_root = ms_balance(this->m_root);
}

template<typename T>
typename cslib::AVLTree<T>::BinaryNode* cslib::AVLTree<T>::ms_balance(BinaryNode* p_subtree) {
    // If there is no subtree
    if (p_subtree == nullptr) {
        return nullptr;
    }

    // If there is only one node
    if (p_subtree->left == nullptr && p_subtree->right == nullptr) {
        return p_subtree;
    }

    Stack<BinaryNode*> last;
    last.push(nullptr);

    Stack<BinaryNode*> stack;
    stack.push(p_subtree);

    // Loop until stack is empty
    BinaryNode* root = p_subtree;
    while (!stack.empty()) {
        // Get the top of the stack
        BinaryNode* node = stack.pop();
        BinaryNode* parent = last.pop();

        BinaryNode* left = node->left;
        BinaryNode* right = node->right;

        bool isLeftEmpty  = (left  == nullptr);
        bool isRightEmpty = (right == nullptr);

        BinaryNode* center = node;

        // If we have something in both left and right
        if (isLeftEmpty || isRightEmpty){
            // Get the center of the balanced subtree
            center = ms_balanceHelper(node);

            // Place new center
            if (parent == nullptr) {
                root = center;
            } else {
                if (parent->data > center->data) {
                    parent->left = center;
                }
                if (parent->data < center->data) {
                    parent->right = center;
                }
            }
        }
        
        
        if (center->left != nullptr) {
            stack.push(center->left);
            last.push(center);
        }
        if (center->right != nullptr) {
            stack.push(center->right);
            last.push(center);
        }
    }

    return root;
}

template<typename T>
typename cslib::AVLTree<T>::BinaryNode* cslib::AVLTree<T>::ms_balanceHelper(BinaryNode* p_subtree) {
    // Get the arms
    BinaryNode* center = p_subtree;
    BinaryNode* left   = p_subtree->left;
    BinaryNode* right  = p_subtree->right;
    
    // Empty status
    bool leftNotEmpty = (left != nullptr);
    bool rightNotEmpty = (right != nullptr);

    // If this node is full, don't bother
    if (!leftNotEmpty || !rightNotEmpty) {
        // Check the left
        if (leftNotEmpty && !rightNotEmpty) {

            //     right     |                       |
            //      /        |                       |
            //   center      |    Right  Rotation    |
            //   /           |                       |
            // left          |                       |
            if (left->left != nullptr && left->right == nullptr) {
                center = ms_balance_RightRotation(center);
            }

            //     left      |                       |
            //      /        |                       |
            //   right       |  Left-Right Rotation  |
            //      \        |                       |
            //      center   |                       |
            else if (left->left == nullptr && left->right != nullptr) {
                center = ms_balance_LeftRightRotation(center);
            }
        }
        // Check the right
        else if (!leftNotEmpty && rightNotEmpty) {

            //   left        |                       |
            //     \         |                       |
            //     center    |     Left Rotation     |
            //        \      |                       |
            //       right   |                       |
            if (right->left == nullptr && right->right != nullptr) {
                center = ms_balance_LeftRotation(center);
            }

            //     left      |                       |
            //       \       |                       |
            //      right    |  Right-Left Rotation  |
            //        /      |                       |
            //     center    |                       |
            else if (right->left != nullptr && right->right == nullptr) {
                center = ms_balance_RightLeftRotation(center);
            }
        }
    }

    return center;
}

template<typename T>
typename cslib::AVLTree<T>::BinaryNode* cslib::AVLTree<T>::ms_balance_LeftRotation(BinaryNode* p_subtree) {
    //   left
    //     \
    //     center
    //        \
    //       right
    
    // Get the pointers
    BinaryNode* left   = p_subtree;
    BinaryNode* center = p_subtree->right;
    BinaryNode* right  = p_subtree->right->right;

    //     center
    //      /  \
    //   left right

    left->right = center->left;
    center->left = left;

    // Return new root
    return center;
}

template<typename T>
typename cslib::AVLTree<T>::BinaryNode* cslib::AVLTree<T>::ms_balance_RightRotation( BinaryNode* p_subtree) {
    //     right
    //      /
    //   center
    //   /
    // left 

    // Get the pointers
    BinaryNode* right  = p_subtree;
    BinaryNode* center = p_subtree->left;
    BinaryNode* left   = p_subtree->left->left;

    //     center
    //      /  \
    //   left right

    right->left = center->right;
    center->right = right;

    return center;
}

template<typename T>
typename cslib::AVLTree<T>::BinaryNode* cslib::AVLTree<T>::ms_balance_LeftRightRotation(BinaryNode* p_subtree) {
    //     right
    //      /
    //    left
    //      \
    //      center

    BinaryNode* right = p_subtree;
    BinaryNode* left = p_subtree->left;
    BinaryNode* center = p_subtree->left->right;

    //     center
    //      /  \
    //   left right
    right->left = center->right;
    left->right = center->left;

    center->right = right;
    center->left = left;

    return center;
}

template<typename T>
typename cslib::AVLTree<T>::BinaryNode* cslib::AVLTree<T>::ms_balance_RightLeftRotation(BinaryNode* p_subtree) {
    // left
    //   \ 
    //  right
    //    /
    // center
    BinaryNode* left = p_subtree;
    BinaryNode* right = p_subtree->right;
    BinaryNode* center = p_subtree->right->left;
    
    //     center
    //      /  \
    //   left right
    left->right = center->left;
    right->left = center->right;

    center->left = left;
    center->right = right;

    return center;
}




#endif