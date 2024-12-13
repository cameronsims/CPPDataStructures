/**
 * @file Set.h
 * @brief Holds the Set data structure
 **/
#ifndef CSSET_H
#define CSSET_H

#include "Universal.h"
#include "AVLTree.h"

namespace cslib {

    /**
     * @class Set
     * @tparam T The type of the data structure
     * @brief A Set containing a list of some sort of unique data
     **/
    template<typename T>
    class Set : public AVLTree<T> {
    public:
        /**
         * @param p_set The right hand side of the set
         * @brief Gets all values between two sets
         * @return Returns the set
         */
        Set<T> unionise(const Set<T>& p_set) const;

        /**
         * @param p_set The right hand side of the set
         * @brief Gets values which are between both sets
         * @return Returns the set
         */
        Set<T> intersection(const Set<T>& p_set) const;

        /**
         * @param p_set The right hand side of the set
         * @brief Gets the left hand side
         * @return Returns the set
         */
        Set<T> difference(const Set<T>& p_set) const;
    protected:
        /// The binary node of parent
        typedef AVLTree<T>::BinaryNode BinaryNode;
    };
}

template<typename T>
cslib::Set<T> cslib::Set<T>::unionise(const Set<T>& p_set) const {
    // Get the two types of set
    const cslib::Set<T>& right = p_set;
    const cslib::Set<T>& left = (*this);
    
    // If either is empty, return the other.
    if (left.empty()) {
        return right;
    }
    if (right.empty()) {
        return left;
    }
    
    // Copy the left hand side
    Set<T> uni = left;

    // Add in right
    Stack<BinaryNode*> stack;
    stack.push(right.m_root); 
    while (!stack.empty()) {
        // Get the data
        BinaryNode* node = stack.pop();
        
        // If it is in the set already.
        bool inSet = BSTree_contains<T>(uni, node->data);
        // Add it if doesn't exist
        if (!inSet) {
            uni.insert(node->data);
        }

        // If there is children
        if (node->left != nullptr)  { 
            stack.push(node->left); 
        }
        if (node->right != nullptr) { 
            stack.push(node->right); 
        }
    }

    return uni;
}

template<typename T>
cslib::Set<T> cslib::Set<T>::intersection(const Set<T>& p_set) const {
    // Short hands
    const Set<T>& left = (*this);
    const Set<T>& right = p_set;

    // Copy the left hand side
    Set<T> intsect;

    // Add in right
    Stack<BinaryNode*> lstack;
    Stack<BinaryNode*> rstack;
    lstack.push(left .m_root);
    rstack.push(right.m_root);

    while (!lstack.empty() || !rstack.empty()) {
        // Get the data
        BinaryNode* lnode = nullptr; 
        if (!lstack.empty()) {
            lnode = lstack.pop();
        }

        BinaryNode* rnode = nullptr; 
        if (!rstack.empty()) {
            rnode = rstack.pop();
        }

        struct SaveOurStack {
            bool nodesUnique : 4;
            bool rightInSet : 1;
            bool rightInLeft : 1;
            bool leftInSet : 1;
            bool leftInRight : 1;
        };

        SaveOurStack b;
        b.nodesUnique = false;
        b.rightInSet = false;
        b.rightInLeft = false;
        b.leftInSet = false;
        b.leftInRight = false;
        
        // Check if it exists
        if (lnode != nullptr && rnode != nullptr) {
            b.nodesUnique = (lnode->data != rnode->data);
        }

        // If only one exists
        else if ((lnode == nullptr && rnode != nullptr) || (lnode != nullptr && rnode == nullptr)) {
            b.nodesUnique = true;
        }

        // Check if it exists in both
        // If right is not empty
        if (rnode != nullptr) {
            b.rightInSet = BSTree_contains(intsect, rnode->data);
            b.rightInLeft = BSTree_contains(left, rnode->data);
            
            if (!b.rightInSet && b.rightInLeft && b.nodesUnique) {
                intsect.insert(rnode->data);
            }

            // If there is children
            if (rnode->left != nullptr) {
                rstack.push(rnode->left);
            }
            if (rnode->right != nullptr) {
                rstack.push(rnode->right);
            }
        }
        if (lnode != nullptr) {
            b.leftInSet = BSTree_contains(intsect, lnode->data);
            b.leftInRight = BSTree_contains(right, lnode->data);
            
            if (!b.leftInSet && b.leftInRight) {
                intsect.insert(lnode->data);
            }

            // If there is children
            if (lnode->left != nullptr) {
                lstack.push(lnode->left);
            }
            if (lnode->right != nullptr) {
                lstack.push(lnode->right);
            }
        }
    }

    return intsect;
}

template<typename T>
cslib::Set<T> cslib::Set<T>::difference(const Set<T>& p_set) const {
    // Short hands
    const Set<T>& left = (*this);
    const Set<T>& right = p_set;
    
    // If there is nothing in the left, return nothing
    if (left.empty()) {
        return left;
    }

    // If there is nothing in the right, just return left
    if (right.empty()) {
        return left;
    }

    // Difference
    Set<T> dif;

    // Check all left nodes to ensure it doesn't exist in right
    Stack<BinaryNode*> stack;
    stack.push(left.m_root);
    while (!stack.empty()) {
        // Get the data
        BinaryNode* node = stack.pop();

        // If it is in the set already.
        bool inRight = BSTree_contains(right, node->data);
        // Add it if doesn't exist
        if (!inRight) {
            dif.insert(node->data);
        }

        // If there is children
        if (node->left != nullptr) {
            stack.push(node->left);
        }
        if (node->right != nullptr) {
            stack.push(node->right);
        }
    }

    return dif;
}

#endif