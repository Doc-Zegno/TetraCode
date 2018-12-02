INCLUDE_DIRS = $(wildcard Include/**) \
	External/Include
INCLUDE = $(addprefix -I, $(INCLUDE_DIRS))

CC = g++
FLAGS = -Wall -Werror -std=c++17
DEPFLAGS = -MMD -MP

SRC = $(wildcard Source/**/*.cpp)
SRC_EXTERNAL = $(wildcard External/Source/*.cpp)


.PHONY: clean time
.SILENT: dirs


all: dirs compileall

compileall: $(SRC:Source/%.cpp=Object/%.o) $(SRC_EXTERNAL:External/Source/%.cpp=Object/External/%.o)
	$(CC) $(FLAGS) -o Build/TetraCode
	
time:
	touch $(SRC) $(SRC_EXTERNAL) $(wildcard Include/**/*.h) $(wildcard External/Include/*.h)


$(SRC:Source/%.cpp=Object/%.o) : Object/%.o :
		$(CC) $(FLAGS) $(DEPFLAGS) $(INCLUDE) Source/$*.cpp -c -o Object/$*.o

$(SRC_EXTERNAL:External/Source/%.cpp=Object/External/%.o) : Object/External/%.o :
		$(CC) $(FLAGS) $(DEPFLAGS) $(INCLUDE) External/Source/$*.cpp -c -o Object/External/$*.o


dirs:
	mkdir -p Build
    mkdir -p Object
	mkdir -p $(patsubst Source/%, Object/%, $(dir $(SRC)))
	mkdir -p Object/External
	
clean:
	rm -rf Build Object


-include $(SRC:Source/%.cpp=Object/%.d)
-include $(SRC_EXTERNAL:External/Source/%.cpp=Object/External/%.d)