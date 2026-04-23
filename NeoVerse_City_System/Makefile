CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g
TARGET = build/neoverse.exe

SOURCES = src/Engineer.cpp src/CityData.cpp src/Event.cpp src/CityZone.cpp src/SystemReports.cpp src/FileManager.cpp src/main.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)
	@echo Build completed!

clean:
	@if exist build\neoverse.exe del /F /Q build\neoverse.exe

run: $(TARGET)
	$(TARGET)

.PHONY: all clean run
