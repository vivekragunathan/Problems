#pragma once

#include <stdarg.h>

#include "Include.h"
#include "Convert.h"

class StringBuilder
{
private: std::basic_string<TCHAR> _fmtedString;


public: explicit StringBuilder()
        {
        }

public: StringBuilder(const TCHAR* pszFormat, ...)
        {
           TCHAR buf[1024];

           va_list marker;
           va_start(marker, pszFormat);

#ifdef UNICODE
           vswprintf_s(buf, pszFormat, marker);
#else
           vsprintf_s(buf, pszFormat, marker);
#endif

           _fmtedString = Convert::ToString(buf);
        }

public: operator std::basic_string<TCHAR>() const

        {
           return _fmtedString;
        }

public: operator const TCHAR*() const
        {
           return _fmtedString.c_str();
        }        


public: const TCHAR* ToString() const
        {
           return _fmtedString.c_str();
        }

public: void Append(const std::basic_string<TCHAR>& charStr)
        {
           _fmtedString.append(charStr);
        }


public: void AppendLine(const std::basic_string<TCHAR>& charStr = _TXT(""))
        {  
           _fmtedString.append(charStr);
           _fmtedString.append(NEW_LINE);
        }

        //
        //  Uncomment the following section when working on ATL\COM
        //
//public: CComBSTR ToBSTR() const
//        {
//           return _fmtedString.c_str();
//        }

//public: operator CComBSTR() const
//        {
//           return _fmtedString.c_str();
//        }

};
