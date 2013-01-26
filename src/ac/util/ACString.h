/// ACString.h
///
/// This header file includes various functions taht relat
/// to manipulating strings.
///
/// NOTE:
/// This is called ACString.h because if it were called
/// String.h a compiler may confuse it with the standard C header
/// file.
///
/// LAST UPDATED:
/// 22/11/12 9:31AM
///
/// PROGRAMMERS:
/// Miguel Martin
///
/// This software is provided 'as-is',
/// without any express or implied warrantly.
/// In no even will the authors be held
/// liable for any damages arising from
/// the use of this software.
///
///
///          AC - Anax Creations
/// Copyright (C) 2012. All rights reserved.
///

#ifndef __AC_ACSTRING_H__
#define __AC_ACSTRING_H__

#include <cstring>

#include <string>
#include <algorithm>
#include <sstream>

namespace ac
{
	namespace util
	{
		/// Erases whitespace in a string
		/// \param str The string you wish to erase the whitespace from
		/// \return A new string with no whitespace characters
		inline std::string EraseWhitespaceFromString(const std::string& str)
		{
			std::string temp = str;
			temp.erase(std::remove(temp.begin(), temp.end(), ' '), temp.end());
			return temp;
		}


		template <class UnaryOperator>
		std::string ConvertString(const std::string& str, UnaryOperator unaryOp)
		{
			std::string temp(str);
			std::transform(temp.begin(), temp.end(), temp.begin(), unaryOp);

			return temp;
		}


		std::string StringToUpper(const std::string& str)
		{
			return ConvertString(str, ::toupper);
		}

		/// Converts a string to lower case
		/// \param str The string you wish to convert
		/// \return The string passed in with lower case
		std::string StringToLower(const std::string& str)
		{
			return ConvertString(str, ::tolower);
		}


		/// Centers a string
		/// \param str The string you wish to center
		/// \param amountOfCharatersInALine The amount of characters in a line
		/// \param fillChar The character you wish to fill the line with
		/// \return The centered string
		std::string CenterString(const std::string& str, int amountOfCharactersInALine, char fillChar)
		{
			int halfStringSize = str.length() / 2;
			int amountOfFillCharactersRequired = (amountOfCharactersInALine / 2) - halfStringSize;

			std::string fillCharacter(amountOfFillCharactersRequired, fillChar);

			return fillCharacter + str + fillCharacter;
		}


		/// Converts a type from a string
		/// \param str The string you wish to convert from
		/// \return The converted variable
		template <typename T>
		T ConvertFromString(const std::string& str)
		{
			std::istringstream stream(str);
			T temp;
			stream >> temp;

			return temp;
		}


		/// Gets an Extension from a string.
		/// \param str The string you wish to get the extension from.
		/// \return The extension from the string you parsed in.
		template <typename Str>
		Str GetExtensionFromString(const Str& str)
		{
			std::string extension; // Holds the extension

			size_t sizeOfStringUntilExtension = 0;
			size_t sizeOfExtension = 0; // How many characters are in the extension

			for(size_t i = 0; i < str.size(); ++i)
			{
				if(str[i] == '.')
				{
					sizeOfStringUntilExtension = i + 1;
				}
			}

			sizeOfExtension = static_cast<int>(str.size() - sizeOfStringUntilExtension);

			extension = str.substr(str.size() - sizeOfExtension);
			return extension;
		}
	}
}


#endif // __AC_ACSTRING_H__