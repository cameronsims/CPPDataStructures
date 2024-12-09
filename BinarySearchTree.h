/**
 * @file BinarySearchTree.h
 * @brief Holds the BinarySearchTree structure.
 **/

#ifndef CSBINARYSEARCHTREE_H
#define CSBINARYSEARCHTREE_H

#include "Universal.h"

namespace cslib {

    /**
     * @class BSTNodeException
     * @brief Base for all exceptions thrown by the binary search tree
     **/
    class BSTNodeException : public Exception {
        const char* what() const throw();
    };

    /**
     * @class BSTNodeExists
     * @brief Thrown when a node exists when we're trying to insert it.
     **/
    class BSTNodeExists : public BSTNodeException {
        const char* what() const throw();
    };

    /**
     * @class BSTNodeNotFound
     * @brief Used when a node we're looking for / trying to delete doesn't exist.
     **/
    class BSTNodeNotFound : public BSTNodeException {
        const char* what() const throw();
    };
    
    /**
     * @class BinarySearchTree
     * @tparam T The type of the data structure
     * @brief An unbalanced binary tree structure
     **/
    template<typename T>
    class BinarySearchTree {
    public:
        /**
         * @brief Constructs the class
         */
        BinarySearchTree();

        /**
         * @param p_bst The Binary Search Tree we're copying  
         * @brief Copies the right bst into the left
         */
        BinarySearchTree(const BinarySearchTree<T>& p_bst);

        /**
         * @param p_bst The Binary Search Tree we're copying
         * @brief Copies the right bst into the left
         * @return Returns "this" binary search tree we've just copied
         */
        BinarySearchTree<T>& operator= (const BinarySearchTree<T>& p_bst);

        /**
         * @brief Destructs the class
         */
        ~BinarySearchTree();

        /**
         * @param p_key The data we're looking for
         * @brief Searches for the key, returns the entire value of the key
         * @return Returns the value when we find it
         */
        const T& search(const T& p_key) const;

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

        /**
         * @tparam TF The function type that we're going to play
         * @param p_func The function we're going to play when we go past a node
         * @brief Plays the tree in order (1->2->3->4)
         */
        template<typename TF>
        void inorder  (TF&& p_func) const;

        /**
         * @tparam TF The function type that we're going to play
         * @param p_func The function we're going to play when we go past a node
         * @brief Plays the tree, center first, left and then right.
         */
        template<typename TF>
        void preorder (TF&& p_func) const;

        /**
         * @tparam TF The function type that we're going to play
         * @param p_func The function we're going to play when we go past a node
         * @brief Plays the tree, left then right then center.
         */
        template<typename TF>
        void postorder(TF&& p_func) const;

        /**
         * @tparam TF The function type that we're going to play
         * @param p_func The function we're going to play when we go past a node
         * @brief Plays the tree, goes down each subtree by each subtree.
         */
        template<typename TF>
        void depthFirst(TF&& p_func) const;

        /**
         * @tparam TF The function type that we're going to play
         * @param p_func The function we're going to play when we go past a node
         * @brief Plays the tree, goes down in a queue each layer by each layer.
         */
        template<typename TF>
        void breadthFirst(TF&& p_func) const;

        /**
         * @brief Gets the depth of the tree, 0 = one node, 1 = 2-3 nodes
         * @return The depth of the tree
         */
        size_t depth () const;

        /**
         * @brief Gets the amount of nodes in the tree
         * @return The amount of nodes in the tree
         */
        size_t amount() const;

        /**
         * @brief Clears the tree of all contents
         */
        void clear();
    
    protected:
        /**
         * @struct BinaryNode
         * @brief Each node in the tree
         **/
        struct BinaryNode {
            /// The data value that represents the node
            T data;

            /// The node to the left of this node (will be smaller)
            BinaryNode* left;

            /// The node to the right of this node (will be bigger)
            BinaryNode* right;
        };

        /**
         * @param p_bst The binary search tree we are copying
         * @brief Copies the entire binary search tree
         */
        void m_copy(const BinarySearchTree<T>& p_bst);
        
        /**
         * @brief Delete all the tree
         */
        void m_delete();

        /**
         * @param p_key Creates a new node with the node
         * @brief Copies the entire binary search tree
         * @return Returns the pointer to a new node
         */
        BinaryNode* m_create(const T& p_key);
    
        /// The root of the tree, where we start.
        BinaryNode* m_root;
    
    };

    /**
     * @fn BinarySearchTree_contains
     * @tparam T The type of the binary tree
     * @param p_bst Binary Search Tree that we're reading
     * @param p_data The data we're trying to find
     * 
     * @brief Used to see if the binary search tree contains something without throwing an error
     * @return True if it exists, false if it doesn't
     */
    template<typename T>
    bool BinarySearchTree_contains(const BinarySearchTree<T>& p_bst, const T& p_data);


}

#include "Vector.h"
#include "Stack.h"
#include "Queue.h"

const char* cslib::BSTNodeException::what() const throw() { return "Node Exception."; }
const char* cslib::BSTNodeExists::what() const throw() { return "Node exists."; }
const char* cslib::BSTNodeNotFound::what() const throw() { return "Node not found."; }

template<typename T>
cslib::BinarySearchTree<T>::BinarySearchTree() : m_root(nullptr) {
    
}

template<typename T>
cslib::BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& p_bst) {
    m_delete();
    m_copy(p_bst);
}

template<typename T>
cslib::BinarySearchTree<T>& cslib::BinarySearchTree<T>::operator= (const BinarySearchTree<T>& p_bst) {
    m_delete();
    m_copy(p_bst);
}

template<typename T>
cslib::BinarySearchTree<T>::~BinarySearchTree() {
    // Delete all...
    m_delete();
}

template<typename T>
const T& cslib::BinarySearchTree<T>::search(const T& p_key) const {
    // If empty
    if (this->m_root == nullptr) {
        throw BSTNodeNotFound();
    }

    // Search until we find a root
    BinaryNode* node = this->m_root;
    while (node != nullptr) {
        if (node->data < p_key) { 
            node = node->right;
        }
        else if (node->data > p_key) {
            node = node->left;
        } else {
            return node->data;
        }
    }

    throw BSTNodeNotFound();
}

template<typename T>
T cslib::BinarySearchTree<T>::remove(const T& p_key) {
    // Create node
    BinaryNode* node = this->m_create(p_key);

    // If empty
    if (this->m_root == nullptr) {                
        throw BSTNodeNotFound();
    }

    // First we start off at the root and slowly make our way down the tree...
    BinaryNode* last = this->m_root;
    BinaryNode* current = this->m_root;
    while (current != nullptr) {
        // If the data is equal.
        if (current->data == p_key) {
            // Get the left and right of our old 
            BinaryNode* left = current->left;
            BinaryNode* right = current->right;

            bool isLeft = (last->left == current);
            bool isRight = (last->right == current);

            delete current;
            current = nullptr;
            
            // If the data was on the left of the last node
            if (isLeft) {
                last->left = left;

                current = last->left;
                while (current != nullptr) {
                    last = current;
                    current = current->right;
                }

                last->right = right;

                return p_key;
            }

            // If the data was on the right of the last node
            else if (isRight) {
                last->right = right;

                current = last->right;
                while (current->left != nullptr) {
                    last = current;
                    current = current->left;
                }

                last->left = right;
            }
        }

        else if (current->data > p_key) {
            last = current;
            current = current->left;
        }

        else if (current->data < p_key) {
            last = current;
            current = current->right;
        }
    }

    throw BSTNodeNotFound();
}

template<typename T>
const T& cslib::BinarySearchTree<T>::insert(const T& p_key) {
    // Create node
    BinaryNode* node = this->m_create(p_key);

    // If empty
    if (this->m_root == nullptr) {   
        // Create new                
        this->m_root = node;
        return node->data;
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
                return node->data;;
            }
            current = current->left;

        }
        
        else if (current->data < node->data) {
            // If right is null...
            if (current->right == nullptr) {
                // Set it
                current->right = node;
                return node->data;
            }

            current = current->right;

        } 
        
        else {
            throw BSTNodeExists();
        }
    }

    throw BSTNodeExists();
    
}

template<typename T> template<typename TF>
void cslib::BinarySearchTree<T>::inorder(TF&& p_func) const {
    // If empty
    if (this->m_root == nullptr) {
        return;
    }
    
    // First, we want to add our root
    const size_t nodeSize = this->amount();
    Stack<BinaryNode*> stack;
    Vector<BinaryNode*> visited(nodeSize);

    stack  .push(this->m_root);
    visited.push(this->m_root);

    // If the address is in the vector.
    auto exists = [&](const BinaryNode* p) {
        for (size_t i = 0; i < visited.size(); i++) {
            if (visited[i] == p) {
                return true;
            }
        }
        return false;
    };

    while (!stack.empty()) {
        // First we will check if the top of the stack has any left nodes.
        BinaryNode* node = stack.top();

        // If it does have a left node, we will play that first.
        if (node->left != nullptr && !exists(node->left)) {
            stack.push(node->left);
            visited.push(node->left);
        }

        // If we do not have antoher node to the left
        else {
            // Play "this node"
            stack.pop();
            p_func(node->data);

            // Add the right to the stack...
            if (node->right != nullptr) {
                stack.push(node->right);
                visited.push(node->right);
            }
        }
    }
}

template<typename T> template<typename TF>
void cslib::BinarySearchTree<T>::preorder(TF&& p_func) const {
    // If empty
    if (this->m_root == nullptr) {
        return;
    }

    // Root -> Left -> Right
    Stack<BinaryNode*> stack;
    stack.push(this->m_root);

    while (!stack.empty()) {
        // This node
        BinaryNode* node = stack.pop();
        p_func(node->data);

        // If there is values to the left...
        if (node->right != nullptr) {
            stack.push(node->right);
        }
        if (node->left != nullptr) {
            // Add these to the queue
            stack.push(node->left);
        }
    }

}

template<typename T> template<typename TF>
void cslib::BinarySearchTree<T>::postorder(TF&& p_func) const {
    // If empty
    if (this->m_root == nullptr) {
        return;
    }

    // Left->Right->Root
    Stack<BinaryNode*> stack;
    stack.push(this->m_root);

    Vector<BinaryNode*> visited( this->amount() );
    visited.push(this->m_root);

    auto exists = [&](const BinaryNode* p) {
        for (size_t i = 0; i < visited.size(); i++) {
            if (visited[i] == p) {
                return true;
            }
        }
        return false;
    };

    while (!stack.empty()) {
        BinaryNode* node = stack.top();

        bool goRight = node->right != nullptr && !exists(node->right);
        bool goLeft = node->left != nullptr && !exists(node->left);

        if (goRight) {
            stack.push(node->right);
            visited.push(node->right);
        }

        if (goLeft) {
            stack.push(node->left);
            visited.push(node->left);
        }

        if (!goRight && !goLeft) {
            node = stack.pop();
            p_func(node->data);
        }
    }
}

template<typename T> 
template<typename TF>
void cslib::BinarySearchTree<T>::depthFirst(TF&& p_func) const {
    // If not empty
    if (this->m_root == nullptr) {
        return;
    }

    // Stack based search
    Stack<BinaryNode*> stack;
    stack.push(this->m_root);

    while (!stack.empty()) {
        // POp the stack
        BinaryNode* node = stack.pop();

        p_func(node->data);

        // Add both the children to the stack
        if (node->right != nullptr) {
            stack.push(node->right);
        }
        if (node->left != nullptr) {
            stack.push(node->left);
        }
    }
}

template<typename T> 
template<typename TF>
void cslib::BinarySearchTree<T>::breadthFirst(TF&& p_func) const {
    // If we have no data...
    if (this->m_root == nullptr) {
        return;
    }

    // Queue based search
    Queue<BinaryNode*> queue;

    // Add the root node.
    queue.enqueue(this->m_root);
    while (!queue.empty()) {
        // Get top node
        BinaryNode* node = queue.dequeue();

        // Play the function
        p_func(node->data);

        if (node->left != nullptr) {
            queue.enqueue(node->left);
        }
        if (node->right != nullptr) {
            queue.enqueue(node->right);
        }
    }
}

template<typename T>
size_t cslib::BinarySearchTree<T>::depth() const {
    if (this->m_root == nullptr) {
        throw BSTNodeNotFound();
    }

    // Loop for all depths
    struct Depth { 
        size_t depth; 
        BinaryNode* node;
    };

    Stack<Depth> stack;
    Depth depth;
    depth.depth = 0;
    depth.node = this->m_root;
    stack.push(depth);

    size_t max = 0;

    // While we have nodes to look at
    while (!stack.empty()) {
        depth = stack.pop();
        BinaryNode* node = depth.node;

        if (max < depth.depth) {
            max = depth.depth;
        }

        if (node->left != nullptr) { 
            Depth newDepth;
            newDepth.node = node->left;
            newDepth.depth = depth.depth + 1;
            stack.push(newDepth);  
        }
        if (node->right != nullptr) { 
            Depth newDepth;
            newDepth.node = node->right;
            newDepth.depth = depth.depth + 1;
            stack.push(newDepth);
        }
    }

    return max;
}

template<typename T>
size_t cslib::BinarySearchTree<T>::amount() const {
    // Function to calc 
    size_t n = 0;

    // Get all nodes via breath first.
    
    // If we have no data...
    if (this->m_root == nullptr) {
        return 0;
    }

    // Queue based search
    Queue<BinaryNode*> queue;

    // Add the root node.
    queue.enqueue(this->m_root);
    while (!queue.empty()) {
        // Get top node
        BinaryNode* node = queue.dequeue();

        n++;

        if (node->left != nullptr) {
            queue.enqueue(node->left);
        }
        if (node->right != nullptr) {
            queue.enqueue(node->right);
        }
    }

    return n;
}

template<typename T>
void cslib::BinarySearchTree<T>::clear() {
    this->m_delete();
}

template<typename T>
void cslib::BinarySearchTree<T>::m_copy(const BinarySearchTree<T>& p_bst) {
    // If we have no data...
    if (p_bst.m_root == nullptr) {
        return;
    }

    // Queue based search
    Queue<BinaryNode*> lqueue;
    Queue<BinaryNode*> rqueue;

    // Add the root node.
    rqueue.enqueue(p_bst.m_root);

    this->m_root = m_create(p_bst.m_root->data);
    lqueue.enqueue(p_bst.m_root);

    while (!rqueue.empty()) {
        // Get top node
        BinaryNode* rnode = rqueue.dequeue();
        BinaryNode* lnode = lqueue.dequeue();

        if (rnode->left != nullptr) {
            rqueue.enqueue(rnode->left);

            lnode->left = m_create(rnode->left->data);
            lqueue.enqueue(lnode->left);
        }
        if (rnode->right != nullptr) {
            rqueue.enqueue(rnode->right);

            lnode->right = m_create(rnode->right->data);
            lqueue.enqueue(lnode->right);
        }
    }
}

template<typename T>
void cslib::BinarySearchTree<T>::m_delete() {
    // If we have no data...
    if (this->m_root == nullptr) {
        return;
    }

    // Queue based search
    Queue<BinaryNode*> queue;

    // Add the root node.
    queue.enqueue(this->m_root);
    while (!queue.empty()) {
        // Get top node
        BinaryNode* node = queue.dequeue();
        if (node->left != nullptr) {
            queue.enqueue(node->left);
        }
        if (node->right != nullptr) {
            queue.enqueue(node->right);
        }
        
        delete node;
    }

    this->m_root = nullptr;
}

template<typename T>
typename cslib::BinarySearchTree<T>::BinaryNode* cslib::BinarySearchTree<T>::m_create(const T& p_key) {
    // Create node
    BinaryNode* node = new BinaryNode;
    node->data = p_key;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}


template<typename T>
bool cslib::BinarySearchTree_contains(const BinarySearchTree<T>& p_bst, const T& p_data) {
    // Search the tree and return false if not
    try {
        p_bst.search(p_data);
    } catch (const BSTNodeNotFound&) {
        return false;
    }

    return true;
}



#endif