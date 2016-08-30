// A C++ stream formatter base class for dynamic construction\logging of messages

#pragma once

#include <string>
#include <deque>
#include <map>
#include <sstream>

struct InsertionInfo
{
    std::string Value;
    bool Used;

    InsertionInfo() : Value(""), Used(false)
    {
    }

    InsertionInfo(const std::string& paramValue) : Value(paramValue), Used(false)
    {
    }
};

template<typename T>
class StreamFormatter
{
private: static const char PlaceHolderChar = '%';

         typedef std::deque<InsertionInfo> InsertionInfoSequence;
         typedef InsertionInfoSequence::iterator InsertionInfoSequenceIter;
         typedef InsertionInfoSequence::const_iterator InsertionInfoSequenceConstIter;

private: std::string _formatSpec;
private: InsertionInfoSequence _paramValues;

public: StreamFormatter(const std::string& fmtSpec) : _formatSpec(fmtSpec)
        {
        }

public: ~StreamFormatter()
        {
            try
            {
                const std::string streamText = PrepareStream();
                Flush(streamText);
            }
            catch(...)
            {
                _ASSERTE(0);
            }
        }

public: template<typename TInput> StreamFormatter<T>& operator <<(const TInput& tObj)
        {
            std::ostringstream ostr;
            ostr << tObj;
            _paramValues.push_back(InsertionInfo(ostr.str()));
            return *this;
        }

protected: std::string StreamFormatter<T>::PrepareStream(const std::string& noMatchDelimiter = "")
           {
               size_t placeHolderIndex = 0;
               size_t scanStartIndex = 0;

               std::ostringstream ostr;

               placeHolderIndex = _formatSpec.find(PlaceHolderChar, placeHolderIndex);
               if (std::string::npos == placeHolderIndex)
               {
                   ostr << _formatSpec;
                   UpdateStream(ostr, noMatchDelimiter);

                   return ostr.str();
               } 

               while(std::string::npos != placeHolderIndex)
               {
                   size_t tempPHI = placeHolderIndex + 1;
                   while(tempPHI < _formatSpec.length() && isdigit(_formatSpec[tempPHI++]));
                   --tempPHI;

                   const size_t numberLength = tempPHI - placeHolderIndex - 1;
                   if (0 == numberLength || numberLength > 3)
                   {
                       placeHolderIndex = tempPHI;
                       placeHolderIndex = _formatSpec.find(PlaceHolderChar, tempPHI);
                       continue;
                   }

                   const std::string formatItemIndexString = _formatSpec.substr(placeHolderIndex + 1, numberLength);
                   const size_t formatItemIndex = atol(formatItemIndexString.c_str());

                   if (formatItemIndex >= 255 || formatItemIndex >= _paramValues.size())
                   {
                       // Found %'formatItemIndex' @ placeHolderIndex
                       placeHolderIndex = tempPHI;
                       placeHolderIndex = _formatSpec.find(PlaceHolderChar, tempPHI);
                       continue;
                   }

                   ostr << _formatSpec.substr(scanStartIndex, placeHolderIndex - scanStartIndex) << _paramValues[formatItemIndex].Value;
                   _paramValues[formatItemIndex].Used = true;
                   placeHolderIndex = tempPHI;
                   scanStartIndex = tempPHI;

                   placeHolderIndex = _formatSpec.find(PlaceHolderChar, scanStartIndex);
               }

               ostr << _formatSpec.substr(scanStartIndex, _formatSpec.length() - scanStartIndex);
               UpdateStream(ostr, noMatchDelimiter);

               return ostr.str();
           }

private: void StreamFormatter<T>::UpdateStream(std::ostringstream& ostr, const std::string& noMatchDelimiter)
         {
             for (InsertionInfoSequenceIter iter = _paramValues.begin(); iter != _paramValues.end(); ++iter)
             {
                 if (!(*iter).Used)
                 {
                     ostr << noMatchDelimiter << (*iter).Value;
                     (*iter).Used = true;
                 }
             }
         }

public: virtual void Flush(const std::string& streamText) { };

protected: StreamFormatter<T>(const StreamFormatter<T>&);
protected: StreamFormatter<T>& operator=(const StreamFormatter<T>&);

           friend class T;
};
