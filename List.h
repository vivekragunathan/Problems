#pragma once

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class LinkedList
{

public: class Node
		{
		private: T item;
		private: Node* next;

		public: Node(const T& item)
				{
					this->item = item;
					this->next = nullptr;
				}

		public: Node(const T& item, Node* next)
				{
					this->item = item;
					this->next = next;
				}

		public: T& Item()
				{
					return this->item;
				}

		public: const T& Item() const
				{
					return this->item;
				}

		public: LinkedList<T>::Node*& Next()
				{
					return this->next;
				}
		};

private: LinkedList<T>::Node* root;
private: LinkedList<T>::Node* end;
private: LinkedList<T>::Node* prevHead;

public: LinkedList()
        {
           root = end = prevHead = nullptr;
        }

public: ~LinkedList()
		{
			// **********************************************************
			// TODO: Check if cyclic, else will keep deleting nodes!
			// **********************************************************

			// Delete all nodes
			auto current = root;
			while (current != nullptr)
			{
				auto temp = current->Next();
				delete current;
				current = temp;
			}
		}

public: Node* operator[](int index) const
		{
			return GetNthNode(index);
		}

public: LinkedList<T>::Node* GetNthNode(int index) const // index is zero-based.
		 {
			auto node = root;
			while (index >= 0 && node != nullptr)
			{
				node = node->Next();
				--index;
			}

			return node;
		 }

public: Node* Append(T item)
        {
           Node* node = new Node(item);
           if (root == nullptr)
           {
              root = end = node;
           }
           else
           {
              end->Next() = node;
              end = node;
           }

           return node;
        }

public: LinkedList<T>::Node* Root() const
        {
           return this->root;
        }

public: void Print(std::ostream& ostr = std::cout,
           const std::string& separator = " -> ",
           const std::string& terminator = "\r\n")
        {
           Node* currentNode = root;

           while (currentNode != nullptr)
           {
              const bool lastNode = currentNode->Next() == nullptr;
              const std::string linkText = (lastNode ? "" : separator);
              ostr << currentNode->Item() << linkText.c_str();

              currentNode = currentNode->Next();
           }

           ostr << terminator.c_str();
        }
        
public: bool IsCyclic2() const
        {
            int iterCount = 0;

            auto jmpBy1Ptr = root;
            auto jmpBy2Ptr = root->Next();

            while (jmpBy2Ptr != jmpBy1Ptr && jmpBy2Ptr != nullptr && jmpBy1Ptr != nullptr)
            {
               jmpBy1Ptr = jmpBy1Ptr->Next();

               auto temp = jmpBy2Ptr->Next();
               jmpBy2Ptr = ((temp == nullptr) ? nullptr : temp->Next());

               ++iterCount;
            }

            cout << "IsCyclic Iteration Count: " << iterCount << std::endl;

            return jmpBy2Ptr == jmpBy1Ptr;
        }

public: bool IsCyclic() const
        {   
            int iterCount = 0;

            auto jmpBy1Ptr = root;
            auto jmpBy2Ptr = root;

            while (jmpBy1Ptr != nullptr && jmpBy2Ptr != nullptr && jmpBy2Ptr->Next() != nullptr)
            {
            	jmpBy1Ptr = jmpBy1Ptr->Next();
            	jmpBy2Ptr = jmpBy2Ptr->Next()->Next();

            	if (jmpBy1Ptr == jmpBy2Ptr)
            	{
            		cout << "Stop node is " << jmpBy1Ptr->Item() << std::endl;
            		return true;
            	}

            	++iterCount;
            }

            return false;
        }

public: LinkedList<T>::Node* FindCyclicNode() const
		{
			int iterCount = 0;

			auto jmpBy1Ptr = root;
			auto jmpBy2Ptr = root;

			while (jmpBy1Ptr != nullptr && jmpBy2Ptr != nullptr && jmpBy2Ptr->Next() != nullptr)
			{
				jmpBy1Ptr = jmpBy1Ptr->Next();
				jmpBy2Ptr = jmpBy2Ptr->Next()->Next();

				if (jmpBy1Ptr == jmpBy2Ptr)
				{
					const int noOfNodesInLoop = CountNoOfNodesInLoop(jmpBy1Ptr);

					cout << "No of nodes in loop: " << noOfNodesInLoop << std::endl;

					auto p1= root;
					auto p2 = GetNthNode(noOfNodesInLoop - 1); // zero based index

					cout << "Node at index " << noOfNodesInLoop << ": " << p2->Item() << std::endl;

					// Pointers meet at loop starting node
					while (p1 != p2)
					{
						p1 = p1->Next();
						p2 = p2->Next();
					}

					p2 = p2->Next();
					while(p2->Next() != p1)
					{
						p2 = p2->Next();
					}

					return p2;
				}

				++iterCount;
			}

			return nullptr;
		}

public: void Reverse()
        {
           Node* current = this->root;
           Node* prev = nullptr;
           Node* next = nullptr;

           while (current != nullptr)
           {
              next = current->Next();
              current->Next() = prev;

              if (next == nullptr)
              {
                 break;
              }

              prev = current;
              current = next;
           }

           this->end = this->root;
           this->root = current;			
        }

public: void Reverse2()
        {
           root = ReverseList(root, nullptr);
        }

public: void Reverse(int k)
        {
           prevHead = nullptr;

           auto head = root;
           root = _Reverse(head, k);
           head = head->Next();

           while (head != nullptr)
           {
              _Reverse(head, k);
              
              /*auto next2Head = head->Next();
              if (next2Head == nullptr)
              {  
                 end = head;
              }

              head = next2Head;*/
              head = head->Next();
           }

           prevHead = nullptr;
        }

private: Node* ReverseList(Node* current, Node* next)
         {
            if (current == nullptr)
            {
               // cout << "Empty List!" << endl;
               return nullptr;
            }

            if (next == nullptr)
            {
               // cout << "next is nullptr"  << endl;
               next = current->Next();
               current->Next() = nullptr;
               end = current;
            }

            // cout << "Current: " << current->Item() << endl;
            // cout << "Next: " << next->Item() << endl;

            Node* nextNext = next->Next();
            next->Next() = current;

            if (nextNext == nullptr)
            {
               // cout << "Reached end of list!" << endl;
               return next;
            }

            return ReverseList(next, nextNext);
         }

private: Node* _Reverse(Node* head, int k)
         {
            int iter = k;

            Node* current = head;
            Node* prev = nullptr;
            Node* next = nullptr;

            while (current != nullptr && iter >= 1)
            {
               next = current->Next();
               current->Next() = prev;

               if (next == nullptr)
               {
                  break;
               }

               prev = current;
               current = next;
               --iter;
            }

            if (prevHead != nullptr)
            {
               prevHead->Next() = next != nullptr ? prev : current;
            }

            prevHead = head;
            head->Next() = next;

            return prev;
         }

private: int CountNoOfNodesInLoop(LinkedList<T>::Node* stopNode) const
		 {
			int count = 1;
			auto p1 = stopNode;
			auto p2 = stopNode;

			while (p1->Next() != p2)
			{
				p1 = p1->Next();
				++count;
			}

			return count;
		 }
};
