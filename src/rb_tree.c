#include "rb_tree.h"
#include <assert.h>
#include <string.h>
#include <stdint.h>

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
        void * comparison_func; 
};

typedef RedBlack_T T; 

/*********************************
 * PRIVATE FUNCTION DECLARATIONS *
 *********************************/ 

Node *construct_node(void * value);
void deallocate_all_tree_nodes(Node *n); 
Node *private_insert(Node *root, Node *new_node, void *comparison_func(void *val1, void *val2));
void fix_violation(RedBlack_T tree, Node *inserted);
void rotate_left(RedBlack_T tree, Node *n); 
void rotate_right(RedBlack_T tree, Node *n); 
Node *find_in_tree(RedBlack_T tree, void *value, void *comparison_func(void *val1, void *val2));
void rb_private_inorder_map(Node *root, 
                            int depth,
                            void func_to_apply(void *value, int depth, void *cl), 
                            void *cl);

/************************
 * FUNCTION DEFINITIONS *
 ************************/ 

T new_rb_tree(void *comparison_func)
{
        T tree = malloc(sizeof(struct rb_tree)); 

        tree->root = NULL; 

        if (comparison_func == NULL) {
                tree->comparison_func = &strcmp; 
        } else {
                tree->comparison_func = comparison_func; 
        }

        return tree; 
}

int insert_value(T tree, void *value)
{
        assert(tree != NULL && value != NULL); 

        Node *new_node = construct_node(value); 

        tree->root = private_insert(tree->root, new_node, tree->comparison_func); 

        fix_violation(tree, new_node);  

        return 0;
}

Node *private_insert(Node *root, Node *new_node, 
                     void *comparison_func(void *val1, void *val2)) 
{
        if (root == NULL) { 
                return new_node; 
        }

        if ((int)(intptr_t) comparison_func(new_node->value, root->value) < 0) {
                root->left = private_insert(root->left, new_node, comparison_func); 
                root->left->parent = root; 
        } else {
                root->right = private_insert(root->right, new_node, comparison_func); 
                root->right->parent = root; 
        }

        return root; 
}

void fix_violation(RedBlack_T tree, Node *culprit)
{
        Node *parent_node = NULL; 
        Node *grand_parent_node = NULL; 

        while ((culprit != tree->root) && (culprit->color != BLACK) && (culprit->parent->color == RED)) {
                
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
                                        rotate_left(tree, parent_node); 
                                        culprit = parent_node; 
                                        parent_node = culprit->parent; 
                                }

                                rotate_right(tree, grand_parent_node); 

                                char temp = parent_node->color; 
                                parent_node->color = grand_parent_node->color; 
                                grand_parent_node->color = temp; 

                                culprit = parent_node; 

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
                                        rotate_right(tree, parent_node); 
                                        culprit = parent_node; 
                                        parent_node = culprit->parent; 
                                }

                                rotate_left(tree, grand_parent_node);

                                char temp = parent_node->color; 
                                parent_node->color = grand_parent_node->color; 
                                grand_parent_node->color = temp; 

                                culprit = parent_node; 

                        }
                }
        }

        tree->root->color = BLACK; 
}

void rotate_left(RedBlack_T tree, Node *n)
{

        Node *right_child = n->right; 

        n->right = right_child->left; 

        if (n->right != NULL)
                n->right->parent = n; 

        right_child->parent = n->parent; 

        if(n->parent == NULL) {
                tree->root = right_child; 
        } else if (n == n->parent->left) {
                (void) tree; 
                n->parent->left = right_child; 
        } else {
                (void) tree; 
                n->parent->right = right_child; 
        }

        right_child->left = n; 
        n->parent = right_child; 
}

void rotate_right(RedBlack_T tree, Node *n)
{ 
        Node *left_child = n->left; 

        n->left = left_child->right; 

        if (n->left != NULL)
                n->left->parent = n; 

        left_child->parent = n->parent; 

        if(n->parent == NULL) {
                tree->root = left_child; 
        } else if (n == n->parent->left) {
                (void) tree; 
                n->parent->left = left_child; 
        } else {
                (void) tree; 
                n->parent->right = left_child; 
        }

        left_child->right = n; 
        n->parent = left_child; 
}

Node *construct_node(void * value)
{
        Node *new_node = (Node *) malloc(sizeof(Node)); 

        new_node->parent = NULL;
        new_node->left = NULL; 
        new_node->right = NULL; 
        new_node->value = value; 

        new_node->color = RED; 

        return new_node; 
}

void *rb_search(RedBlack_T tree, void *value)
{
        Node *result = find_in_tree(tree, value, tree->comparison_func); 

        if (result != NULL) 
                return (void *) result->value; 

        return result; //AKA return NULL 
}

Node *find_in_tree(RedBlack_T tree, void *value, 
                   void *comparison_func(void *val1, void *val2))
{
        bool found = false; 
        Node *curr = tree->root; 
        int c = 0; 

        while (!found && curr != NULL) {
                c = (int)(intptr_t) comparison_func(value, curr->value); 

                if (c == 0) {
                        found = true; 
                } else if (c < 0) {
                        curr = curr->left; 
                } else if (c > 0) {
                        curr = curr->right; 
                }
        }

        return curr; 
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

void rb_map_inorder(RedBlack_T tree,  
                    void func_to_apply(void *value, int depth, void *cl), 
                    void *cl)
{
        int depth = 0; 

        rb_private_inorder_map(tree->root, depth, func_to_apply, cl); 
}

void rb_private_inorder_map(Node *root, 
                            int depth, 
                            void func_to_apply(void *root, int depth, void *cl), 
                            void *cl)
{

        if (root->left != NULL)
                rb_private_inorder_map(root->left, depth + 1, func_to_apply, cl); 

        func_to_apply(root->value, depth, cl); 

        if (root->right != NULL)
                rb_private_inorder_map(root->right, depth + 1, func_to_apply, cl); 
}