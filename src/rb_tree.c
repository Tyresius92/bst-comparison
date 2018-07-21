#include "rb_tree.h"
#include <assert.h>

/*** MACRO DEFINITIONS ***/

#define BLACK 'b'
#define RED 'r'

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
void deallocate_all_tree_nodes(Node *n); 

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

        Node new_node = construct_node(value); 

        Node *curr_node = tree->root; 


        //I believe there is a logic error in this while loop. 
        //Going to let it percolate
        while (curr_node != NULL) {
                if (curr_node->value > value)
                        curr_node = curr_node->left; 
                else if (curr_node->value <= value)
                        curr_node = curr_node->right; 
        }

        //delete later
        (void) new_node; 

        return 0;
}


//Need to heap allocate? Not sure. 
Node construct_node(void * value)
{
        (void) value;
        Node new_node; 

        new_node.parent = NULL;
        new_node.left = NULL; 
        new_node.right = NULL; 
        new_node.value = value; 

        new_node.color = RED; 

        return new_node; 
}

void free_rb_tree(RedBlack_T tree)
{
        assert(tree != NULL);

        deallocate_all_tree_nodes(tree->root); 
        free(tree); 

        tree = NULL; 
}

void deallocate_all_tree_nodes(Node *n) {
        if (n->left != NULL) 
                deallocate_all_tree_nodes(n->left);
        else if (n->right != NULL)
                deallocate_all_tree_nodes(n->right); 

        free(n); 
}

bool rb_tree_is_empty(RedBlack_T tree)
{
        assert(tree != NULL); 

        if (tree->root == NULL)
                return true; 
        else 
                return false; 
}
