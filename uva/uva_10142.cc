#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void GetLineScores(const string& line, vector<int>* scores) {
  int number;
  istringstream iss(line);
  while (iss >> number) {
    scores->push_back(number);
  }
}

void EliminateCandidates(const map<int, int>& score_map,
                         map<int, bool>* eliminated_candidates,
                         string* solution) {
  int max_element;
  int max_value = -1;
  int min_element;
  int min_value = -1;
  for (
}

void SelectCandidate(const vector<string>& candidates,
                     const vector<vector<int> >& scores,
                     string* result) {
  int total_votes = scores.size();
  map<int, int> score_map;
  map<int, bool> eliminated_candidates;
  for (int i = 0; i < candidates.size(); ++i) {
    eliminated_candidates[i] = false;
  }
  for (int i = 0; i < candidates.size(); ++i) {
    for (int j = 0; j < total_votes; ++j) {
      if (!score_map[scores[i][j]]) {
        score_map[scores[i][j]] = 0;
      }
      ++score_map[scores[i][j]];
    }
    EliminateCandidates(score_map, &eliminated_candidates, result);
  }
}

int main() {
  int num_cases;
  cin >> num_cases;
  for (int i = 0; i < num_cases; ++i) {
    int candidates;
    cin >> candidates;
    vector<string> candidates_names(candidates);
    for (int j = 0; j < candidates; ++j) {
      cin >> candidates_names[j];
    }
    string line;
    vector<vector<int> > scores;
    while (getline(cin, line)) {
      vector<int> line_scores;
      GetLineScores(line, &line_scores);
      scores.push_back(line_scores);
    }
    string winner;
    SelectCandidate(candidates_names, scores, &winner);
    cout << winner << endl;
  }
}
