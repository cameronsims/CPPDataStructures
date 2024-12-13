/**
 * @file Map.h
 * @brief Holds the Map structure.
 **/

#ifndef CSMAP_H
#define CSMAP_H

#include "Universal.h"

#include "AVLTree.h"

namespace cslib {
    /**
     * @struct MapNode
     * @tparam T1 The key of the data structure
     * @tparam T2 The data relating to the key of the data structure
     * @brief Node for the map
     **/
    template<typename T1, typename T2>
    struct MapNode {
        /// The key
        T1 key;

        /// The data
        T2 data;

        /**
         * @param right The right hand of the equation
         * @brief Used if the node's key is equal to the other
         **/
        bool operator==(const MapNode& right);

        /**
         * @param right The right hand of the equation
         * @brief Used if the node's key are not equal to the other
         **/
        bool operator!=(const MapNode& right);

        /**
         * @param right The right hand of the equation
         * @brief Used if the node's key is smaller to the other
         **/
        bool operator< (const MapNode& right);

        /**
         * @param right The right hand of the equation
         * @brief Used if the node's key is smaller or equal to the other
         **/
        bool operator<=(const MapNode& right);

        /**
         * @param right The right hand of the equation
         * @brief Used if the node's key is bigger to the other
         **/
        bool operator> (const MapNode& right);

        /**
         * @param right The right hand of the equation
         * @brief Used if the node's key is bigger or equal to the other
         **/
        bool operator>=(const MapNode& right);
    };
    
    /**
     * @class Map
     * @tparam T1 The key of the data structure
     * @tparam T2 The data relating to the key of the data structure
     * @brief A balanced map structure
     **/
    template<typename T1, typename T2>
    class Map : protected AVLTree<MapNode<T1, T2>> {
    public:

        /**
         * @param p_key The key that we're using to find
         * @brief Returns the value using the key
         **/
        T2& operator[](const T1& p_key);

        /**
         * @param p_key The key that we're using to find
         * @brief Returns the value using the key
         **/
        const T2& operator[](const T1& p_key) const;

        /**
         * @brief Returns the amount of nodes
         **/
        size_t size() const;

        /**
         * @brief Returns a vector full of keys
         **/
        Vector<const T1&> keys() const;

        /**
         * @brief Returns a vector full of values
         **/
        Vector<const T2&> values() const;

    protected:
        /// The internal data structure
        typedef MapNode<T1, T2> MapNode;

        /// The structure used in the avl tree
        typedef AVLTree<MapNode>::BinaryNode BinaryNode;

        /**
         * @param p_key The key we're looking for
         * @brief Returns a value to the value in the tree
         * @return Returns the data relating to the keys
         **/
        T2& m_insert(const T1& p_key);
    };
}


template<typename T1, typename T2>
bool cslib::MapNode<T1, T2>::operator==(const cslib::MapNode<T1, T2>& right) {
    const MapNode& left = (*this);
    return (left.key == right.key);
}

template<typename T1, typename T2>
bool cslib::MapNode<T1, T2>::operator!=(const cslib::MapNode<T1, T2>& right) {
    const MapNode& left = (*this);
    return !(left == right);
}

template<typename T1, typename T2>
bool cslib::MapNode<T1, T2>::operator< (const cslib::MapNode<T1, T2>& right) {
    const MapNode& left = (*this);
    return left.key < right.key;
}

template<typename T1, typename T2>
bool cslib::MapNode<T1, T2>::operator<=(const cslib::MapNode<T1, T2>& right) {
    const MapNode& left = (*this);
    return !(left.key > right.key);
}

template<typename T1, typename T2>
bool cslib::MapNode<T1, T2>::operator> (const cslib::MapNode<T1, T2>& right) {
    const MapNode& left = (*this);
    return left.key > right.key;
}

template<typename T1, typename T2>
bool cslib::MapNode<T1, T2>::operator>=(const cslib::MapNode<T1, T2>& right) {
    const MapNode& left = (*this);
    return !(left.key < right.key);
}

template<typename T1, typename T2>
T2& cslib::Map<T1, T2>::operator[](const T1& p_key) {

    // If empty
    if (this->m_root == nullptr) {
        return this->m_insert(p_key);
    }

    // Search until we find a root
    BinaryNode* node = this->m_root;
    while (node != nullptr) {
        if (node->data.key < p_key) {
            node = node->right;
        } else if (node->data.key > p_key) {
            node = node->left;
        } else {
            return node->data.data;
        }
    }

    return this->m_insert(p_key);
}

template<typename T1, typename T2>
const T2& cslib::Map<T1, T2>::operator[](const T1& p_key) const {
    // If empty
    if (this->m_root == nullptr) {
        throw BSTNodeNotFound();
    }

    // Search until we find a root
    BinaryNode* node = this->m_root;
    while (node != nullptr) {
        if (node->data.key < p_key) {
            node = node->right;
        } else if (node->data.key > p_key) {
            node = node->left;
        } else {
            return node->data.data;
        }
    }

    throw BSTNodeNotFound();
}

template<typename T1, typename T2>
size_t cslib::Map<T1, T2>::size() const {
    // The amount of nodes.
    return this->amount();
}

template<typename T1, typename T2>
cslib::Vector<const T1&> cslib::Map<T1, T2>::keys() const {
    // The vector full of keys
    const size_t size = this->amount();
    Vector<const T1&> keys(size);

    // Get all the keys
    this->inorder([&](const MapNode& node) {
        keys.push(node.key);
    });
    return keys;
}

template<typename T1, typename T2>
cslib::Vector<const T2&> cslib::Map<T1, T2>::values() const {
    // The vector full of keys
    const size_t size = this->amount();
    Vector<const T2&> vals(size);

    // Get all the keys
    this->inorder([&](const MapNode& node) {
        vals.push(node.data);
    });
    return vals;
}

template<typename T1, typename T2>
T2& cslib::Map<T1, T2>::m_insert(const T1& p_key) {
    // Create node
    MapNode mapnode;
    mapnode.key = p_key;
    mapnode.data = T2();
    BinaryNode* node = BSTree<MapNode>::m_create(mapnode);

    // If empty
    if (this->m_root == nullptr) {
        // Create new                
        this->m_root = node;
        return node->data.data;
    }

    // Check if we need to go left or right, check for all nodes until we find
    BinaryNode* current = this->m_root;
    while (current != nullptr) {

        // Check the values.
        if (current->data > node->data) {
            // If left is null...
            if (current->left == nullptr) {
                // Set it
                current->left = node;
                return node->data.data;
            }
            current = current->left;

        }

        else if (current->data < node->data) {
            // If right is null...
            if (current->right == nullptr) {
                // Set it
                current->right = node;
                return node->data.data;
            }

            current = current->right;

        }

        else {
            throw BSTNodeExists();
        }
    }

    throw BSTNodeExists();
}

#endif