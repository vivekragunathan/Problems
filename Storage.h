#pragma once

//#include <sys/time.h>
#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T, size_t L>
class Storage
{
private: class Node
		 {
		 public: T Value;
		 public: unsigned long Timestamp;
		 };

private: Node nodes[L];
private: Node resetNode;

public: Storage()
		{
			this->resetNode.Timestamp = 0;
		}

public: T Get(int index) const
		{
			if (static_cast<unsigned long>(index) < L)
			{
				const long timeDiff = resetNode.Timestamp - nodes[index].Timestamp;
				return timeDiff == 0 ? nodes[index].Value : resetNode.Value;
			}

			throw std::out_of_range("Index out of bounds!");
		}

public: void Set(int index, T value)
		{
			if (static_cast<unsigned long>(index) >= L)
			{
				throw std::out_of_range("Index out of bounds!");
			}

			this->nodes[index].Value = value;
			this->nodes[index].Timestamp = this->resetNode.Timestamp;
			cout << "Set(Value: " << this->nodes[index].Value << ", " << "TimeStamp: " << this->nodes[index].Timestamp << ");" << std::endl;
		}

public: void Reset(T value)
		{
			this->resetNode.Value = value;
			++this->resetNode.Timestamp;
			cout << "Reset(Value: " << this->resetNode.Value << ", " << "TimeStamp: " << this->resetNode.Timestamp << ");" << std::endl;
		}

public: int Length() const
		{
			return static_cast<int>(L);
		}

//private: static unsigned long GetTicks()
//		 {
//			struct timeval tv;
//			gettimeofday(&tv, NULL);
//			const double seconds = tv.tv_sec * 1000000.0 + tv.tv_usec;
//			return static_cast<unsigned long>(10);
//		 }

// Non-copyable
private: Storage(const Storage& other);
private: Storage& operator=(const Storage& rhs);
};

template<typename T, size_t L>
void PrintValue(Storage<T, L>& buffer, int index)
{
	const T value = buffer.Get(index);
	cout << "Value @ " << index << ": " << value << std::endl;
}

template<typename T, size_t L>
void PrintBuffer(Storage<T, L>& buffer)
{
	for (int index = 0; index < buffer.Length(); ++index)
	{
		PrintValue(buffer, index);
	}
}

void TestStorage()
{
	Storage<int, 10> buffer;

	for (int index = 0; index < buffer.Length(); ++index)
	{
		buffer.Set(index, index * 10);
	}

	buffer.Set(9, 100);
	PrintValue(buffer, 9);

	buffer.Reset(1);

	PrintBuffer(buffer);

	buffer.Set(2, 123);

	PrintBuffer(buffer);
}

/*
#include <sys/timeb.h>

int GetMilliCount()
{
  // Something like GetTickCount but portable
  // It rolls over every ~ 12.1 days (0x100000/24/60/60)
  // Use GetMilliSpan to correct for rollover
  timeb tb;
  ftime( &tb );
  int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
  return nCount;
}
*/
