#include "LinkedList.h"

const char* cslib::LinkedListException::what() const throw() {
    return "Linked List Exception!";
}

const char* cslib::LinkedListNodeCantCreate::what() const throw() {
    return "Linked List node can't be created!";
}