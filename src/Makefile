CC= gcc
 CFLAGS =  -Wall -Werror -Wextra -std=c11
SOURSES_C= datastructs/*.c parse_input.c reverse_polish_notation.c calculations.c utils.c
SOURSES_O= linked_list.o stack_list.o parse_input.o reverse_polish_notation.o calculations.o utils.o stack_num.o
LIB=SmartCalc.a
RUN = build/smart_calc
TEST_FLAGS=-lcheck -lrt -lpthread -lsubunit -lm
TEST_FLAGS_MAC=-lcheck  -lpthread -lm
COV_FLAGS=--coverage

all: install
	$(RUN)

$(LIB):	$(SOURSES_C)
	$(CC)  $(CFLAGS) -c $(SOURSES_C)  $(COV_FLAGS)
	ar rcs $(LIB)  $(SOURSES_O) 
	ranlib $(LIB)

format:
	clang-format -i *.c *.h  datastructs/*.c datastructs/*.h smart_calc/*.cpp smart_calc/*.h test/*.c test/*.h
check:
	clang-format -i *.c *.h  datastructs/*.c datastructs/*.h smart_calc/*.cpp smart_calc/*.h test/*.c test/*.h

clean:
	rm -rf *.o
	rm -rf *.a main
	rm -rf $(LIB)
	rm -rf coverage*
	rm -rf *.gcda *.gcno testing 

dvi:
	open ../README.md

install: uninstall
	mkdir build
	cd build && cmake build ../smart_calc
	make -C ./build/

uninstall:
	rm -Rf build/
	rm -rf SmartCalc_v1.0.tar

dist:
	tar -cf SmartCalc_v1.0.tar smart_calc

test: $(LIB) test_main.o test_case_general.o
	$(CC) -o testing $(CFLAGS) test_main.o test_case_general.o -L. $(LIB)  $(COV_FLAGS) $(TEST_FLAGS)
	./testing

test_mac: $(LIB) test_main.o test_case_general.o
	$(CC) -o testing $(CFLAGS) test_main.o test_case_general.o -L. $(LIB)  $(COV_FLAGS) $(TEST_FLAGS_MAC)
	./testing



test_case_general.o:
	$(CC) $(CFLAGS)  -c test/test_case_general.c

gcov_report:
	gcovr -r . --html --html-details -o coverage_report.html

test_main.o:
	$(CC) $(CFLAGS)  -c test/test_main.c
