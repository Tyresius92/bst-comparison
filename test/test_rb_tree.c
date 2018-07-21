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
        TEST_ASSERT_NOT_NULL(new_rb_tree());
}

void test_insert_null_value(void)
{
        RedBlack_T test_tree = new_rb_tree(); 
        TEST_ASSERT_EQUAL(-1, insert_value(test_tree, NULL)); 

        free(test_tree);
}

void test_insert_null_tree(void)
{
        TEST_ASSERT_EQUAL(-1, insert_value(NULL, (void *) "hello")); 
}

void test_insert_null_tree_and_null_value(void)
{
        TEST_ASSERT_EQUAL(-1, insert_value(NULL, NULL));
}

void test_is_empty_null_tree(void)
{
        RedBlack_T test_tree = new_rb_tree();
        TEST_ASSERT_TRUE(rb_tree_is_empty(test_tree));
}

void test_is_empty_one_item_tree(void)
{
        
}

int main(void)
{
        UnityBegin("test/test_bst_node.c");

        RUN_TEST(test_new_rb_tree); 
        RUN_TEST(test_insert_null_value);
        RUN_TEST(test_insert_null_tree); 
        RUN_TEST(test_insert_null_tree_and_null_value);
        RUN_TEST(test_is_empty_null_tree); 

        UnityEnd();
        return 0;
}
