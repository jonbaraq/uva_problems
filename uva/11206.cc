#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
  int a;
  int b;
  Edge(int a, int b) : a(a), b(b) {}
};

int kMaxColors;

bool AllProcessed(const vector<bool>& processed) {
  for (int i = 0; i < processed.size(); ++i) {
    if (!processed[i]) {
      return false;
    }
  }
  return true;
}

int GetSolution(const vector<vector<bool> >& graph, const vector<Edge>& list,
    vector<int>& diff_colors) {
  vector<int> colors(graph.size(), -1);
  vector<bool> processed(graph.size(), false);
  // Color the graph.
  colors[0] = 0;
  processed[0] = true;
  queue<int> q;
  q.push(0);
  while(!q.empty()) {
    int element = q.front();
    q.pop();
    if (AllProcessed(processed)) {
      break;
    }
    vector<bool> colors_used(4, false);
    for (int i = 0; i < graph.size(); ++i) {
      if (!graph[element][i]) {
        continue;
      }
      if (i == element) {
        continue;
      }
      if (colors[i] == -1) {
        // Assign temp color.
        colors[i] == 0;
        q.push(i);
      } else {
        if (processed[i]) {
          colors_used[colors[i]] = true;
        }
      }
    }

    for (int i = 0; i < colors_used.size(); ++i) {
      if (!colors_used[i]) {
        colors[element] = i;
      }
    }
    processed[element] = true;
  }

  for (int i = 0; i < colors.size(); ++i) {
  }

  int result = 0;
  do {
    int tmp_result = 0;
    for (int i = 0; i < list.size(); ++i) {
      Edge edge = list[i];
      tmp_result += pow(diff_colors[colors[edge.a]] -
          diff_colors[colors[edge.b]], 2);
    }
    result = max(result, tmp_result);
  } while (next_permutation(diff_colors.begin(), diff_colors.end()));

  return result;
}

int main() {
  while (true) {
    int regions;
    cin >> regions;
    if (regions == 0) {
      break;
    }
    int edges, c1, c2, c3, c4;
    cin >> edges >> c1 >> c2 >> c3 >> c4;
    vector<vector<bool> > graph(regions, vector<bool>(regions, false));
    vector<Edge> edges_list;
    vector<int> diff_colors(4);
    diff_colors[0] = c1;
    diff_colors[1] = c2;
    diff_colors[2] = c3;
    diff_colors[3] = c4;
    for (int i = 0; i < edges; ++i) {
      int a, b;
      cin >> a >> b;
      a -= 1;
      b -= 1;
      Edge edge(a, b);
      edges_list.push_back(edge);
      graph[a][b] = true;
      graph[b][a] = true;
    }
    cout << GetSolution(graph, edges_list, diff_colors) << endl;
  }
  return 0;
}
