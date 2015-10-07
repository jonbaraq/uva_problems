// http://codercharts.com/puzzle/bits-manipulation

#include <cstdio>

int main(int argc, char** argv) {
  FILE* f = fopen(argv[1], "r");
  unsigned int number;
  while (fscanf(f, "%u", &number) == 1) {
    printf("%u\n", ((number >> 1) & 0x55555555) | ((number & 0x55555555) << 1));
  }
}
