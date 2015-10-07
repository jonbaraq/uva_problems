#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

double kMinSpeed = 5.0;
double kMaxSpeed = 25.0;

double GetTime(double length, double max_speed, double speed) {
  double time = (speed / max_speed) * (length / (2 * speed) + 10.0 + length / (2 
        * kMinSpeed)) + (1 - speed / max_speed) * length / speed;
  return time;
}

double CalculateTime(const vector<double>& section_length,
    int i, int j, vector<vector<double> >* cache) {
  double max_speed = kMaxSpeed - j;
  if ((*cache)[i][j] < 1000000.0) {
    return (*cache)[i][j];
  }
  double length = section_length[i];

  // Time equation for any state would be.
  // T[p][y] Time from p to the last point having y accidents.
  // T[p][y] = (speed / max_speed) * (length / (2 * speed) + 10 + length / 10) +
  //           (1 - speed / max_speed) * (length / speed) +
  //           (speed / max_speed) * T[p+1][y+1] +
  //           (1 - speed / max_speed) * T[p+1][y]

  // The optimal speed for this equation is obtained through derived.
  //   speed = sqrt(10 * max_speed * length / (100 + length + 10 T[p+1][y+1] - 10 T[p+1][y]))
  // Where max_speed = kMaxSpeed - y;
  double section_time = 1000000.0;
  double speed = sqrt(10 * max_speed * length / (100 + length + 10 * 
        CalculateTime(section_length, i+1, j+1, cache) - 10 * 
        CalculateTime(section_length, i+1, j, cache)));
  if (speed < kMinSpeed) {
    speed = kMinSpeed;
  }
  if (speed > max_speed) {
    speed = max_speed;
  }
  section_time = GetTime(length, max_speed, speed) +
    (speed / max_speed) * CalculateTime(section_length, i+1, j+1, cache) +
    (1 - speed / max_speed) * CalculateTime(section_length, i+1, j, cache);
  (*cache)[i][j] = section_time;
  return (*cache)[i][j];
}

void SolveProblem(const vector<double>& section_length) {
  // Add an extra section that we will populate with times 0.
  vector<vector<double> > cache(section_length.size() + 1, 
      vector<double>(section_length.size() + 1, 1000000.0));
  // We have added an extra row that we will populate with 0's.
  for (int i = 0; i < cache.size(); ++i) {
    cache[cache.size() - 1][i] = 0;
    cache[i][cache.size() - 1] = 0;
  }

  cout << setprecision(4);
  cout << fixed;
  cout << CalculateTime(section_length, 0, 0, &cache) << endl;
}

int main() {
  double speed;
  while (cin >> speed) {
    kMaxSpeed = speed;
    int sections;
    cin >> sections;
    vector<double> section_length(sections);
    for (int i = 0; i < sections; ++i) {
      cin >> section_length[i];
    }

    SolveProblem(section_length);
  }
  return 0;
}
