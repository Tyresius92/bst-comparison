/**********************************************************************
 * rb_tree.h                                                          *
 *                                                                    *
 * Interface for a polymorphic red black tree                         *
 **********************************************************************/

/***************************
 * PREPROCESSOR DIRECTIVES *
 ***************************/

#ifndef RB_TREE_H
#define RB_TREE_H

/*** INCLUDED FILES ***/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

/*** DEFINITIONS AND TYPEDEFS ***/

typedef struct rb_tree *RedBlack_T;

/**********************
 * FUNCTION CONTRACTS *
 * AND DECLARATIONS   *
 **********************/

/*
 * new_rb_tree
 * 
 * returns a pointer to a new, empty red black tree
 * 
 * CREs         n/a
 * UREs         system out of memory
 *              
 * 
 * @param       void * - pointer to a comparison function. if NULL is passed 
 *                              as argument, strcmp is assumed. 
 *              
 *              comparison_function
 *              @param          item being inserted (val1)
 *              @param          item from tree which we are comparing (val2)
 *              @return         int 
 *                               - zero (0) if val1 == val2
 *                               - positive value (n > 0) if val1 > val2
 *                               - negative value (n < 0) if val1 < val2
 *        
 * @return      pointer to empty rb_tree
 */
RedBlack_T new_rb_tree(void *comparison_func); 

/*
 * free_rb_tree
 * 
 * given a pointer to a red black tree, deallocates the tree and all nodes
 * contained within it, then sets the value of the pointer to NULL
 *
 * CREs         tree == NULL
 * UREs         n/a
 * 
 * @param       RedBlack_T - the tree to be freed
 * @return      n/a
 */
void free_rb_tree(RedBlack_T tree); 

/*
 * insert_value
 * 
 * given a value (cast to void), inserts the value into the given RB Tree
 * 
 * CREs         tree == NULL
 *              value == NULL
 * 
 * UREs         system out of memory
 * 
 * @param       RedBlack_T - tree in which to insert value
 * @param       void * - a pointer to any item to be inserted
 * @return      n/a
 */
int rb_insert_value(RedBlack_T tree, void * value);

/*
 * rb_delete_value
 */
void rb_delete_value(RedBlack_T tree, void * value); 

/*
 * rb_tree_is_empty
 * 
 * returns true if the tree is empty, and false otherwise
 * 
 * CREs         tree == NULL
 * UREs         n/a
 * 
 * @param       Redblack_T - tree to be checked if empty
 * @return      bool - true if empty, false otherwise
 */ 
bool rb_tree_is_empty(RedBlack_T tree); 

/*
 * search
 */
void *rb_search(RedBlack_T tree, void *value); 

/*
 * tree_minimum
 */
void *tree_minimum(RedBlack_T tree); 

/*
 * tree_maximum
 */
void *tree_maximum(RedBlack_T tree); 

void *successor_of_value(RedBlack_T tree, void *value); 

void *predecessor_of_value(RedBlack_T tree, void *value); 

/*
 * rb_map_inorder
 * 
 * given a tree and a pointer to a function, applies the function to every
 * element stored in the tree via an inorder walk
 * example valid operations include: 
 *              - print every value
 *              - increment every stored value by one
 *              - store every element in an array (stored in closure)
 * 
 * CREs         tree == NULL
 *              func_to_apply == NULL
 * UREs         func_to_apply modifies tree structure by performing different
 *                      operations on each node. (for instance, subtracting 1 
 *                      from the first node, 2 from the second, 3 from the 
 *                      third...and n from the nth could result in the BST 
 *                      property being invalidated)
 *                              
 * 
 * @param       Redblack_T - tree to apply function to
 * @param       void * - pointer to a function
 * @param       void * - a closure item; can be anything you would like to 
 *                              make use of when evaluating your function
 * @return      n/a
 */
void rb_map_inorder(RedBlack_T tree, 
                    void func_to_apply(void *root, int depth, void *cl), 
                    void *cl); 

/*
 * rb_map_preorder
 * 
 * given a tree and a pointer to a function, applies the function to every
 * element stored in the tree via a preorder walk
 * example valid operations include: 
 *              - print every value
 *              - increment every stored value by one
 *              - store every element in an array (stored in closure)
 * 
 * CREs         tree == NULL
 *              func_to_apply == NULL
 * UREs         func_to_apply modifies tree structure by performing different
 *                      operations on each node. (for instance, subtracting 1 
 *                      from the first node, 2 from the second, 3 from the 
 *                      third...and n from the nth could result in the BST 
 *                      property being invalidated)
 *                              
 * 
 * @param       Redblack_T - tree to apply function to
 * @param       void * - pointer to a function
 * @param       void * - a closure item; can be anything you would like to 
 *                              make use of when evaluating your function
 * @return      n/a
 */
void rb_map_preorder(RedBlack_T tree, 
                     void func_to_apply(void *root, int depth, void *cl), 
                     void *cl); 

/*
 * rb_map_postorder
 * 
 * given a tree and a pointer to a function, applies the function to every
 * element stored in the tree via a postorder walk
 * example valid operations include: 
 *              - print every value
 *              - increment every stored value by one
 *              - store every element in an array (stored in closure)
 * 
 * CREs         tree == NULL
 *              func_to_apply == NULL
 * UREs         func_to_apply modifies tree structure by performing different
 *                      operations on each node. (for instance, subtracting 1 
 *                      from the first node, 2 from the second, 3 from the 
 *                      third...and n from the nth could result in the BST 
 *                      property being invalidated)
 *                              
 * 
 * @param       Redblack_T - tree to apply function to
 * @param       void * - pointer to a function
 * @param       void * - a closure item; can be anything you would like to 
 *                              make use of when evaluating your function
 * @return      n/a
 */
void rb_map_postorder(RedBlack_T tree, 
                      void func_to_apply(void *root, int depth, void *cl), 
                      void *cl); 

#endif