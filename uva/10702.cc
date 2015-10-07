#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int GetResult(int start, int end, int travels,
    vector<vector<vector<int> > >* graph) {
  if ((*graph)[start][end][travels] != -1) {
    return (*graph)[start][end][travels];
  }
  int result = -1;
  // Distance[start][end][travels] = distance[start][tmp][travels-1] +
  //   distance[tmp][end][0];
  for (int i = 0; i < graph->size(); ++i) {
    result = max(result, GetResult(start, i, travels - 1, graph) +
        GetResult(i, end, 0, graph));
  }
  (*graph)[start][end][travels] = result;
  return result;
}

int main() {
  int cities, start_city, end_cities, intercity_travels;
  while (cin >> cities >> start_city >> end_cities >> intercity_travels) {
    if (cities == 0 && start_city == 0 &&
        end_cities == 0 && intercity_travels == 0) {
      return 0;
    }

    // dp_graph will contain the structure from city A to city B with
    // intercity_travel I make this win.
    vector<vector<vector<int> > > dp_graph(
        cities, vector<vector<int> >(cities, vector<int>(intercity_travels, -1)));
    for (int i = 0; i < cities; ++i) {
      for (int j = 0; j < cities; ++j) {
        cin >> dp_graph[i][j][0];
      }
    }

    int result = 0.0;
    for (int i = 0; i < end_cities; ++i) {
      int city_to_end;
      cin >> city_to_end;
      result = max(
          result, GetResult(
            start_city - 1, city_to_end - 1, intercity_travels - 1, &dp_graph));
    }
    cout << result << endl;
  }
}
