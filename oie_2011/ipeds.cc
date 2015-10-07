// http://www.olimpiada-informatica.org/?cmd=problema&pbm=ipeds

#include <iostream>
#include <map>
#include <vector>

using namespace std;
typedef long long int64;

// Case 4 not successful.
void BuildIPed(map<int64, vector<int64> >* time_map) {
  vector<int64> elements_map(4, 0);
  for (map<int64, vector<int64> >::iterator it = time_map->begin();
       it != time_map->end(); ++it) {
    int64 time = it->first;
    elements_map[0] += it->second[0];
    elements_map[1] += it->second[1];
    elements_map[2] += it->second[2];
    elements_map[3] += it->second[3];
    int64 number_ipeds = 0;
    number_ipeds = min(min(elements_map[0], elements_map[1]),
                       min(elements_map[2], elements_map[3]));
    elements_map[0] -= number_ipeds;
    elements_map[1] -= number_ipeds;
    elements_map[2] -= number_ipeds;
    elements_map[3] -= number_ipeds;
    if (number_ipeds > 0) {
      cout << time << " " << number_ipeds << endl;
    }
  }
}

int main() {
  int number_lines;
  while (cin >> number_lines) {
    int counter = 0;
    map<int64, vector<int64> > time_map;
    while (counter < number_lines) {
      int64 time;
      int number_elements;
      char kind_element;
      cin >> time >> number_elements >> kind_element;
      if (time_map.find(time) == time_map.end()) {
        time_map[time] = vector<int64>(4, 0);
      }
      switch (kind_element) {
        case 'C':
          time_map[time][0] += number_elements;
          break;
        case 'P':
          time_map[time][1] += number_elements;
          break;
        case 'B':
          time_map[time][2] += number_elements;
          break;
        case 'M':
          time_map[time][3] += number_elements;
          break;
      }
      ++counter;
    }
    BuildIPed(&time_map);
  }
}
