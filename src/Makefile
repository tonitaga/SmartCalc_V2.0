CC=g++
CFLAGS=-Wall -Werror -Wextra -std=c++17
TESTFLAGS=-lgtest
SRC=Engineer/*.cpp
HEADER=Engineer/*.hpp

OBJ=$(patsubst %.cpp, %.o, $(SRC))
OS=$(shell uname)

.PHONY: all

all: build static_lib test

build:
	@$(CC) $(CFLAGS) -c $(SRC)

static_lib:
	@ar rc Engineer.a engineermodel.o
	@ranlib Engineer.a
	@echo ==Static lib created==

test: build static_lib test.cpp
	@$(CC) $(CFLAGS) -c test.cpp -o test.o
	@$(CC) test.o $(SRC) $(TESTFLAGS) -o test
	@./test

gcov_report: all
	@$(CC) $(CFLAGS) --coverage test.cpp $(SRC) Engineer.a $(TESTFLAGS) -o gcov_report
	@chmod +x *
	@./gcov_report
	@lcov -t "gcov_report" -o gcov_report.info --no-external -c -d .
	@genhtml -o report/ gcov_report.info
	@open ./report/index.html

install:
	@make clean
	@mkdir build
	@cd TinyWindowsCalculator && qmake && make -j6 && make clean && rm Makefile && cd ../ && mv TinyWindowsCalculator/TinyWindowsCalculator.app build
	@echo ==Install finished==
	@echo ==To open application write 'make open'==

uninstall:
	@rm -rf build/
	@echo ==Uninstall finished==

dvi:
	@open readme.html

dist:
	@rm -rf Archive_SmartCalc_v2.0/
	@mkdir Archive_SmartCalc_v2.0/
	@mkdir Archive_SmartCalc_v2.0/src
	@mv ./build/TinyWindowsCalculator.app Archive_SmartCalc_v2.0/src/
	@tar cvzf Archive_SmartCalc_v2.0.tgz Archive_SmartCalc_v2.0/
	@rm -rf Archive_SmartCalc_v2.0/
	@echo ==Archive was created==
	
clean:
	@rm -rf *.{a,o,dSYM,out}
	@rm -rf $(EXECUTABLE)
	@rm -rf gcov_report
	@rm -rf report
	@rm -rf CPPLINT.cppfg
	@rm -rf *.gcda
	@rm -rf *.gcno
	@rm -rf *.info
	@rm -rf test
	@rm -rf Archive_SmartCalc_v2.0 
	@rm -rf *tgz
	@rm -rf build
	@rm -rf gcov_test
	@echo ==Clean was finished==

rebuild: clean all

check:
	@cp ../materials/linters/.clang-format .clang-format
	@clang-format -i Engineer/*.cpp Engineer/*.h
	@clang-format -n Engineer/*.cpp Engineer/*.h
	@clang-format -i TinyWindowsCalculator/*.cpp TinyWindowsCalculator/*.h
	@clang-format -n TinyWindowsCalculator/*.cpp TinyWindowsCalculator/*.h
	@cd ../
	@rm .clang-format
	@echo ==No style errors==

open:
	@open build/TinyWindowsCalculator.app