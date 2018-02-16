#include <iostream>
using namespace std;

int iArr[10];
char inStr[]  = "Int #";
char slrStr[] = "Allowed hi of 10 reached...";
char mStr[]   = "More? (n or N = no, other = yes) ";
char ieStr[]  = " ints entered, odd-even grouped: ";

int main()
{
                    int used = 0,
                        numEven = 0;
                    char reply;
                    int oneInt,
                        leftInt,
                        rightInt;
                    int* hopPtr1;
                    int* hopPtr2;
                    int* endPtr1;
                    int* endPtr2;

                    hopPtr1 = iArr;
                    endPtr1 = iArr + 9;
                    //do
begDW1://           {
                       cout << inStr << (used + 1);
                       cout << ':' << ' ';
                       cin >> oneInt;
                       //if (oneInt & 1 != 0)
                       if ((oneInt & 1) == 0) goto elseI1;
begI1://               {
                          *hopPtr1 = oneInt;
                          ++hopPtr1;
                       goto endI1;
//                     }
elseI1://              else
//                     {
                          ++numEven;
                          *endPtr1 = oneInt;
                          --endPtr1;
endI1://               }
                       ++used;
                       //if (used == 10)
                       if (used != 10) goto elseI2;
begI2://               {
                          cout << slrStr << endl;
                          reply = 'n';
                       goto endI2;
//                     }
elseI2://              else
//                     {
                          cout << mStr;
                          cin >> reply;
endI2://               }
endDW1://           }
                    //while (reply != 'n' && reply != 'N');
DWTest1:
                    ///if (reply != 'n' && reply != 'N') goto begDW1;
                    if (reply == 'n') goto xitDW1;
                    if (reply != 'N') goto begDW1;
xitDW1:

                    //if (numEven > 0)
cout << "numEven = " << numEven << endl;
                    if (numEven <= 0) goto endI3;
begI3://            {
                       hopPtr2 = endPtr1 + 1;
                       endPtr2 = iArr + 9;
                       //while (hopPtr2 < endPtr2)
                       goto WTest1;
begW1://               {
                          leftInt = *hopPtr2;
                          rightInt = *endPtr2;
                          *hopPtr2 = rightInt;
                          *endPtr2 = leftInt;
                          ++hopPtr2;
                          --endPtr2;
endW1://               }
WTest1:
                       if (hopPtr2 < endPtr2) goto begW1;

                       hopPtr2 = endPtr1 + 1;
                       endPtr2 = iArr + 9;
                       //while (hopPtr2 <= endPtr2)
                       goto WTest2;
begW2://               {
                          *hopPtr1 = *hopPtr2;
                          ++hopPtr1;
                          ++hopPtr2;
endW2://               }
WTest2:
                       if (hopPtr2 <= endPtr2) goto begW2;

endI3://            }

                    cout << used << ieStr;
                    hopPtr1 = iArr;
                    endPtr1 = hopPtr1 + used;
                    //while (hopPtr1 < endPtr1)
                    goto WTest3;
begW3://            {
                       //if (hopPtr1 < endPtr1 - 1)
                       if (hopPtr1 >= endPtr1 - 1) goto elseI4;
begI4://               {
                          cout << *hopPtr1 << ' ' << ' ';
                       goto endI4;
//                     }
elseI4://              else
//                     {
                          cout << *hopPtr1 << endl;
endI4://               }
                       ++hopPtr1;
endW3://            }
WTest3:
                    if (hopPtr1 < endPtr1) goto begW3;

                    return 0;
}
