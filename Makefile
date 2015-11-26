objects = main.o stdafx.o Input.o Output.o Deal.o Variable.o Calculator.o Calculate.o

calculator : $(objects)
	g++ -lncursesw -o calculator $(objects)

main.o : main.cpp
stdafx.o : stdafx.cpp
Input.o : Input.cpp
	g++ -std=c++11 -c Input.cpp
Output.o : Output.cpp
	g++ -std=c++11 -c Output.cpp
Deal.o : Deal.cpp
	g++ -std=c++11 -c Deal.cpp
Variable.o : Variable.cpp
Calculate.o : Calculate.cpp
	g++ -std=c++11 -c Calculate.cpp
Calculator.o : Calculator.cpp

clean:
	rm Calculator $(objects)
