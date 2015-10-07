// http://www.olimpiada-informatica.org/?cmd=problema&pbm=flyingkick

#include <cstdlib>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

void PrintResult(const vector<pair<int, int> >& guys, int chuck,
                 int malo, int no_kick) {
  int infinity = 1000000;
  int size = static_cast<int>(guys.size());
  vector<int> time(size, infinity);
  vector<int> steps(size, infinity);
  priority_queue<pair<int, int> > q;
  q.push(make_pair(0, chuck));
  time[chuck] = 0;
  steps[chuck] = 0;
  while (!q.empty()) {
    int position = q.top().second;
    if (position == malo) {
      cout << -q.top().first + 20 << endl;
      return;
    }
    q.pop();
    for (int i = 0; i < size; ++i) {
      if (i == position) continue;
      int distance = max(abs(guys[position].first - guys[i].first),
                         abs(guys[position].second - guys[i].second));
      if (distance > no_kick) {
        continue;
      }
      int new_time = time[position] + distance;
      int new_steps = steps[position] + distance;
      if (new_steps > no_kick) {
        new_steps = distance;
        new_time += 20;
      }
      if (time[i] > new_time) {
        time[i] = new_time;
        steps[i] = new_steps;
        q.push(make_pair(-new_time, i));
      } else if (time[i] == new_time && steps[i] > new_steps) {
        steps[i] = new_steps;
      }
    }
  }
  cout << -1 << endl;
}

int main() {
  int rows, columns, no_kick;
  while (cin >> rows >> columns >> no_kick) {
    vector<pair<int, int> > guys;
    int chuck = -1;
    int malo = -1;
    for (int i = 0; i < rows; ++i) {
      string content;
      cin >> content;
      for (int j = 0; j < columns; ++j) {
        if (content[j] != '.') {
          if (content[j] == 'C') {
            chuck = static_cast<int>(guys.size());
          }
          if (content[j] == 'X') {
            malo = static_cast<int>(guys.size());
          }
          guys.push_back(make_pair(i, j));
        }
      }
    }
    PrintResult(guys, chuck, malo, no_kick);
  }
}
