#include <fstream>
#define k(l, o) for(; i < l; i++) e[i] = o(e[i])

main(int b, char** a) {
  std::ifstream f(a[1]);
  std::string e;
  for (b = 0; getline(f, e); b ? printf("%s\n", e.data()) : b = 1) {
    int i = 0, l;
    k(e.size(), toupper);
    l = e.rfind(32);
    if (l != -1) {
      b = e.rfind(32, l - 1);
      i = 1;
      if (b + 1) {
        k(b, tolower);
        i = b;
        if (e[l - 1] - 46)
          k(l, tolower);
      } else
        k(l, tolower);
    }
  }
}
