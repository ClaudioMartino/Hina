#include <cstdio>
#include <stdexcept>

void assert_that(bool statement, std::string msg) {
  if(!statement)
    throw std::runtime_error(msg);
}

void run_test(void(*test)(), const char* name) {
  try {
    test();
    printf("[+] '%s' test successful.\n", name);
  }
  catch (const std::exception& e) {
    printf("[-] '%s' test failed. %s\n", name, e.what());
  } 
}
