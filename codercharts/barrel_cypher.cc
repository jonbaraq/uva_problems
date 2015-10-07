#include <fstream>

#define g(a) std::getline(f, a)

main(int, char** b) {
  std::ifstream f(b[1]);
  std::string k, l;
  for (g(k); g(k), g(l); puts(&l[0]))
    for (int a = 0, s = k.size(), t = 0; l[a]; ++a)
      l[a] - 32 ?
        l[a] -= k[(t / s) % 2 ? s - t % s - 1 : t % s] - 48,
        l[a] < 97 ? l[a] += 26 : 0,
        ++t : 0;
}
