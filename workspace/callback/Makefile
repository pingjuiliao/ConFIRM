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
targets := callback_cfi.exe callback_vuln.exe

all: $(targets)
callback_cfi.exe: callback_linux_cfi.o setup_cfi.o
	$(CXX) $(CFIFLAGS) -o $@ $^
callback_vuln.exe: callback_linux_vuln.o setup_vuln.o
	$(CXX) $(CXXFLAGS) -o $@ $^
%_cfi.o: %.cpp
	$(CXX) $(CFIFLAGS) -c $< -o $@
%_vuln.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm $(wildcard *.ll) $(wildcard *.exe) $(wildcard *.bc) $(wildcard *.o)
