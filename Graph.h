/**
 * @file Graph.h
 * @brief Holds the Graph Data Structure, non-linear data strucutre. Represents nodes and connections.
 **/

#ifndef CSGRAPH_H
#define CSGRAPH_H

#include "Universal.h"
#include "Vector.h"
#include "LinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "BSTree.h"

namespace cslib {
    /**
     * @class GraphException
     * @brief Base for all exceptions thrown by the graph
     **/
    class GraphException : public Exception {
    public:
        const char* what() const throw();
    };

    /**
     * @class GraphNodeException
     * @brief Base for all node exceptions thrown by the graph 
     **/
    class GraphNodeException : public GraphException {
    public:
        const char* what() const throw();
    };
    
    /**
     * @class GraphNodeNotFound
     * @brief Used when we can't find a node that was requested.
     **/
    class GraphNodeNotFound : public GraphNodeException {
    public:
        const char* what() const throw();
    };

    /**
     * @class GraphNodeCantCreate
     * @brief Thrown when we can't create the node
     **/
    class GraphNodeCantCreate : public GraphNodeException {
    public:
        const char* what() const throw();
    };

    /**
     * @class GraphConnectionException
     * @brief Base for all connection exceptions thrown by the graph
     **/
    class GraphConnectionException : public GraphException {
    public:
        const char* what() const throw();
    };

    /**
     * @class GraphConnectionNotFound
     * @brief Thrown when we can't find a connection
     **/
    class GraphConnectionNotFound : public GraphConnectionException {
    public:
        const char* what() const throw();
    };

    /**
     * @class GraphBasic
     * @tparam T Type of the data structure.
     * @brief A basic graph data structure, used to be the base for real graphs.
     **/
    template<typename T>
    class GraphBasic {
    public:
        /**
         * @brief Returns the size of the data structure
         * @return Returns the size of the data structure.
         */
        virtual size_t size() const = 0;

        /**
         * @param p_data The data we're inserting into the graph
         *
         * @brief Insert a value into the graph 
         * @return Returns the id of the node
         */
        virtual size_t insert(const T& p_data) = 0;

        /**
         * @param p_index The index of the node we want to delete
         *
         * @brief Delete a value from the graph
         */
        virtual void   remove(size_t p_index) = 0;

        /**
         * @param p_left The id of the first node we're connecting (if directed, the origin)
         * @param p_right The id of the second node we're connecting (if directed, the destination.)
         * @param p_directed If we want to make a one-way connection (false by default)
         *
         * @brief Connect into the node of two nodes
         */
        virtual void   connect(size_t p_left, size_t p_right, bool p_directed = false) = 0;

        /**
         * @param p_left The id of the first node we're connecting (if directed, the origin)
         * @param p_right The id of the second node we're connecting (if directed, the destination.)
         * @param p_directed If we want to delete both ways (false by default)
         *
         * @brief Disconnect into the node of two nodes
         */
        virtual void   disconnect(size_t p_left, size_t p_right, bool p_removeBoth = false) = 0;

        /**
         * @param p_index The index of the id we're getting the neighbours for.
         *
         * @brief Gets the ids of the neighbours of a node.
         * @return Returns the linked list of ids 
         */
        virtual LinkedList<size_t>& neighbours(size_t p_index) = 0;

        /**
         * @param p_index The index of the id we're getting the neighbours for.
         *
         * @brief Gets the ids of the neighbours of a node.
         * @return Returns the linked list of ids
         */
        virtual const LinkedList<size_t>& neighbours(size_t p_index) const = 0;

        /**
         * @param p_index The index of the id we're getting
         *
         * @brief Gets the node of the id we're looking for
         * @return Gets the value of the node
         */
        virtual T& operator[](size_t p_id) = 0;

        /**
         * @param p_index The index of the id we're getting
         *
         * @brief Gets the node of the id we're looking for
         * @return Gets the value of the node
         */
        virtual const T& operator[](size_t p_id) const = 0;

    protected:
        /**
         * @class Node
         * @brief A node in the graph
         **/
        struct Node {
            /// The data of the node
            T data;

            /// The connections, size_t is the node id
            LinkedList<size_t> connections;
        };

        /**
         * @param p_data The data we're creating.
         *
         * @brief Creates a new node
         * @return Return the node we just created
         */
        virtual Node* m_create(const T& p_data) = 0;

        /// The nodes in the graph
        Vector<Node*> m_nodes;
    };

    /**
     * @class Graph
     * @tparam T Type of the data structure.
     * @brief A functional directed graph.
     **/
    template<typename T>
    class Graph : public GraphBasic<T> {
    public:
        /**
         * @brief Creates the graph
         */
        Graph();

        /**
         * @param p_graph The graph we're copying.
         *
         * @brief Creates a graph and copies the graph.
         */
        Graph(const Graph<T>& p_graph);

        /**
         * @param p_graph The graph we're copying.
         *
         * @brief Creates a graph and copies the graph.
         * @return Returns the graph of "this"
         */
        Graph<T>& operator= (const Graph<T>& p_graph);

        /**
         * @brief Deletes the object
         */
        ~Graph();

        size_t size() const;

        size_t insert(const T& p_data);
        void   remove(size_t p_index);

        void   connect(size_t p_left, size_t p_right, bool p_directed = false);
        void   disconnect(size_t p_left, size_t p_right, bool p_removeBoth = false);

        LinkedList<size_t>& neighbours(size_t p_index);
        const LinkedList<size_t>& neighbours(size_t p_index) const;

        /**
         * @tparam TF The function type
         * @param p_start The node we're starting from
         * @param p_func The function that we are using when we read the nodes.
         *
         * @brief Views the graphs, goes as far deep as possible. Doesn't visited visited nodes.
         */
        template<typename TF>
        void depthFirst(size_t p_start, TF&& p_func) const;

        /**
         * @tparam TF The function type
         * @param p_start The node we're starting from
         * @param p_func The function that we are using when we read the nodes.
         *
         * @brief Views the graphs, visits neighbours and once that is finished their neighbours, etc.
         */
        template<typename TF>
        void breadthFirst(size_t p_start, TF&& p_func) const;

        T& operator[](size_t p_id);
        const T& operator[](size_t p_id) const;
    protected:
        /// The node in the Graph 
        typedef GraphBasic<T>::Node Node;

        /**
         * @param p_graph The graph we're copying.
         *
         * @brief Copies the graph.
         */
        void m_copy(const Graph<T>& p_graph);
        Node* m_create(const T& p_data);
    };
}

const char* cslib::GraphException::what() const throw() {
    return "Graph Exception!";
}

const char* cslib::GraphNodeException::what() const throw() {
    return "Graph Node Exception!";
}
const char* cslib::GraphNodeNotFound::what() const throw() {
    return "Graph Node Not Found!";
}
const char* cslib::GraphNodeCantCreate::what() const throw() {
    return "Graph Node could not be created!";
}

const char* cslib::GraphConnectionException::what() const throw() {
    return "Graph Connection Exception!";
}
const char* cslib::GraphConnectionNotFound::what() const throw() {
    return "Graph Connection Not Found!";
}

template<typename T>
cslib::Graph<T>::Graph() {

}

template<typename T>
cslib::Graph<T>::Graph(const Graph<T>& p_graph) {
    this->m_copy(p_graph);
}

template<typename T>
cslib::Graph<T>& cslib::Graph<T>::operator= (const Graph<T>& p_graph) {
    this->m_copy(p_graph);
    return (*this);
}

template<typename T>
cslib::Graph<T>::~Graph() {
    // Delete all 
    for (size_t i = 0; i < this->m_nodes.size(); i++) {
        delete this->m_nodes[i];
    }
}

template<typename T>
size_t cslib::Graph<T>::size() const {
    return this->m_nodes.size();
}

template<typename T>
size_t cslib::Graph<T>::insert(const T& p_data) {
    // Create node
    Node* node = this->m_create(p_data);
    
    // If the size of the value is 0...
    const size_t size = this->m_nodes.size();
    if (size == 0) {
        this->m_nodes.push(node);
        return 0;
    }

    // Otherwise, we will search through every element
    size_t i;
    for (i = 0; i < size; i++) {
        if (this->m_nodes[i] == nullptr) {
            this->m_nodes[i] = node;
            return i;
        }
    }

    this->m_nodes.push(node);
    return size;
}

template<typename T>
void cslib::Graph<T>::remove(size_t p_index) {
    // If size is bad
    size_t size = this->m_nodes.size();
    if (size == 0 || p_index >= size) {
        throw GraphNodeNotFound();
    }

    // Get the pointer
    Node* node = this->m_nodes[p_index];
    for (size_t i = 0; i < size; i++) {
        // This node 
        Node* current = this->m_nodes[i];
        // If the value isn't null
        if (current != nullptr) {
            // Remove all mentions of this node, in this node's connections
            LinkedList<size_t>& cons = current->connections;
            Queue<size_t> indexes;

            // Add all indexes into the queue
            size_t i = 0;
            for (LinkedList<size_t>::ConstIterator it = cons.cbegin(); it != cons.cend(); ++it) {
                // If it is equal to the value
                if (*it == p_index) {
                    size_t n = indexes.size();
                    indexes.enqueue(i - n);
                }
                i++;
            }

            // Now remove it from the linked list.
            while (!indexes.empty()) {
                size_t index = indexes.dequeue();
                cons.remove(index);
            }
        }
    }

    // Delete and set node to zero
    delete this->m_nodes[p_index];
    this->m_nodes[p_index] = nullptr;
}

template<typename T>
void cslib::Graph<T>::connect(size_t p_left, size_t p_right, bool p_directed) {
    // Get left and right
    Node* left = this->m_nodes[p_left];
    Node* right = this->m_nodes[p_right];

    // Add the connection
    left->connections.append(p_right);
    
    // If left and right are the same, take the choice away.
    if (!p_directed && p_left != p_right) {
        right->connections.append(p_left);
    }
}

template<typename T>
void cslib::Graph<T>::disconnect(size_t p_left, size_t p_right, bool p_removeBoth) {
    // Get both nodes
    Node* left = this->m_nodes[p_left];
    Node* right = this->m_nodes[p_right];

    const size_t lSize = left->connections.size();
    bool found = false;
    
    // Find the connection
    size_t i = 0;
    for (i = 0; i < lSize; i++) {
        if (left->connections[i] == p_right) {
            found = true;
            break;
        }
    }

    // If found
    if (!found) {
        throw GraphConnectionNotFound();
    }

    // Remove it from the left
    left->connections.remove(i);

    // If we want to remove both sides
    if (p_removeBoth) {
        const size_t rSize = right->connections.size();
        found = false;

        for (i = 0; i < rSize; i++) {
            if (right->connections[i] == p_left) {
                found = true;
            }
        }

        // If found
        if (!found) {
            throw GraphConnectionNotFound();
        }
        
        right->connections.remove(i);
    }

}

template<typename T>
cslib::LinkedList<size_t>& cslib::Graph<T>::neighbours(size_t p_index) {
    return this->m_nodes[p_index]->connections;
}

template<typename T>
const cslib::LinkedList<size_t>& cslib::Graph<T>::neighbours(size_t p_index) const {
    return this->m_nodes[p_index]->connections;
}

template<typename T>
T& cslib::Graph<T>::operator[](size_t p_id) {
    return this->m_nodes[p_id]->data;
}

template<typename T>
const T& cslib::Graph<T>::operator[](size_t p_id) const {
    return this->m_nodes[p_id]->data;
}

template<typename T>
template<typename TF>
void cslib::Graph<T>::depthFirst(size_t p_start, TF&& p_func) const {
    // If not empty
    if (this->m_nodes.size() == 0) {
        return;
    }

    // Stack based search
    BSTree<size_t> visited;
    visited.insert(p_start);

    Stack<size_t> stack;
    stack.push(p_start);

    while (!stack.empty()) {
        // POp the stack
        size_t index = stack.pop();

        Node* node = this->m_nodes[index];
        LinkedList<size_t>& ll = node->connections;

        p_func(node->data);

        // Add children
        typedef LinkedList<size_t>::ConstIterator LLConstIterator;
        for (LLConstIterator it = ll.cbegin(); it != ll.cend(); ++it) {
            // If value is
            size_t value = *it;
            if (!BSTree_contains(visited, value)) {
                stack.push(value);
                visited.insert(value);
            }
        }
    }
}

template<typename T>
template<typename TF>
void cslib::Graph<T>::breadthFirst(size_t p_start, TF&& p_func) const {
    // If not empty
    if (this->m_nodes.size() == 0) {
        return;
    }

    // Stack based search
    BSTree<size_t> visited;
    visited.insert(p_start);

    Queue<size_t> queue;
    queue.enqueue(p_start);

    while (!queue.empty()) {
        // POp the stack
        size_t index = queue.dequeue();

            Node* node = this->m_nodes[index];
            LinkedList<size_t>& ll = node->connections;

            p_func(node->data);

            // Add children
            typedef LinkedList<size_t>::ConstIterator LLConstIterator;
            for (LLConstIterator it = ll.cbegin(); it != ll.cend(); ++it) {
                size_t value = *it;
                if (!BSTree_contains(visited, value)) {
                    queue.enqueue(value);
                    visited.insert(value);
                }
            }

        
    }
}

template<typename T>
void cslib::Graph<T>::m_copy(const Graph<T>& p_graph) {
    // Clear this node
    const size_t size = p_graph.m_nodes.size();
    this->m_nodes = Vector<Node>(size);
    for (size_t i = 0; i < size; i++) {
        this->m_nodes[i] = p_graph.m_nodes[i];
    }
}

template<typename T>
typename cslib::Graph<T>::Node* cslib::Graph<T>::m_create(const T& p_data) {
    // Create the node.
    try {
        Node* node = new Node;
        node->data = p_data;
        node->connections;
        return node;
    } catch (const std::exception&) {
        throw GraphNodeCantCreate();
    }
}


#endif