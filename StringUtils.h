#pragma once

class StringUtils
{
        // Trims the characters specified in trimChars at the start of inString
public: static std::string TrimStart(const std::string& inString,
           const std::string& trimChars = " \t")
        {
           if (inString.empty())
           {
              return inString;
           }

           size_t posLeft = inString.find_first_not_of(trimChars, 0);
           return inString.substr(posLeft, inString.length() - posLeft);
        }

        // Trims the characters specified in trimChars at the end of inString
public: static std::string TrimEnd(const std::string& inString,
           const std::string& trimChars = " \t")
        {
           if (inString.empty())
           {
              return inString;
           }

           size_t posRight = inString.find_last_not_of(trimChars);
           return inString.substr(0, posRight + 1);
        }

        // Trims the characters specified in trimChars at the start and end of inString
public: static std::string Trim(const std::string& inString,
           const std::string& trimChars = " \t")
        {
           if (inString.empty())
           {
              return inString;
           }

           size_t posLeft = inString.find_first_not_of(trimChars, 0);
           size_t posRight = inString.find_last_not_of(trimChars);

           return inString.substr(posLeft, posRight - posLeft + 1);
        }
};

template <template<typename, typename> class TStlContainer, typename TElementType>
static std::string ToString(TStlContainer<TElementType, std::allocator<TElementType>> stlContainer,
   const std::string& delimiter = ", ")
{
   std::ostringstream ostr;

   std::copy(stlContainer.begin(),
      stlContainer.end(),
      std::ostream_iterator<TElementType>(ostr, delimiter.c_str()));

   std::string fmtText = ostr.str();
   std::string::size_type index = fmtText.rfind(delimiter);      
   fmtText.erase(index, delimiter.length());

   return fmtText;
}

template <template<typename, typename> class TStlContainer, typename TElementType>
static std::string ToString(TStlContainer<TElementType, std::allocator<TElementType>> stlContainer,
   std::pointer_to_unary_function<TElementType, std::string> itemFunctor,
   const std::string& delimiter = ", ",
   bool insertDelimiterAtFirst = false,
   bool insertDelimiterAtLast = false)
{
   typedef typename TStlContainer<TElementType, std::allocator<TElementType>> StlContainer;
   typedef StlContainer::const_iterator StlContainterConstIter; 

   std::ostringstream ostr;

   for (StlContainterConstIter iter = stlContainer.begin(); iter != stlContainer.end(); ++iter)
   {
      if (iter == stlContainer.begin() && insertDelimiterAtFirst)
      {
         ostr << delimiter;
      }

      std::string iterText = itemFunctor(*iter);
      ostr << iterText << delimiter;
   }

   if (insertDelimiterAtLast)
   {
      return ostr.str();
   }

   // Remove the delimiter at the end and return text
   std::string fmtText = ostr.str();
   std::string::size_type index = fmtText.rfind(delimiter);      
   fmtText.erase(index, delimiter.length());
   return fmtText;
}
