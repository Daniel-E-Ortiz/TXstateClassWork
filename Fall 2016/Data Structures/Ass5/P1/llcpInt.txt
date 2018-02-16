#ifndef LLCP_INT_H
#define LLCP_INT_H

#include <iostream>

struct Node
{
   int data;
   Node *link;
};

int    FindListLength(Node* headPtr);
bool   IsSortedUp(Node* headPtr);
void   InsertAsHead(Node*& headPtr, int value);
void   InsertAsTail(Node*& headPtr, int value);
void   InsertSortedUp(Node*& headPtr, int value);
bool   DelFirstTargetNode(Node*& headPtr, int target);
bool   DelNodeBefore1stMatch(Node*& headPtr, int target);
void   ShowAll(std::ostream& outs, Node* headPtr);
void   FindMinMax(Node* headPtr, int& minValue, int& maxValue);
double FindAverage(Node* headPtr);
void   ListClear(Node*& headPtr, int noMsg = 0);

// prototype for CopySingletonsGatherDups of Assignment 5 Part 2
void MakeEachValRepImmOnce(Node* head);
void MakeOddsComeB4EvensInOrigOrder(Node*& head);
void InterleaveOddsAndEvensInOrigOrder(Node* head);
void MoveToSList1UnsharedItemsInSList2(Node*& head1, Node*& head2);
void BuildUniqueSList2FromSList1(Node*& head1, Node*& head2);
void Form2NoDupListsUsgGivenList(Node* head1, Node*& head2);
void RemOddDupEven(Node*& head);
void MakeDistinctPairs(Node* head);

// prototype for CopySingletonsGatherDups of Assignment 5 Part 1
void CopySingletonsGatherDups(Node* head1, Node*& head2);
#endif

