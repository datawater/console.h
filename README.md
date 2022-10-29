# console.h
A very bad, but small terminal library

# example:
```c
#include <stdio.h>

#define CONSOLE_IMPLEMENTATION
#include "console.h"

int main(void) {
  console_init();
  console_printc(STDOUT,  FLRED, "Hello, World!\n");
  return 0;
}
  ```
