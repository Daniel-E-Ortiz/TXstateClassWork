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
                    do
                    {
                       cout << inStr << (used + 1);
                       cout << ':' << ' ';
                       cin >> oneInt;
                       if ((oneInt & 1) != 0)
                       {
                          *hopPtr1 = oneInt;
                          ++hopPtr1;
                       }
                       else
                       {
                          ++numEven;
                          *endPtr1 = oneInt;
                          --endPtr1;
                       }
                       ++used;
                       if (used == 10)
                       {
                          cout << slrStr << endl;
                          reply = 'n';
                       }
                       else
                       {
                          cout << mStr;
                          cin >> reply;
                       }
                    }
                    while (reply != 'n' && reply != 'N');

                    if (numEven > 0)
                    {
                       hopPtr2 = endPtr1 + 1;
                       endPtr2 = iArr + 9;
                       while (hopPtr2 < endPtr2)
                       {
                          leftInt = *hopPtr2;
                          rightInt = *endPtr2;
                          *hopPtr2 = rightInt;
                          *endPtr2 = leftInt;
                          ++hopPtr2;
                          --endPtr2;
                       }
                       hopPtr2 = endPtr1 + 1;
                       endPtr2 = iArr + 9;
                       while (hopPtr2 <= endPtr2)
                       {
                          *hopPtr1 = *hopPtr2;
                          ++hopPtr1;
                          ++hopPtr2;
                       }
                    }

                    cout << used << ieStr;
                    hopPtr1 = iArr;
                    endPtr1 = hopPtr1 + used;
                    while (hopPtr1 < endPtr1)
                    {
                       if (hopPtr1 < endPtr1 - 1)
                       {
                          cout << *hopPtr1 << ' ' << ' ';
                       }
                       else
                       {
                          cout << *hopPtr1 << endl;
                       }
                       ++hopPtr1;
                    }

                    return 0;
}

