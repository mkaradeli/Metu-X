#include "myMalloc.h"
#include <stdlib.h>

void *myMalloc(int size) {
  void *pointer = malloc(size);
  return pointer;
}
