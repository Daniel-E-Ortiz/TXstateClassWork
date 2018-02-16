#####################################################################
# Title: Assign02P3			Author: Daniel Ortiz
# Class: CS 2318-002, Fall 2016		Submitted: <date>
#####################################################################
# Program: MIPS translation of a given C++ program
#####################################################################
# Pseudocode description: supplied a2p2_SampSoln.cpp
#####################################################################
######################## data segment ###############################
			.data
einStr:			.asciiz "\nEnter integer #"
moStr:			.asciiz "Max of "
ieStr:			.asciiz "ints entered..."
emiStr:			.asciiz "Enter more ints? (n or N = no, others = yes) "
begA1Str:		.asciiz "beginning a1: "
procA1Str:		.asciiz "processed a1: "
commA2Str:		.asciiz "          a2: "
commA3Str:		.asciiz "          a3: "
dacStr:			.asciiz "Do another case? (n or N = no, others = yes) "
dlStr:			.asciiz "================================"
byeStr:			.asciiz "bye..."

			.text
			.globl main
main:
#include <iostream>
#using namespace std;
#int a1[12],
#    a2[12],
#    a3[12];
#char einStr[]    = "";
#char moStr[]     = "";
#char ieStr[]     = "";
#char emiStr[]    = "";
#char begA1Str[]  = "";
#char procA1Str[] = ;
#char commA2Str[] = ;
#char commA3Str[] = ;
#char dacStr[]    = ;
#char dlStr[]     = ;
#char byeStr[]    = ;
#####################################################################
# Register Usage:
#################
# $a1: endPtr1
# $a2: endPtr2
# $a3: endPtr3
# $t0: store-to address or temp holder 2 (non-overlappingly)
# $t1: used1
# $t2: used2
# $t3: used3
# $t4: target
# $t5: hopPtr1
# $t6: hopPtr2
# $t7: hopPtr3
# $t8: hopPtr21 or mean (overlap with no harm)
# $t9: total
# $v1: temp holder 1 (non-overlappingly)
#####################################################################

#               cout << endl;
#               reply = 'y';
#               //while (reply != 'n' && reply != 'N')
#               goto WTest1;
begW1:#//       {
#                  used1 = 0;
#                  used2 = 0;
#                  used3 = 0;
#                  hopPtr1 = a1;
#                  //while (reply != 'n' && reply != 'N')
#                  goto WTest2;
begW2:#//          {
#                     cout << einStr;
#                     cout << (used1 + 1);
#                    cout << ':' << ' ';
                     cin >> *hopPtr1;
                     ++used1;
                     ++hopPtr1;
                     //if (used1 < 12)
                     if (used1 >= 12) goto else1;
begI1://             {
                        cout << emiStr;
                        cin >> reply;
                     goto endI1;
//                   }
else1://             else
//                   {
                        cout << moStr << 12 << ieStr << endl;
                        reply = 'n';
endI1://             }
WTest2://         }
                  ////if (reply != 'n' && reply != 'N') goto begW2;
                  if (reply == 'n') goto xitW2;
                  if (reply != 'N') goto begW2;
xitW2:
                  cout << endl;

                  //if (used1 > 0)
                  if (used1 <= 0) goto endI2;
begI2://          {
                     total = 0;
                     //for (hopPtr1 = a1, endPtr1 = a1 + used1; hopPtr1 < endPtr1; ++hopPtr1)
                     hopPtr1 = a1;
                     endPtr1 = a1 + used1;
                     goto FTest1;
begF1://             {
                        target = *hopPtr1;
                        total += target;
                        //if (target % 2 == 1)
                        ////if (target % 2 != 1) goto else3;
                        if ( (target & 1) != 1) goto else3;
begI3://                {
                           hopPtr3 = a3 + used3 - 1;
                           endPtr3 = a3;
                           //while (hopPtr3 >= endPtr3)
                           goto WTest3;
begW3://                   {
                              //if (*hopPtr3 > target)
                              if (*hopPtr3 <= target) goto else4;
begI4://                      {
                                 *(hopPtr3 + 1) = *hopPtr3;
                                 --hopPtr3;
                              goto endI4;
//                            }
else4://                      else
//                            {
                                 //break;
                                 goto xitW3;
endI4://                      }
WTest3://                  }
                           if (hopPtr3 >= endPtr3) goto begW3;
xitW3:
                           *(hopPtr3 + 1) = target;
                           ++used3;
                        goto endI3;
//                      }
else3://                else
//                      {
                           hopPtr2 = a2;
                           endPtr2 = a2 + used2;
                           //while (hopPtr2 < endPtr2)
                           goto WTest4;
begW4://                   {
                              //if (*hopPtr2 >= target)
                              if (*hopPtr2 < target) goto else5;
begI5://                      {
                                 hopPtr21 = endPtr2;
                                 ///while (hopPtr21 > hopPtr2)
                                 goto WTest5;
begW5://                         {
                                    *hopPtr21 = *(hopPtr21 - 1);
                                    --hopPtr21;
WTest5://                        }
                                 if (hopPtr21 > hopPtr2) goto begW5;

                                 ///break;
                                 goto xitW4;
                           ///goto endI5; // unreacheable
//                            }
else5://                      else
//                            {
                                 ++hopPtr2;
endI5://                      }
WTest4://                  }
                           if (hopPtr2 < endPtr2) goto begW4;
xitW4:
                           *hopPtr2 = target;
                           ++used2;
endI3://                }
                        mean = total/used1;
                     ++hopPtr1;
FTest1://            }
                     if (hopPtr1 < endPtr1) goto begF1;

                     cout << begA1Str;
                     //if (used1 > 0)
                     if (used1 <= 0) goto endI6;
begI6://             {
                        hopPtr1 = a1;
                        endPtr1 = a1 + used1;
//                      do
begDW1://               {
                           cout << *hopPtr1 << ' ' << ' ';
                           ++hopPtr1;
DWTest1://              }
                        //while (hopPtr1 < endPtr1);
                        if (hopPtr1 < endPtr1) goto begDW1;
endI6://             }
                     cout << endl;

                     cout << commA2Str;
                     //if (used2 > 0)
                     if (used2 <= 0) goto endI7;
begI7://             {
                        hopPtr2 = a2;
                        endPtr2 = a2 + used2;
//                      do
begDW2://               {
                           cout << *hopPtr2 << ' ' << ' ';
                           ++hopPtr2;
DWTest2://              }
                        //while (hopPtr2 < endPtr2);
                        if (hopPtr2 < endPtr2) goto begDW2;
endI7://             }
                     cout << endl;

                     cout << commA3Str;
                     //if (used3 > 0)
                     if (used3 <= 0) goto endI8;
begI8://             {
                        hopPtr3 = a3;
                        endPtr3 = a3 + used3;
//                      do
begDW3://               {
                           cout << *hopPtr3 << ' ' << ' ';
                           ++hopPtr3;
DWTest3://              }
                        //while (hopPtr3 < endPtr3);
                        if (hopPtr3 < endPtr3) goto begDW3;
endI8://             }
                     cout << endl;

                     hopPtr1 = a1;
                     hopPtr2 = a2;
                     hopPtr3 = a3;
                     endPtr2 = a2 + used2;
                     endPtr3 = a3 + used3;
                     //while (hopPtr2 < endPtr2 && hopPtr3 < endPtr3)
                     goto WTest6;
begW6://             {
                        //if (*hopPtr2 < *hopPtr3)
                        if (*hopPtr2 >= *hopPtr3) goto else9;
begI9://                {
                           *hopPtr1 = *hopPtr2;
                           ++hopPtr2;
                        goto endI9;
//                      }
else9://                else
//                      {
                           *hopPtr1 = *hopPtr3;
                           ++hopPtr3;
endI9://                }
                        ++hopPtr1;
WTest6://            }
                     ////if (hopPtr2 < endPtr2 && hopPtr3 < endPtr3) goto begW6;
                     if (hopPtr2 >= endPtr2) goto xitW6;
                     if (hopPtr3 < endPtr3) goto begW6;
xitW6:
                     //while (hopPtr2 < endPtr2)
                     goto WTest7;
begW7://             {
                        *hopPtr1 = *hopPtr2;
                        ++hopPtr2;
                        ++hopPtr1;
WTest7://            }
                     if (hopPtr2 < endPtr2) goto begW7;

                     //while (hopPtr3 < endPtr3)
                     goto WTest8;
begW8://             {
                        *hopPtr1 = *hopPtr3;
                        ++hopPtr3;
                        ++hopPtr1;
WTest8://            }
                     if (hopPtr3 < endPtr3) goto begW8;

                     hopPtr1 = a1;
                     hopPtr2 = a2;
                     hopPtr3 = a3;
                     endPtr1 = a1 + used1;
                     used2 = 0;
                     used3 = 0;
                     //while (hopPtr1 < endPtr1)
                     goto WTest9;
begW9://             {
                        target = *hopPtr1;
                        //if (target < mean)
                        if (target >= mean) goto else10;
begI10://               {
                           *hopPtr2 = target;
                           ++used2;
                           ++hopPtr2;
                        goto endI10;
//                      }
else10://               else
//                      {
                           //if (target > mean)
                           if (target <= mean) goto endI11;
begI11://                  {
                              *hopPtr3 = target;
                              ++used3;
                              ++hopPtr3;
endI11://                  }
endI10://               }
                        ++hopPtr1;
WTest9://            }
                     if (hopPtr1 < endPtr1) goto begW9;

                     cout << procA1Str;
                     //if (used1 > 0)
                     if (used1 <= 0) goto endI12;
begI12://            {
                        hopPtr1 = a1;
                        endPtr1 = a1 + used1;
                        //do
begDW4://               {
                           cout << *hopPtr1 << ' ' << ' ';
                           ++hopPtr1;
DWTest4://               }
                        //while (hopPtr1 < endPtr1);
                        if (hopPtr1 < endPtr1) goto begDW4;
endI12://            }
                     cout << endl;

                     cout << commA2Str;
                     //if (used2 > 0)
                     if (used2 <= 0) goto endI13;
begI13://            {
                        hopPtr2 = a2;
                        endPtr2 = a2 + used2;
                        //do
begDW5://               {
                           cout << *hopPtr2 << ' ' << ' ';
                           ++hopPtr2;
DWTest5://               }
                        //while (hopPtr2 < endPtr2);
                        if (hopPtr2 < endPtr2) goto begDW5;
endI13://            }
                     cout << endl;

                     cout << commA3Str;
                     //if (used3 > 0)
                     if (used3 <= 0) goto endI14;
begI14://            {
                        hopPtr3 = a3;
                        endPtr3 = a3 + used3;
                        //do
begDW6://               {
                           cout << *hopPtr3 << ' ' << ' ';
                           ++hopPtr3;
DWTest6://               }
                        //while (hopPtr3 < endPtr3);
                        if (hopPtr3 < endPtr3) goto begDW6;
endI14://            }
                     cout << endl;
endI2://          }

                  cout << endl;
                  cout << dacStr;
                  cin >> reply;
                  cout << endl;
WTest1://      }
               ////if (reply != 'n' && reply != 'N') goto begW1;
               if (reply == 'n') goto xitW1;
               if (reply != 'N') goto begW1;
xitW1:
               cout << dlStr << '\n';
               cout << byeStr << '\n';
               cout << dlStr << '\n';

               return 0;
}

