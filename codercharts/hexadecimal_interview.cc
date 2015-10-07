// http://codercharts.com/puzzle/hexadecimal-interview

#include <iostream>
#include <fstream>

using namespace std;

int GetFactorial(int number) {
  int count = 0;
  for (int i = 2; i <= number; i *= 2) {
    count += number / i;
  }
  return count / 4;
}

int main(int argc, char** argv) {
  ifstream file(argv[1]);
  int number_cases;
  file >> number_cases;
  while (number_cases--) {
    int number;
    file >> number;
    cout << GetFactorial(number) << endl;
  }
}
