CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = traffic_signal

.PHONY: all clean run test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean: 
	rm -f $(SRCDIR)/*.o $(TARGET) tests/test_runner

test: $(SRCDIR)/traffic_light.o tests/test_traffic_light.cpp
	$(CXX) $(CXXFLAGS) tests/test_traffic_light.cpp $(SRCDIR)/traffic_light.o -o tests/test_runner
	./tests/test_runner