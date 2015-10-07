// http://www.codercharts.com/puzzle/magic-words-decrypter

#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

void StringToLow(string* s) {
  for (int i = 0; i < static_cast<int>(s->size()); ++i) {
    (*s)[i] = tolower((*s)[i]);
  }
}

string GetKey(const string& word) {
  int size = static_cast<int>(word.size());
  if (size > 3) {
    string substring = word.substr(1, size - 2);
    sort(substring.begin(), substring.end());
    return word[0] + substring + word[size - 1];
  }
  return word;
}

int main(int argc, char** argv) {
  ifstream file(argv[1]);
  ifstream dictionary_file(argv[2]);
  map<string, string> dictionary;
  string dictionary_word;
  while (getline(dictionary_file, dictionary_word)) {
    StringToLow(&dictionary_word);
    string key = GetKey(dictionary_word);
    if (dictionary.find(key) == dictionary.end()) {
      dictionary[key] = dictionary_word;
    }
  }
  string line;
  while (getline(file, line)) {
    istringstream iss(line);
    string word;
    for (bool start = true; iss >> word; start = false) {
      cout << (start ? "" : " ");
      cout << dictionary[GetKey(word)];
    }
    cout << endl;
  }
}
