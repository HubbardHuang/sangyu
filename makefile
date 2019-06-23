CPP_SOURCES = $(shell find . -name "*.cpp")
CPP_OBJECTS = $(patsubst %.cpp, %.o, $(CPP_SOURCES))

# 指定编译器名称
CC = g++

# 指定搜索路径
INCLUDE_PATH = -I . -I lexical_analyzer -I test

# 指定编译参数
CPP_FLAGS = $(INCLUDE_PATH)

# 指定可执行文件名字
EXE = la.out

all:$(CPP_OBJECTS) link run

.cpp.o:
	@echo Compiling $< for $@ ...
	@$(CC) -c $(CPP_FLAGS) $< -o $@

link:
	@echo Linking object files to generate an executable file named $(EXE) ...
	@$(CC) $(CPP_OBJECTS) -o $(EXE)

.PHONY:run
run:
	@echo Start Running $(EXE) ...
	@echo --------------------------------
	@./$(EXE)
	@echo --------------------------------
	@echo Ended.

.PHONY:remove
remove:
	@rm -r -f $(CPP_OBJECTS)
	@echo All redundant files has been deleted.