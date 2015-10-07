#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Vertex {
  int x;
  int y;
  Vertex(int x, int y) : x(x), y(y) {}
  Vertex() {}
};

Vertex v0;

// O(N).
void SetOrigin(vector<Vertex>& vertexes) {
  Vertex result = vertexes[0];
  int index = 0;
  for (int i = 0; i < vertexes.size(); ++i) {
    Vertex tmp = vertexes[i];
    if (tmp.y < vertexes[index].y) {
      index = i;
    } else if (tmp.y == vertexes[index].y) {
      if (tmp.x < vertexes[index].x) {
        index = i;
      }
    }
  }
  swap(vertexes[0], vertexes[index]);
  v0 = vertexes[0];
}

// Three points are a counter-clockwise turn if ccw > 0, clockwise if
// ccw < 0, and collinear if ccw = 0 because ccw is a determinant that
// gives twice the signed  area of the triangle formed by p1, p2 and p3.
int CounterClockWise(const Vertex& a, const Vertex& b, const Vertex& c) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int GetDistance(const Vertex& v1, const Vertex& v2) {
  return sqrt(pow((v1.x - v2.x), 2) + pow((v1.y - v2.y), 2));
}

bool CompareVertexes(const Vertex& v1, const Vertex& v2) {
  int ccw = CounterClockWise(v0, v1, v2);
  // If the points are colinear, compare based on distance.
  if (ccw == 0) {
    return GetDistance(v0, v2) < GetDistance(v0, v1);
  }
  return (ccw > 0);
}

// Solve the problem with Graham scan algorithm.
vector<Vertex> GetConvexHull(const vector<Vertex>& vertexes_orig) {
  vector<Vertex> vertexes = vertexes_orig;

  // Get the point with the minimum y and put it on position 0.
  // If there are more than one select the one that has lower X. O(N).
  SetOrigin(vertexes);

  // Sort the vertex based on the angle they have with vertex 0.
  // A vertex v1 comes before v2 in sorted ouput if v2 has larger polar angle
  // (in counterclockwise direction) than v1.
  // O(NlogN).
  sort(vertexes.begin() + 1, vertexes.end(), CompareVertexes);
  // Add as final vertex the first one to close the convex hull.
  int position = 1;

  for (int i = 1; i < vertexes.size(); ++i) {
    while (CounterClockWise(
              vertexes[position - 1], vertexes[position], vertexes[i]) <= 0) {
      if (position > 1) {
        position -= 1;
      } else if (position == vertexes.size() - 1) {
        // All points are colinear.
        break;
      } else {
        i += 1;
      }
    }
    position += 1;
    swap(vertexes[position], vertexes[i]);
  }

  vertexes.erase(vertexes.begin() + position + 1, vertexes.end());
  return vertexes;
}

double GetArea(const vector<Vertex>& list) {
  double area = 0.0;
  for (int i = 0; i < list.size(); ++i) {
    int next = (i + 1) % list.size();
    area += 0.5 * (list[i].x * list[next].y - list[i].y * list[next].x);
  }

  return abs(area);
}

void SolveProblem(const vector<Vertex>& vertexes, int tile) {
  double area_polygon = GetArea(vertexes);
  vector<Vertex> convex_hull = GetConvexHull(vertexes);
  double area_covex_hull = GetArea(convex_hull);
  double wasted_space = (1.0 - area_polygon / area_covex_hull) * 100.0;

  cout << "Tile #" << tile << endl;
  cout << setprecision(2);
  cout << fixed;
  cout << "Wasted Space = " << wasted_space << " %" << endl;
}

int main() {
  int vertexes;
  int tile = 1;
  while (cin >> vertexes) {
    if (vertexes == 0) {
      return 0;
    }
    if (tile > 1) {
      cout << endl;
    }
    vector<Vertex> vertex_list(vertexes, Vertex(0, 0));
    for (int i = 0; i < vertexes; ++i) {
      int x, y;
      cin >> x >> y;
      vertex_list[i] = Vertex(x, y);
    }
    SolveProblem(vertex_list, tile);
    ++tile;
  }
}
