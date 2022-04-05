CXX = g++
CPPFLAGS = -Wall -Werror -MP -MMD
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system
SFML_INC = thirdparty/SFML/include

LIB_INPUT = obj/src/libinput
OBJ_TODO = obj/src/todolist
OBJ_TEST = obj/test

SRC_INPUT = src/libinput
SRC_TODO = src/todolist

JSONINCLUDE = thirdparty/json/single_include

INCLUDE = -I $(SRC_TODO) -I $(SRC_INPUT) -I $(JSONINCLUDE) -I $(SFML_INC)

OBJFILES = $(OBJ_TODO)/editWindow.o $(OBJ_TODO)/modules.o $(OBJ_TODO)/notesList.o $(LIB_INPUT)/input.o $(OBJ_TODO)/main.o
HEADERS = $(SRC_INPUT)/input.h $(SRC_TODO)/configNote.h $(SRC_TODO)/configModules.h $(SRC_TODO)/notesList.h

bin/todolist.exe: $(OBJFILES)
	$(CXX) -o bin/toDoList.exe $(OBJFILES) $(SFML_LIBS)

$(OBJ_TODO)/main.o: $(SRC_TODO)/main.cpp $(HEADERS)
	$(CXX) $(CPPFLAGS) -c -o $(OBJ_TODO)/main.o $(SRC_TODO)/main.cpp $(INCLUDE)

$(LIB_INPUT)/input.o: $(SRC_INPUT)/input.cpp $(HEADERS)
	 $(CXX) $(CPPFLAGS) -c -o $(LIB_INPUT)/input.o $(SRC_INPUT)/input.cpp $(INCLUDE)

$(OBJ_TODO)/notesList.o: $(SRC_TODO)/notesList.cpp $(HEADERS)
	$(CXX) $(CPPFLAGS) -c -o $(OBJ_TODO)/notesList.o $(SRC_TODO)/notesList.cpp $(INCLUDE)

$(OBJ_TODO)/editWindow.o: $(SRC_TODO)/editWindow.cpp $(HEADERS)
	$(CXX) $(CPPFLAGS) -c -o $(OBJ_TODO)/editWindow.o $(SRC_TODO)/editWindow.cpp $(INCLUDE)

$(OBJ_TODO)/modules.o: $(SRC_TODO)/modules.cpp $(HEADERS)
	$(CXX) $(CPPFLAGS) -c -o $(OBJ_TODO)/modules.o $(SRC_TODO)/modules.cpp $(INCLUDE)

$(OBJ_TEST)/libInput.a: $(LIB_INPUT)/input.o
		ar rcs $@ $^

$(OBJ_TEST)/libTodo.a: $(OBJ_TODO)/main.o $(OBJ_TODO)/notesList.o $(OBJ_TODO)/editWindow.o $(OBJ_TODO)/modules.o
		ar rcs $@ $^

test: bin/test.exe

bin/test.exe: $(OBJ_TEST)/libInput.a $(OBJ_TEST)/libTodo.a obj/test/test.o
	$(CXX) $(INCLUDE) -Wall -Werror -o bin/test obj/test/test.o $(OBJ_TEST)/libTodo.a $(OBJ_TEST)/libInput.a $(SFML_LIBS)

obj/test/test.o: test/test.cpp 
	$(CXX) $(INCLUDE) -I thirdparty/catch $(CPPFLAGS) -c -o obj/test/test.o test/test.cpp $(SFML_LIBS)

-include main.d input.d notesList.d modules.d editWindow.d

.PHONY: clean

clean: 
	rm -rf $(OBJ_TODO)/*.o $(OBJ_TODO)/*.d $(LIB_INPUT)/*.o $(LIB_INPUT)/*.d $(OBJ_TEST)/*.o $(OBJ_TEST)/*.d bin/*.exe