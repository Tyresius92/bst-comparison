/**********************************************************************
 * rb_tree.h                                                          *
 *                                                                    *
 * Interface for a red black tree which stores char *                 *
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
 * @return      pointer to empty rb_tree
 */
RedBlack_T new_rb_tree(); 

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
int insert_value(RedBlack_T tree, char * value);

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
 * //TODO
 * //Write Function Contract
 */ 
bool is_in_tree(RedBlack_T tree, char *value);

/*
 * rb_map
 * 
 * given a tree and a pointer to a function, applies the function to every
 * element stored in the tree 
 * 
 * CREs         tree == NULL
 *              func_to_apply == NULL
 * UREs         n/a
 * 
 * @param       Redblack_T - tree to apply function to
 * @param       void * - pointer to a function
 * @param       void * - a closure item; can be anything you would like to 
 *                              make use of when evaluating your function
 * @return      n/a
 */
void rb_map(RedBlack_T tree, void *func_to_apply, void *cl); 

#endif