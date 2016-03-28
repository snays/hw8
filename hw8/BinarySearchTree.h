/** @file BinarySearchTree.h
 @brief Contains the class declarations and definitions for a BinarySearchTree templated class.
 @author Sneha Belkhale
 @date Febuary 11th, 2016
 
 This class is a binary search tree model that holds treeNodes (on heap) with any T data types, in a sorted binary search tree. 
 It sorts the nodes based on the CMP comparator that is specified, if no comparator is specified we use the standard librarys comparison 
 operator "less<T>" (works well with integers, strings, etc). The class takes care of all heap memory with a custom destructor, and also 
 has many useful functions for working with the tree.
 The binary search tree also can generate TreeIterators, it is useful to note that the end() iterator that is returned points to the node
 AFTER the largest node in the tree, we call this node endNode and save it as a public variable of the tree.

 We create this endNode place saver so that we can still call -- on an iterator pointing to the node after the largest node. 
 */

#ifndef BinarySearchTree_h
#define BinarySearchTree_h
#include "TreeNode.h"
#include "TreeIterator.h"
#include <iostream>
#include <functional>

template <typename T,typename CMP= std::less<T>>
class BinarySearchTree
{
public:
    //constructor
    BinarySearchTree();
    //deep copy constructor
    BinarySearchTree(const BinarySearchTree &copy);
    //move copy constructor
    BinarySearchTree(BinarySearchTree&& copy);
    //assignment operator
    BinarySearchTree& operator=(BinarySearchTree assign);
    //insert element into tree
    void insert(T data);
    //remove element
    void erase(T data);
    //print all elements
    void print() const;
    //find the smallest T value in tree
    T smallest();
    //find the largest T value in tree
    T largest();
    //access iterator to the smallest and largest values of tree
    TreeIterator<T,CMP> begin();
    TreeIterator<T,CMP> end();
    //destructor
    ~BinarySearchTree();
    //helper for copy constructor
    void copy_helper(TreeNode<T,CMP>* N);
    //helper for destructor
    void destroy(TreeNode<T,CMP>* N);
    //TreeNode pointer to one after the largest node the tree
    TreeNode<T,CMP>* endNode;
private:
    //TreeNode pointer to the root of the tree
    TreeNode<T,CMP>* root;
   

};

/** Definition of standard constructor for the binary search tree that essentially just sets the root to nullptr

 */
template <typename T,typename CMP>
BinarySearchTree<T,CMP>::BinarySearchTree()
{
    //set root to null
    root = nullptr;
    //set our "endNode" to null
    endNode=nullptr;
   
}

/** Definition of deep copy constructor for binary search tree, uses the copy_helper function(defined next) in order to successfully copy each element of the binary search tree.
 
 @param binary search tree that you want to make a copy of (L VALUE)
 */
template <typename T,typename CMP>
BinarySearchTree<T,CMP>::BinarySearchTree(const BinarySearchTree<T,CMP> &copy)
{
    //set initial root to null just in case the tree you want to copy is empty
    root=nullptr;
    //give the root of the tree you want to copy to the copy_helper
    copy_helper(copy.root);
    std::cout<<"Copy made"<<std::endl;
}


/** The Copy_helper function inserts the current node into the new tree, and then recursively calls itself on the children of the current node so that we efficiently deep copy the entire tree.
 @param root of subtree you want to copy
 */
template <typename T,typename CMP>
void BinarySearchTree<T,CMP>::copy_helper(TreeNode<T,CMP>* N)

{
    //as long as our subtree is not empty
    if(N!=nullptr)
    {
        //insert the current node (new heap memory so this is a deep copy)
        insert(N->data);
        //recursively call copy on the left and right subtree until they are empty
        copy_helper(N->left);
        copy_helper(N->right);
    }
}


/** Definition of move copy constructor for binary search tree, this constructor makes use of the fact that its parameter is an R Value and is not going to be used after the end of this function. The caller is therefore able to "steal" the root of the R Value Paramter.
 
 @param binary search tree that you want to make a copy of (R VALUE)
 */
template <typename T,typename CMP>
BinarySearchTree<T,CMP>::BinarySearchTree(BinarySearchTree&& copy)
{
    //steal root
    this->root=copy.root;
    //set parameters root to null
    copy.root=nullptr;
    std::cout<<"Move performed"<<std::endl;

}
/** Overloading the assignment operator for the Binary Search Tree class. This assignment operator uses the copy swap idiom by first making a deep copy of the parameter and then swapping the root of the parameter with the caller.
 
 @param binary search tree that you want to assign
 @return reference to a deep copy of the parameter
 */
template <typename T,typename CMP>
BinarySearchTree<T,CMP>& BinarySearchTree<T,CMP>::operator=(BinarySearchTree assign)
{
   //shallow swap
    std::swap(this->root, assign.root);
    return *this;
}

/** Definition of the Binary Search tree destructor, necessary because the destructor manages memory located on the heap.
 we use the helper function destroy, to safely delete the memory (defined next)
 */
template <typename T,typename CMP>
BinarySearchTree<T,CMP>::~BinarySearchTree()
{
    //use helper function to safely delete memory
    destroy(root);
}




/** Definition of the destroy function, which takes in a node and recursively calls destroy on the left subtree, and right subtree, and then deletes the node itself. This function helps us safely delete all heap memory of the binary search tree.
 */
template <typename T,typename CMP>
void BinarySearchTree<T,CMP>:: destroy(TreeNode<T,CMP> *N)
{
    //if the node exists
    if(N!=nullptr)
    {
        //destroy left subtree
        destroy(N->left);
        N->left=nullptr;
        //destroy right subtree
        destroy(N->right);
        N->right=nullptr;
        //delete the node
        delete N;
    }
}


/** Definition of the print function, which calls print_nodes on the root of the tree in order to print out all the elements of the tree in order.
 */
template <typename T,typename CMP>
void BinarySearchTree<T,CMP>::print() const
{
    //if the tree is not empty, call the TreeNode's print function
    if (root != endNode)
        root->print_nodes();
}


/** Definition of the insert function that essentially creates a new TreeNode with the desired integer value, then adds it to the tree.
 @param integer value of the node you want to insert into the tree
 
 */

template <typename T,typename CMP>
void BinarySearchTree<T,CMP>::insert(T data)
{
    //create new TreeNode pointer
    TreeNode<T,CMP>* new_node = new TreeNode<T,CMP>(*this);
    //set its data value
    new_node->data = data;
    //set left and right pointers to nullptr
    new_node->left = nullptr;
    new_node->right = nullptr;
    
    //if the tree is empty
    if (root == nullptr)
    {
        //make the new TreeNode the root of the tree
        root = new_node;
        new_node->parent=nullptr;
        
        //create a new TreeNode to be the end node
        endNode=new TreeNode<T,CMP>(*this);
        //set its initial data
        endNode->data=data;
        //link properly
        new_node->right = endNode;
        endNode->parent=root;
        endNode->right=nullptr;
        endNode->left=nullptr;
        //end node left and rights
    }
    //if the tree is not empty, insert new node correctly into the tree using TreeNode's insert function
    else root->insert_node(new_node);
}

/** Definition of the erase function, that first tries to find the inputed value in the tree, and if found, removes it from the tree and relinks the tree safely.
 
 @param integer value of the node you want to remove from the tree
 
 */

template <typename T,typename CMP>
void BinarySearchTree<T,CMP>::erase(T data)
{
    // Find node to be removed
    TreeNode<T,CMP>* to_be_removed = root;
    TreeNode<T,CMP>* parent2 = nullptr;
    bool found = false;
    while (!found && to_be_removed != nullptr)
    {
        //search right side of the tree if the data value is greater than current ptr
        if (to_be_removed->data < data)
        {
            parent2 = to_be_removed;
            to_be_removed = to_be_removed->right;
        }
        //search left side of tree if data value is less than current ptr
        else if (data < to_be_removed->data)
        {
            parent2 = to_be_removed;
            to_be_removed = to_be_removed->left;
        }
        else found = true;
    }
    
    //if we could not find the tree, exit the function
    if (!found) return;
    
    // If one of the children is empty, use the other
    if (to_be_removed->left == nullptr || to_be_removed->right == nullptr)
    {
        TreeNode<T,CMP>* new_child;
        //if the empy child is the left child
        if (to_be_removed->left == nullptr)
            //the new_child becomes the right child
            new_child = to_be_removed->right;
        else
            //else the new child becomes the right child
            new_child = to_be_removed->left;
        
        //if the node we want to remove is the root
        if (parent2 == nullptr)
        {
            //the root now points to the new child
            root = new_child;
            new_child->parent=nullptr;
        }
        //if the node we want to remove is a left child
        else if (parent2->left == to_be_removed)
        {
            //re-link the left child of the parent
            parent2->left = new_child;
            if (new_child!=nullptr)
                new_child->parent=parent2;
        }
        //if the node we want to remove is a right child
        else
        {
            //relink the right child of the parent
            parent2->right = new_child;
            if (new_child != nullptr)
                new_child->parent=parent2;
        }
        //take care of heap memory of deleted node
        delete to_be_removed;
        return;
    }
    
    // If neither subtree is empty
    
    // Find largest element of the left subtree
    TreeNode<T,CMP>* largest_parent = to_be_removed;
    TreeNode<T,CMP>* largest = to_be_removed->left;
    //find the right most element of the left subtree
    while (largest->right != nullptr)
    {
        largest_parent = largest;
        largest = largest->right;
    }
    
    // largest contains largest child in left subtree
    
    // Move contents of the nodes
    to_be_removed->data = largest->data;
    //if the parent of the largest node is the node we want to remove, re link accordingly
    if (largest_parent == to_be_removed)
    {
        largest_parent->left = largest->left;
        if(largest_parent->left!=nullptr)
            //set parent correctly
            largest_parent->left->parent=largest_parent;
        //clear heap memory
        delete largest;
    }
    //if the parent of the largest node is not the node we want to remove, re link accordingly
    else
    {
        largest_parent->right = largest->left;
        if(largest_parent->right!=nullptr)
            //set parent correctly
            largest_parent->right->parent=largest_parent;
        //remove heap memory
        delete largest;
        
    }
    
}

/** Definition of the smallest function that returns the smallest element of the tree.
 
 @returns integer value of the smallest value in the tree
 */

template <typename T,typename CMP>
T BinarySearchTree<T,CMP>::smallest()
{
    //have a treenode to keep track of traversal
    TreeNode<T,CMP>* cur=root;
    //traverse tree for the left most node
    while(cur->left!=NULL)
    {
        cur=cur->left;
    }
    //return the data value of the smallest value
    return cur->data;
}

/** Definition of the largest function that returns the largest element of the tree.
 
 @returns integer value of the largest value in the tree
 */
template <typename T,typename CMP>
T BinarySearchTree<T,CMP>::largest()
{
    //have a treenode to keep track of traversal
    TreeNode<T,CMP>* cur=root;
    //traverse tree for right most node
    while(cur->right!=NULL)
    {
        cur=cur->right;
    }
    //return largest value in the tree
    return cur->data;
}


/** Definition of the begin() function, returns a TreeIterator to the smallest value in the tree, useful so that we can use the auto: functionality for the BST
 
 @returns a TreeIterator to the smallest value in the tree
 */

template <typename T,typename CMP>
TreeIterator<T,CMP> BinarySearchTree<T,CMP>::begin()
{
    //create a new tree iterator
    TreeIterator<T,CMP> iter;
    TreeNode<T,CMP>* cur=root;
    //traverse tree for leftmost smallest node
    while(cur->left!=NULL)
    {
        cur=cur->left;
    }
    //set the iterator's node to the smallest node
    iter.node=cur;
    return iter;
    
}

/** Definition of the end() function, returns a TreeIterator to the position after the largest value in the tree, useful so that we can use the auto: functionality for the BST
 
 @returns a TreeIterator to the position to one after the largest value in the tree (the endNode)
 */
template <typename T,typename CMP>
TreeIterator<T,CMP> BinarySearchTree<T,CMP>::end()
{
    //create a new tree iterator
    TreeIterator<T,CMP> iter;

    //set the end iterators node to the tree's end Node
    iter.node=endNode;
    
    
    return iter;
    
}



#endif /* BinarySearchTree_h */
