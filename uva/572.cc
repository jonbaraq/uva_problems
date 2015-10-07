#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Point {
  int x;
  int y;
  Point(int x, int y) : x(x), y(y) {}
};

bool AllVisited(const vector<bool>& visited) {
  for (int i = 0; i < visited.size(); ++i) {
    if (!visited[i]) {
      return false;
    }
  }
  return true;
}

int GetNext(const vector<bool>& visited) {
  for (int i = 0; i < visited.size(); ++i) {
    if (!visited[i]) {
      return i;
    }
  }
  return -1;
}

bool AreNeighbors(const Point& a, const Point& b) {
  int distance = max(abs(a.x - b.x), abs(a.y - b.y));
  return distance < 2;
}

void SolveProblem(const vector<Point>& points) {
  vector<bool> visited(points.size(), false);
  int components = 0;
  while (!AllVisited(visited)) {
    int id = GetNext(visited);
    queue<int> q;
    q.push(id);
    while (!q.empty()) {
      int id = q.front();
      q.pop();
      for (int i = 0; i < points.size(); ++i) {
        if (i == id) {
          continue;
        }
        if (!visited[i] && AreNeighbors(points[id], points[i])) {
          q.push(i);
        }
      }
      visited[id] = true;
    }
    ++components;
  }
  cout << components << endl;
}

int main() {
  while (true) {
    int rows, columns;
    cin >> rows >> columns;
    if (rows == 0) {
      return 0;
    }
    vector<Point> pockets;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        char input;
        cin >> input;
        if (input == '@') {
          Point p(i, j);
          pockets.push_back(p);
        }
      }
    }
    SolveProblem(pockets);
  }
}
