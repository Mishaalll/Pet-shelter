CXX = g++

all: shelter

shelter: src/main.cpp src/employee.cpp src/pet.cpp src/shelter.cpp
	$(CXX) -std=c++17 -Iheaders src/main.cpp src/employee.cpp src/pet.cpp src/shelter.cpp -o shelter

run: shelter
	./shelter $(ARGS)

clear:
	rm shelter
