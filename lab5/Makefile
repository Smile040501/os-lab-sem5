all: run

solution.out: solution.cpp
	g++ -o solution.out -pthread solution.cpp

run: solution.out
	./solution.out

clean:
	rm -rf solution.out