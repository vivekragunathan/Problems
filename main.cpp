// Reverse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "List.h"

using namespace std;

template<int n>
class Factorial
{
public: enum { value = n * Factorial<n - 1>::value};
};

template<>
class Factorial<0>
{
public: enum { value = 1 };
};

void GetInput()
{
   /*int input;
   LinkedList<int> ll;

   do
   {
      cout << "Input: ";
      cin >> input;

      if (input < 0)
      {
         break;
      }

      ll.Append(input);
   } while (input >= 0);*/
}

void WaitForKey(const std::string& msg)
{
   cout << msg.c_str() << endl;
   cin.get();
}

int _tmain(int argc, _TCHAR* argv[])
{
   const int x = Factorial<5>::value;

   LinkedList<int> ll;

   for (int index = 1; index <= 122; ++index)
   {
      ll.Append(index);
   }

   cout << "Printing the input sequence......................" << endl;
   ll.Print(cout);

   cout << "Reverse K nodes.................................." << endl;
   ll.Reverse(3);
   ll.Print();
   
   WaitForKey("Press any key to reverse the list (iterative) .....................");
   ll.Reverse2();
   ll.Print();
   
   WaitForKey("Press any key to reverse the list (recursive) .....................");
   ll.Reverse();
   ll.Print();

   return 0;
}