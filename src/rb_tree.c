#include "rb_tree.h"
#include <assert.h>
#include <string.h>

/*** MACRO DEFINITIONS ***/

#define BLACK 'b'
#define RED 'r'

typedef struct Node {
        char * value;
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

Node *construct_node(char * value);
void deallocate_all_tree_nodes(Node *n); 
Node *private_insert(Node *root, Node *new_node);
void fix_violation(Node *root, Node *inserted);
void rotate_left(Node *root, Node *n); 
void rotate_right(Node *root, Node *n); 

/************************
 * FUNCTION DEFINITIONS *
 ************************/ 

T new_rb_tree()
{
        T tree = malloc(sizeof(struct rb_tree)); 

        tree->root = NULL; 

        return tree; 
}

int insert_value(T tree, char *value)
{
        assert(tree != NULL && value != NULL); 

        Node *new_node = construct_node(value); 

        tree->root = private_insert(tree->root, new_node); 

        fix_violation(tree->root, new_node);  

        return 0;
}

Node *private_insert(Node *root, Node *new_node) 
{
        if (root == NULL) { 
                return new_node; 
        }

        if (strcmp(new_node->value, root->value) < 0) {
                root->left = private_insert(root->left, new_node); 
                root->left->parent = root; 
        } else {
                root->right = private_insert(root->right, new_node); 
                root->right->parent = root; 
        }

        return root; 
}

void fix_violation(Node *root, Node *culprit)
{
        Node *parent_node = NULL; 
        Node *grand_parent_node = NULL; 

        while ((culprit != root) && (culprit->color != BLACK) && (culprit->parent->color == RED)) {
                
                parent_node = culprit->parent; 
                grand_parent_node = culprit->parent->parent; 

                if (parent_node == grand_parent_node->left){

                        Node *uncle = grand_parent_node->right; 

                        if (uncle != NULL && uncle->color == RED) {

                                grand_parent_node->color = RED; 
                                parent_node->color = BLACK; 
                                uncle->color = BLACK; 
                                culprit = grand_parent_node; 

                        } else {

                                if (culprit == parent_node->right) {
                                        rotate_left(root, parent_node); 
                                        culprit = parent_node; 
                                        parent_node = culprit->parent; 
                                }

                                rotate_right(root, grand_parent_node); 

                                char temp = parent_node->color; 
                                parent_node->color = grand_parent_node->color; 
                                parent_node->color = temp; 

                                culprit = parent_node; 

                                if (root == grand_parent_node) {
                                        root = culprit; 
                                }
                        }
                } else { // parent_node == grand_parent_node->right
                        Node *uncle = grand_parent_node->left; 

                        if ((uncle != NULL) && (uncle->color == RED)) {
                                grand_parent_node->color = RED; 
                                parent_node->color = BLACK; 
                                uncle->color = BLACK; 
                                culprit = grand_parent_node; 
                        } else {
                                if (culprit == parent_node->left) {
                                        rotate_right(root, parent_node); 
                                        culprit = parent_node; 
                                        parent_node = culprit->parent; 
                                }

                                rotate_left(root, grand_parent_node);

                                char temp = parent_node->color; 
                                parent_node->color = grand_parent_node->color; 
                                parent_node->color = temp; 

                                culprit = parent_node; 

                                if (root == grand_parent_node) {
                                        root = culprit; 
                                }
                        }
                }
        }

        root->color = BLACK; 
}

void rotate_left(Node *root, Node *n)
{
        Node *right_child = n->right; 

        n->right = right_child->left; 

        if (n->right != NULL)
                n->right->parent = n; 

        right_child->parent = n->parent; 

        if(n->parent == NULL) {
                root = right_child; 
        } else if (n == n->parent->left) {
                (void) root; 
                n->parent->left = right_child; 
        } else {
                (void) root; 
                n->parent->right = right_child; 
        }

        right_child->left = n; 
        n->parent = right_child; 
}

void rotate_right(Node *root, Node *n)
{
        Node *left_child = n->left; 

        n->left = left_child->right; 

        if (n->left != NULL)
                n->left->parent = n; 

        left_child->parent = n->parent; 

        if(n->parent == NULL) {
                root = left_child; 
        } else if (n == n->parent->left) {
                (void) root; 
                n->parent->left = left_child; 
        } else {
                (void) root; 
                n->parent->right = left_child; 
        }

        left_child->right = n; 
        n->parent = left_child; 
}

Node *construct_node(char * value)
{
        Node *new_node = (Node *) malloc(sizeof(Node)); 

        new_node->parent = NULL;
        new_node->left = NULL; 
        new_node->right = NULL; 
        new_node->value = value; 

        new_node->color = RED; 

        return new_node; 
}

bool is_in_tree(RedBlack_T tree, char *value)
{
        bool found = false; 
        Node *curr = tree->root; 
        int c = 0; 

        while (!found && curr != NULL) {
                c = strcmp(value, curr->value); 

                if (c == 0) {
                        found = true; 
                } else if (c < 0) {
                        curr = curr->left; 
                } else if (c > 0) {
                        curr = curr->right; 
                }
        }

        return found; 
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
        if (n->right != NULL)
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

void rb_map(RedBlack_T tree, void *func_to_apply, void *cl)
{
        (void) tree; 
        (void) func_to_apply; 
        (void) cl; 
}