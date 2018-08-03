CFLAGS  = -std=c99
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
#CFLAGS += -pedantic
CFLAGS += -Werror

VFLAGS  = --quiet
VFLAGS += --tool=memcheck
VFLAGS += --leak-check=full
VFLAGS += --error-exitcode=1

compare_bst: src/compare_bsts.c src/compare_bsts.h splay.o rb_tree.o basic_bst.o
	@echo Compiling $@ executable
	@$(CC) $(CFLAGS) src/rb_tree.c splay_tree.o basic_bst.o compare_bsts.o -o compare_bst

test: splay_tests.out bst_tests.out rb_tests.out
	@./bst_tests.out
	@./rb_tests.out
	@./splay_tests.out

memcheck: bst_tests.out rb_tests.out splay_tests.out
	@valgrind $(VFLAGS) ./bst_tests.out
	@valgrind $(VFLAGS) ./rb_tests.out
	@valgrind $(VFLAGS) ./splay_tests.out
	@echo "Memory check passed"

splay.o: src/splay_tree.c src/splay_tree.h 
	@$(CC) $(CFLAGS) src/splay_tree.c -c splay.o

rb_tree.o: src/rb_tree.c src/rb_tree.h 
	@$(CC) $(CFLAGS) src/rb_tree.c -c rb_tree.o

basic_bst.o: src/basic_bst.c src/basic_bst.h
	@$(CC) $(CFLAGS) src/basic_bst.c -c basic_bst.o

clean:
	rm -rf *.o *.out *.out.dSYM *~

rb_tests.out: test/test_rb_tree.c src/rb_tree.c src/rb_tree.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) src/rb_tree.c test/vendor/unity.c test/test_rb_tree.c -o rb_tests.out

bst_tests.out: test/test_basic_bst.c src/basic_bst.c src/basic_bst.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) src/basic_bst.c test/vendor/unity.c test/test_basic_bst.c -o bst_tests.out

splay_tests.out: test/test_splay_tree.c src/splay_tree.c src/splay_tree.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) src/splay_tree.c test/vendor/unity.c test/test_splay_tree.c -o splay_tests.out
