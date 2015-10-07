// http://www.codercharts.com/puzzle/airport-gas-stations

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

double CalculateDistance(const pair<double, double>& point1,
                         const pair<double, double>& point2) {
  return (point1.first - point2.first) * (point1.first - point2.first)
      + (point1.second - point2.second) * (point1.second - point2.second);
}

bool IsUpdating(const vector<pair<double, double> >& airports,
                vector<pair<double, double> >* centroids,
                vector<int>* airport_labels, double* total_distance,
                vector<int>* aiports_per_station) {
  bool changed = false;
  int kCentroids = static_cast<int>(centroids->size());
  (*aiports_per_station) = vector<int>(static_cast<int>(airports.size()), 0);
  for (int i = 0; i < static_cast<int>(airports.size()); ++i) {
    double distance = 1e10;
    int label = -1;
    for (int j = 0; j < kCentroids; ++j) {
      double dist = CalculateDistance(airports[i], (*centroids)[j]);
      if (dist < distance) {
        distance = dist;
        label = j;
      }
    }
    if ((*airport_labels)[i] != label) {
      *total_distance += CalculateDistance((*centroids)[label], airports[i]) -
          CalculateDistance((*centroids)[(*airport_labels)[i]], airports[i]);
      (*airport_labels)[i] = label;
      changed = true;
    }
    (*centroids)[(*airport_labels)[i]].first += airports[i].first;
    (*centroids)[(*airport_labels)[i]].second += airports[i].second;
    ++(*aiports_per_station)[(*airport_labels)[i]];
  }
  for (int i = 0; i < kCentroids; ++i) {
    if ((*aiports_per_station)[i]) {
      (*centroids)[i].first /= (*aiports_per_station)[i];
      (*centroids)[i].second /= (*aiports_per_station)[i];
    }
  }
  return changed;
}

double InitializeCentroids(const vector<pair<double, double> >& airports,
                           vector<pair<double, double> >* centroids,
                           const vector<int>& airport_labels) {
  int kAirports = static_cast<int>(airports.size());
  int kCentroids = static_cast<int>(centroids->size());
  // Select the first airport.
  (*centroids)[0] = airports[rand() % kAirports];
  vector<double> distances(kAirports, 0);
  vector<double> accumulated_distances(kAirports, 0);
  double tmp_dist = 0;
  for (int i = 0; i < kAirports; ++i) {
    distances[i] = CalculateDistance(airports[i], (*centroids)[0]);
    tmp_dist += distances[i];
    accumulated_distances[i] = tmp_dist * tmp_dist;
  }
  for (int i = 1; i < kCentroids; ++i) {
    double v =
        rand() * accumulated_distances[static_cast<int>(
            accumulated_distances.size()) - 1]/ RAND_MAX;
    vector<double>::iterator next_point;
    next_point = lower_bound(accumulated_distances.begin(),
                             accumulated_distances.end(), v);
    (*centroids)[i] =
        airports[static_cast<int>(next_point - accumulated_distances.begin())];
    for (int j = 0; j < kAirports; ++j) {
      double tmp_distance = CalculateDistance(airports[j], (*centroids)[i]);
      if (tmp_distance < distances[j]) {
        distances[j] = tmp_distance;
      }
      accumulated_distances[j] += distances[j] * distances[j];
    }
  }
  double distance = 0;
  for (int i = 0; i < kAirports; ++i) {
    distance += CalculateDistance(airports[i], (*centroids)[airport_labels[i]]);
  }
  return distance;
}

double LocatePetrolStations(const vector<pair<double, double> >& airports,
                            vector<pair<double, double> >* centroids,
                            vector<int>* airport_labels) {
  int kCentroids = static_cast<int>(centroids->size());
  int kAirports = static_cast<int>(airports.size());
  if (kCentroids >= kAirports) {
    for (int i = 0; i < kCentroids; ++i) {
      if (i >= kAirports) {
        (*centroids)[i] = airports[0];
        continue;
      }
      (*centroids)[i] = airports[i];
    }
    return 0;
  }
  vector<int> aiports_per_station(kCentroids, 0);
  double dist = InitializeCentroids(airports, centroids, *airport_labels);
  while (IsUpdating(airports, centroids, airport_labels,
                    &dist, &aiports_per_station)) {}
  return dist;
}

int main(int argc, char** argv) {
  srand(clock());
  clock_t start_parse, start, end;
  start_parse = clock();
  ifstream file(argv[1]);
  // Read number of airports.
  int kAirports;
  file >> kAirports;
  vector<pair<double, double> > airports_coordinates(kAirports);
  // Read coordinates of the airports.
  for (int i = 0; i < kAirports; ++i) {
    double coordinate_x, coordinate_y;
    file >> coordinate_x >> coordinate_y;
    airports_coordinates[i] = make_pair(coordinate_x, coordinate_y);
  }
  // Read number of different cases.
  int kCases;
  file >> kCases;
  // Read the different cases.
  vector<int> centroids_cases(kCases);
  vector<double> distances(kCases);
  for (int i = 0; i < kCases; ++i) {
    int number_centroids;
    file >> number_centroids;
    centroids_cases[i] = number_centroids;
    distances[i] = 1e10;
  }
  vector<int> airport_labels(kAirports, -1);
  start = clock();
  double remaining_clocks = 2.25 * CLOCKS_PER_SEC - (start - start_parse);
  vector<vector<pair<double, double> > > centroids(kCases);
  for (int i = 0; i < kCases; ++i) {
    vector<pair<double, double> > centroids_tmp(centroids_cases[i]);
    double dist = LocatePetrolStations(airports_coordinates, &centroids_tmp,
                                       &airport_labels);
    if (dist < distances[i]) {
      distances[i] = dist;
      centroids[i] = centroids_tmp;
    }
  }
  end = clock();
  if (end - start == 0) {
    end += 0.000000001;
  }
  int iterations = (remaining_clocks - (end - start)) / (end - start) - 1;
  for (int j = 0; j < iterations; ++j) {
    for (int i = 0; i < kCases; ++i) {
      vector<pair<double, double> > centroids_tmp(centroids_cases[i]);
      double dist = LocatePetrolStations(airports_coordinates, &centroids_tmp,
                                         &airport_labels);
      if (dist < distances[i]) {
        distances[i] = dist;
        centroids[i] = centroids_tmp;
      }
    }
  }
  for (int i = 0; i < kCases; ++i) {
    for (int j = 0; j < static_cast<int>(centroids[i].size()); ++j) {
      cout << centroids[i][j].first << " " << centroids[i][j].second;
      if (j < static_cast<int>(centroids[i].size()) - 1) {
        cout << " ";
      } else {
        cout << endl;
      }
    }
  }
}
