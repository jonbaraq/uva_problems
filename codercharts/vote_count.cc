#include <fstream>
#include <map>

#define k for(typeof(m.end()) e=m.begin();e!=m.end();++e)if(e->second>v)

main(int c, char** a) {
  std::ifstream f(a[1]);
  std::map<std::string, int> m;
  for (f >> c; c--; m[*a] = 1)
    f >> *a;
  int v, T = 0;
  for (f >> c; c--; m[*a] ? T += v, m[*a] += v : 0)
    f >> *a >> v;
  k
    v = e->second - 1;
  k
    printf("%s %.2f\n", &e->first[0], 100. * v / T);
}
