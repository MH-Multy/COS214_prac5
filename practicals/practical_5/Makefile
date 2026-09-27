# Emmanuel Boateng (23586975)
# Mohammadhossein Jafari (25312040)
# Jay Macaskill (25198387)

# COS 214 (Software Modelling) Practical 5
# Last Modified: 27 September 2026

# Makefile

CXX      := g++
CXXFLAGS := -std=c++11 -Wall -g

SRC := $(wildcard *.cpp)

MAIN_SRC := $(filter-out demo.cpp, $(SRC))
DEMO_SRC := $(filter-out main.cpp, $(SRC))

MAIN_OBJ := $(MAIN_SRC:.cpp=.o)
DEMO_OBJ := $(DEMO_SRC:.cpp=.o)

OBJ := $(MAIN_OBJ) $(DEMO_OBJ)
DEP := $(OBJ:.o=.d)

TARGET      := campusguard
DEMO_TARGET := demo

all: $(TARGET) $(DEMO_TARGET)

$(TARGET): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(DEMO_TARGET): $(DEMO_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP) $(TARGET) $(DEMO_TARGET)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

valgrind-demo:
	valgrind --leak-check=full --show-leak-kinds=all ./$(DEMO_TARGET)

.PHONY: all clean valgrind valgrind-demo
