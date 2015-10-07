// http://www.codercharts.com/puzzle/road-trip

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
  int dest;
  int dist;
  double time;
};

void GetShortestPathTime(const int start,
                         const vector<vector<Edge> >& distances,
                         vector<double>* time) {
  const double kInfinity = 1e100;
  *time = vector<double>(static_cast<int>(distances.size()), kInfinity);
  typedef pair<double, int> TimeNode;
  priority_queue<TimeNode, vector<TimeNode>, greater<TimeNode> > q;
  q.push(TimeNode(0, start));
  (*time)[start] = 0;
  while (!q.empty()) {
    const int position = q.top().second;
    q.pop();
    const vector<Edge>& tmp = distances[position];
    for (int i = 0; i < static_cast<int>(tmp.size()); ++i) {
      const double new_time = tmp[i].time + (*time)[position];
      if ((*time)[tmp[i].dest] > new_time) {
        (*time)[tmp[i].dest] = new_time;
        q.push(TimeNode(new_time, tmp[i].dest));
      }
    }
  }
}

void GetShortestPathMileage(const int start,
                            const vector<vector<Edge> >& distances,
                            vector<double>* time) {
  const int kInfinity = 10000000;
  const double kEpsilon = 1e-6;
  const int size = static_cast<int>(distances.size());
  vector<int> distance(size, kInfinity);
  *time = vector<double>(size, kInfinity);
  typedef pair<pair<int, double>, int> DistanceTimeNode;
  priority_queue<DistanceTimeNode, vector<DistanceTimeNode>,
      greater<DistanceTimeNode> > q;
  q.push(make_pair(make_pair(0, 0), start));
  distance[start] = 0;
  (*time)[start] = 0;
  while (!q.empty()) {
    const int position = q.top().second;
    q.pop();
    const vector<Edge>& tmp = distances[position];
    for (int i = 0; i < static_cast<int>(tmp.size()); ++i) {
      const int new_distance = tmp[i].dist + distance[position];
      const double new_time = tmp[i].time + (*time)[position];
      if (distance[tmp[i].dest] > new_distance
          || (fabs(distance[tmp[i].dest] - new_distance) < kEpsilon
           && (*time)[tmp[i].dest] > new_time)) {
        (*time)[tmp[i].dest] = new_time;
        distance[tmp[i].dest] = new_distance;
        q.push(make_pair(make_pair(new_distance, new_time), tmp[i].dest));
      }
    }
  }
}

int main(int argc, char** argv) {
  ifstream file(argv[1]);
  int intersections, roads, start;
  file >> intersections >> roads >> start;
  vector<vector<Edge> > distances(intersections);
  int origin, destination, distance;
  double speed;
  Edge edge;
  while (roads--) {
    file >> origin >> destination >> distance >> speed;
    edge.dest = destination;
    edge.dist = distance;
    edge.time = distance * 60 / speed;
    distances[origin].push_back(edge);
  }
  vector<double> times_mileage;
  GetShortestPathMileage(start, distances, &times_mileage);
  vector<double> times_short;
  GetShortestPathTime(start, distances, &times_short);
  int number_destinations;
  file >> number_destinations;
  while (number_destinations--) {
    file >> destination;
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << fabs(times_mileage[destination] - times_short[destination]) << endl;
  }
}
