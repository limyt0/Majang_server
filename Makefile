CXX = g++

CXXFLAGS = -std=c++17 -Wall -I. -IGameData -IGameData/PeaAndBlock

# 링킹 옵션 (스레드 라이브러리 추가)
LDFLAGS = -pthread

SRCS = test.cpp \
	   GameManager.cpp \
       $(wildcard GameData/*.cpp) \
       $(wildcard GameData/PeaAndBlock/*.cpp) \
	   $(wildcard HwaryoChecker/*.cpp) \
	   $(wildcard HwaryoChecker/Yaku/*.cpp)

OBJS = $(SRCS:.cpp=.o)
TARGET = test

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)