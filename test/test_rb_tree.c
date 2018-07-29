#include "vendor/unity.h"
#include "../src/rb_tree.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_new_rb_tree(void)
{
        RedBlack_T test_tree = new_rb_tree(NULL);
        TEST_ASSERT_NOT_NULL(test_tree);

        free(test_tree); 
}

void test_insert_string(void)
{
        RedBlack_T test_tree = new_rb_tree(NULL);
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "Hello")); 

        free_rb_tree(test_tree); 
}

void test_is_empty_on_empty_tree(void)
{
        RedBlack_T test_tree = new_rb_tree(NULL);
        TEST_ASSERT_TRUE(rb_tree_is_empty(test_tree));

        free(test_tree); 
}

void test_is_empty_one_item_tree(void)
{
        RedBlack_T test_tree = new_rb_tree(NULL);
        insert_value(test_tree, "hello");

        TEST_ASSERT_FALSE(rb_tree_is_empty(test_tree)); 

        free_rb_tree(test_tree); 
}

void test_insert_several_values(void)
{
        RedBlack_T test_tree = new_rb_tree(NULL); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "hello")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "world"));
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "the"));
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "earth"));
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "says"));
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "hello"));

        free_rb_tree(test_tree); 
}

void test_insert_many_times_and_force_rebalancing(void)
{
        RedBlack_T test_tree = new_rb_tree(NULL); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "a")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "b")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "c")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "d")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "e")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "f")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "g")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "h")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "i")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "j")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "k")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "l")); 

        free_rb_tree(test_tree); 
}

void test_insert_reversed_order_and_force_rebalancing(void)
{
        RedBlack_T test_tree = new_rb_tree(NULL); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "l")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "k")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "j")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "i")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "h")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "g")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "f")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "e")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "d")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "c")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "b")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "a")); 

        free_rb_tree(test_tree); 
}

void test_search(void)
{
        RedBlack_T test_tree = new_rb_tree(NULL); 

        insert_value(test_tree, "a"); 
        TEST_ASSERT_NOT_NULL(rb_search(test_tree, "a")); 
        TEST_ASSERT_EQUAL_STRING("a", rb_search(test_tree, "a")); 

        TEST_ASSERT_NULL(rb_search(test_tree, "b")); 
        insert_value(test_tree, "b"); 
        TEST_ASSERT_NOT_NULL(rb_search(test_tree, "b")); 
        TEST_ASSERT_EQUAL_STRING("b", rb_search(test_tree, "b")); 

        TEST_ASSERT_NULL(rb_search(test_tree, "hello")); 
        insert_value(test_tree, "hello"); 
        TEST_ASSERT_NOT_NULL(rb_search(test_tree, "hello")); 
        TEST_ASSERT_EQUAL_STRING("a", rb_search(test_tree, "a")); 


        free_rb_tree(test_tree); 
}

int integer_comparison(void *val_one, void *val_two)
{
        if (*(int *) val_one == *(int *) val_two) {
                return 0; 
        } else if (*(int *) val_one > *(int *) val_two) {
                return 1; 
        } else {
                return -1; 
        }
}

void test_insert_ints(void)
{
        RedBlack_T test_tree = new_rb_tree(&integer_comparison);

        int *test_ptr = NULL; 

        int a[] = { 1, 2, 3, 4, 5, 6, 6, 7, 9, 11};

        for (int i = 0; i < 10; i++) {
                test_ptr = &a[i]; 
                TEST_ASSERT_EQUAL(0, insert_value(test_tree, test_ptr)); 
        }

        free_rb_tree(test_tree); 
}

void test_search_for_ints(void)
{
        RedBlack_T test_tree = new_rb_tree(&integer_comparison);

        int *test_ptr = NULL; 

        int a[] = { 214, 25, 64, 4, 7, 729, 34, 28, 9, 11};

        for (int i = 0; i < 10; i++) {
                test_ptr = &a[i]; 
                insert_value(test_tree, test_ptr); 
        }

        int x = 4; 
        int y = 9; 
        int z = 70000000; 

        TEST_ASSERT_NOT_NULL(rb_search(test_tree, &x)); 
        TEST_ASSERT_EQUAL(x, *(int *) rb_search(test_tree, &x)); 
        
        TEST_ASSERT_NOT_NULL(rb_search(test_tree, &y)); 
        TEST_ASSERT_EQUAL(y, *(int *) rb_search(test_tree, &y)); 

        TEST_ASSERT_NULL(rb_search(test_tree, &z)); 

        free_rb_tree(test_tree); 
}

struct string_closure_size_six {
        int depth_ray[6]; 
        int index; 
};


void function_to_apply_test_map_inorder_string(void *value, int depth, void *cl)
{
        struct *closure = (struct string_closure_size_six *) cl; 
                
        closure->depth_ray[index] = depth; 

        closure->index = index + 1; 
}

void test_rb_map_inorder_string(void)
{
        RedBlack_T test_tree = new_rb_tree(NULL); 

        char *word_ray[] = {"hello", "world", "the", "earth", "says", "hello"}; 
        int expected_depth[] = { 2, 1, 3, 2, 0, 1 }

        insert_value(test_tree, word_ray[0]); 
        insert_value(test_tree, word_ray[1]);
        insert_value(test_tree, word_ray[2]);
        insert_value(test_tree, word_ray[3]);
        insert_value(test_tree, word_ray[4]);
        insert_value(test_tree, word_ray[5]);

        string_closure_size_six->depth_ray = {-1, -1, -1, -1, -1, -1}
        string_closure_size_six->index = 0; 
        
        rb_map_inorder(test_tree, &function_to_apply_test_map_inorder_string, &string_closure_size_six);

        free_rb_tree(test_tree); 
}

int main(void)
{
        UnityBegin("test/test_bst_node.c");

        RUN_TEST(test_new_rb_tree); 
        RUN_TEST(test_insert_string); 
        RUN_TEST(test_is_empty_on_empty_tree); 
        RUN_TEST(test_is_empty_one_item_tree); 
        RUN_TEST(test_insert_several_values); 
        RUN_TEST(test_insert_many_times_and_force_rebalancing); 
        RUN_TEST(test_insert_reversed_order_and_force_rebalancing); 
        RUN_TEST(test_search); 
        RUN_TEST(test_insert_ints); 
        RUN_TEST(test_search_for_ints); 

        RUN_TEST(test_rb_map_inorder_string); 

        UnityEnd();
        return 0;
}
