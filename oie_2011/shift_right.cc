// http://www.olimpiada-informatica.org/?cmd=problema&pbm=shiftright

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void PrintWord(const string& word) {
  int last_string_position = static_cast<int>(word.size());
  cout << word[last_string_position - 1];
  for (int k = 0; k < last_string_position - 1; ++k) {
    cout << word[k];
  }
}

void PrintLine(const string& line) {
  istringstream iss(line);
  string word;
  vector<string> words_line;
  while (iss >> word) {
    words_line.push_back(word);
  }
  int number_words = static_cast<int>(words_line.size());
  PrintWord(words_line.back());
  for (int j = 0; j < number_words - 1; ++j) {
    cout << " ";
    PrintWord(words_line[j]);
  }
  cout << endl;
}

void PrintLinesShiftedRight(const vector<string>& lines) {
  int number_lines = static_cast<int>(lines.size());
  PrintLine(lines.back());
  for (int i = 0; i < number_lines - 1; ++i) {
    PrintLine(lines[i]);
  }
}

int main() {
  int number_lines;
  while (cin >> number_lines >> ws) {
    vector<string> lines(number_lines);
    int tmp_counter = 0;
    while (tmp_counter < number_lines) {
      getline(cin, lines[tmp_counter]);
      ++tmp_counter;
    }
    PrintLinesShiftedRight(lines);
  }
}
