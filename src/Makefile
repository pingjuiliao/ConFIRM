CXX=clang++
CXXFLAGS=-m64

tests := fptr.exe
tests += callback_linux.exe
tests += load_time_dynlnk_linux.exe
tests += run_time_dynlnk.exe
# tests += data_symbl.exe
tests += vtbl_call.exe
# tests += code_coop_linux.exe
tests += tail_call.exe
tests += switch.exe
# tests += ret.exe
tests += unmatched_pair.exe
tests += signal.exe
tests += cppeh.exe
tests += convention.exe
tests += multithreading_linux64.exe
# tests += mem.exe
# tests += jit.exe

.PHONY=clean

all: $(tests) libinc.so
libinc.so: inc.o
	$(CXX) -shared -o $@ $< 
%.exe: setup.o %.o
	$(CXX) $(CXXFLAGS) -o $@ $^
callback_linux.exe: setup.o callback_linux.o
	$(CXX) $(CXXFLAGS) -lpthread -o $@ $^
multithreading_linux64.exe: setup.o multithreading_linux64.o
	$(CXX) $(CXXFLAGS) -lpthread -o $@ $^
run_time_dynlnk.exe: setup.o run_time_dynlnk.o
	$(CXX) $(CXXFLAGS) -ldl -o $@ $^
code_coop_linux.exe: setup.o code_coop_linux.o
	$(CXX) $(CXXFLAGS) -o $@ $^
code_coop_linux.o: code_coop_linux.cpp
	$(CXX) $(CXXFLAGS) -I/usr/include/gtkmm-3.0 -I/usr/include/glibmm-2.4 -o $@ $< 
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
clean:
	rm $(wildcard *.o) $(wildcard *.exe) $(wildcard *.so)

