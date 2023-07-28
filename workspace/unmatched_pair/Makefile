CC=clang
CXX=clang++

INCLUDES=`pkg-config --cflags --libs gtkmm-3.0` -I/usr/include/c++/11/ \
				 -I/usr/include/x86_64-linux-gnu/c++/11
LOADS=-L/usr/local/lib 
CFLAGS=-m64 
CXXFLAGS=$(CFLAGS)
CFIFLAGS=$(CFLAGS) -fsanitize=cfi -flto -fvisibility=default
LLFLAGS=$(CXXFLAGS) -emit-llvm -S

#targets := code_coop_linux.exe 
targets := unmatched_pair_cfi.exe unmatched_pair_vuln.exe

all: $(targets)
%_cfi.exe: %.cpp
	$(CXX) $(CFIFLAGS) $< -o $@
%_vuln.exe: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
clean:
	rm $(wildcard *.ll) $(wildcard *.exe)
