#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int Codify(const string& value) {
  int result = 0;
  for (int i = 0; i < static_cast<int>(value.size()); i++) {
    result = (result << 5) + static_cast<int>(value[i]) - 96;
  }
  return result;
}

int PopulateSet(const string& input, set<int>* strings) {
  int number_words = 0;
  istringstream iss(input);
  string word;
  while (iss >> word) {
    ++number_words;
    strings->insert(Codify(word));
  }
  return number_words;
}

int CalculateMinimumConstant(const set<int>& strings, int number_words) {
  int strings_size = static_cast<int> (strings.size());
  set<int>::iterator it = strings.end();
  int max_value = *(--it);
  int min_value = *(--it);
  for (int i = min_value; i < max_value; ++i) {
    map<int, int> hash;
    int repeated_hash;
    for (it = strings.begin(); it != strings.end(); ++it) {
      int partial_result = (i / *it) % number_words;
      if (hash.count(partial_result) == 0) {
        hash[partial_result] = *it;
      } else {
        repeated_hash = partial_result;
      }
    }
    int set_size = static_cast<int>(hash.size());
    if (set_size == strings_size) {
      return i;
    // If all the results are the same, the maximum value of C is calculated
    // according to the formula provided, and the next value of i should be that
    // one that makes the result of the formula different for the two biggest
    // hashes stored in the table.
    } else if (set_size == 1) {
      it = strings.end();
      int tmp_hash = *(--it);
      tmp_hash = *(--it);
      i = (i / tmp_hash + 1) * tmp_hash - 1;
      for (it = strings.begin(); it != strings.end(); ++it) {
        int tmp = (i / *it + 1) * *it;
        max_value = max(tmp, max_value) + 1;
      }
    // If there are results repeated the next value of i should be one that
    // makes these results different.
    } else {
      i = hash[repeated_hash] *
          (i / hash[repeated_hash] + 1) - 1;
    }
  }
  // If we don't reach a solution 0 is returned.
  return 0;
}

int main() {
  string input;
  while (getline(cin, input)) {
    set<int> strings;
    int number_words = PopulateSet(input, &strings);
    int result = CalculateMinimumConstant(strings, number_words);
    cout << input << endl;
    cout << result << endl;
    cout << endl;
  }
}
