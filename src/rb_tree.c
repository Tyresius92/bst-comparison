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
Node *private_find_in_tree(RedBlack_T tree, void *value, void *comparison_func(void *val1, void *val2));
void rb_private_inorder_map(Node *root, 
                            int depth,
                            void func_to_apply(void *value, int depth, void *cl), 
                            void *cl);
void rb_private_preorder_map(Node *root, 
                             int depth, 
                             void func_to_apply(void *root, int depth, void *cl), 
                             void *cl);
void rb_private_postorder_map(Node *root, 
                              int depth, 
                              void func_to_apply(void *root, int depth, void *cl), 
                              void *cl);
Node *find_successor(Node *n); 
Node *find_predecessor(Node *n); 
void rb_transplant(T tree, Node *u, Node *v); 
void rb_delete_fixup(T tree, Node *x);
Node *subtree_minimum(Node *curr_node);
Node *subtree_maximum(Node *curr_node);
void *private_successor_of_value(RedBlack_T tree, void *value, 
                                 void *comparison_func(void *val1, void *val2));
void *private_predecessor_of_value(RedBlack_T tree, void *value, 
                                 void *comparison_func(void *val1, void *val2)); 

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

int rb_insert_value(T tree, void *value)
{
        assert(tree != NULL && value != NULL); 

        Node *new_node = construct_node(value); 
        tree->root = private_insert(tree->root, new_node, tree->comparison_func); 

        fix_violation(tree, new_node);  

        return 0;
}

void rb_delete_value(T tree, void *value)
{
        assert(tree != NULL && value != NULL); 

        Node *subtree_of_deleted = NULL; 

        Node *delete_me = private_find_in_tree(tree, value, tree->comparison_func); 

        if (delete_me == NULL) 
                return;

        Node *y = delete_me; 
        char y_original_color = y->color; 

        if (delete_me->left == NULL) {
                subtree_of_deleted = delete_me->right; 
                rb_transplant(tree, delete_me, delete_me->right); 
        } else if (delete_me->right == NULL) {
                subtree_of_deleted = delete_me->left; 
                rb_transplant(tree, delete_me, delete_me->left);
        } else {
                y = find_successor(delete_me); 
                y_original_color = y->color; 

                subtree_of_deleted = y->right; 

                if (y->parent == delete_me && subtree_of_deleted != NULL) {
                        subtree_of_deleted->parent = y; 
                } else {
                        rb_transplant(tree, y, y->right); 
                        y->right = delete_me->right; 
                        if (y->right != NULL)
                                y->right->parent = y; 
                }

                rb_transplant(tree, delete_me, y); 
                y->left = delete_me->left; 
                y->left->parent = y; 
                y->color = delete_me->color; 
        }

        free(delete_me); 

        if (y_original_color == BLACK) 
                rb_delete_fixup(tree, subtree_of_deleted); 
}

void rb_delete_fixup(T tree, Node *culprit)
{
        Node *sibling = NULL; 

        while (culprit != tree->root && culprit->color == BLACK) {
                if (culprit == culprit->parent->left) {
                        sibling = culprit->parent->right; 

                        if (sibling->color == RED) {
                                sibling->color = BLACK; 
                                culprit->parent->color = RED; 
                                rotate_left(tree, culprit->parent); 
                                sibling = culprit->parent->right; 
                        }

                        if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                                sibling->color = RED; 
                                culprit = culprit->parent; 
                        } else {
                                if (sibling->right->color == BLACK) {
                                        sibling->left->color = BLACK; 
                                        sibling->color = RED; 
                                        rotate_right(tree, sibling); 
                                        sibling = culprit->parent->right; 
                                }
                                sibling->color = culprit->parent->color; 
                                culprit->parent->color = BLACK; 
                                sibling->right->color = BLACK; 
                                rotate_left(tree, culprit->parent); 
                                culprit = tree->root; 
                        }
                } else { //culprit == culprit->parent->right
                        sibling = culprit->parent->left; 

                        if (sibling->color == RED) {
                                sibling->color = BLACK; 
                                culprit->parent->color = RED; 
                                rotate_left(tree, culprit->parent); 
                                sibling = culprit->parent->left; 
                        }

                        if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
                                sibling->color = RED; 
                                culprit = culprit->parent; 
                        } else {
                                if (sibling->left->color == BLACK) {
                                        sibling->right->color = BLACK; 
                                        sibling->color = RED; 
                                        rotate_left(tree, sibling); 
                                        sibling = culprit->parent->left; 
                                }
                                sibling->color = culprit->parent->color; 
                                culprit->parent->color = BLACK; 
                                sibling->left->color = BLACK; 
                                rotate_right(tree, culprit->parent); 
                                culprit = tree->root; 
                        }
                }
        }
        culprit->color = BLACK; 
}

void rb_transplant(T tree, Node *u, Node *v) 
{
        if (u->parent == NULL) 
                tree->root = v; 
        else if (u == u->parent->left)
                u->parent->left = v; 
        else 
                u->parent->right = v;

        if (v != NULL)
                v->parent = u->parent; 
}

void *successor_of_value(RedBlack_T tree, void *value)
{
        return private_successor_of_value(tree, value, tree->comparison_func); 
}

void *private_successor_of_value(RedBlack_T tree, void *value, 
                                 void *comparison_func(void *val1, void *val2))
{
        Node *curr_node = tree->root; 
        Node *successor = NULL; 

        while (curr_node != NULL) {
                int c = (int)(intptr_t) comparison_func(value, curr_node->value);

                if (c < 0) {
                        successor = curr_node; 
                        curr_node = curr_node->left; 
                } else {
                        curr_node = curr_node->right; 
                }
        }

        if (successor == NULL) 
                return NULL; 
        else
                return successor->value; 
}

void *predecessor_of_value(RedBlack_T tree, void *value)
{
        return private_predecessor_of_value(tree, value, tree->comparison_func); 
} 

void *private_predecessor_of_value(RedBlack_T tree, void *value, 
                                 void *comparison_func(void *val1, void *val2))
{
        Node *curr_node = tree->root; 
        Node *successor = NULL; 

        while (curr_node != NULL) {
                int c = (int)(intptr_t) comparison_func(value, curr_node->value);

                if (c > 0) {
                        successor = curr_node; 
                        curr_node = curr_node->right; 
                } else {
                        curr_node = curr_node->left; 
                }
        }

        if (successor == NULL) 
                return NULL; 
        else
                return successor->value; 
}

void *tree_minimum(T tree)
{
        Node *result = subtree_minimum(tree->root); 

        return result->value; 
}

void *tree_maximum(T tree)
{
        Node *result = subtree_maximum(tree->root); 

        return result->value; 
}

Node *subtree_minimum(Node *curr_node)
{
        while (curr_node->left != NULL)
                curr_node = curr_node->left; 

        return curr_node;
}

Node *find_successor(Node *n)
{
        return subtree_minimum(n->right);  
}

Node *subtree_maximum(Node *curr_node)
{
        while (curr_node->right != NULL)
                curr_node = curr_node->right; 

        return curr_node;
}

Node *find_predecessor(Node *n)
{
        return subtree_maximum(n->left); 
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
        Node *result = private_find_in_tree(tree, value, tree->comparison_func); 

        if (result != NULL) 
                return (void *) result->value; 

        return result; //AKA return NULL 
}

Node *private_find_in_tree(RedBlack_T tree, void *value, 
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

void rb_map_preorder(RedBlack_T tree, 
                     void func_to_apply(void *root, int depth, void *cl), 
                     void *cl)
{
        int depth = 0; 

        rb_private_preorder_map(tree->root, depth, func_to_apply, cl); 
}

void rb_private_preorder_map(Node *root, 
                            int depth, 
                            void func_to_apply(void *root, int depth, void *cl), 
                            void *cl)
{
        func_to_apply(root->value, depth, cl); 

        if (root->left != NULL)
                rb_private_preorder_map(root->left, depth + 1, func_to_apply, cl); 

        if (root->right != NULL)
                rb_private_preorder_map(root->right, depth + 1, func_to_apply, cl); 
}

void rb_map_postorder(RedBlack_T tree, 
                      void func_to_apply(void *root, int depth, void *cl), 
                      void *cl)
{
        int depth = 0; 

        rb_private_postorder_map(tree->root, depth, func_to_apply, cl); 
}

void rb_private_postorder_map(Node *root, 
                              int depth, 
                              void func_to_apply(void *root, int depth, void *cl), 
                              void *cl)
{
        if (root->left != NULL)
                rb_private_postorder_map(root->left, depth + 1, func_to_apply, cl); 

        if (root->right != NULL)
                rb_private_postorder_map(root->right, depth + 1, func_to_apply, cl); 

        func_to_apply(root->value, depth, cl); 

}