#include <iostream>
#include <cstdlib>
//#include <stack>     // provides stack class template from STL
//#include <queue>     // provides queue class template from STL
//
using namespace std;

bool chk_pal();

int main()
{
   char reply;
   bool result;

   do
   {
      result = chk_pal();
      if (result)
         cout << "it's a palindrome" << endl;
      else
         cout << "it's not a palindrome" << endl;

      cout << "Do another? (n = no, any other = yes) ";
      cin >> reply;
      cin.ignore(9999, '\n');
   }
   while (reply != 'n');

   return EXIT_SUCCESS;
}

/* (pseudocode)
Function to check if given sequence of chars is palindrome:
   //create stack of chars s
   //create queue of chars q
   init capacity (size of array of chars) to 10
   init used (size of "relevant chars so far") to 0
   create dynamic array of chars
   //
   while (there's still char to process)
      input char c
      if ( isalnum(c) )
         //s.push( tolower(c) )
         //q.push( tolower(c) )
         if (array of chars is full)
            increase capacity by ~50%
         append c to "relevant chars so far" & increment used
         //
   //while ( ! s.empty() )
   //   if ( s.top() != q.front() )
   //      return false
   //   else
   //      s.pop()
   //      q.pop()
   //return true
   init forward tracing index i to 0 (point @ first relevant char)
   init backward tracing index j to used - 1 (point @ last relevant char)
   while (forward index is still behind backward index)
      if (relevant char @ forward index != relevant char @ backward index)
         break
      increment forward index
      decrement backward index
   free array of chars
   if (forward index is no longer behind backward index)
      return true
   else
      return false
   //
*/

bool chk_pal()
{
   //stack<char> s;
   //queue<char> q;
   int capacity = 10, used = 0;
   char* alnumChars = new char [capacity];
   //
   char c;

   cout << "Enter sequence: ";
   while ( cin.peek() != '\n' )
   {
      c = cin.get();
      if ( isalnum(c) )
      {
         c = tolower(c);
         //s.push(c);
         //q.push(c);
         if (used == capacity)
         {
            capacity = 1.5*capacity + 1;
            char* largerCharArr = new char [capacity];
            for (int i = 0; i < used; ++i)
               largerCharArr[i] = alnumChars[i];
            delete [] alnumChars;
            alnumChars = largerCharArr;
         }
         alnumChars[used++] = c;
         //
      }
   }
   //while ( ! s.empty() )
   //   if ( s.top() != q.front() )
   //      return false;
   //   else
   //   {
   //      s.pop();
   //      q.pop();
   //   }
   //return true;
   int i = 0, j = used - 1;
   while (i < j)
   {
      if (alnumChars[i] != alnumChars[j])
         break;
      ++i;
      --j;
   }
   delete [] alnumChars;
   alnumChars = 0;
   return (i >= j) ? true : false;
   //
}

