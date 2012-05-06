#include <iostream>
#include "List.h"

using namespace std;

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

void TestListCyclic()
{
	LinkedList<int> ll;
	LinkedList<int>::Node* lastNode = nullptr;

	for (int index = 1; index <= 10; ++index)
	{
		lastNode = ll.Append(index);
	}

	/*auto cycledNode = ll.Root()->Next()->Next()->Next();
	cout << "Cycled Node: " << cycledNode->Item() << std::endl;

	lastNode->Next() = cycledNode;*/

	cout << "IsCyclic: " << ll.IsCyclic() << std::endl;

	auto cyclicNode = ll.FindCyclicNode();
	cout << "Cyclic Node: " << (cyclicNode == nullptr ? -999 : cyclicNode->Item()) << std::endl;
}

void TestListReverse()
{
   LinkedList<int> ll;
    
   for (int index = 1; index <= 10; ++index)
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
}
