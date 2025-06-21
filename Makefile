# Define variables
CXX = g++
CXXFLAGS = -std=c++11 -Iinclude
SRC = src/main.cpp src/BankAccount.cpp
TARGET = BankApp.exe

# Default rule: compile the project
all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Run the executable
run: all
	./$(TARGET)

# Clean build files
clean:
	del $(TARGET) 2>nul || rm -f $(TARGET)
