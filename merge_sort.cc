#include <iostream>
#include <vector>

using namespace std;


void Merge(const vector<int>& left, const vector<int>& right, vector<int>* result) {
  int position = 0;
  int left_pos = 0;
  int right_pos = 0;
  cout << "Printing left " << endl;
  for (int i = 0; i < left.size(); ++i) {
    cout << left[i] << endl;
  }
  cout << "Printing right " << endl;
  for (int i = 0; i < right.size(); ++i) {
    cout << right[i] << endl;
  }
  for (int i = 0; i < result->size(); ++i) {
    if (left_pos > (left.size() - 1)) {
      (*result)[i] = right[right_pos];
      ++right_pos;
      continue;
    }
    if (right_pos > (right.size() - 1)) {
      (*result)[i] = left[left_pos];
      ++left_pos;
      continue;
    }
    if (left[left_pos] < right[right_pos]) {
      (*result)[i] = left[left_pos];
      ++left_pos;
    } else {
      (*result)[i] = right[right_pos];
      ++right_pos;
    }
  }
  cout << "Printing merge" << endl;
  for (int i = 0; i < result->size(); ++i) {
    cout << (*result)[i] << endl;
  }
}

void MergeSort(const vector<int>& orig, vector<int>* result) {
  if (orig.size() > 2) {
    vector<int>::const_iterator middle = orig.begin() + (orig.size() / 2);
    vector<int> left(orig.begin(), middle);
    vector<int> right(middle, orig.end());

    // Results to be populated.
    vector<int> left_result(left.size());
    vector<int> right_result(right.size());

    MergeSort(left, &left_result);
    MergeSort(right, &right_result);
    Merge(left_result, right_result, result);
  }
  if (orig.size() == 1) {
    (*result)[0] = orig[0];
  } else {
    if (orig[0] > orig[1]) {
      (*result)[0] = orig[1];
      (*result)[1] = orig[0];
    } else {
      (*result)[0] = orig[0];
      (*result)[1] = orig[1];
    }
  }
}

int main() {
  vector<int> list(10);
  cout << "Insert the number you want to sort:" << endl;
  for (int i = 0; i < list.size(); ++i) {
    cin >> list[i];
  } 
  vector<int> result(list.size());
  MergeSort(list, &result);
  cout << endl;
  for (int i = 0; i < result.size(); ++i) {
    cout << result[i] << endl;
  } 
}
