#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

double MAX_DISTANCE = 10000.0;

struct Point {
  double x;
  double y;
  Point (double x, double y) : x(x), y(y) {}
  void Print() const {
    cout << "(" << x << ", " << y << ")" << endl;
  }
};

double GetDistance(const Point& a, const Point& b) {
  return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

bool ComparePoints(const Point& a, const Point& b) {
  if (a.x == b.x) {
    return a.y <= b.y;
  }
  return a.x < b.x;
}

double GetDistanceForPoints(vector<Point>& points, int start, int end) {
  if ((end - start) < 2) {
    return MAX_DISTANCE;
  } else if ((end - start) == 2) {
    return GetDistance(points[start], points[end - 1]);
  } else if ((end - start) == 3) {
    // For 3 points we calculate directly the minimum distance using.
    double distance = MAX_DISTANCE;
    for (int i = start; i < end; ++i) {
      for (int j = start; j < end; ++j) {
        if (i == j) {
          continue;
        }
        distance = min(distance, GetDistance(points[i], points[j]));
      }
    }
    return distance;
  }

  int middle = (start + end) / 2;

  double left_distance = GetDistanceForPoints(points, start, middle);
  double right_distance = GetDistanceForPoints(points, middle, end);

  // Now we need to ensure that between the distance between a point on the left
  // and another one on the right is not lower than this.
  // We will add into the left_point vector all those points that are closer
  // than right_distance just taking into account the X coordinates.
  vector<Point> left_points;
  for(int i = middle - 1; i >= start; i--) {
    if ((points[i].x - points[middle].x) < right_distance) {
      left_points.push_back(points[i]);
    } else {
      break;
    }
  }

  // We will add into the left_point vector all those points that are closer
  // than right_distance just taking into account the X coordinates.
  vector<Point> right_points;
  for(int i = middle; i < end; ++i) {
    if ((points[i].x - points[middle - 1].x) < left_distance) {
      right_points.push_back(points[i]);
    } else {
      break;
    }
  }

  double minimum = min(left_distance, right_distance);

  for (int i = 0; i < left_points.size(); ++i) {
    for (int j = 0; j < right_points.size(); ++j) {
      minimum = min(minimum, GetDistance(left_points[i], right_points[j]));
    }
  }

  return minimum;
}

void SolveProblem(vector<Point>& point_list) {
  // First we need to sort the points by Coordinate x.
  sort(point_list.begin(), point_list.end(), ComparePoints);

  // Now let's solve the problem
  double distance = GetDistanceForPoints(point_list, 0, point_list.size());

  if (distance < MAX_DISTANCE) {
    cout << setprecision(4);
    cout << fixed;
    cout << distance << endl;
  } else {
    cout << "INFINITY" << endl;
  }
}

int main() {
  while (true) {
    int points;
    cin >> points;
    if (points == 0) {
      return 0;
    }
    vector<Point> point_list(points, Point(0.0, 0.0));
    for (int i = 0; i < points; ++i) {
      double x, y;
      cin >> x >> y;
      Point p(x, y);
      point_list[i] = p;
    }
    SolveProblem(point_list);
  }
}
