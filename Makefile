CXX = g++

CXXFLAGS = -std=c++17 -Wall -I. -IGameData -IGameData/PeaAndBlock

SRCS = test.cpp \
       $(wildcard GameData/*.cpp) \
       $(wildcard GameData/PeaAndBlock/*.cpp) \
	   $(wildcard GameData/HwaryoChecker/*.cpp)

OBJS = $(SRCS:.cpp=.o)
TARGET = test

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)