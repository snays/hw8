/** @file TreeIterator.h
 @brief Contains the class declarations and definitions for a TreeIterator templated class
 @author Sneha Belkhale
 @date Febuary 11th, 2016
 
 The TreeIterator overloads all necessary operators so that it can function as a bidirectional iterator for the BinarySearchTree. 
 The TreeIterator accesses TreeNodes with data type T and also keeps track of the comparator being used to compare node values
 */

#ifndef TreeIterator_h

#include "TreeNode.h"
#include <iostream>
#include <utility>

//forward declarations of the BinarySearch Tree so compiler knows it is templated
template <typename T,typename CMP> class BinarySearchTree;

//forward declarations of the friend == operators compiler knows it is templated
template <typename T,typename CMP>
bool operator==(TreeIterator<T,CMP> a, TreeIterator<T,CMP> b);

//forward declarations of the friend != operators compiler knows it is templated
template <typename T,typename CMP>
bool operator!=(TreeIterator<T,CMP> a, TreeIterator<T,CMP> b);


template <typename T,typename CMP>
class TreeIterator {

public:
    //prefix next largest node operator
    TreeIterator<T,CMP>& operator++();
    //postfix next largest node operator
    TreeIterator<T,CMP> operator++(int);
    //prefix next smallest node operator
    TreeIterator<T,CMP>& operator--();
	//postfix next smallest node operator
	TreeIterator<T,CMP> operator--(int);
    //retrieve value of node
    T operator*();
    //retrieve value of node
    T operator->();
    //comparison operators
    friend bool operator==<>(TreeIterator<T,CMP> a, TreeIterator<T,CMP> b);
    friend bool operator!=<>(TreeIterator<T,CMP> a, TreeIterator<T,CMP> b);

    
private:
    //pointer to current node
    TreeNode<T,CMP>* node;
    //declare friend class
    friend class BinarySearchTree<T,CMP>;


};


/** Definition of ++ as a prefix operator, for example, this function is called like so: ++iterator. It uses the in-order algorithm to move to the next largest node in the tree.
 
 @return a reference to the original tree iterator with its node pointer now pointing at the next largest element of the tree
 
 */
template <typename T,typename CMP>
TreeIterator<T,CMP>& TreeIterator<T,CMP>::operator++()
{
    
    //have a pointer to the current node
    TreeNode<T,CMP>* cur=node;
    //and a pointer to the parent
    TreeNode<T,CMP>*parent2=node->parent;
    //if the node doesnt have a right subtree
    if(node->right==nullptr)
    {
        //traverse tree upwards to find the first node that is a left child
        while (parent2!=nullptr&&cur==parent2->right)
        {
            cur=parent2;
            parent2=parent2->parent;
        }
        //set the new iterator node to be parent of that node
        node=parent2;
        return *this;
    }
    //if the node has a right subtree
    else
    {
        //find the smallest element of the right subtree
        cur=node->right;
        //a.k.a the left most element
        while(cur->left!=nullptr)
        {
            cur=cur->left;
        }
        //set new iterator node to the smallest element of right subtree
        node=cur;
        return *this;
    }
    
}


/** Definition of ++ as a postfix operator, for example, this function is called like so: iterator++. It uses the in-order algorithm to move to the next largest node in the tree. Since the code is essentially the same as the prefix operator, we just call the prefix operator in order to avoid duplicating code.
 
 @return a copy of the original TreeIterator before it was incremented.
 
 */
template <typename T,typename CMP>
TreeIterator<T,CMP> TreeIterator<T,CMP>::operator++(int)
{
    //create a temporary TreeIterator to hold the Iterators current position
    TreeIterator<T,CMP> previous=(*this);
    //increment original iterator
    ++(*this);
    //return an iterator to the original position
    return previous;
}


/** Definition of -- as a prefix operator, for example, this function is called like so: --iterator. It uses the reverse in-order algorithm to move to the next smallest node in the tree.
 
 @return a copy of the original TreeIterator before it was decremented.
 
 */
template <typename T,typename CMP>
TreeIterator<T,CMP>& TreeIterator<T,CMP>::operator--()
{
    
    //have a pointer to the current node
    TreeNode<T,CMP>* cur=node;
    //have a pointer to the parent
    TreeNode<T,CMP>* parent2=node->parent;
    //if the node has a left subtree
    if(node->left!=nullptr)
    {
        //get the largest element of the left subtree
        while(cur->right!=nullptr)
        {
            cur=cur->right;
        }
        //set the new iterator node to the largest element of the left subtree
        node=cur;
        return *this;
    }
    //if the node does not have a left subtree, traverse upwards until you reach the first node that is a right child
    while(parent2!=nullptr&&cur==parent2->left)
    {
        cur=parent2;
        parent2=parent2->parent;
        
    }
    //set the current iterator node to the parent of that node
    node=parent2;
    return *this;
    
}


/** Definition of -- as a postfix operator, for example, this function is called like so: iterator--. It uses the in-order algorithm to move to the next smallest node in the tree. Since the code is essentially the same as the prefix operator, we just call the prefix operator in order to avoid duplicating code.
 
 @return a reference to the original tree iterator with its node pointer now pointing at the next smallest element of the tree
 
 */
template <typename T,typename CMP>
TreeIterator<T,CMP> TreeIterator<T,CMP>::operator--(int)
{
    //save current position
    TreeIterator<T,CMP> old=(*this);
    //decrement iterator
    --(*this);
    //return old position
    return old;
}


/** Definition of * operator, so that we can reference the value of the node that the iterator is currently pointing to.
 
 @return the integer value of the current node
 */
template <typename T,typename CMP>
T TreeIterator<T,CMP>::operator*()
{
    //return current value of node
    return node->data;
    
}


/** Definition of -> operator, so that we can reference the value of the node that the iterator is currently pointing to.
 
 @return the integer value of the current node
 */
template <typename T,typename CMP>
T TreeIterator<T,CMP>::operator->()
{
    //return current value of node
    return node->data;
    
}


/** Definition of == operator, this is a friend function used to check if two iterators are pointing to the same node.
 
 @return boolean value, true if the two iterators are pointing to the same node
 */
template <typename T,typename CMP>
bool operator==(TreeIterator<T,CMP> a, TreeIterator<T,CMP> b)
{
    //return true if pointing to same node
    return(a.node==b.node);
}


/** Definition of != operator, this is a friend function used to check if two iterators are not pointing to the same node.
 
 @return boolean value, true if the two iterators are not pointing to the same node
 */
template <typename T,typename CMP>
bool operator!=(TreeIterator<T,CMP> a, TreeIterator<T,CMP> b)
{
    //return false if pointing to same node
    if (a.node==b.node) return false;
    return true;
}








#define TreeIterator_h

#endif /* TreeIterator_h */
