#pragma once

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Node {
private: T item;
private: Node<T>* next;

public: Node(const T& item) {
           this->item = item;
           this->next = nullptr;
        }

public: Node(const T& item, Node<T>* next) {
           this->item = item;
           this->next = next;
        }

public: T& Item() {
           return this->item;
        }

public: Node<T>*& Next() {
           return this->next;
        }
};

template<typename T>
class LinkedList
{
private: Node<T>* root;
private: Node<T>* end;
private: Node<T>* prevHead;

public: LinkedList()
        {
           root = end = prevHead = nullptr;
        }

public: Node<T>* Append(T item)
        {
           Node<T>* node = new Node<T>(item);
           if (root == nullptr)
           {
              root = end = node;
           }
           else
           {
              //_ASSERTE(end != nullptr);
              end->Next() = node;
              end = node;
           }

           return node;
        }

public: Node<T>* Root() const
        {
           return this->root;
        }

public: void Print(std::ostream& ostr = std::cout,
           const std::string& separator = " -> ",
           const std::string& terminator = "\r\n")
        {
           Node<T>* currentNode = root;

           while (currentNode != nullptr)
           {
              const bool lastNode = currentNode->Next() == nullptr;
              const std::string linkText = (lastNode ? "" : separator);
              ostr << currentNode->Item() << linkText.c_str();

              currentNode = currentNode->Next();
           }

           ostr << terminator.c_str();
        }

public: void Reverse()
        {
           Node<T>* current = this->root;
           Node<T>* prev = nullptr;
           Node<T>* next = nullptr;

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

private: Node<T>* ReverseList(Node<T>* current, Node<T>* next)
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

            Node<T>* nextNext = next->Next();
            next->Next() = current;

            if (nextNext == nullptr)
            {
               // cout << "Reached end of list!" << endl;
               return next;
            }

            return ReverseList(next, nextNext);
         }

private: Node<T>* _Reverse(Node<T>* head, int k)
         {
            int iter = k;

            Node<T>* current = head;
            Node<T>* prev = nullptr;
            Node<T>* next = nullptr;

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
};