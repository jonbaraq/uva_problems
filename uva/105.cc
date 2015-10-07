#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Interval {
  int start;
  int height;
  int end;
  Interval(int start, int height, int end) :
    start(start), height(height), end(end) {}
  void Print() {
    cout << endl;
    cout << "Interval: " << start << " " << height << " " << end << endl;
  }
};

struct Intersection {
  int coordinate;
  bool is_start;
  int height;
  Intersection(int coordinate, bool is_start, int height) :
    coordinate(coordinate), is_start(is_start), height(height) {}
  void Print() {
    cout << coordinate << " " << is_start << " " << height << endl;
  }
};

bool Smaller(const Intersection& a, const Intersection& b) {
  if (a.coordinate == b.coordinate) {
    if (!a.is_start && b.is_start) {
      return true;
    }
    if (a.is_start && !b.is_start) {
      return false;
    }
    if (a.height >= b.height) {
      return true;
    } 
    return false;
  }
  return a.coordinate < b.coordinate;
}

void SolveProblem(const vector<Interval>& buildings) {
  // This vector will have 2*buildings.size() size.
  vector<Intersection> intersections;
  for (int i = 0; i < buildings.size(); ++i) {
    Interval b = buildings[i];
    // Skip intervals with no height.
    if (b.height == 0) {
      continue;
    }
    Intersection start(b.start, true, b.height);
    Intersection end(b.end, false, b.height);
    intersections.push_back(start);
    intersections.push_back(end);
  }

  // Sort intersections by coordinates. O(nlogn).
  sort(intersections.begin(), intersections.end(), Smaller);

  vector<Interval> intervals;
  map<int, int> height_map;
  for (int i = 0; i < intersections.size(); ++i) {
    Intersection intersection = intersections[i];
    if (!intersection.is_start) {
      if (height_map.find(intersection.height) == height_map.end()) {
        continue;
      }
      height_map[intersection.height]--;
      if (height_map[intersection.height] == 0) {
        height_map.erase(intersection.height);
      }
    } else {
      if (height_map.find(intersection.height) == height_map.end()) {
        height_map[intersection.height] = 0;
      }
      height_map[intersection.height]++;
    }
    int height = 0;
    if (height_map.size() > 0) {
      map<int, int>::iterator it = height_map.end();
      --it;
      height = it->first;
    }
    int end = 0;
    if (i < intersections.size() - 1) {
      end = intersections[i+1].coordinate;
    }
    Interval interval(intersection.coordinate, height, end);
    intervals.push_back(interval);
  }

  // Now let's print the result.
  if (intervals.empty()) {
    return;
  }
  Interval first = intervals[0];
  int start = first.start;
  int height = first.height;
  int end = first.end;
  cout << start << " ";
  int current_pos = start;
  for (int i = 1; i < intervals.size(); ++i) {
    Interval tmp = intervals[i];
    if (tmp.start == tmp.end) {
      continue;
    }
    if (end < tmp.start) {
      cout << height << " " << end << " ";
      // Insert interval with 0 size.
      start = end;
      end = tmp.start;
      current_pos = end;
      height = 0;
      continue;
    }
    // Merge contiguous intersections.
    if (tmp.height == height) {
      end = tmp.end;
      continue;
    } else {
      cout << height << " " << end << " ";
      start = tmp.start;
      end = tmp.end;
      height = tmp.height;
    }
  }
  cout << "0" << endl;
}

int main() {
  int start, height, end;
  vector<Interval> buildings;
  while (cin >> start >> height >> end) {
    Interval b(start, height, end);
    buildings.push_back(b);
  }
  SolveProblem(buildings);
  return 0;
}
