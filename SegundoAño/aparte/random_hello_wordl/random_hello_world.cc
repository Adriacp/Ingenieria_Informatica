#include <iostream>
#include <ctime>
#include <unistd.h>

int main() {
  std::string final;
  char x;
  srand(time(0));
  std::string hello = "hello world";
  for(int i = 0; i < hello.length(); i++) {
    while(x != hello[i]) {
      if(hello[i] != ' ') {
        x = static_cast<char>(97 + (rand() % (123 -97)));  //limite inferior + rand() % (limite superior - limite inferior);
      }
      else x = ' ';
      std::cout << final + x << std::endl;
      usleep(20000);
    }
    final += x;
  }
  return 0;
}
