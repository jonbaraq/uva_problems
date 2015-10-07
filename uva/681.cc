#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct Vertex {
  int x;
  int y;
  Vertex(int x, int y) : x(x), y(y) {}
  Vertex() {}
  void Print() const {
    cout << x << " " << y << endl;
  }
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
void SolveProblem(vector<Vertex>& vertexes) {
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

  // Print the hull.
  cout << position + 2 << endl;
  for (int i = 0; i <= position; ++i) {
    vertexes[i].Print();
  }
  vertexes[0].Print();
}

int main() {
  int cases;
  cin >> cases;
  cout << cases << endl;
  while (cases > 0) {
    int vertex;
    cin >> vertex;
    vector<Vertex> vertexes(vertex - 1, Vertex(0, 0));
    for (int i = 0; i < vertex; ++i) {
      int x, y;
      cin >> x >> y;
      // Skip the last vertex.
      if (i == (vertex - 1)) {
        continue;
      }
      Vertex v(x, y);
      vertexes[i] = v;
    }

    SolveProblem(vertexes);

    if (cases > 1) {
      int separator;
      cin >> separator;
      cout << separator << endl;
    }
    --cases;
  }
  return 0;
}
