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
                   goto WTest_m;
begW_m:
                      PopulateArray1(reply, a1, &used1, 12);
                      if (used1 <= 0) goto endI_m;
begI_m:
                         cout << endl;
                         ShowArrayLabeled(a1, used1, begA1Str);
                         mean = PopulateArray1223(a1, a2, a3, used1, &used2, &used3);
                         ShowArrayLabeled(a2, used2, commA2Str);
                         ShowArrayLabeled(a3, used3, commA3Str);
                         ProcArrays(mean, a1, a2, a3, used1, &used2, &used3);
                         ShowArrayLabeled(a1, used1, procA1Str);
                         ShowArrayLabeled(a2, used2, commA2Str);
                         ShowArrayLabeled(a3, used3, commA3Str);
endI_m:
                      cout << endl;
                      cout << dacStr;
                      cin >> reply;
                      cout << endl;
WTest_m:
                   if (reply == 'n') goto xitW_m;
                   if (reply != 'N') goto begW_m;
xitW_m:
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
                   goto WTest_PA1;
begW_PA1:
                      CoutCstr(einStr);
                      CoutOneInt(*used1Ptr + 1);
                      cout << ':' << ' ';
                      cin >> a1[*used1Ptr];
                      ++(*used1Ptr);
                      if (*used1Ptr != cap) goto else_PA1;
begI_PA1:
                         CoutCstr(moStr);
                         CoutOneInt(cap);
                         CoutCstr(ieStr);
                         cout << endl;
                         reply = 'n';
                      goto endI_PA1;
 else_PA1:
                         CoutCstr(emiStr);
                         cin >> reply;
endI_PA1:
WTest_PA1:
                   if (reply == 'n') goto xitW_PA1;
                   if (reply != 'N') goto begW_PA1;
xitW_PA1:
                   return;
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
                   hopPtr1 = a1;
                   endPtr1 = a1 + used1;
                   goto FTest_PA1223;
begF_PA1223:
                      target = *hopPtr1;
                      total += target;
                      if (target % 2 == 0) goto else_PA1223;
begI_PA1223:
                         PopulateArray1223AuxO(a3, used3Ptr, target);
                      goto endI_PA1223;
else_PA1223:
                         PopulateArray1223AuxE(a2, used2Ptr, target);
endI_PA1223:
                   ++hopPtr1;
FTest_PA1223:
                   if (hopPtr1 < endPtr1) goto begF_PA1223;
                   return total/used1;
}

void PopulateArray1223AuxO(int a3[], int* used3Ptr, int target)
{
                   int *hopPtr3,
                       *endPtr3;
                   hopPtr3 = a3 + *used3Ptr - 1;
                   endPtr3 = a3;
                   goto WTest_PA1223AO;
begW_PA1223AO:
                      if (*hopPtr3 <= target) goto else_PA1223AO;
begI_PA1223AO:
                         *(hopPtr3 + 1) = *hopPtr3;
                         --hopPtr3;
                      goto endI_PA1223AO;
else_PA1223AO:
                         goto xitW_PA1223AO;
endI_PA1223AO:
WTest_PA1223AO:
                   if (hopPtr3 >= endPtr3) goto begW_PA1223AO;
xitW_PA1223AO:
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
                   goto WTest1_PA1223AE;
begW1_PA1223AE:
                      if (*hopPtr2 < target) goto else_PA1223AE;
begI_PA1223AE:
                         hopPtr21 = endPtr2;
                         goto WTest2_PA1223AE;
begW2_PA1223AE:
                            *hopPtr21 = *(hopPtr21 - 1);
                            --hopPtr21;
WTest2_PA1223AE:
                         if (hopPtr21 > hopPtr2) goto begW2_PA1223AE;

                         goto xitW1_PA1223AE;
else_PA1223AE:
                         ++hopPtr2;
endI_PA1223AE:
WTest1_PA1223AE:
                   if (hopPtr2 < endPtr2) goto begW1_PA1223AE;
xitW1_PA1223AE:
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
                   goto WTest1_MC2321;
begW1_MC2321:
                      if (*hopPtr2 >= *hopPtr3) goto else_MC2321;
begI_MC2321:
                         *hopPtr1 = *hopPtr2;
                         ++hopPtr2;
                      goto endI_MC2321;
else_MC2321:
                         *hopPtr1 = *hopPtr3;
                         ++hopPtr3;
endI_MC2321:
                      ++hopPtr1;
WTest1_MC2321:
                   if (hopPtr2 >= endPtr2) goto xitW1_MC2321;
                   if (hopPtr3 < endPtr3) goto begW1_MC2321;
xitW1_MC2321:

                   goto WTest2_MC2321;
begW2_MC2321:
                      *hopPtr1 = *hopPtr2;
                      ++hopPtr2;
                      ++hopPtr1;
WTest2_MC2321:
                   if (hopPtr2 < endPtr2) goto begW2_MC2321;

                   goto WTest3_MC2321;
begW3_MC2321:
                      *hopPtr1 = *hopPtr3;
                      ++hopPtr3;
                      ++hopPtr1;
WTest3_MC2321:
                   if (hopPtr3 < endPtr3) goto begW3_MC2321;
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
                   goto WTest_LMGMC1223;
begW_LMGMC1223:
                      target = *hopPtr1;
                      if (target >= mean) goto else1_LMGMC1223;
begI1_LMGMC1223:
                         *hopPtr2 = target;
                         ++(*used2Ptr);
                         ++hopPtr2;
                      goto endI1_LMGMC1223;
else1_LMGMC1223:
                         if (target <= mean) goto endI2_LMGMC1223;
begI2_LMGMC1223:
                            *hopPtr3 = target;
                            ++(*used3Ptr);
                            ++hopPtr3;
endI2_LMGMC1223:
endI1_LMGMC1223:
                      ++hopPtr1;
WTest_LMGMC1223:
                   if (hopPtr1 < endPtr1) goto begW_LMGMC1223;
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
                   i = 0;
                   goto FTest_SA;
begF_SA:
                      cout << array[i] << ' ' << ' ';
                   ++i;
FTest_SA:
                   if (i < used) goto begF_SA;

                   cout << endl;
}

void ShowArrayLabeled(const int array[], int used, const char label[])
{
                   CoutCstr(label);
                   ShowArray(array, used);
}
