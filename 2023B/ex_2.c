typedef struct BTree {
  struct BTree *left;
  struct BTree *right;
  int data;
} BTree;

void printDepthVal(BTree *root, int num) {
  BTree *nodeOfNumber = findNodeOfNumber(root);
  int treeDepth = findDepth(root);
  int nodeOfNumberDepth = treeDepth - findDepth(nodeOfNumber);
}
void printAtDepth(BTree *root, int depth, int currentDepth) {
  if (root == NULL) return;
  if (depth == currentDepth) {
    printf("%d\n", root->data);
    return;
  }
  printAtDepth(root->left, depth, currentDepth + 1);
  printAtDepth(root->right, depth, currentDepth + 1);
}
int findDepth(BTree *root) {
  int rightDepth = 1;
  int leftDepth = 1;
  if (root == NULL) return 0;

  if (root->left != NULL) leftDepth += findDepth(root->left);
  if (root->right != NULL) rightDepth += findDepth(root->right);
  return (leftDepth > rightDepth) ? leftDepth : rightDepth;
}
BTree *findNodeOfNumber(BTree *root, int num) {
  BTree *left;
  BTree *right;

  if (root == NULL) return NULL;
  if (root->data == num) return root;
  left = findNodeOfNumber(root->left, num);
  right = findNodeOfNumber(root->right, num);
  if (left != NULL) return left;
  return right;
}
