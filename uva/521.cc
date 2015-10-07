#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class UnionFind {
 private:
  vector<int> id;
  vector<int> size;

 public:
  UnionFind(int elements) {
    id.resize(elements);
    size.resize(elements);
    for (int i = 0; i < elements; ++i) {
      id[i] = i;
      size[i] = 1;
    }
  }

  int root(int i) {
    while(i != id[i]) {
      id[i] = id[id[i]];
      i = id[i];
    }
    return i;
  }

  int find(int p, int q) {
    return root(p) == root(q);
  }

  void unite(int p, int q) {
    int i = root(p);
    int j = root(q);

    if(size[i] < size[j]) {
      id[i] = j;
      size[j] += size[i];
    } else {
      id[j] = i;
      size[i] += size[j];
    }
  }
};

struct Driver {
  int id;
  int start_stop;
  int line;
  Driver(int id, int start_stop, int line) :
    id(id), start_stop(start_stop), line(line) {}
  void ToString() {
    cout << "ID: " << id << " start: " << start_stop << " line: " << line << 
      endl;
  }
};

bool AreWeDone(UnionFind& union_find, int drivers) {
  int first = 0;
  for (int i = 1; i < drivers; ++i) {
    if (!union_find.find(0, i)) {
      return false;
    }
  }
}

int GetStop(const vector<int>& line, int start_stop, int iterations) {
  int start_index = 0;
  for (int i = 0; i < line.size(); ++i) {
    if (line[i] == start_stop) {
      start_index = i;
      break;
    }
  }
  int current_index = (start_index + iterations) % line.size();
  return line[current_index];
}

// We will resolve the problem using UnionFind.
void SolveProblem(vector<vector<int> >& lines, vector<Driver>& drivers) {
  if (drivers.size() <= 1) {
    cout << "Yes" << endl;
    return;
  }

  UnionFind union_find(drivers.size());

  int max_size_line = 0;
  for (int i = 0; i < lines.size(); ++i) {
    if (lines[i].size() > max_size_line) {
      max_size_line = lines[i].size();
    }
  }

  // We will iterate through the time and check if the drivers are all on the
  // same group. The worst case in time would be to iterate max_size_line *
  // max_size_line which will ensure that a line of 50 stops can coincide with
  // another of 49.
  for (int i = 0; i < max_size_line * max_size_line; ++i) {
    if (AreWeDone(union_find, drivers.size())) {
      cout << "Yes" << endl;
      return;
    }
    map<int, vector<int> > drivers_per_station;
    for (int j = 0; j < drivers.size(); ++j) {
      int current_stop = GetStop(
          lines[drivers[j].line], drivers[j].start_stop, i);
      drivers_per_station[current_stop].push_back(drivers[j].id);
    }
    map<int, vector<int> >::iterator it;
    for (it = drivers_per_station.begin(); it != drivers_per_station.end(); ++it) {
      if (it->second.size() > 1) {
        vector<int> drivers_in_station = it->second;
        for (int k = 1; k < drivers_in_station.size(); ++k) {
          union_find.unite(drivers_in_station[0] - 1, drivers_in_station[k] - 1);
        }
      }
    }
  }

  cout << "No" << endl;
}

int main() {
  while (true) {
    string line;
    getline(cin, line);
    istringstream is(line);
    int lines, drivers, stops;
    is >> lines >> drivers >> stops;
    if (lines == 0 && drivers == 0 && stops == 0) {
      return 0;
    }
    vector<vector<int> > lines_vector(lines);
    vector<Driver> drivers_list;
    for (int i = 0; i < lines; ++i) {
      // Get the stops associated with the line.
      getline(cin, line);
      istringstream iss(line);
      int stop_id;
      while (iss >> stop_id) {
        lines_vector[i].push_back(stop_id);
      }
      // Get the drivers.
      getline(cin, line);
      istringstream iss2(line);

      while (iss2 >> stop_id) {
        int driver_id;
        iss2 >> driver_id;
        Driver d(driver_id, stop_id, i);
        drivers_list.push_back(d);
      }
    }

    SolveProblem(lines_vector, drivers_list);
  }
}
