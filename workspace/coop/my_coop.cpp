#include <stdio.h>
#include <iostream>

class CODECOOP {
 public:
  CODECOOP() {}
  virtual ~CODECOOP() = default;
 protected:
  int run(void);
  void on_clicked();
};

void CODECOOP::on_clicked() {
  std::cout << "This is a test for COOP attack" << std::endl;
}

int CODECOOP::run(void) {
  std::cout << "Running" << std::endl;
  return 1;
}


int main(int argc, char** argv) {
  CODECOOP codecoop;
  char buf[1];
  scanf("%s", buf);

  return 0;
}
