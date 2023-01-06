NAME = my_matrix
CC := g++ -std=c++17
CFLAGS := -Wall -Werror -Wextra
GCOV := -fprofile-arcs -ftest-coverage
HEADERS := my_matrix.h
SOURCES := my_matrix.cpp
OBJECTS := my_matrix.o
TEST_NAME := test
TEST_SOURCES := test.cpp

OS=$(shell uname -s)
ifeq ($(OS),Darwin)
	GTESTFLAGS=-lgtest -lgtest_main 
	OPENFILE=open
else
	GTESTFLAGS=-lgtest -lgtest_main -lpthread -lrt -lm -lsubunit -ldl
	OPENFILE=xdg-open 
endif

.PHONY: test

all: test

$(NAME).a:
	$(CC) $(CFLAGS) -c $(SOURCES) -o $(OBJECTS)
	ar rcs lib$(NAME).a $(OBJECTS)
	ranlib lib$(NAME).a

test: $(NAME).a
	@$(CC) $(GCOV) $(TEST_SOURCES) -L . -l$(NAME) $(GTESTFLAGS) -o $(TEST_NAME)
	./$(TEST_NAME)
	@rm -f *.o 
	@make gcov_report
	
gcov_report: 
	@lcov -t "GcovReport" -o GcovReport.info -c -d . --no-external
	@genhtml  -o report GcovReport.info
	$(OPENFILE) ./report/index.html
	@rm -f *.gcno *.gcda *.info

clean:
	@rm -f *.o *.a a.out
	@rm -f $(TEST_NAME)
	@rm -f *.gcno *.gcda *.info
	@rm -rf ./report
	@rm -f valgrind-out.txt

rebuild: clean all

clang:
	clang-format -i $(SOURCES) $(TEST_SOURCES) $(HEADERS)

#----Checking----
linter:
	echo "--------Linter Clang-Format--------"
	clang-format -n $(SOURCES) $(TEST_SOURCES) $(HEADERS)
leaks:
	echo "--------Leaks Checking--------"
	CK_FORK=no leaks -atExit -- ./$(TEST_NAME)
cppcheck:
	echo "--------Static Code Checking--------"
	cppcheck --enable=all --suppress=missingIncludeSystem ./
valgrind:
	CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./$(TEST_NAME) >valgrind-out.txt 2>&1


