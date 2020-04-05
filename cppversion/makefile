CPPFLAGS=-std=c++11 -Wall -g
LDFLAGS=-g
LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system
SRCS=$(shell find . -name "*.cpp")
OBJS=$(patsubst %.cpp, %.o, $(SRCS))

epidemic-app : $(OBJS)
	g++ $(LDFLAGS) -o epidemic-app $(OBJS) $(LDLIBS)

%.o : %.cpp
	g++ -c -o $@ $(CPPFLAGS) $<

clean :
	rm -f $(OBJS)

dist-clean: clean
