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
        RedBlack_T test_tree = new_rb_tree();
        TEST_ASSERT_NOT_NULL(test_tree);

        free(test_tree); 
}

void test_insert_string(void)
{
        RedBlack_T test_tree = new_rb_tree();
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "Hello")); 

        free_rb_tree(test_tree); 
}

void test_is_empty_on_empty_tree(void)
{
        RedBlack_T test_tree = new_rb_tree();
        TEST_ASSERT_TRUE(rb_tree_is_empty(test_tree));

        free(test_tree); 
}

void test_is_empty_one_item_tree(void)
{
        RedBlack_T test_tree = new_rb_tree();
        insert_value(test_tree, "hello");

        TEST_ASSERT_FALSE(rb_tree_is_empty(test_tree)); 

        free_rb_tree(test_tree); 
}

void test_insert_several_values(void)
{
        RedBlack_T test_tree = new_rb_tree(); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "hello")); 
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "world"));
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "the"));
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "earth"));
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "says"));
        TEST_ASSERT_EQUAL(0, insert_value(test_tree, "hello"));

        rb_map(test_tree, NULL, NULL); 

        free_rb_tree(test_tree); 
}

void test_insert_many_times_and_force_rebalancing(void)
{
        RedBlack_T test_tree = new_rb_tree(); 
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
        RedBlack_T test_tree = new_rb_tree(); 
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

        rb_map(test_tree, NULL, NULL); 

        free_rb_tree(test_tree); 
}

void test_is_in_tree(void)
{
        RedBlack_T test_tree = new_rb_tree(); 
        insert_value(test_tree, "a"); 

        TEST_ASSERT_TRUE(is_in_tree(test_tree, "a")); 
        TEST_ASSERT_FALSE(is_in_tree(test_tree, "b")); 

        insert_value(test_tree, "b"); 

        TEST_ASSERT_TRUE(is_in_tree(test_tree, "b")); 

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
        RUN_TEST(test_is_in_tree); 

        UnityEnd();
        return 0;
}
