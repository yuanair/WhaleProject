//
// Created by admin on 2024/7/5.
//

#include "FLocale.hpp"

// #include "boost/locale.hpp"

namespace Whale
{
	
	
	StringA FLocale::Between(const StringA &text, const StringA &toEncoding, const StringA &fromEncoding)
	{
		//return boost::locale::conv::between(text.CStr(), toEncoding.CStr(), fromEncoding.CStr()).c_str();
		return "!";
	}
	
	StringW FLocale::ToUTFString(const StringA &text, const StringA &fromEncoding)
	{
		//return boost::locale::conv::to_utf<CharW>(text.CStr(), fromEncoding.CStr()).c_str();
		return L"!";
	}
	
	StringA FLocale::UTFToString(const StringW &text, const StringA &toEncoding)
	{
		//return boost::locale::conv::from_utf(text.CStr(), toEncoding.CStr()).c_str();
		return "!";
	}
	
	Bool FLocale::IsEOF(int32 ch)
	{
		return ch == EOF || ch == WEOF;
	}
	
	Bool FLocale::IsSpace(int32 ch)
	{
		switch (ch)
		{
			case '\t':
			case '\n':
			case '\v':
			case '\f':
			case '\r':
			case ' ':
				return true;
			default:
				return false;
		}
	}
	
	Bool FLocale::IsSpaceIncludeNull(int32 ch)
	{
		return EOF == ch || WEOF == ch || '\0' == ch || IsSpace(ch);
	}
	
	Bool FLocale::IsNewLine(int32 ch)
	{
		return ch == '\n' || ch == '\r';
	}
	
	Bool FLocale::IsDigit(int32 ch)
	{
		return ch >= '0' && ch <= '9';
	}
	
	Bool FLocale::IsUpper(int32 ch)
	{
		return ch >= 'A' && ch <= 'Z';
	}
	
	Bool FLocale::IsLower(int32 ch)
	{
		return ch >= 'a' && ch <= 'z';
	}
	
	Bool FLocale::IsAlpha(int32 ch)
	{
		return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
	}
	
	Bool FLocale::IsXDigit(int32 ch)
	{
		return (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f');
	}
	
	Bool FLocale::IsADigit(int32 ch)
	{
		return (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
	}
	
	Bool FLocale::IsPunct(int32 ch)
	{
		return (ch >= '!' && ch <= '/') || (ch >= ':' && ch <= '@') || (ch >= '[' && ch <= '`') ||
		       (ch >= '{' && ch <= '~');
	}
	
	Bool FLocale::IsCtrl(int32 ch)
	{
		return (ch >= '\x00' && ch <= '\x1F') || ch == '\x7F';
	}
	
	int32 FLocale::Escape(int32 ch)
	{
		switch (ch)
		{
			case '0':
				return '\0';
			case '1':
				return '\1';
			case '2':
				return '\2';
			case '3':
				return '\3';
			case '4':
				return '\4';
			case '5':
				return '\5';
			case '6':
				return '\6';
			case '7':
			case 'a':
				return '\a';
			case 'b':
				return '\b';
			case 'f':
				return '\f';
			case 'n':
				return '\n';
			case 'r':
				return '\r';
			case 't':
				return '\t';
			case 'v':
				return '\v';
			default:
				return ch;
		}
	}
	
	int32 FLocale::Unescape(int32 ch)
	{
		switch (ch)
		{
			case '\0':
				return '0';
			case '\1':
				return '1';
			case '\2':
				return '2';
			case '\3':
				return '3';
			case '\4':
				return '4';
			case '\5':
				return '5';
			case '\6':
				return '6';
			case '\a': // '\7'
				return 'a';
			case '\b':
				return 'b';
			case '\f':
				return 'f';
			case '\n':
				return 'n';
			case '\r':
				return 'r';
			case '\t':
				return 't';
			case '\v':
				return 'v';
			default:
				return ch;
		}
	}
	
	
} // Whale