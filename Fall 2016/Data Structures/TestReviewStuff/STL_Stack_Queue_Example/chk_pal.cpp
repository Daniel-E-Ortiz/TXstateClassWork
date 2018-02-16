#include <iostream>
#include <cstdlib>
#include <stack>     // provides stack class template from STL
#include <queue>     // provides queue class template from STL
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
   create stack of chars s
   create queue of chars q
   while (there's still char to process)
      input char c
      if ( isalnum(c) )
         s.push( tolower(c) )
         q.push( tolower(c) )
   while ( ! s.empty() )
      if ( s.top() != q.front() )
         return false
      else
         s.pop()
         q.pop()
   return true
*/

bool chk_pal()
{
   stack<char> s;
   queue<char> q;
   char c;

   cout << "Enter sequence: ";
   while ( cin.peek() != '\n' )
   {
      c = cin.get();
      if ( isalnum(c) )
      {
         c = tolower(c);
         s.push(c);
         q.push(c);
      }
   }
   while ( ! s.empty() )
      if ( s.top() != q.front() )
         return false;
      else
      {
         s.pop();
         q.pop();
      }
   return true;
}
