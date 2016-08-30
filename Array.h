#pragma once

template<typename T> class Array
{
private: T* _tPtr;
private: size_t _length;
private: bool _isOwner;

public: Array(size_t length, bool isOwner = true)
           : _isOwner(isOwner)
        {
           _length = length;
           _tPtr = new T[length]; 
        }

public: Array(T* tPtr, size_t numItems, bool isOwner = true)
           : _isOwner(isOwner)
        {
           if (NULL == tPtr)
           {
              throw std::exception("Specified T* pointer is NULL.");
           }

           this->_length = numItems;
           this->_tPtr = tPtr;
        }

public: template<typename TSTLContainerType>
        Array(const TSTLContainerType& stlContainer, bool isOwner) : _isOwner(isOwner)
        {
           _length = stlContainer.size();
           _tPtr = new T[_length];

           int index = 0;
           for (TSTLContainerType::const_iterator iter = stlContainer.begin();
              iter != stlContainer.end();
              ++iter, ++index)
           {
              _tPtr[index] = *iter;
           }
        }

public: ~Array()
        {
           if (IsOwner())
           {
              delete _tPtr;
           }
        }

public: T& operator[](size_t index) const
        {
           return GetItem(index);
        }

public: T& operator[](int index) const
        {
           return GetItem(static_cast<size_t>(index));
        }

        // Gets a copy of the value at the specified index
public: T GetValue(size_t index)
        {
           return GetItem(index);
        }

public: operator T* const() const
        {
           return _tPtr;
        }

public: T* const Get() const
        {
           return _tPtr;
        }

public: operator const T* const()
        {
           return _tPtr;
        }

public: int Length() const
        {
           return static_cast<int>(this->_length);
        }

public: int Size() const
        {
           return _length * typeof(T);
        }

public: bool IsOwner() const
        {
           return this->_isOwner;
        }

public: void CopyTo(T* tPtr, size_t copySize)
        {
           memcpy(tPtr, this->_tPtr, copySize);
        }

        // Gets a reference to the item (T) at the specified index
private: T& GetItem(size_t index) const
         {
            const size_t length = static_cast<size_t>(Length());
            if  (index > length)
            {
               throw std::exception("Index out of bounds");
            }

            return _tPtr[index];
         }
};
