#pragma once

#include <Types.h>
#include <cstdlib>
#include <utility>

namespace FLCL {

	//This should work
	inline Bool8 IsStringEqual(char *first, char *second) {
		Bool8 res = (first == second);

		char* curPosFirst = first;
		char* curPosSecond = second;

		if (curPosFirst && curPosSecond) {
			while (*curPosFirst && *curPosSecond && (*curPosFirst == *curPosSecond)) {
				++curPosFirst;
				++curPosSecond;
			}
			res = ((*curPosFirst == 0) && (*curPosSecond == 0));
		};

		return res;
	};

	// Does this really work??
	inline Bool8 IsStringEqual(umm firstLength, char *first, char *second) {

		Bool8 res = false;

		if (second) {
			char *At = second;
			for (umm Index = 0; Index < firstLength; ++Index, ++first) {
				if ((*At == 0) || (first[Index] != *At))
					return false;
			}
			res = (*At == 0);
		}
		else {
			res = (firstLength == 0);
		}

		return res;

	}

	// This seems to work.
	inline Bool8 IsStringEqual(memory_index firstLength, char *first, memory_index secondLength, char *second) {
		Bool8 res = (firstLength == secondLength);

		if (res) {
			res = true;
			for (Int32 Index = 0; Index < firstLength; ++Index) {
				if (first[Index] != second[Index]) {
					return false;
					//res = false;
					//break;
				}
			}
		}

		return res;

	}

	/*
		Utility function to see if the current char is a eol char
	*/
	inline Bool8 IsEndOfLine(char chr) {
		return ((chr == '\n') ||
			(chr == '\r'));
	};

	/*
		Utility function that parses a string to an int
	*/
	inline Int32 IntFromString(char *string) {
		Int32 res = 0;

		char* curPos = string;

		while ((*curPos >= '0') && (*curPos <= '9')) {
			res *= 10;
			res += (*curPos - '0');
			++curPos;
		}

		return res;

	}

	/*
		Parses an int from a string but also advances the string pointer forward in the string for as many
		chars that are read in and parsed as an int. This is useful if you want to call this from a custom 
		parse function for instance.
	*/
	inline Int32 IntFromString(char **stringPtr) {
		Int32 res = 0;

		char* curPos = *stringPtr;

		while ((*curPos >= '0') && (*curPos <= '9')) {
			res *= 10;
			res += (*curPos - '0');
			++curPos;
		}

		*stringPtr = curPos;

		return res;
	}

	/*
		Utility function for checking if the value is a whitespace character or not
	*/
	inline Bool8 IsWhitespace(char chr) {
		return ((chr == ' ') ||
			(chr == '\t') ||
			(chr == '\v') ||
			(chr == '\f') ||
			IsEndOfLine(chr));
	}

	/*
		Utility function for checking if the value is a alphanumeric character or not
	*/
	inline Bool8 IsAlpha(char chr) {

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
		This version uses an array of defined characters to verify against. This is useful 
		if you want to remove certain characters to be valid for instance.
	*/
	inline Bool8 IsAlpha2(char chr)
	{
		const char *curPtr = Chrs;

		while (*curPtr++)
			if (*curPtr == chr)
				return true;

		return false;

	}

	/*
		Utility function for checking if the value is a digit or not
	*/
	inline Bool8 IsDigit(char chr) {
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

	/*
		Reverses a string inplace
	*/
	inline void ReverseString(char *str) {
		char *tmpPtr = str;
		while (tmpPtr[0] != 0) tmpPtr++;

		for (int iCount = 0, iEnd = ((tmpPtr - str) / 2); iCount < iEnd; iCount++) {
			tmpPtr--;
			char tmpChar = tmpPtr[0];
			tmpPtr[0] = str[iCount];
			str[iCount] = tmpChar;
		}

	}

	/*
		Give a string representaion of a integer value
	*/
	inline void IntToString(char *Dest, UInt64 Value, UInt32 Base = 10) {

		char *tmpPtr = Dest;

		// Find the char that the digit correspond to and put it in the string
		do {
			char digit = DecChars[(Value % Base)];
			tmpPtr[0] = digit;
			tmpPtr++;
			Value /= Base;
		} while (Value != 0);
		tmpPtr[0] = '\0';

		// The string is in the wrong order after the digits is put in. Reverse it.
		for (int iCount = 0; iCount < ((tmpPtr - Dest) / 2); iCount++) {
			tmpPtr--;
			char tmpChar = tmpPtr[0];
			tmpPtr[0] = Dest[iCount];
			Dest[iCount] = tmpChar;
		}

	}


} // namespace FLCL