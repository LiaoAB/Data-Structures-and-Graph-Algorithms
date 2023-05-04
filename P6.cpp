#include<bits/stdc++.h>
using namespace std;

#define MAX 9999;

// define data structure node for tree
struct Node {
  int l, r;
  int min, max;
  Node *left, *right;
};

int max(int a, int b);
int min(int a, int b);
void update(Node *root, int x, int value);
void query(Node *root, int l, int r);
void build(Node *root, int l, int r);

Node tree[20000];
int num[10000];
int nNodeCount = 0;

// build tree to store input data
void build(Node *root, int l, int r) {
  root->l = l;
  root->r = r;

  // create a line segment tree for the [l,r] interval
  if (l == r) {
    root->min = root->max = num[l];
    return;
  }
  nNodeCount++;
  root->left = tree + nNodeCount;
  nNodeCount++;
  root->right = tree + nNodeCount;
  int m = (l + r) >> 1;

  // recursively build trees for the left and right intervals
  build(root->left, l, m);
  build(root->right, m + 1, r);
  root->max = max(root->left->max, root->right->max);
  root->min = min(root->left->min, root->right->min);
}


void update(Node *root, int pos, int value) {

  if (root->l == root->r) {
    root->max += value;
    root->min = root->max;
    return;
  }

  // when the current interval is a subset of the modified interval, 
  // directly modify the value of the current node, 
  // then mark it, and end the modification
  int m = (root->l + root->r) >> 1;
  if (pos <= m) {
    update(root->left, pos, value);
  } else {
    update(root->right, pos, value);
  }

  // get max in l or r
  root->max = max(root->left->max, root->right->max);
  // get min in l or r
  root->min = min(root->left->min, root->right->min);
}

int max(int a, int b) {
  // check max in a or b
  int maxValue;
  maxValue = a > b ? a : b;
  return maxValue;
}

int min(int a, int b) {
  // check min in a or b
  int minValue;
  minValue = a < b ? a : b;
  return minValue;
}

int ans_max, ans_min;


void query(Node *root, int l, int r) {
  if (root->l == l && root->r == r) {
    // [l,r] is completely contained by the query interval
    ans_max = ans_max > root->max ? ans_max : root->max;
    ans_min = ans_min < root->min ? ans_min : root->min;
    return;
  }

  int m = (root->l + root->r) >> 1;
 
  if (r <= m) {
    // if the query range is in the left half, only check the left half
    query(root->left, l, r);
  } else if (l > m) {
    // if the query range is in the right half, only check the right half
    query(root->right, l, r);
  } else {
    // if the query interval spans two halves, then cut the query interval in half
    // this ensures that [root->l,root->r] must be within [L,R] after recursion
    query(root->left, l, m);
    query(root->right, m + 1, r);
  }
}

int main() {
  int i = 0;
  int input, L, R;
  cout << "Enter a sequence (-1 is the end):\n";
  while (cin >> input && input != -1) {
    num[i] = input;
    i++;
  }

  cout << "Enter left bound: ";
  cin >> L;
  cout << "Enter right bound: ";
  cin >> R;

  build(tree, 0, i);
  query(tree, L, R);
  cout << "max:" << ans_max << endl;
}