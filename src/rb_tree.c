#include "rb_tree.h"

typedef struct Node {
        void * value;
        struct Node * parent;
        struct Node * left; 
        struct Node * right; 
        char color; 
} Node;

struct rb_tree {
        Node * root; 
};

typedef RedBlack_T T; 

/*********************************
 * PRIVATE FUNCTION DECLARATIONS *
 *********************************/ 

Node construct_node(void * value);

/************************
 * FUNCTION DEFINITIONS *
 ************************/ 

T new_rb_tree()
{
        T tree = malloc(sizeof(struct rb_tree)); 

        tree->root = NULL; 

        return tree; 
}


int insert_value(T tree, void *value)
{
        if (tree == NULL || value == NULL) {
                return -1;
        }

        return 0;
}

Node construct_node(void * value)
{
        (void) value;
        Node new_node; 

        return new_node; 
}