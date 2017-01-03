#pragma once

namespace FLCL {

	/*
		Utility function for checking if the value is a whitespace character or not
	*/
	inline bool isWhitespace(char chr) {

		if (chr == ' ' || 
			chr == '\t' ||
			chr == '\n' ||
			chr == '\v' ||
			chr == '\f' ||
			chr == '\r')
		{
			return true;
		}

		return false;
	}

	/*
		Utility function for checking if the value is a alphanumeric character or not
	*/
	inline bool isAlpha(char chr) {

		if (((chr >= 'A') && (chr <= 'Z')) ||
			((chr >= 'a') && (chr <= 'z')))
		{
			return true;
		}
		else if (chr == '�' ||
			chr == '�' ||
			chr == '�' ||
			chr == '�' ||
			chr == '�' ||
			chr == '�')
		{
			return true;
		}

		return false;
	}

	/*
		Utility function for checking if the value is a alphanumeric character or not.
		This version uses an array of defined characters to verify against.
	*/
	inline bool isAlpha2(char c)
	{
		static const char chrs[] = "abcdefghijklmnopqrstuvwxyz���ABCDEFGHIJKLMNOPQRSTUVWXYZ���";

		const char *curPtr = chrs;

		while (*curPtr++)
			if (*curPtr == c)
				return true;

		return false;

	}

	/*
		Utility function for checking if the value is a digit or not
	*/
	inline bool isDigit(char chr) {
		return (chr >= '0') && (chr <= '9');
	}

	/*
		Utility function for turning a character to its uppercase equivalent
	*/
	inline char toUpper(char chr) {
		if ((chr >= 'a') && (chr <= 'z'))
			chr += 'A' - 'a';
		else if (chr == '�')
			chr += '�' - '�';
		else if (chr == '�')
			chr += '�' - '�';
		else if (chr == '�')
			chr += '�' - '�';

		return chr;
	}

	/*
		Utility function for turning a character to its lowercase equivalent
	*/
	inline char toLower(char chr) {
		if ((chr >= 'A') && (chr <= 'Z'))
			chr += 'a' - 'A';
		else if (chr == '�')
			chr += '�' - '�';
		else if (chr == '�')
			chr += '�' - '�';
		else if (chr == '�')
			chr += '�' - '�';

		return chr;
	}

} // namespace FLCL