#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Create Linked list given a vector of int values
// returns pointer to head of lined list
ListNode* createLinkedList(vector<int> values) {
  ListNode* head;
  ListNode* node = new ListNode();
  head = node;
  for (int value : values) {
    node->next = new ListNode(value);
    node = node->next;
  }
  head = head->next;
  return head;
}

// Prints Linked List
// e.g. 5->8->3->NULL
void printLinkedList(ListNode* head) {
  ListNode* node = head;

  while (node != nullptr) {
    cout << node->val << "->";
    node = node->next;
  }
  cout << "NULL\n";
}

// Version 1:
//    Runtime 50 ms Beats 32.20%
//    Memory 18.6 MB Beats 16.61%
void reorderList1(ListNode* head) {
  // do nothing for link lists that have 0, 1 or 2 elements
  if ((head == nullptr) || (head->next == nullptr) || (head->next->next == nullptr))
    return;

  int num_nodes = 0, num = 0;
  ListNode* node = head;
  ListNode* temp;
  stack<ListNode*> stack_nodes;

  // add all the nodes on to the stack
  while (node != nullptr) {
    stack_nodes.push(node);
    node = node->next;
  }

  num_nodes = stack_nodes.size();
  node = head;
  while (num < num_nodes / 2) {
    temp = node->next;  // 3
    // set the next node
    node->next = stack_nodes.top();  // 4
    stack_nodes.pop();

    node = node->next;  // 4
    node->next = temp;  // 3
    node = node->next;  // 3
    num++;
  }

  node->next = nullptr;
}

// Version 2:
//    Runtime 48 ms Beats 39.35%
//    Memory 17.8 MB Beats 51.6%
void reorderList(ListNode* head) {
  // do nothing for link lists that have 0, 1 or 2 elements
  if ((head == nullptr) || (head->next == nullptr) || (head->next->next == nullptr))
    return;

  ListNode* slow = head;
  ListNode* fast = head->next;

  while ((fast) && (fast->next)) {
    slow = slow->next;
    fast = fast->next->next;
  }

  // slow is pointing to the middle element of the list
  // cout << "slow: " << slow->val << endl;

  // get the element next to the middle element
  ListNode* second = slow->next;
  // in our new list the middle element is the last element so it should point to null
  slow->next = nullptr;

  // reverse the second half of the list starting with second
  ListNode* previous = nullptr;
  ListNode* temp;
  while (second) {
    temp = second->next;
    second->next = previous;
    previous = second;
    second = temp;
  }

  // merge the 2 halfs of the list
  ListNode* first = head;
  ListNode* temp2;
  second = previous;
  // ListNode* temp2;
  while (second) {
    temp = first->next;
    first->next = second;

    temp2 = second->next;
    second->next = temp;

    first = temp;
    second = temp2;
  }
}

int main(int argc, char const* argv[]) {
  ListNode* n = createLinkedList({1, 2, 3, 4, 5});
  printLinkedList(n);
  reorderList(n);
  printLinkedList(n);
  return 0;
}
