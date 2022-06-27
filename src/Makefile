.PHONY: all clean tests dvi install uninstall dist
XX=g++
APP=$(BD)smart_calc_v2.app

FILES= MODEL/calculatorModel.cpp \
	   MODEL/graphModel.cpp \
	   MODEL/depositModel.cpp \
	   MODEL/creditModel.cpp \
	   CONTROLLER/calculatorController.cpp \

DIRS= VIEW \
	  MODEL \
	  QCUSTOMPLOT \
	  CONTROLLER \
	  img \

LDFLAGS= -Wall -Wextra -Werror -std=c++17 -g
OS := $(shell uname -s)
TEST_FLAGS= -lgtest -lgtest_main -lpthread
CFLAGS= -fprofile-arcs -ftest-coverage
BD= build/

ifeq ($(OS), Darwin)
	CC += -D OS_MAC
else
	CC += -D OS_LINUX
endif

all: build install tests

build: clean copy
	cd $(BD); qmake smart_calc_v2.pro
	make -C $(BD)

copy:
	@mkdir build
	cp *.pro *.cpp $(BD)
	rsync -rupE $(DIRS) img $(BD)

install: build
	@mkdir $(HOME)/Applications/SmartCalcV2/ 2>/dev/null
	cp -rf $(APP) $(HOME)/Applications/SmartCalcV2/
	make clean

uninstall: 
	rm -rf $(HOME)/Applications/SmartCalcV2

dist:
	rm -rf SmartCalcV2
	mkdir SmartCalcV2
	cp Makefile *.pro *.cpp *.user SmartCalcV2/
	rsync -rupE $(DIRS)  SmartCalcV2/
	tar -cvzf $(HOME)/Desktop/SmartCalcV2.tgz SmartCalcV2/
	rm -rf SmartCalcV2/

dvi:
	open DOCUMENTATION/man.html

tests: clean
	$(XX) $(LDFLAGS) $(FLAGS) TESTS/calculatorTests.cpp $(FILES) -lstdc++ $(TEST_FLAGS) -o test
	./test

clean:
	rm -rf build test *.a *.o *.cfg *.gcda *.gcno *.html *.info *.dSYM report
