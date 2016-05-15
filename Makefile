#figlet `date` && g++ -Wall -Wextra -Wpedantic -g3 -fsanitize=address -fsanitize=undefined -std=c++11 shader.cpp camera.cpp debug.cpp main.cpp -o main `pkg-config --libs glfw3 gl glew` -lSOIL && ./main

IMGUI_PATH=/home/dv/src/lib/imgui

CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g3 -Wall -Wextra -Wpedantic -fsanitize=address -fsanitize=undefined -std=c++11 -I/home/dv/src/lib/imgui
LDFLAGS=-g3 -Wall -Wextra -Wpedantic -fsanitize=address -fsanitize=undefined -std=c++11
LDLIBS=`pkg-config --libs glfw3 gl glew` -lSOIL -L$(IMGUI_PATH)

SRCS=imgui_impl_gl2/imgui_impl_glfw_gl2.cpp main.cpp camera.cpp shader.cpp debug.cpp
OBJS=$(subst .cpp,.o,$(SRCS)) $(IMGUI_PATH)/imgui.o $(IMGUI_PATH)/imgui_draw.o

all: tool

tool: $(OBJS)
	$(CXX) $(LDFLAGS) -o main $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .depend

include .depend
