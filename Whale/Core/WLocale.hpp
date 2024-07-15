//
// Created by admin on 2024/7/5.
//

#pragma once

#include "FTypeDef.hpp"
#include "WObject.hpp"

namespace Whale
{
	
	///
	/// 本地化
	class WHALE_API WLocale : public WObject
	{
	public:
		
		static std::string
		Between(const std::string &text, const std::string &to_encoding, const std::string &from_encoding);
		
		static std::wstring ToUTFString(const std::string &text, const std::string &from_encoding);
		
		static std::string UTFToString(const std::wstring &text, const std::string &to_encoding);

//		static constexpr void CharToWChar(const Char *from, WChar *to, SizeT to_size);
//
//		static constexpr void WCharToChar(const WChar *from, Char *to, SizeT to_size);
		
	};

//	constexpr void WLocale::CharToWChar(const Char *from, WChar *to, SizeT to_size)
//	{
//		if (!from || !to || !to_size)
//			return;
//
//		int n = 0;
//
//		for (int i = 0; from[i] != '\0' && n < to_size - 1;)
//		{
//			long char_size = ((
//								  (from[i] & 0xf8) == 0xf0
//							  ) ? 4 :     // 1st bits of 4-byte character (11110)
//							  ((from[i] & 0xf0) == 0xe0) ? 3 :    // 1st bits of 3-byte character (1110)
//							  ((from[i] & 0xe0) == 0xc0) ? 2 :    // 1st bits of 2-byte character (110)
//							  1
//			);                                 // 1st bits of 1-byte character (0)
//
//			// Checks for data integrity
//			for (int j = 1; j < char_size; j++)
//				if (from[i + j] == '\0' || (from[i + j] & 0xc0) != 0x80)
//					char_size = 1;
//
//			to[n] = 0;
//
//			long first_bits;
//
//			if ((from[i] & 0xf8) == 0xf0)
//				first_bits = 0x7;    // 11110xxx
//			else if ((from[i] & 0xf0) == 0xe0)
//				first_bits = 0xf;    // 1110xxxx
//			else if ((from[i] & 0xe0) == 0xc0)
//				first_bits = 0x1f;   // 110xxxxx
//			else if ((from[i] & 0x80) == 0x0)
//				first_bits = 0x7f;   // 0xxxxxx
//			else
//				first_bits = 0xff;   // xxxxxxx
//
//			to[n] |= from[i] & first_bits;
//
//			for (int j = 1; j < char_size; j++)
//			{
//				to[n] <<= 6;                    // Makes space for a new portion of data
//				to[n] |= (from[i + j] & 0x3f);  // Next byte: 10xxxxxx
//			}
//
//			i += char_size;
//			n++;
//		}
//
//		to[n] = L'\0';
//	}
//
//	constexpr void WLocale::WCharToChar(const WChar *from, Char *to, SizeT to_size)
//	{
//		if (!from || !to || !to_size)
//			return;
//
//		int n = 0;
//
//		for (int i = 0; from[i] != L'\0' && n < to_size - 1; i++)
//		{
//			int num_of_bytes = ((
//									(from[i] & 0x1f0000) != 0x0 && sizeof(wchar_t) > 2
//								) ? 4 :       // 17-21 bits
//								((from[i] & 0xf800) != 0x0) ? 3 :                               // 12-16 bits
//								((from[i] & 0x780) != 0x0) ? 2 :                                // 8-11 bits
//								1
//			);                                                             // 1-7 bits
//
//			long head_bits;
//			long head_data;
//
//			// Checks if there is enough size for encoding
//			if (i + num_of_bytes - 1 >= to_size)
//				num_of_bytes = 1;
//
//			if (num_of_bytes == 4)
//			{
//				// 11110xxx
//				head_bits = 0xf0;
//				head_data = 0x7;
//			}
//			else if (num_of_bytes == 3)
//			{
//				// 1110xxxx
//				head_bits = 0xe0;
//				head_data = 0xf;
//			}
//			else if (num_of_bytes == 2)
//			{
//				// 110xxxxx
//				head_bits = 0xc0;
//				head_data = 0x1f;
//			}
//			else if (num_of_bytes == 1)
//			{
//				// 0xxxxxx
//				head_bits = 0x0;
//				head_data = 0x7f;
//			}
//
//			int offset = 6 * (num_of_bytes - 1);
//
//			to[n] = 0;
//			to[n] |= head_bits;
//			to[n] |= ((from[i] >> offset) & head_data);
//
//			for (int j = 1; j < num_of_bytes; j++)
//			{
//				offset = 6 * (num_of_bytes - j - 1);
//
//				to[n + j] = 0;
//				to[n + j] |= 0x80;
//				to[n + j] |= ((from[i] >> offset) & 0x3f);
//			}
//
//			n += num_of_bytes;
//		}
//
//		to[n] = '\0';
//	}
	
} // Whale
