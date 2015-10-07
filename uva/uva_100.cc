#include <iostream>
#include <vector>

using namespace std;

// Returns the number of elements after executing the explained algorithm.
int NumberElements(int number) {
  // Number is always positive.
  if (number <= 1)
    return 1;
  if (number % 2 == 1) {
    return (1 + NumberElements(3 * number + 1));
  } else {
    return (1 + NumberElements(number / 2));
  }
}

int CalculateMaxNumberElements(int first_number, int last_number) {
  if (first_number > last_number) {
    int tmp_number = first_number;
    first_number = last_number;
    last_number = tmp_number;
  }
  int maximum = 0;
  for (int i = first_number; i <= last_number; ++i) {
    int n_elements = NumberElements(i);
    if (n_elements > maximum) {
      maximum = n_elements;
    }
  }
  return maximum;
}

int main() {
  int first_number, last_number;
  while (cin >> first_number >> last_number) {
    int maximum = CalculateMaxNumberElements(first_number, last_number);
    cout << first_number << " " << last_number << " " << maximum << endl;
  }
}
