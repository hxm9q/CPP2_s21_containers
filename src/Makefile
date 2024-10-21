CPP = g++
CPPFLAGS = -std=c++17 -I/opt/homebrew/opt/googletest/include --coverage
LDFLAGS = -L/opt/homebrew/opt/googletest/lib -lgtest -lgtest_main -pthread
LIBRARY = tests/*.cpp
EXE = test_exe
COVERAGE = -fprofile-arcs -lcheck -ftest-coverage

all : clean test gcov_report

test : $(EXE)
	./$(EXE)

$(EXE): $(LIBRARY)
	$(CPP) $(CPPFLAGS) -o $@ $(LIBRARY) $(LDFLAGS)

gcov_report : test
		#gcov -f *.gcda
		lcov -t "test_exe" -o test_exe.info -c -d .
		genhtml -o report test_exe.info
clean :
	@rm -rf report
	@rm -f $(EXE) *.log *.gc* *.info