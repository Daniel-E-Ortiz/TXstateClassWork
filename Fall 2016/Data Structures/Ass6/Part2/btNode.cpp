#include "btNode.h"

void dumpToArrayInOrder(btNode* bst_root, int* dumpArray)
{
   if (bst_root == 0) return;
   int dumpIndex = 0;
   dumpToArrayInOrderAux(bst_root, dumpArray, dumpIndex);
}

void dumpToArrayInOrderAux(btNode* bst_root, int* dumpArray, int& dumpIndex)
{
   if (bst_root == 0) return;
   dumpToArrayInOrderAux(bst_root->left, dumpArray, dumpIndex);
   dumpArray[dumpIndex++] = bst_root->data;
   dumpToArrayInOrderAux(bst_root->right, dumpArray, dumpIndex);
}

void tree_clear(btNode*& root)
{
   if (root == 0) return;
   tree_clear(root->left);
   tree_clear(root->right);
   delete root;
   root = 0;
}

int bst_size(btNode* bst_root)
{
   if (bst_root == 0) return 0;
   return 1 + bst_size(bst_root->left) + bst_size(bst_root->right);
}

// write definition for bst_insert here
void bst_insert(btNode*& bst_root, int insInt)
{
   if (bst_root == 0)
   {
      bst_root = new btNode;
      bst_root->data = insInt;
      bst_root->left = 0;
      bst_root->right = 0;
      return;
   }
   btNode* ptr = bst_root;
   btNode* prev = 0;
   while (ptr != 0)
   {
      prev = ptr;
      if (insInt < ptr->data)
         ptr = ptr->left;
      else if (insInt > ptr->data)
         ptr = ptr->right;
      else
         return;
   }
   if (insInt < prev->data)
   {
      ptr = new btNode;
      ptr->data = insInt;
      ptr->left = 0;
      ptr->right = 0;
      prev->left = ptr;
   }
   else
   {
      ptr = new btNode;
      ptr->data = insInt;
      ptr->left = 0;
      ptr->right = 0;
      prev->right = ptr;
   }
}

// write definition for bst_remove here
bool bst_remove(btNode*& bst_root, int remInt)
{
   if (bst_root == 0)
      return false;
   if (remInt == bst_root->data)
   {
      if (bst_root->left && bst_root->right)
         bst_remove_max(bst_root->left, bst_root->data);
      else
      {
         btNode *ptr = bst_root;
         if (bst_root->left)
            bst_root = bst_root->left;
         else if(bst_root->right)
            bst_root = bst_root->right;
         else
            bst_root = 0;
         delete ptr;
      }
      return true;
   }
   else if (remInt > bst_root->data)
      return bst_remove(bst_root->right,remInt);
   else
      return bst_remove(bst_root->left,remInt);
   return false;
}

// write definition for bst_remove_max here
void bst_remove_max(btNode*& bst_root, int& value)
{
   if (!(bst_root->right))
   {
      value = bst_root->data;
      btNode *ptr = bst_root;
      bst_root = bst_root->left;
      delete ptr;
   }
   else
      bst_remove_max(bst_root->right,value);
}