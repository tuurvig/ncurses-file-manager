NAME = filemanager
CXX = g++
LD = ld
DOXYGEN = doxygen
CXXFLAGS = -Wall -pedantic -std=c++14 -g

all: compile doc

compile: $(NAME)

run:	
	./$(NAME)

clean:
	rm -rf obj/
	rm -rf doc/
	rm -f $(NAME)

doc:
	mkdir -p doc
	$(DOXYGEN) Doxyfile

$(NAME): obj/$(NAME).o
	$(CXX) $(CXXFLAGS) $^ -o $@ -lncurses

obj/$(NAME).o: obj/main.o \
 obj/UI/UserInterface.o \
 obj/UI/Controller.o \
 obj/UI/Menu.o \
 obj/UI/Dialog/Info.o \
 obj/UI/Dialog/TextBox.o \
 obj/UI/Dialog/YesNo.o \
 obj/UI/Dialog.o \
 obj/UI/Window.o \
 obj/DirNavigation.o \
 obj/Types/Directory.o \
 obj/HierarchyNode.o \
 obj/Types/File.o \
 obj/Types/SymLink.o
	mkdir -p obj
	$(LD) -r $^ -o $@

obj/main.o: src/main.cpp \
 src/UI/UserInterface.hpp \
 src/UI/Menu.hpp \
 src/UI/Controller.hpp \
 src/UI/Dialog/Info.hpp \
 src/UI/Dialog/TextBox.hpp \
 src/UI/Dialog/YesNo.hpp \
 src/UI/Dialog/Dialog.hpp \
 src/UI/Window.hpp \
 src/Core/DirNavigation.hpp \
 src/Core/Directory.hpp \
 src/Core/HierarchyNode.hpp \
 src/Core/File.hpp \
 src/Core/SymLink.hpp
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/UI/UserInterface.o: src/UI/UserInterface.cpp \
 src/UI/UserInterface.hpp \
 src/UI/Menu.hpp \
 src/UI/Controller.hpp \
 src/UI/Dialog/Info.hpp \
 src/UI/Dialog/TextBox.hpp \
 src/UI/Dialog/YesNo.hpp \
 src/UI/Dialog/Dialog.hpp \
 src/UI/Window.hpp \
 src/Core/DirNavigation.hpp \
 src/Core/Directory.hpp \
 src/Core/HierarchyNode.hpp \
 src/Core/File.hpp \
 src/Core/SymLink.hpp
	mkdir -p obj/UI
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/UI/Menu.o: src/UI/Menu.cpp \
 src/UI/Menu.hpp \
 src/UI/Controller.hpp \
 src/UI/Dialog/Info.hpp \
 src/UI/Dialog/TextBox.hpp \
 src/UI/Dialog/YesNo.hpp \
 src/UI/Dialog/Dialog.hpp \
 src/UI/Window.hpp \
 src/Core/DirNavigation.hpp \
 src/Core/Directory.hpp \
 src/Core/HierarchyNode.hpp \
 src/Core/File.hpp \
 src/Core/SymLink.hpp
	mkdir -p obj/UI
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/UI/Controller.o: src/UI/Controller.cpp \
 src/UI/Controller.hpp \
 src/UI/Dialog/Info.hpp \
 src/UI/Dialog/TextBox.hpp \
 src/UI/Dialog/YesNo.hpp \
 src/UI/Dialog/Dialog.hpp \
 src/UI/Window.hpp \
 src/Core/DirNavigation.hpp \
 src/Core/Directory.hpp \
 src/Core/HierarchyNode.hpp \
 src/Core/File.hpp \
 src/Core/SymLink.hpp
	mkdir -p obj/UI
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/UI/Dialog/Info.o: src/UI/Dialog/Info.cpp \
 src/UI/Dialog/Info.hpp \
 src/UI/Dialog/Dialog.hpp \
 src/UI/Window.hpp
	mkdir -p obj/UI/Dialog
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/UI/Dialog/TextBox.o: src/UI/Dialog/TextBox.cpp \
 src/UI/Dialog/TextBox.hpp \
 src/UI/Dialog/Dialog.hpp \
 src/UI/Window.hpp
	mkdir -p obj/UI/Dialog
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/UI/Dialog/YesNo.o: src/UI/Dialog/YesNo.cpp \
 src/UI/Dialog/YesNo.hpp \
 src/UI/Dialog/Dialog.hpp \
 src/UI/Window.hpp
	mkdir -p obj/UI/Dialog
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/UI/Dialog.o: src/UI/Dialog/Dialog.cpp \
 src/UI/Dialog/Dialog.hpp \
 src/UI/Window.hpp
	mkdir -p obj/UI/Dialog
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/UI/Window.o: src/UI/Window.cpp \
 src/UI/Window.hpp
	mkdir -p obj/UI
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/DirNavigation.o: src/Core/DirNavigation.cpp \
 src/Core/DirNavigation.hpp \
 src/Core/Directory.hpp \
 src/Core/HierarchyNode.hpp \
 src/Core/File.hpp \
 src/Core/SymLink.hpp
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/Types/Directory.o: src/Core/Directory.cpp \
 src/Core/Directory.hpp \
 src/Core/HierarchyNode.hpp \
 src/Core/File.hpp \
 src/Core/SymLink.hpp
	mkdir -p obj/Types
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/HierarchyNode.o: src/Core/HierarchyNode.cpp \
 src/Core/HierarchyNode.hpp 
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/Types/File.o: src/Core/File.cpp \
 src/Core/File.hpp \
 src/Core/Directory.hpp \
 src/Core/HierarchyNode.hpp \
 src/Core/SymLink.hpp
	mkdir -p obj/Types
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj/Types/SymLink.o: src/Core/SymLink.cpp \
 src/Core/SymLink.hpp \
 src/Core/Directory.hpp \
 src/Core/HierarchyNode.hpp \
 src/Core/File.hpp
	mkdir -p obj/Types
	$(CXX) $(CXXFLAGS) -c -o $@ $<

