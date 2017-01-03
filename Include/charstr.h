#pragma once

namespace FLCL {

	/*
		Utility function for checking if the value is a whitespace character or not
	*/
	inline bool IsWhitespace(char chr) {

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
	inline bool IsAlpha(char chr) {

		if (((chr >= 'A') && (chr <= 'Z')) ||
			((chr >= 'a') && (chr <= 'z')))
		{
			return true;
		}
		else if (chr == 'å' ||
			chr == 'Å' ||
			chr == 'ä' ||
			chr == 'Ä' ||
			chr == 'ö' ||
			chr == 'Ö')
		{
			return true;
		}

		return false;
	}

	/*
		Utility function for checking if the value is a alphanumeric character or not.
		This version uses an array of defined characters to verify against.
	*/
	inline bool IsAlpha2(char c)
	{
		static const char chrs[] = "abcdefghijklmnopqrstuvwxyzåäöABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ";

		const char *curPtr = chrs;

		while (*curPtr++)
			if (*curPtr == c)
				return true;

		return false;

	}

	/*
		Utility function for checking if the value is a digit or not
	*/
	inline bool IsDigit(char chr) {
		return (chr >= '0') && (chr <= '9');
	}

	/*
		Utility function for turning a character to its uppercase equivalent
	*/
	inline char ToUpper(char chr) {
		if ((chr >= 'a') && (chr <= 'z'))
			chr += 'A' - 'a';
		else if (chr == 'ö')
			chr += 'Ö' - 'ö';
		else if (chr == 'ä')
			chr += 'Ä' - 'ä';
		else if (chr == 'å')
			chr += 'Å' - 'å';

		return chr;
	}

	/*
		Utility function for turning a character to its lowercase equivalent
	*/
	inline char ToLower(char chr) {
		if ((chr >= 'A') && (chr <= 'Z'))
			chr += 'a' - 'A';
		else if (chr == 'Ö')
			chr += 'ö' - 'Ö';
		else if (chr == 'Ä')
			chr += 'ä' - 'Ä';
		else if (chr == 'Å')
			chr += 'å' - 'Å';

		return chr;
	}

} // namespace FLCL