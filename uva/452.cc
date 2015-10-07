#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Task {
  char id;
  int length;
  string dependencies;
  int start_time;
  Task() {
    id = '#';
    length = 0;
    dependencies = "";
  }
  Task(char id, int length, string dependencies) :
    id(id), length(length), dependencies(dependencies) {}
  void Add(char input) {
    dependencies.push_back(input);
  }
  void Print() const {
    cout << "ID: " << id << " length: " << length << " dependencies: " << 
      dependencies << endl;
  }
};

void SolveProblem(const vector<Task>& tasks) {
  map<char, vector<char> > inverse_dependencies;
  map<char, int> amount_dependencies;
  map<char, Task> task_id_to_task;
  int end_time = 0;
  queue<Task> q;
  // Initialize the data structures in O(N^2).
  for (int i = 0; i < tasks.size(); ++i) {
    Task t = tasks[i];
    task_id_to_task[t.id] = t;
    amount_dependencies[t.id] = t.dependencies.size();
    if (t.dependencies.size() == 0) {
      t.start_time = end_time;
      q.push(t);
    }
    for (int j = 0; j < t.dependencies.size(); ++j) {
      inverse_dependencies[t.dependencies[j]].push_back(t.id);
    }
  }

  // O(N^2)
  while (!q.empty()) {
    Task t = q.front();
    vector<char> dependencies = inverse_dependencies[t.id];
    q.pop();
    int start_time = t.start_time + t.length;
    end_time = max(end_time, start_time);
    for (int i = 0; i < dependencies.size(); ++i) {
      amount_dependencies[dependencies[i]] -= 1;
      if (amount_dependencies[dependencies[i]] == 0) {
        Task t1 = task_id_to_task[dependencies[i]];
        t1.start_time = start_time;
        q.push(t1);
      }
    }
  }

  cout << end_time << endl;
}

int main() {
  int cases;
  cin >> cases;
  string line;
  getline(cin, line);
  bool start = true;
  while (cases > 0) {
    if (start) {
      getline(cin, line);
      start = false;
    }
    vector<Task> tasks;
    while (getline(cin, line)) {
      if (line.empty()) {
        break;
      }
      istringstream iss(line);
      char char_id;
      int length;
      string dependencies;
      iss >> char_id >> length >> dependencies;
      Task t(char_id, length, dependencies);
      tasks.push_back(t);
    }
    SolveProblem(tasks);
    --cases;
    if (cases > 0) {
      cout << endl;
    }
  }
  return 0;
}
