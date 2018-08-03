#include "vendor/unity.h"
#include "../src/splay_tree.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_splay_new(void)
{
        Splay_T test_tree = splay_new(NULL);
        TEST_ASSERT_NOT_NULL(test_tree);

        splay_free(test_tree); 
}

void test_splay_insert_string(void)
{
        Splay_T test_tree = splay_new(NULL);
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "Hello")); 

        splay_free(test_tree); 
}

void test_splay_is_empty_on_empty_tree(void)
{
        Splay_T test_tree = splay_new(NULL);
        TEST_ASSERT_TRUE(splay_is_empty(test_tree));

        splay_free(test_tree); 
}

void test_splay_is_empty_one_item_tree(void)
{
        Splay_T test_tree = splay_new(NULL);
        splay_insert_value(test_tree, "hello");

        TEST_ASSERT_FALSE(splay_is_empty(test_tree)); 

        splay_free(test_tree); 
}

void test_splay_get_value_at_root_empty_tree(void)
{
        Splay_T test_tree = splay_new(NULL); 
        TEST_ASSERT_NULL(splay_get_value_at_root(test_tree)); 

        splay_free(test_tree); 
}

void test_splay_insert_several_values(void)
{
        Splay_T test_tree = splay_new(NULL); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "hello")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "world"));
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "the"));
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "earth"));
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "says"));
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "hello"));

        splay_free(test_tree); 
}

void test_splay_insert_many_times(void)
{
        Splay_T test_tree = splay_new(NULL); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "a")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "b")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "c")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "d")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "e")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "f")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "g")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "h")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "i")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "j")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "k")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "l")); 

        splay_free(test_tree); 
}

void test_splay_insert_reversed_order(void)
{
        Splay_T test_tree = splay_new(NULL); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "l")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "k")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "j")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "i")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "h")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "g")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "f")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "e")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "d")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "c")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "b")); 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "a")); 

        splay_free(test_tree); 
}

void test_splay_search(void)
{
        Splay_T test_tree = splay_new(NULL); 

        splay_insert_value(test_tree, "a"); 
        TEST_ASSERT_NOT_NULL(splay_search(test_tree, "a")); 
        TEST_ASSERT_EQUAL_STRING("a", splay_search(test_tree, "a")); 

        TEST_ASSERT_NULL(splay_search(test_tree, "b")); 
        splay_insert_value(test_tree, "b"); 
        TEST_ASSERT_NOT_NULL(splay_search(test_tree, "b")); 
        TEST_ASSERT_EQUAL_STRING("b", splay_search(test_tree, "b")); 

        TEST_ASSERT_NULL(splay_search(test_tree, "hello")); 
        splay_insert_value(test_tree, "hello"); 
        TEST_ASSERT_NOT_NULL(splay_search(test_tree, "hello")); 
        TEST_ASSERT_EQUAL_STRING("a", splay_search(test_tree, "a")); 


        splay_free(test_tree); 
}

void test_splay_get_value_at_root_one_item_tree(void)
{
        Splay_T test_tree = splay_new(NULL); 
        TEST_ASSERT_NULL(splay_get_value_at_root(test_tree)); 

        splay_insert_value(test_tree, "hello"); 

        TEST_ASSERT_EQUAL_STRING("hello", splay_get_value_at_root(test_tree)); 

        splay_free(test_tree); 
}

void test_splay_get_value_at_root_after_insertions(void)
{
        Splay_T test_tree = splay_new(NULL); 
        TEST_ASSERT_NULL(splay_get_value_at_root(test_tree)); 

        splay_insert_value(test_tree, "hello"); 
        TEST_ASSERT_EQUAL_STRING("hello", splay_get_value_at_root(test_tree)); 

        splay_insert_value(test_tree, "a"); 
        TEST_ASSERT_EQUAL_STRING("a", splay_get_value_at_root(test_tree)); 

        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "b")); 
        TEST_ASSERT_EQUAL_STRING("b", splay_get_value_at_root(test_tree)); 

        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "c")); 
        TEST_ASSERT_EQUAL_STRING("c", splay_get_value_at_root(test_tree)); 

        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "d")); 
        TEST_ASSERT_EQUAL_STRING("d", splay_get_value_at_root(test_tree)); 

        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "e")); 
        TEST_ASSERT_EQUAL_STRING("e", splay_get_value_at_root(test_tree)); 

        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "f")); 
        TEST_ASSERT_EQUAL_STRING("f", splay_get_value_at_root(test_tree)); 

        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "g")); 
        TEST_ASSERT_EQUAL_STRING("g", splay_get_value_at_root(test_tree)); 

        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "h")); 
        TEST_ASSERT_EQUAL_STRING("h", splay_get_value_at_root(test_tree)); 

        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "i")); 
        TEST_ASSERT_EQUAL_STRING("i", splay_get_value_at_root(test_tree)); 

        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "j")); 
        TEST_ASSERT_EQUAL_STRING("j", splay_get_value_at_root(test_tree)); 

        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "k"));
        TEST_ASSERT_EQUAL_STRING("k", splay_get_value_at_root(test_tree)); 
 
        TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, "l")); 
        TEST_ASSERT_EQUAL_STRING("l", splay_get_value_at_root(test_tree)); 

        splay_free(test_tree); 
}

void test_splay_get_value_at_root_after_search(void)
{
        Splay_T test_tree = splay_new(NULL); 

        splay_insert_value(test_tree, "a"); 
        TEST_ASSERT_EQUAL_STRING("a", splay_search(test_tree, "a")); 
        TEST_ASSERT_EQUAL_STRING("a", splay_get_value_at_root(test_tree)); 

        TEST_ASSERT_NULL(splay_search(test_tree, "b")); 
        splay_insert_value(test_tree, "b"); 
        TEST_ASSERT_EQUAL_STRING("b", splay_search(test_tree, "b")); 
        TEST_ASSERT_EQUAL_STRING("b", splay_get_value_at_root(test_tree)); 

        TEST_ASSERT_NULL(splay_search(test_tree, "hello")); 
        splay_insert_value(test_tree, "hello"); 
        TEST_ASSERT_EQUAL_STRING("hello", splay_get_value_at_root(test_tree)); 

        TEST_ASSERT_EQUAL_STRING("a", splay_search(test_tree, "a")); 
        TEST_ASSERT_EQUAL_STRING("a", splay_get_value_at_root(test_tree)); 

        splay_free(test_tree); 
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

void test_splay_insert_ints(void)
{
        Splay_T test_tree = splay_new(&integer_comparison);

        int *test_ptr = NULL; 

        int a[] = { 1, 2, 3, 4, 5, 6, 6, 7, 9, 11};

        for (int i = 0; i < 10; i++) {
                test_ptr = &a[i]; 
                TEST_ASSERT_EQUAL(0, splay_insert_value(test_tree, test_ptr)); 
        }

        splay_free(test_tree); 
}

void test_splay_search_for_ints(void)
{
        Splay_T test_tree = splay_new(&integer_comparison);

        int *test_ptr = NULL; 

        int a[] = { 214, 25, 64, 4, 7, 729, 34, 28, 9, 11};

        for (int i = 0; i < 10; i++) {
                test_ptr = &a[i]; 
                splay_insert_value(test_tree, test_ptr); 
        }

        int x = 4; 
        int y = 9; 
        int z = 70000000; 

        TEST_ASSERT_NOT_NULL(splay_search(test_tree, &x)); 
        TEST_ASSERT_EQUAL(x, *(int *) splay_search(test_tree, &x)); 
        
        TEST_ASSERT_NOT_NULL(splay_search(test_tree, &y)); 
        TEST_ASSERT_EQUAL(y, *(int *) splay_search(test_tree, &y)); 

        TEST_ASSERT_NULL(splay_search(test_tree, &z)); 

        splay_free(test_tree); 
}

void test_splay_delete_value(void)
{
        Splay_T test_tree = splay_new(NULL); 
        splay_insert_value(test_tree, "hello"); 
        splay_insert_value(test_tree, "world");
        splay_insert_value(test_tree, "the");
        splay_insert_value(test_tree, "earth");
        splay_insert_value(test_tree, "says");

        TEST_ASSERT_EQUAL_STRING("hello", splay_search(test_tree, "hello")); 

        splay_delete_value(test_tree, "hello"); 

        TEST_ASSERT_NULL(splay_search(test_tree, "hello")); 
        TEST_ASSERT_EQUAL_STRING("world", splay_search(test_tree, "world"));
        TEST_ASSERT_EQUAL_STRING("the", splay_search(test_tree, "the"));
        TEST_ASSERT_EQUAL_STRING("earth", splay_search(test_tree, "earth"));
        TEST_ASSERT_EQUAL_STRING("says", splay_search(test_tree, "says"));

        splay_delete_value(test_tree, "the"); 

        TEST_ASSERT_NULL(splay_search(test_tree, "the"));
        TEST_ASSERT_NULL(splay_search(test_tree, "hello")); 
        TEST_ASSERT_EQUAL_STRING("world", splay_search(test_tree, "world"));
        TEST_ASSERT_EQUAL_STRING("earth", splay_search(test_tree, "earth"));
        TEST_ASSERT_EQUAL_STRING("says", splay_search(test_tree, "says"));

        splay_delete_value(test_tree, "earth"); 

        TEST_ASSERT_NULL(splay_search(test_tree, "earth"));
        TEST_ASSERT_NULL(splay_search(test_tree, "the"));
        TEST_ASSERT_NULL(splay_search(test_tree, "hello")); 
        TEST_ASSERT_EQUAL_STRING("world", splay_search(test_tree, "world"));
        TEST_ASSERT_EQUAL_STRING("says", splay_search(test_tree, "says"));

        splay_delete_value(test_tree, "world"); 

        TEST_ASSERT_NULL(splay_search(test_tree, "earth"));
        TEST_ASSERT_NULL(splay_search(test_tree, "the"));
        TEST_ASSERT_NULL(splay_search(test_tree, "hello")); 
        TEST_ASSERT_NULL(splay_search(test_tree, "world"));
        TEST_ASSERT_EQUAL_STRING("says", splay_search(test_tree, "says"));

        splay_delete_value(test_tree, "says"); 

        TEST_ASSERT_NULL(splay_search(test_tree, "earth"));
        TEST_ASSERT_NULL(splay_search(test_tree, "the"));
        TEST_ASSERT_NULL(splay_search(test_tree, "hello")); 
        TEST_ASSERT_NULL(splay_search(test_tree, "world"));
        TEST_ASSERT_NULL(splay_search(test_tree, "says"));

        TEST_ASSERT_TRUE(splay_is_empty(test_tree)); 

        splay_free(test_tree); 
}

void test_splay_delete_value_not_in_tree(void)
{
        Splay_T test_tree = splay_new(NULL); 
        splay_insert_value(test_tree, "hello"); 
        splay_insert_value(test_tree, "world");
        splay_insert_value(test_tree, "the");
        splay_insert_value(test_tree, "earth");
        splay_insert_value(test_tree, "says");

        TEST_ASSERT_EQUAL_STRING("hello", splay_search(test_tree, "hello")); 
        TEST_ASSERT_EQUAL_STRING("world", splay_search(test_tree, "world"));
        TEST_ASSERT_EQUAL_STRING("the", splay_search(test_tree, "the"));
        TEST_ASSERT_EQUAL_STRING("earth", splay_search(test_tree, "earth"));
        TEST_ASSERT_EQUAL_STRING("says", splay_search(test_tree, "says"));
        TEST_ASSERT_NULL(splay_search(test_tree, "not_in_tree"));

        splay_delete_value(test_tree, "not_in_tree"); 

        TEST_ASSERT_EQUAL_STRING("hello", splay_search(test_tree, "hello")); 
        TEST_ASSERT_EQUAL_STRING("world", splay_search(test_tree, "world"));
        TEST_ASSERT_EQUAL_STRING("the", splay_search(test_tree, "the"));
        TEST_ASSERT_EQUAL_STRING("earth", splay_search(test_tree, "earth"));
        TEST_ASSERT_EQUAL_STRING("says", splay_search(test_tree, "says"));
        TEST_ASSERT_NULL(splay_search(test_tree, "not_in_tree"));

        splay_free(test_tree); 
}

void test_splay_tree_minimum(void)
{
        Splay_T test_tree = splay_new(NULL); 
        splay_insert_value(test_tree, "hello"); 
        splay_insert_value(test_tree, "world");
        splay_insert_value(test_tree, "the");
        splay_insert_value(test_tree, "earth");
        splay_insert_value(test_tree, "says");

        TEST_ASSERT_EQUAL_STRING("earth", splay_tree_minimum(test_tree)); 

        splay_free(test_tree); 
}

void test_splay_tree_maximum(void)
{
        Splay_T test_tree = splay_new(NULL); 
        splay_insert_value(test_tree, "hello"); 
        splay_insert_value(test_tree, "world");
        splay_insert_value(test_tree, "the");
        splay_insert_value(test_tree, "earth");
        splay_insert_value(test_tree, "says");

        TEST_ASSERT_EQUAL_STRING("world", splay_tree_maximum(test_tree)); 

        splay_free(test_tree); 
}

void test_splay_successor_of_value(void)
{
        Splay_T test_tree = splay_new(NULL); 
        splay_insert_value(test_tree, "hello"); 
        splay_insert_value(test_tree, "world");
        splay_insert_value(test_tree, "the");
        splay_insert_value(test_tree, "earth");
        splay_insert_value(test_tree, "says");

        TEST_ASSERT_EQUAL_STRING("world", splay_successor_of_value(test_tree, "the"));
        TEST_ASSERT_EQUAL_STRING("hello", splay_successor_of_value(test_tree, "earth"));
        TEST_ASSERT_EQUAL_STRING("the", splay_successor_of_value(test_tree, "says")); 
        TEST_ASSERT_EQUAL_STRING("says", splay_successor_of_value(test_tree, "not_in_tree"));
        TEST_ASSERT_NULL(splay_successor_of_value(test_tree, "world"));

        splay_free(test_tree); 
}

void test_splay_predecessor_of_value(void)
{
        Splay_T test_tree = splay_new(NULL); 
        splay_insert_value(test_tree, "hello"); 
        splay_insert_value(test_tree, "world");
        splay_insert_value(test_tree, "the");
        splay_insert_value(test_tree, "earth");
        splay_insert_value(test_tree, "says");

        TEST_ASSERT_EQUAL_STRING("says", splay_predecessor_of_value(test_tree, "the"));
        TEST_ASSERT_EQUAL_STRING("hello", splay_predecessor_of_value(test_tree, "says"));
        TEST_ASSERT_EQUAL_STRING("earth", splay_predecessor_of_value(test_tree, "hello"));  
        TEST_ASSERT_EQUAL_STRING("hello", splay_predecessor_of_value(test_tree, "not_in_tree"));
        TEST_ASSERT_NULL(splay_predecessor_of_value(test_tree, "earth"));

        splay_free(test_tree); 
}

int main(void)
{
        UnityBegin("test/test_splay_tree.c");

        RUN_TEST(test_splay_new); 
        RUN_TEST(test_splay_insert_string); 
        RUN_TEST(test_splay_is_empty_on_empty_tree); 
        RUN_TEST(test_splay_is_empty_one_item_tree); 
        RUN_TEST(test_splay_get_value_at_root_empty_tree); 
        RUN_TEST(test_splay_insert_several_values); 
        RUN_TEST(test_splay_insert_many_times); 
        RUN_TEST(test_splay_insert_reversed_order); 
        RUN_TEST(test_splay_get_value_at_root_one_item_tree); 
        RUN_TEST(test_splay_get_value_at_root_after_insertions); 
        RUN_TEST(test_splay_get_value_at_root_after_search); 
        RUN_TEST(test_splay_search); 
        RUN_TEST(test_splay_insert_ints); 
        RUN_TEST(test_splay_search_for_ints); 
        RUN_TEST(test_splay_delete_value); 
        RUN_TEST(test_splay_delete_value_not_in_tree); 
        RUN_TEST(test_splay_tree_minimum); 
        RUN_TEST(test_splay_tree_maximum); 
        RUN_TEST(test_splay_successor_of_value); 
        RUN_TEST(test_splay_predecessor_of_value); 

        UnityEnd();
        return 0;
}
