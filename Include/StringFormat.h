#pragma once
#include <stdarg.h>
#include <assert.h>
#include <charstr.h>

namespace FLCL {
	//struct StringFormatter {
	//
	//	private:
	//
	//};


	//typedef char* va_list;
	//
	//
	//#define _ADDRESSOF(v) (&const_cast<char&>(reinterpret_cast<const volatile char&>(v)))
	//#define _INTSIZEOF(n)          ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))
	//
	//#define va_start(ap, v) ((void)(ap = (va_list)_ADDRESSOF(v) + _INTSIZEOF(v)))
	//#define va_arg(ap, t)     (*(t*)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)))
	//#define va_end(ap)        ((void)(ap = (va_list)0))


	// Our own custom string formatter. Should be made into som sort of class or something later on perhaps
	// to encapsulate the code a bit cleaner

	struct format_dest {
		Int32 Size;
		char *BufPos;
	};

	void OutChar(format_dest *Dest, char ch) {
		if (Dest->Size) {
			--Dest->Size;
			*Dest->BufPos++ = ch;
		}
	};

	void OutChar(format_dest *Dest, char *chars) {
		while (*chars)
			OutChar(Dest, *chars++);
	};

	// If IsWidthSpecified is set and width is 0, then the specified width was a *, otherwise it was an actual
	// width value
	struct format_params {
		Bool8 ForceSign = false;
		Bool8 PadWithZeros = false;
		Bool8 LeftJustify = false;
		Bool8 PositiveSignIsBlank = false;
		Bool8 AnnotateIfNotZero = false;
		Bool8 IsWidthSpecified = false;
		Int32 Width = 0;
		Bool8 IsPrecisionSpecified = false;
		Int32 Precision = 0;
	};

	Int64 ReadIntFromArgList(Int32 Length, va_list *ArgList) {

		Int64 res = 0;
		switch (Length) {
			case 1: {
				res = va_arg(*ArgList, Int8);
			} break;
			case 2: {
				res = va_arg(*ArgList, Int16);
			} break;
			case 4: {
				res = va_arg(*ArgList, Int32);
			} break;
			case 8: {
				res = va_arg(*ArgList, Int64);
			} break;
		}

		return res;

	};

	UInt64 ReadUnsignedIntFromArgList(UInt32 Length, va_list *ArgList) {

		UInt64 res = 0;
		switch (Length) {
			case 1:
			{
				res = va_arg(*ArgList, UInt8);
			} break;
			case 2:
			{
				res = va_arg(*ArgList, UInt16);
			} break;
			case 4:
			{
				res = va_arg(*ArgList, UInt32);
			} break;
			case 8:
			{
				res = va_arg(*ArgList, UInt64);
			} break;
		}
		return res;
	};

	//Int64 ReadSignedIntFromArgList(Int32 Length, va_list *ArgList) {
	//
	//	Int64 tempRes = ReadUnsignedIntFromArgList(Length, ArgList);
	//	Int64 res
	//
	//	return res;
	//};

	Float64 ReadFloatFromArgList(Int32 Length, va_list *ArgList) {

		Float64 res = 0;
		switch (Length) {
			case 4:
			{
				res = va_arg(*ArgList, Float32);
			} break;
			case 8:
			{
				res = va_arg(*ArgList, Float64);
			} break;
		}

		return res;

	};

	void IntToString(format_dest *Dest, UInt64 Value, UInt32 Base, const char *Digits) {
		assert(Base != 0);

		do {
			char digit = Digits[(Value % Base)];
			OutChar(Dest, digit);
			Value /= Base;

		} while (Value != 0);

	}

	Int32 FormatStringByList(Int32 DestBufferSize, char *DestBuffer, char *Format, va_list ArgList) {

		format_dest Dest{ DestBufferSize, DestBuffer };
		format_params Params;

		if (Dest.Size) {

			char *curPos = Format;
			while (curPos[0]) {
				if (curPos[0] == '%') {
					++curPos;

					// Parse flags
					Bool8 parsingFlags = true;
					while (parsingFlags) {
						switch (*curPos) {
							case '+': Params.ForceSign = true;  break;
							case '0': Params.PadWithZeros = true; break;
							case '-': Params.LeftJustify = true; break;
							case ' ': Params.PositiveSignIsBlank = true; break;
							case '#': Params.AnnotateIfNotZero = true; break;
							default:
								parsingFlags = false;
								break;
						}

						if (parsingFlags)
							++curPos;

					}

					// Parse width
					if (*curPos == '*') {
						ReadIntFromArgList(4, &ArgList);		// fetch the value from the stack anyways?
																//va_arg(ArgList, int);				// fetch the value from the stack anyways?
						Params.IsWidthSpecified = true;
						++curPos;
					}
					else if ((*curPos >= '0') && (*curPos <= '9')) {
						Params.Width = IntFromString(&curPos);
						Params.IsWidthSpecified = true;
					}

					// Parse the precision
					if (*curPos == '.') {
						++curPos;
						if (*curPos == '*') {
							va_arg(ArgList, int);			// fetch the value from the stack anyways?
							Params.IsPrecisionSpecified = true;
							++curPos;
						}
						else if ((*curPos >= '0') && (*curPos <= '9')) {
							Params.Precision = IntFromString(&curPos);
							Params.IsPrecisionSpecified = true;
						}
						else {
							assert(!"Malformed printf precision specifier");
						}
					}

					Int32 IntLength = 4;
					Int32 FloatLength = 8;

					// Parse the length
					if ((curPos[0] == 'h') && (curPos[1] == 'h')) {
						curPos += 2;
					}
					else if ((curPos[0] == 'l') && (curPos[1] == 'l')) {
						curPos += 2;
					}
					else if (*curPos == 'h') {
						++curPos;
					}
					else if (*curPos == 'l') {
						++curPos;
					}
					else if (*curPos == 'j') {
						++curPos;
					}
					else if (*curPos == 'z') {
						++curPos;
					}
					else if (*curPos == 't') {
						++curPos;
					}
					else if (*curPos == 'L') {
						++curPos;
					}


					char Temp[64];
					format_dest tmpDest = { 64, Temp };
					char *Prefix = "";

					// Parse the specifiers
					switch (*curPos) {
						case 'd':
						case 'i': {
							auto tmpVal = ReadIntFromArgList(IntLength, &ArgList);
							Bool8 IsNegative = (tmpVal < 0);
							if (IsNegative)
								tmpVal = -tmpVal;
							IntToString(&tmpDest, (UInt64)tmpVal, 10, DecChars);
							if (IsNegative)
								Prefix = "-";
							else if (Params.ForceSign)
								Prefix = "+";
							else if (Params.PositiveSignIsBlank)
								Prefix = " ";

						} break;
						case 'u': {
							auto tmpVal = ReadUnsignedIntFromArgList(IntLength, &ArgList);
							IntToString(&tmpDest, (UInt64)tmpVal, 10, DecChars);
						} break;
						case 'o': {
							auto tmpVal = ReadUnsignedIntFromArgList(IntLength, &ArgList);
							IntToString(&tmpDest, (UInt64)tmpVal, 8, DecChars);
							if (Params.AnnotateIfNotZero)
								Prefix = "o";
						} break;
						case 'x': {
							auto tmpVal = ReadUnsignedIntFromArgList(IntLength, &ArgList);
							IntToString(&tmpDest, (UInt64)tmpVal, 16, LowerHexChars);
							if (Params.AnnotateIfNotZero)
								Prefix = "0x";
						} break;
						case 'X': {
							auto tmpVal = ReadUnsignedIntFromArgList(IntLength, &ArgList);
							IntToString(&tmpDest, (UInt64)tmpVal, 16, UpperHexChars);
							if (Params.AnnotateIfNotZero)
								Prefix = "0X";
						} break;
						case 'f': {
							auto tmpVal = ReadFloatFromArgList(FloatLength, &ArgList);
						} break;
						case 'F': {
							auto tmpVal = ReadFloatFromArgList(FloatLength, &ArgList);
						} break;
						case 'e': {
							auto tmpVal = ReadFloatFromArgList(FloatLength, &ArgList);
						} break;
						case 'E': {
							auto tmpVal = ReadFloatFromArgList(FloatLength, &ArgList);
						} break;
						case 'g': {
							auto tmpVal = ReadFloatFromArgList(FloatLength, &ArgList);
						} break;
						case 'G': {
							auto tmpVal = ReadFloatFromArgList(FloatLength, &ArgList);
						} break;
						case 'a': {
							auto tmpVal = ReadFloatFromArgList(FloatLength, &ArgList);
						} break;
						case 'A': {
							auto tmpVal = ReadFloatFromArgList(FloatLength, &ArgList);
						} break;
						case 'c': {
							// Handle both wchar and char here perhaps??
							auto tmpVal = va_arg(ArgList, int);
							OutChar(&tmpDest, (char)tmpVal);
						} break;
						case 's': {
							char *tmpString = va_arg(ArgList, char *);
							//for(char *src = tmpString; *src; ++src)
							//OutChar(&Dest, *src);
							while (*tmpString != '\0')			// Is this better than the above for loop? Something to ponder about. For vs while
								OutChar(&Dest, *tmpString++);
						} break;
						case 'p': {
							auto tmpVal = va_arg(ArgList, void *);	// We might need to cast this
							IntToString(&tmpDest, *(umm *)&tmpVal, 16, LowerHexChars);
						} break;
						case 'n': {
							auto tmpVal = va_arg(ArgList, int*);
							*tmpVal = (Int32)(Dest.BufPos - DestBuffer);
						} break;
						case '%': {
							OutChar(&Dest, '%');
						} break;
						default: { assert("Unrecognized format specifier"); } break;
					}

					for (char *tmpCh = Prefix; *tmpCh; ++tmpCh)
						OutChar(&Dest, *tmpCh);

					// Write the temporary buffer back in reverse order since its parsed that way.
					while (tmpDest.BufPos != Temp) {
						--tmpDest.BufPos;
						OutChar(&Dest, *tmpDest.BufPos);
					}

					if (*curPos)
						++curPos;

				}
				else {
					OutChar(&Dest, *curPos++);
				}
			}

			if (Dest.Size) {
				Dest.BufPos[0] = 0;
				//Dest.At = '\0';
			}
			else {
				Dest.BufPos[-1] = 0;
				//Dest.At[-1] = '\0';
			}
		}

		return (Dest.BufPos - DestBuffer);	// Returns the size of it all

	}

	Int32 FormatString(Int32 DestSize, char *Dest, char *Format, ...) {
		va_list ArgList;

		va_start(ArgList, Format);
		Int32 res = FormatStringByList(DestSize, Dest, Format, ArgList);
		va_end(ArgList);

		return res;

	}
};
