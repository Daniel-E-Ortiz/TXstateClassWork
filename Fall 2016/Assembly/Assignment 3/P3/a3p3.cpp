#include <iostream>
using namespace std;

void PopulateArray1(char reply, int a1[], int* used1Ptr, int cap);
int  PopulateArray1223(int a1[], int a2[], int a3[], int used1, int* used2Ptr, int* used3Ptr);
void PopulateArray1223AuxO(int a3[], int* used3Ptr, int target);
void PopulateArray1223AuxE(int a2[], int* used2Ptr, int target);
void ProcArrays(int mean, int a1[], int a2[], int a3[], int used1, int* used2Ptr, int* used3Ptr);
void MergeCopy2321(int* used2Ptr, int a1[], int a2[], int a3[], int* used3Ptr);
void LtMeanGtMeanCopy1223(int mean, int a1[], int a2[], int a3[],
                          int used1, int* used2Ptr, int* used3Ptr);
void CoutCstr(const char cstr[]);
void CoutCstrNL(const char cstr[]);
void CoutOneInt(int oneInt);
void ShowArray(const int a[], int size);
void ShowArrayLabeled(const int array[], int used, const char label[]);

int main()
{
                   int a1[12],
                       a2[12],
                       a3[12];
                   char reply;
                   int used1,
                       used2,
                       used3,
                       mean;
                   char begA1Str[]  = "beginning a1: ";
                   char procA1Str[] = "processed a1: ";
                   char commA2Str[] = "          a2: ";
                   char commA3Str[] = "          a3: ";
                   char dacStr[]    = "Do another case? (n or N = no, others = yes) ";
                   char dlStr[]     = "================================";
                   char byeStr[]    = "bye...";

                   cout << endl;
                   reply = 'y';
                   while (reply != 'n' && reply != 'N')
                   {
                      PopulateArray1(reply, a1, &used1, 12);
                      if (used1 > 0)
                      {
                         cout << endl;
                         ShowArrayLabeled(a1, used1, begA1Str);
                         mean = PopulateArray1223(a1, a2, a3, used1, &used2, &used3);
                         ShowArrayLabeled(a2, used2, commA2Str);
                         ShowArrayLabeled(a3, used3, commA3Str);
                         ProcArrays(mean, a1, a2, a3, used1, &used2, &used3);
                         ShowArrayLabeled(a1, used1, procA1Str);
                         ShowArrayLabeled(a2, used2, commA2Str);
                         ShowArrayLabeled(a3, used3, commA3Str);
                      }
                      cout << endl;
                      cout << dacStr;
                      cin >> reply;
                      cout << endl;
                   }

                   CoutCstrNL(dlStr);
                   CoutCstrNL(byeStr);
                   CoutCstrNL(dlStr);

                   return 0;
}

void PopulateArray1(char reply, int a1[], int* used1Ptr, int cap)
{
                   char einStr[] = "Enter integer #";
                   char moStr[]  = "Max of ";
                   char ieStr[]  = " ints entered...";
                   char emiStr[] = "Enter more ints? (n or N = no, others = yes) ";
                   *used1Ptr = 0;
                   while (reply != 'n' && reply != 'N')
                   {
                      CoutCstr(einStr);
                      CoutOneInt(*used1Ptr + 1);
                      cout << ':' << ' ';
                      cin >> a1[*used1Ptr];
                      ++(*used1Ptr);
                      if (*used1Ptr == cap)
                      {
                         CoutCstr(moStr);
                         CoutOneInt(cap);
                         CoutCstr(ieStr);
                         cout << endl;
                         reply = 'n';
                      }
                      else
                      {
                         CoutCstr(emiStr);
                         cin >> reply;
                      }
                   }
}

int PopulateArray1223(int a1[], int a2[], int a3[], int used1, int* used2Ptr, int* used3Ptr)
{
                   int target,
                       total,
                       *hopPtr1,
                       *endPtr1;
                   *used2Ptr = 0;
                   *used3Ptr = 0;
                   total = 0;
                   for (hopPtr1 = a1, endPtr1 = a1 + used1; hopPtr1 < endPtr1; ++hopPtr1)
                   {
                      target = *hopPtr1;
                      total += target;
                      if (target % 2 == 1)
                      {
                         PopulateArray1223AuxO(a3, used3Ptr, target);
                      }
                      else
                      {
                         PopulateArray1223AuxE(a2, used2Ptr, target);
                      }
                   }
                   return total/used1;
}

void PopulateArray1223AuxO(int a3[], int* used3Ptr, int target)
{
                   int *hopPtr3,
                       *endPtr3;
                   hopPtr3 = a3 + *used3Ptr - 1;
                   endPtr3 = a3;
                   while (hopPtr3 >= endPtr3)
                   {
                      if (*hopPtr3 > target)
                      {
                         *(hopPtr3 + 1) = *hopPtr3;
                         --hopPtr3;
                      }
                      else
                      {
                         break;
                      }
                   }
                   *(hopPtr3 + 1) = target;
                   ++(*used3Ptr);
}

void PopulateArray1223AuxE(int a2[], int* used2Ptr, int target)
{
                   int *hopPtr2,
                       *hopPtr21,
                       *endPtr2;
                   hopPtr2 = a2;
                   endPtr2 = a2 + *used2Ptr;
                   while (hopPtr2 < endPtr2)
                   {
                      if (*hopPtr2 >= target)
                      {
                         hopPtr21 = endPtr2;
                         while (hopPtr21 > hopPtr2)
                         {
                            *hopPtr21 = *(hopPtr21 - 1);
                            --hopPtr21;
                         }
                         break;
                      }
                      else
                      {
                         ++hopPtr2;
                      }
                   }
                   *hopPtr2 = target;
                   ++(*used2Ptr);
}

void ProcArrays(int mean, int a1[], int a2[], int a3[], int used1, int* used2Ptr, int* used3Ptr)
{

                   MergeCopy2321(used2Ptr, a1, a2, a3, used3Ptr);
                   LtMeanGtMeanCopy1223(mean, a1, a2, a3, used1, used2Ptr, used3Ptr);
}

void MergeCopy2321(int* used2Ptr, int a1[], int a2[], int a3[], int* used3Ptr)
{
                   int *hopPtr1,
                       *hopPtr2,
                       *hopPtr3,
                       *endPtr2,
                       *endPtr3;
                   hopPtr1 = a1;
                   hopPtr2 = a2;
                   hopPtr3 = a3;
                   endPtr2 = a2 + *used2Ptr;
                   endPtr3 = a3 + *used3Ptr;
                   while (hopPtr2 < endPtr2 && hopPtr3 < endPtr3)
                   {
                      if (*hopPtr2 < *hopPtr3)
                      {
                         *hopPtr1 = *hopPtr2;
                         ++hopPtr2;
                      }
                      else
                      {
                         *hopPtr1 = *hopPtr3;
                         ++hopPtr3;
                      }
                      ++hopPtr1;
                   }
                   while (hopPtr2 < endPtr2)
                   {
                      *hopPtr1 = *hopPtr2;
                      ++hopPtr2;
                      ++hopPtr1;
                   }
                   while (hopPtr3 < endPtr3)
                   {
                      *hopPtr1 = *hopPtr3;
                      ++hopPtr3;
                      ++hopPtr1;
                   }
}


void LtMeanGtMeanCopy1223(int mean, int a1[], int a2[], int a3[],
                          int used1, int* used2Ptr, int* used3Ptr)
{
                   int *hopPtr1,
                       *hopPtr2,
                       *hopPtr3,
                       *endPtr1;
                   int target;
                   hopPtr1 = a1;
                   hopPtr2 = a2;
                   hopPtr3 = a3;
                   endPtr1 = a1 + used1;
                   *used2Ptr = 0;
                   *used3Ptr = 0;
                   while (hopPtr1 < endPtr1)
                   {
                      target = *hopPtr1;
                      if (target < mean)
                      {
                         *hopPtr2 = target;
                         ++(*used2Ptr);
                         ++hopPtr2;
                      }
                      else
                      {
                         if (target > mean)
                         {
                            *hopPtr3 = target;
                            ++(*used3Ptr);
                            ++hopPtr3;
                         }
                      }
                      ++hopPtr1;
                   }
}

void CoutCstr(const char cstr[])
{
                   cout << cstr;
}

void CoutCstrNL(const char cstr[])
{
                   CoutCstr(cstr);
                   cout << '\n';
}

void CoutOneInt(int oneInt)
{
                   cout << oneInt;
}

void ShowArray(const int array[], int used)
{
                   int i;
                   for (i = 0; i < used; ++i)
                   {
                      cout << array[i] << ' ' << ' ';
                   }
                   cout << endl;
}

void ShowArrayLabeled(const int array[], int used, const char label[])
{
                   CoutCstr(label);
                   ShowArray(array, used);
}
