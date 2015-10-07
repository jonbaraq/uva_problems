// http://www.codercharts.com/puzzle/noob-cipher

#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

void ConvertLine(const string& line, map<char, char>& dict) {
  for (int i = 0; i < static_cast<int>(line.length()); ++i) {
    if (dict.find(line.at(i)) != dict.end()) {
      cout << dict[line.at(i)];
    } else {
      cout << " ";
    }
  }
  cout << endl;
}

void PopulateDictionary(map<char, char>* dict, string dictionary) {
  string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < static_cast<int>(dictionary.length()); ++i) {
    (*dict)[dictionary.at(i)] = alphabet.at(i);
  }
}

int main(int argc, char** argv) {
  string dictionary = argv[1];
  map<char, char> dict;
  PopulateDictionary(&dict, dictionary);
  ifstream file(argv[2]);
  string line;
  while (getline(file, line)) {
    ConvertLine(line, dict);
  }
}
