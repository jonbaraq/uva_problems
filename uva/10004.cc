#include <iostream>
#include <queue>
#include <vector>

using namespace std;

bool IsBicolorable(const vector<vector<bool> >& graph) {
  vector<int> colors(graph.size(), -1);
  queue<int> q;
  // Push the first element into the queue.
  colors[0] = 0;
  q.push(0);
  while (!q.empty()) {
    int element = q.front();
    q.pop();
    for (int i = 0; i < graph.size(); ++i) {
      if (i == element) {
        continue;
      }
      if (graph[element][i]) {
        if (colors[element] == colors[i]) {
          return false;
        }
        if (colors[i] == -1) {
          colors[i] = colors[element] == 0 ? 1 : 0;
          q.push(i);
        }
      }
    }
  }
  return true;
}

int main() {
  while (true) {
    int vertex;
    cin >> vertex;
    if (vertex == 0) {
      break;
    }
    int edges;
    cin >> edges;
    vector<vector<bool> > graph(vertex, vector<bool>(vertex, false));
    for (int i = 0; i < edges; ++i) {
      int a, b;
      cin >> a >> b;
      graph[a][b] = true;
      graph[b][a] = true;
    }
    if (IsBicolorable(graph)) {
      cout << "BICOLORABLE." << endl;
    } else {
      cout << "NOT BICOLORABLE." << endl;
    }
  }
  return 0;
}
