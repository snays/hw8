/** @file TreeNode.h
 @brief Contains the class declarations and definitions for a templated TreeNode class.
 @author Sneha Belkhale
 @date Febuary 11th, 2016
 
The TreeNode class serves as the nodes in our BinarySearchTree. It holds an integer as well as pointers to the left, right, and parent nodes 
in the binary search tree. It allows both the BinarySearchTree and TreeIterator to be its friend. 
The TreeNode is templated to hold data of type T, and hold a comparator of type CMP (which will be the default less than comparator
if not provided.
 
 */

#ifndef TreeNode_h
#define TreeNode_h

//forward declarations of the BinarySearch Tree so compiler knows it is templated
template <typename T,typename CMP> class BinarySearchTree;
//forward declarations of the TreeIterator so compiler knows it is templated
template <typename T,typename CMP> class TreeIterator;

template<typename T,typename CMP=std::less<T>>
class TreeNode
{
public:
    TreeNode(BinarySearchTree<T,CMP>& parent):myBst(parent){};
    //insert node into correct position
    void insert_node(TreeNode<T,CMP>* new_node);
    //print all nodes
    void print_nodes() const;
    //find specified value in tree
    bool find(T value) const;
  
private:
    //to compare data based on specified comparator
    CMP isless;
    //type T data
    T data;
    //pointer to left, right , and parent TreeNodes
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    //friend classes
    friend class BinarySearchTree<T,CMP>;
    friend class TreeIterator<T,CMP>;
    //reference to the tree that the node is a part of 
    BinarySearchTree <T,CMP>& myBst;
};


#include <iostream>

/** Definition of the insert_node function, that takes a pointer to another treeNode and adds it into the tree in the correct sorted position
 
 @param pointer to the TreeNode that we want to add to the tree
 
 */
template<typename T,typename CMP>
void TreeNode<T,CMP>::insert_node(TreeNode<T,CMP>* new_node)
{
    //if the data we want to insert is less than the current node's data
    if (isless(new_node->data, data))
    {
        //and the current nodes left child is empty
        if (left == NULL)
        {
            //add the new node in
            new_node->parent=this;
            left=new_node;
        }
        //if the current node has a left child, traverse the left side of the tree
        else left->insert_node(new_node);
    }
    //if the data we want to insert is greater than the current node's data
    else if (isless(data,new_node->data))
    {
        //and the current nodes right child is empty
        if (right == myBst.endNode)
        {
            //add the new node in
            new_node->parent=this;
            right = new_node;
            //link correctly and uodate the endNode
            new_node->right=myBst.endNode;
            myBst.endNode->data=new_node->data;
            myBst.endNode->parent=new_node;
        }
        //if the current node has a right child, traverse the right side of the tree
        else right->insert_node(new_node);
    }
}


/** Definition of the find function, that traverses the tree to check if it contains an inputed value
 @param int that we want to see if it exists in the tree
 
 */
template<typename T,typename CMP>
bool TreeNode<T,CMP>::find(T value) const
{
    //if the value we want to find is less than the current nodes data
    if (isless(value,data))
    {
        //return false if there is no node less than
        if (left == NULL) return false;
        //traverse the left side of the tree otherwise
        else return left->find(value);
    }
    //if the value we want to find is greater than the current nodes data
    else if (isless(data,value))
    {
        //return false if there is no right side
        if (right == NULL) return false;
        //traverse the right side otherwise
        else return right->find(value);
    }
    else
        //if the value is equal to current nodes data, return true
        return true;
}


/** Definition of the print_nodes function, that recursively prints out all elements after the starting root
 
 */
template<typename T,typename CMP>
void TreeNode<T,CMP>::print_nodes() const
{
    //recursively print left side
    if (left != NULL)
        left->print_nodes();
    std::cout << data << "\n";
    //recursively print right side
    if (right != NULL)
        right->print_nodes();
}


#endif /* TreeNode_h */
