// http://www.codercharts.com/puzzle/word-mangle

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
  ifstream file(argv[1]);
  string line;
  getline(file, line);
  vector<string> words;
  istringstream iss(line);
  string word;
  while (iss >> word) {
    words.push_back(word);
  }
  for(int i = static_cast<int>(words.size()) - 1; i > 0; --i) {
    cout << words[i] << " ";
  }
  cout << words[0] << endl;
  for (int i = 0; i < static_cast<int>(words.size()) - 1; ++i) {
    for (int j = static_cast<int>(words[i].size()) - 1; j >= 0; --j) {
      cout << words[i][j];
    }
    cout << " ";
  }
  word = words[static_cast<int>(words.size()) - 1];
  for (int j = static_cast<int>(word.size()) - 1; j >= 0; --j) {
    cout << word[j];
  }
  cout << endl;
}
