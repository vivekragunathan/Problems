#pragma once

#include <sstream>
#include <fstream>
#include <iostream>
#include <string>

#ifdef UNICODE
typedef wchar_t TCHAR;
#define _TXT(text) L##text
static const TCHAR* NEW_LINE = L"\r\n";
#else
typedef char TCHAR;
#define _TXT(text) text
static const TCHAR* NEW_LINE = "\r\n";
#endif

typedef std::basic_string<TCHAR> String;

typedef std::basic_ostream<TCHAR> OStream;
typedef std::basic_ostream<char> AOStream;
typedef std::basic_ostream<wchar_t> WOStream;

typedef std::basic_ostringstream<TCHAR> OStringStream;
typedef std::basic_ostringstream<char> AOStringStream;
typedef std::basic_ostringstream<wchar_t> WOStringStream;

typedef std::basic_istream<TCHAR> InputStream;
typedef std::basic_istream<char> InputStreamA;
typedef std::basic_istream<wchar_t> InputStreamW;

typedef std::basic_istringstream<TCHAR> IStringStream;
typedef std::basic_istringstream<char> AIStringStream;
typedef std::basic_istringstream<wchar_t> WIStringStream;

typedef std::basic_stringbuf<TCHAR> StringBuf;

struct Console
{
public: static InputStream& In()
        {
#ifdef UNICODE
           return std::wcin;
#else
           return std::cin;
#endif
        }

public: static OStream& Out()
        {
#ifdef UNICODE
           return std::wcout;
#else
           return std::cout;
#endif
        }

public: static OStream& Error()
        {
#ifdef UNICODE
           return std::wcerr;
#else
           return std::cerr;
#endif
        }

public: static void Write(const String& str)
        {
           Out() << str;
        }

public: static void WriteLine(const String& str)
        {
           Out() << str << NEW_LINE;
        }
};
