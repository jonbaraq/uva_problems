// http://www.codercharts.com/puzzle/crab-fishermen

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void ResolveWithCramer(const vector<double>& coef_eq1,
                       const vector<double>& coef_eq2,
                       double* a, double* c) {
  double D = coef_eq1[0] * coef_eq2[1] - coef_eq2[0] * coef_eq1[1];
  if (D != 0) {
    *a = -(coef_eq1[2] * coef_eq2[1] - coef_eq2[2] * coef_eq1[1]) / D;
    *c = -(coef_eq1[0] * coef_eq2[2] - coef_eq2[0] * coef_eq1[2]) / D;
  }
}

double CalculateGlobalDistance(
    const vector<pair<double, double> >& traps_coordinates,
    double a, double b, double c) {
  double result = 0;
  for (int i = 0; i < static_cast<int>(traps_coordinates.size()); ++i) {
    result +=
        (a * traps_coordinates[i].first + b * traps_coordinates[i].second + c) *
        (a * traps_coordinates[i].first + b * traps_coordinates[i].second + c);
  }
  return result;
}

void ResolveEquation(const vector<pair<double, double> >& traps_coordinates,
                     double* a, double* b, double* c) {
  vector<double> coef_eq1(3, 0);
  vector<double> coef_eq2(3, 0);
  // Calculate normalizing b = 1;
  for (int i = 0; i < static_cast<int>(traps_coordinates.size()); ++i) {
    coef_eq1[0] += traps_coordinates[i].first * traps_coordinates[i].first;
    coef_eq1[1] += traps_coordinates[i].first;
    coef_eq1[2] += traps_coordinates[i].first * traps_coordinates[i].second;
    coef_eq2[0] += traps_coordinates[i].first;
    coef_eq2[1] += 1;
    coef_eq2[2] += traps_coordinates[i].second;
  }
  ResolveWithCramer(coef_eq1, coef_eq2, a, c);
  double D = CalculateGlobalDistance(traps_coordinates, *a, *b, *c);
  double a2 = 1, b2 = 0, c2 = 0;
  coef_eq1 = vector<double>(3, 0);
  coef_eq2 = vector<double>(3, 0);
  // Calculate normalizing a = 1;
  for (int i = 0; i < static_cast<int>(traps_coordinates.size()); ++i) {
    coef_eq1[0] += traps_coordinates[i].second * traps_coordinates[i].second;
    coef_eq1[1] += traps_coordinates[i].second;
    coef_eq1[2] += traps_coordinates[i].second * traps_coordinates[i].first;
    coef_eq2[0] += traps_coordinates[i].second;
    coef_eq2[1] += 1;
    coef_eq2[2] += traps_coordinates[i].first;
  }
  ResolveWithCramer(coef_eq1, coef_eq2, &b2, &c2);
  double dist = CalculateGlobalDistance(traps_coordinates, a2, b2, c2);
  if (dist < D) {
    *a = a2;
    *b = b2;
    *c = c2;
  }
}

int main(int argc, char** argv) {
  double a = 0, b = 1, c = 0;
  ifstream file(argv[1]);
  int kTraps;
  file >> kTraps;
  vector<pair<double, double> > traps_coordinates(kTraps);
  double coordinate_x, coordinate_y;
  for (int i = 0; i < kTraps; ++i) {
    file >> coordinate_x >> coordinate_y;
    traps_coordinates[i] = make_pair(coordinate_x, coordinate_y);
  }
  ResolveEquation(traps_coordinates, &a, &b , &c);
  cout << a << " " << b << " " << c << endl;
}
