#include <fstream>
#include <map>
#define k for(z::iterator i = m[P].begin(); i != m[P].end(); ++i)
#define f first
#define t typedef
using namespace std;
t string s;
t map<s, s> z;
main(int b, char** a) {
  ifstream f(a[1]);
  map<s, z> m;
  s P, E;
  for (f >> b >> b; b--;) {
    f >> P >> E;
    m[P][E];
    m[E][P];
  }
  for (f >> b; b--;) {
    f >> P;
    z r;
    k
      r.insert(m[i->f].begin(), m[i->f].end());
    k
      r.erase(i->f);
    printf("%i\n", r.size() - 1);
  }
}
