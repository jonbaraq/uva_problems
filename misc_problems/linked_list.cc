#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct node {
  int value;
  node* next;
};

void insert(node* list, node* value) {
  while(list->next != NULL) {
    list = list->next;
    cout << "Now pointintg to " << list->value << endl;
  }
  list->next = value;
}

void invert(node* orig) {
  node* prev = NULL;
  node* current = orig;
  node* next;
  while (current != NULL) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  orig = prev;
}

void remove(node* list, int value) {
  bool deleted = false;
  node* previous;
  while(list->next != NULL) {
    if (list->value == value) {
      node* tmp = list->next;
      list->next = tmp->next;
      list->value = tmp->value;
      deleted = true;
    }
    if (list->next == NULL) {
      break;
    }
    previous = list;
    list = list->next;
  }
  if (!deleted && list->value == value) {
    previous->next = NULL;
  }
}

void print(node* list) {
  while(list->next != NULL) {
    cout << list->value << endl;
    list = list->next;
  }
  cout << list->value << endl;
}

void search(node* list, int value) {
  if (list->value == value) {
    cout << list << endl;
  } else if (list->next != NULL) {
    search(list->next, value);
  } else {
    cout << "Not found" << endl;
  }
}

int main() {
  // Print initial content.
  node node3;
  node3.value = 6;
  node3.next = NULL;
  node node2;
  node2.value = 5;
  node2.next = &node3;
  node node1;
  node1.value = 3;
  node1.next = &node2;
  print(&node1);

  // Test search.
  search(&node1, 3);
  search(&node1, 5);
  search(&node1, 8);

  cout << "Test insert " << endl;
  // Test insert.
  node new_node;
  new_node.value = 12;
  new_node.next = NULL;
  insert(&node1, &new_node);
  print(&node1);
  node new_node2;
  new_node2.value = 12213;
  new_node2.next = NULL;
  insert(&node1, &new_node2);
  print(&node1);
  search(&node1, 12213);

  remove(&node1, 12213);
  cout << endl;
  print(&node1);

  cout << endl;
  node inverted;
  invert(&node1);
  print(&node1);
}
