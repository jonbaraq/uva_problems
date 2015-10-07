#include <iostream>
#include <string>

using namespace std;
typedef long long int64;

int kMaxLevel = 5;

struct tree {
  tree* node1;
  tree* node2;
  tree* node3;
  tree* node4;
  char value;
};

tree* BuildTree(const string& a, int* index) {
  tree* t = new tree;
  t->value = a[*index];
  (*index) += 1;
  if (t->value != 'p') {
    return t;
  }
  t->node1 = BuildTree(a, index);
  t->node2 = BuildTree(a, index);
  t->node3 = BuildTree(a, index);
  t->node4 = BuildTree(a, index);
  return t;
}

int CountBlacks(tree* a, tree* b, int level) {
  if (a == NULL && b == NULL) {
    return 0;
  }
  if (a == NULL) {
    if (b->value == 'p') {
      return CountBlacks(NULL, b->node1, level + 1) +
        CountBlacks(NULL, b->node2, level + 1) +
        CountBlacks(NULL, b->node3, level + 1) +
        CountBlacks(NULL, b->node4, level + 1);
    }
    if (b->value == 'e') {
      return 0;
    }
    return (1 << ((kMaxLevel - level) * 2));
  }
  if (b == NULL) {
    if (a->value == 'p') {
      return CountBlacks(a->node1, NULL, level + 1) +
        CountBlacks(a->node2, NULL, level + 1) +
        CountBlacks(a->node3, NULL, level + 1) +
        CountBlacks(a->node4, NULL, level + 1);
    }
    if (a->value == 'e') {
      return 0;
    }
    return (1 << ((kMaxLevel - level) * 2));
  }
  if (a->value == 'f' || b->value == 'f') {
    return (1 << ((kMaxLevel - level) * 2));
  }
  if (a->value == 'e' && b->value == 'e') {
    return 0;
  }
  return CountBlacks(a->node1, b->node1, level + 1) +
    CountBlacks(a->node2, b->node2, level + 1) +
    CountBlacks(a->node3, b->node3, level + 1) +
    CountBlacks(a->node4, b->node4, level + 1);
}

void SolveProblem(const string& a, const string& b) {
  int index_a = 0;
  tree* tree_a = BuildTree(a, &index_a);
  int index_b = 0;
  tree* tree_b = BuildTree(b, &index_b);
  cout << "There are " << CountBlacks(tree_a, tree_b, 0) << " black pixels." << endl;
}

int main() {
  int cases;
  cin >> cases;
  while (cases > 0) {
    string a, b;
    cin >> a;
    cin >> b;
    SolveProblem(a, b);

    --cases;
  }
}
