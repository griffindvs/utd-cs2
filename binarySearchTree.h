/*
 * Created by Griffin Davis on 11/11/2019.
 * CS2337-002 D. Vogel
 *
 * binarySearchTree.h
 * This file implements a binary search tree for a given data type.
*/

#ifndef P4_BST_BINARYSEARCHTREE_H
#define P4_BST_BINARYSEARCHTREE_H

#include <iostream>
#include <string>
#include <vector>

// forward declaration of the template class binarySearchTree
template <class DataType>
class binarySearchTree;

// treeNode class
template <class DataType>
class treeNode {
    // give binarySearchTree access to private members
    friend class binarySearchTree<DataType>;

private:
    // instance variables
    DataType entry;
    treeNode<DataType>* left;
    treeNode<DataType>* right;

    // private member functions:
    // default constructor
    treeNode() {
        DataType entry;
        left = nullptr;
        right = nullptr;
    }

    // initialization constructor
    treeNode(const DataType& data) {
        entry = data;
        left = nullptr;
        right = nullptr;
    }
};

// binarySearchTree class
template <class DataType>
class binarySearchTree {
private:
    // instance variables
    treeNode<DataType>* root;
    int numberNodes;

    // deletes all nodes starting at root
    void deleteAll() {
        deleteAll(root);
        root = nullptr;
    }

    // deletes all nodes starting at treeNode *node recursively
    void deleteAll(treeNode<DataType>* node);

public:
    // default constructor
    binarySearchTree() {
        root = nullptr;
        numberNodes = 0;
    }

    // destructor
    virtual ~binarySearchTree() {
        deleteAll();
    }

    // copy constructor using pre-order traversal
    binarySearchTree(binarySearchTree &other);

    // assignment operator
    const binarySearchTree& operator=(const binarySearchTree &other);

    // returns true if the binary tree is empty
    bool empty() const {
        return numberNodes == 0;
    }

    // returns the number of items in the binary tree
    std::size_t size() const {
        return numberNodes;
    }

    // outputs each element in the tree ordered by key
    // uses in-order traversal
    void print(std::ostream &out) const;

    // calls print(std::cout)
    void print() const;

    // outputs each element in the tree for debugging purposes
    void debug(std::ostream &out) const;

    // returns whether or not the given item was found
    // passed a functional parameter which is given the found item
    bool find(const DataType &searchItem, void (*foundNode)(const DataType&));

    // removes the specified item from the tree, returns
    // true if successful, false otherwise
    bool erase(const DataType &deleteItem);

    // inserts the item into the binary tree, replaces if found
    void insert(const DataType &newItem);

    // inserts the item into the binary tree,
    // if item exists call duplicateItemFound functional parameter
    void insert(const DataType &newItem,
            void (*duplicateItemFound)(DataType &existingItem, const DataType &newItem));

//    // finds newItem and gets a modifiable version (existingItem)
//    // then updates the modifiable version, does not change key
//    void update(DataType &existingItem, const DataType &newItem);

    // completes an in-order traversal of the binary tree and
    // calls the functional parameter itemFound for each item
    void traverse(void (*itemFound)(const DataType& foundItem)) const;

    // static member helper functions
    static void recursiveInOrder(treeNode<DataType>* node, void (*itemFound)(const DataType &));
    static void recursiveCopy(treeNode<DataType>* &toNode, const treeNode<DataType>* fromNode);
};

// non-member helper functions
template<class DataType>
void handlePrintingOfNode(const DataType& data) {
    std::cout << data << std::endl;
}

// static member helper function implementations
template<class DataType>
void binarySearchTree<DataType>::recursiveInOrder(treeNode<DataType>* node, void (*itemFound)(const DataType &)) {
    if (node == nullptr) {
        return;
    }
    recursiveInOrder(node->left, itemFound);
    itemFound(node->entry);
    recursiveInOrder(node->right, itemFound);
}

template<class DataType>
void binarySearchTree<DataType>::recursiveCopy(treeNode<DataType>* &toNode, const treeNode<DataType>* fromNode) {
    if (fromNode == nullptr) {
        // end of fromTree
        toNode = nullptr;
    } else {
        toNode = new treeNode<DataType>(fromNode->entry); // copy data to node
        recursiveCopy(toNode->left, fromNode->left);
        recursiveCopy(toNode->right, fromNode->right);
    }
}

// binarySearchTree member function implementations:
// copy constructor using pre-order traversal
template<class DataType>
binarySearchTree<DataType>::binarySearchTree(binarySearchTree &other) {
    recursiveCopy(root, other.root); // start recursion with root nodes

    // Set size
    this->numberNodes = other.numberNodes;
}

// deletes all nodes starting at treeNode *node recursively
template <class DataType>
void binarySearchTree<DataType>::deleteAll(treeNode<DataType>* node) {
    if (node != nullptr) {
        // delete all nodes to the left
        deleteAll(node->left);
        node->left = nullptr;

        // delete all nodes to the right
        deleteAll(node->right);
        node->right = nullptr;

        // delete the node now
        delete node;
        numberNodes--;
    }
}

// assignment operator
template<class DataType>
const binarySearchTree<DataType>& binarySearchTree<DataType>::operator=(const binarySearchTree &other) {
    if (this != &other) {
        // No self-assigning
        deleteAll(); // clear the tree

        // Complete copy
        recursiveCopy(root, other.root); // start recursion with root nodes

        // Set size
        this->numberNodes = other.numberNodes;
    }
    return *this;
}

template<class DataType>
void binarySearchTree<DataType>::traverse(void (*itemFound)(const DataType &)) const {
    treeNode<DataType>* start = root;
    recursiveInOrder(start, itemFound);
}

template<class DataType>
void binarySearchTree<DataType>::print(std::ostream &out) const {
    traverse(handlePrintingOfNode);
}

template<class DataType>
void binarySearchTree<DataType>::print() const {
    traverse(handlePrintingOfNode);
}

template<class DataType>
void binarySearchTree<DataType>::debug(std::ostream &out) const {
    print(out);
}

template<class DataType>
bool binarySearchTree<DataType>::find(const DataType &searchItem, void (*foundNode)(const DataType &)) {
    treeNode<DataType>* cur = root;
    // Traverse the tree looking for searchItem
    while (cur != nullptr) {
        if (searchItem == cur->entry) {
            foundNode(cur->entry);
            return true;
        } else if (searchItem < cur->entry) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return false;
}


// removes the specified item from the tree, returns
// true if successful, false otherwise
template<class DataType>
bool binarySearchTree<DataType>::erase(const DataType &deleteItem) {
    treeNode<DataType>* parent = nullptr;
    treeNode<DataType>* current = root;

    // Traverse the tree looking for deleteItem
    while (current != nullptr) {
        if (current->entry == deleteItem) {
            // Found the desired node
            if (!current->left && !current->right) {
                // leaf node
                if (parent == nullptr) {
                    // node is root
                    root = nullptr;
                } else if (parent->left == current) {
                    // node is parent's left
                    parent->left = nullptr;
                } else {
                    // node is parent's right
                    parent->right = nullptr;
                }
            } else if (current->left && current->right == nullptr) {
                // node only has left child
                if (parent == nullptr) {
                    // node is root
                    root = nullptr;
                } else if (parent->left == current) {
                    // promote left child of current to parent's left
                    parent->left = current->left;
                } else {
                    // promote left child of current to parent's right
                    parent->right = current->left;
                }
            } else if (current->right && current->left == nullptr) {
                // node only has right child
                if (parent == nullptr) {
                    // node is root
                    root = nullptr;
                } else if (parent->left == current) {
                    // promote right child of current to parent's left
                    parent->left = current->right;
                } else {
                    // promote right child of current to parent's right
                    parent->right = current->right;
                }
            } else {
                // node has two children
                treeNode<DataType>* successor = current->right; // initialize successor to right branch
                // find true successor (leftmost child of right branch)
                while (successor->left != nullptr) {
                    successor = successor->left; // traverse left
                }
                DataType sucData = successor->entry; // get successor data for copy
                erase(sucData); // remove successor from tree
                current->entry = sucData; // promote successor
            }
            numberNodes--;
            return true; // deleteItem found and removed
        } else if (deleteItem > current->entry){
            // search right
            parent = current;
            current = current->right;
        } else {
            // search left
            parent = current;
            current = current->left;
        }
    }
    return false; // deleteItem not found
}

// inserts the item into the binary tree, replaces if found
template<class DataType>
void binarySearchTree<DataType>::insert(const DataType &newItem) {
    // instantiate node with newItem data
    treeNode<DataType>* newNode = new treeNode<DataType>(newItem);

    if (root == nullptr) {
        // set root to newNode
        numberNodes++;
        root = newNode;
        return; // insertion complete
    } else {
        // traverse tree to find insertion location
        treeNode<DataType>* current = root;
        while (current != nullptr) {
            if (newItem == current->entry) {
                // replace current
                current->entry = newItem;
                numberNodes++;
                return; // insertion complete
            } else if (newItem < current->entry) {
                // insert to the left
                if (current->left == nullptr) {
                    // insert as left child of current
                    current->left = newNode;
                    numberNodes++;
                    return; // insertion complete
                } else {
                    // traverse left
                    current = current->left;
                }
            } else {
                // insert to right
                if (current->right == nullptr) {
                    // insert as right child of current
                    current->right = newNode;
                    numberNodes++;
                    return; // insertion complete
                } else {
                    // traverse right
                    current = current->right;
                }
            }
        }
    }
}

// inserts the item into the binary tree,
// if item exists call duplicateItemFound function parameter
template<class DataType>
void binarySearchTree<DataType>::insert(const DataType &newItem, void (*duplicateItemFound)(DataType &existingItem, const DataType &newItem)) {
    // instantiate node with newItem data
    treeNode<DataType>* newNode = new treeNode<DataType>(newItem);

    if (root == nullptr) {
        // set root to newNode
        numberNodes++;
        root = newNode;
        return; // insertion complete
    } else {
        // traverse tree to find insertion location
        treeNode<DataType>* current = root;
        while (current != nullptr) {
            if (newItem == current->entry) {
                // call duplicateItemFound function parameter
                duplicateItemFound(current->entry, newItem);
                return; // insertion complete
            } else if (newItem < current->entry) {
                // insert to the left
                if (current->left == nullptr) {
                    // insert as left child of current
                    current->left = newNode;
                    numberNodes++;
                    return; // insertion complete
                } else {
                    // traverse left
                    current = current->left;
                }
            } else {
                // insert to right
                if (current->right == nullptr) {
                    // insert as right child of current
                    current->right = newNode;
                    numberNodes++;
                    return; // insertion complete
                } else {
                    // traverse right
                    current = current->right;
                }
            }
        }
    }
}

#endif //P4_BST_BINARYSEARCHTREE_H
