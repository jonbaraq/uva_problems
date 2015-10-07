// http://codercharts.com/puzzle/guess-number

#include <fstream>

using namespace std;

int main(int argc, char** argv) {
  ifstream file(argv[1]);
  ofstream myfile(argv[2]);
  int low, high, guess;
  while (1) {
    char c;
    file >> c;
    bool exit = false;
    bool cont = false;
    switch (c) {
      case 'e':
        exit = true;
        break;
      case '=':
        cont = true;
        break;
      case '<':
        low = guess + 1;
        break;
      case '>':
        high = guess - 1;
        break;
      default:
        file >> low >> high;
    }
    if (cont) {
      continue;
    }
    if (exit) {
      break;
    }
    guess = (low + high) / 2;
    myfile << guess << endl;
  }
}
