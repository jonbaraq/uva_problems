// http://www.codercharts.com/puzzle/square-within

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
  ifstream file(argv[1]);
  int size;
  while (file >> size) {
    int result = 0;
    for (int i = 1; i <= size; ++i) {
      result += i * i;
    }
    cout << result << endl;
  }
}
