// http://www.codercharts.com/puzzle/search-trends

#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <string>

using namespace std;

int main(int argc, char** argv) {
  ifstream file(argv[1]);
  map<string, int> dict;
  string line;
  while (getline(file, line)) {
    if (dict.find(line) == dict.end()) {
      dict[line] = 1;
    } else {
      dict[line] += 1;
    }
  }
  int dict_size = static_cast<int>(dict.size());
  map<int, vector<string> > reverse_map;
  map<string, int>::iterator it;
  typedef pair<int, string> Struct;
  priority_queue<Struct, vector<Struct>, greater<Struct> > q;
  for (it = dict.begin(); it != dict.end(); ++it) {
    q.push(make_pair(-(*it).second, (*it).first));
  }
  int counter = 0;
  while (!q.empty()) {
    if (counter == 10)
      break;
    cout << -q.top().first << " " << q.top().second << endl;
    q.pop();
    ++counter;
  }
}
