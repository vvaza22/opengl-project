# HUGE WARNING! THIS DOES NOT WORK---> (linker error)
# g++ -lgtest -lgtest_main -pthread $^ -o $@

# THIS WORKS! (ORDER MATTERS)
# g++ $^ -lgtest -lgtest_main -pthread -o $@

main.out: test_runner.o add.o add_test.o
	g++ $^ -lgtest -lgtest_main -pthread -o $@
	./$@

test_runner.o: test_runner.cpp
	g++ -lgtest -lgtest_main -pthread -c $^ -o $@

add.o: add.cpp
	g++ $^ -lgtest -lgtest_main -pthread -c -o $@

add_test.o: add_test.cpp
	g++ $^ -lgtest -lgtest_main -pthread -c -o $@