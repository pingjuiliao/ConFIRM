CC=clang
CXX=clang++

INCLUDES=`pkg-config --cflags --libs gtkmm-3.0` -I/usr/include/c++/11/ \
				 -I/usr/include/x86_64-linux-gnu/c++/11
LOADS=-L/usr/local/lib 
CFLAGS=-m64 -fsanitize=cfi -flto -fvisibility=default 
CXXFLAGS=$(CFLAGS)
LLFLAGS=$(CXXFLAGS) -emit-llvm -S

#targets := code_coop_linux.exe 
targets := my_coop.exe code_coop_linux.exe

all: $(targets)
my_coop.exe: my_coop.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
code_coop_linux.ll: code_coop_linux.cpp
	$(CXX) $(LLFLAGS) $< -o $@
code_coop_linux.exe: code_coop_linux.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LOADS) $< -o $@
clean:
	rm $(wildcard *.ll) $(wildcard *.exe)
