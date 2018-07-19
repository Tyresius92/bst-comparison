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

/*** MACRO DEFINITIONS ***/

#define BLACK 'b'
#define RED 'r'

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
int insert_value(RedBlack_T tree, void * value);


#endif