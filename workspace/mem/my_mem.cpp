#include <cstdio>
#include <cstring>
#include <iostream>
#include <sys/mman.h>


void callee1(bool&);
// void callee2();

typedef void(*FUNCPTR)(bool&);
const size_t QWORD = 8;

int main(int argc, char** argv) {
  void *caller;
  bool flag_1 = false;
  int r;
  caller = mmap(NULL, 0x1000, PROT_READ|PROT_WRITE,
                MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
  memcpy(caller, (void *)&callee1, 0x200);
  r = mprotect(caller, 0x1000, PROT_EXEC|PROT_READ|PROT_WRITE);
  if (r == -1) {
    printf("mprotect failed\n");
    exit(1);
  }

  ((FUNCPTR) caller)(flag_1);
  if (flag_1) {
    printf("mem test passed\n");
  } else {
    printf("mem test failed\n");
  }

  return 0;
}


void callee1(bool &arg_flag)
{
  arg_flag = true;
}
/*void callee2()
{
  flag_2 = true;
}*/
