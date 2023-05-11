CC = g++
CFLAGS = -std=c++17 -O2 -Wall -Wno-missing-braces
INCLUDES = -I include/
#LIBS = -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
TARGET = main.exe

BUILD_DIR = build/
HEADERS := $(wildcard src/*.h)
SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp,$(BUILD_DIR)%.o,$(SRCS))

build/%.o: src/%.cpp $(HEADERS)
	@cmd.exe /c if not exist $(@D) mkdir $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

build: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

default: ./build

clean:
	@rm -rf ./build/*.o ${TARGET}

