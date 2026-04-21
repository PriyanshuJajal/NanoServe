CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
LDFLAGS = -lws2_32

SRCS = src/main.cpp src/TCPServer.cpp src/HTTPRequest.cpp src/HTTPResponse.cpp

TARGET = server.exe

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	del $(TARGET)