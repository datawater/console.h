# console.h
A very bad cross-platform self-documented terminal library

You can just include this in your file, define `#CONSOLE_IMPLEMENTATION` and youre done

#example:
```c
#include <stdio.h>

#define CONSOLE_IMPLEMENTATION
#include "include/console.h"

int main() {
  console(RED);
  printf("Im Red!");
  console(RESET);
  console(GREEN);
  printf("Im Green!");
  console(RESET);
  console(blue);
  printf("Im Blue!");
  console(RESET):
  console(MAGENTA);
  printf("Im magenta!");
  console(RESET);
  console(CYAN);
  printf("Im Cyan!");
  console(RESET);
  
  console(CLEAR);
  printf("I cleared the screen!");
}
  ```
