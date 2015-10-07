#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int number_students;
  bool exit = false;
  while (!exit) {
    cin >> number_students;
    if (number_students == 0) {
      exit = true;
      break;
    }
    vector<double> expenses(number_students);
    double total_cost = 0;
    for (int i = 0; i < number_students; ++i) {
      cin >> expenses[i];
      total_cost += expenses[i];
    }
    double average_total = total_cost / number_students;
    double result = 0;
    for (int i = 0; i < number_students; ++i) {
      result += abs(average_total - expenses[i]) / 2;
    }
    cout << result << endl;
  }
}
