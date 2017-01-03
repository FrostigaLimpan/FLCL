#pragma once
//#include <stdint.h>
#include <Types.h>
#include <string>
#include <random>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace FLCL {
	namespace UUID {
		/*
		Generic struct for a UUID. This could be generated as any version of a UUID.

		It should also be possible to store the UUID as four data blocks instead of 2 as is now.

		2 blocks:
		Bits | Name
		64		data1
		64		data2

		4 blocks:
		Bits | Bytes | Name
		32		4		Data1
		16		2		Data2
		16		2		Data3
		64		8		Data4

		Both would end up giving the total of 128-bit.

		Default the hex numbers should be printed out in lowercase in its canonical format.
		There is an option to print in uppcase if wanted however.

		*/
		struct UUID {

			union {
				UInt64 data[2];

				struct {
					UInt64 data1;
					UInt64 data2;
				};

			};

			bool operator==(const UUID &other) const {
				return data[0] == other.data[0] && data[1] == other.data[1];
			};

			bool operator!=(const UUID &other) const {
				return !operator==(other);
			};

			inline std::string ToString(bool raw = false, bool uppercase = false) const {
				std::stringstream ss;
				if (!raw) ss << "{";
				if (uppercase)
					ss << std::hex << std::uppercase << std::setfill('0');
				else
					ss << std::hex << std::nouppercase << std::setfill('0');


				UInt32 first = (data[0] >> 32);
				UInt32 second = (data[0] & 0xFFFFFFFF);
				UInt32 third = (data[1] >> 32);
				UInt32 fourth = (data[1] & 0xFFFFFFFF);

				ss << std::setw(8) << (first) << '-';
				ss << std::setw(4) << (second >> 16) << '-';
				ss << std::setw(4) << (second & 0xFFFF) << '-';
				ss << std::setw(4) << (third >> 16) << '-';
				ss << std::setw(4) << (third & 0xFFFF);
				ss << std::setw(8) << fourth;
				if (!raw) ss << "}";

				return ss.str();
			};

			inline friend std::ostream &operator<<(std::ostream &out, const UUID &self) {
				out << self.ToString(false);
				return out;
			};

		};

		/*
		A version 4 UUID is defined as a random UUID (RFC4122). It is generated from random or pseudo-random numbers.
		According to the specification the version number (4 bits) should be set as well as two reserved bits. All
		other bits are random or pseudo-random.

		Version 4 UUID has the form of: xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx where x is any hexadecimal digit and y
		is one of 8,9,a or b.

		Ex: {a799c064-2329-4b22-8d20-1f8970b62376}

		*/
		UUID CreateUUID() {
			std::random_device rdev;
			std::uniform_int_distribution<UInt64> dist(0, (UInt64)(~0));

			UUID res = {};

			res.data[0] = dist(rdev);
			res.data[1] = dist(rdev);

			// This is for conformance with the specification for a version 4 UUID.
			res.data[0] = (res.data[0] & 0xFFFFFFFFFFFF0FFFULL) | 0x0000000000004000ULL;	// Make sure we set the version to 4
			res.data[1] = (res.data[1] & 0x3FFFFFFFFFFFFFFFULL) | 0x8000000000000000ULL;	// Make sure we set the reserved bits

			return res;
		}

		/*
		A NIL/Empty version of the UUID has all its values set to 0. This can also be accomplished by initializing the
		struct with {}.

		Ex: {00000000-0000-0000-0000-000000000000}
		*/
		UUID CreateEmptyUUID() {
			UUID res = {};

			return res;
		}

		/*
		Parses a UUID from a "raw" string. A raw atring does not contain the enclosing curly brackets
		Ex: a799c064-2329-4b22-8d20-1f8970b62376

		The canonical form is five groups (blocks) in the form: 8-4-4-4-12 for a total of
		36 chars (32 alphanumeric chars and four hypens).
		*/
		void ParseRawUUID(const std::string &str, UUID *uuid) {
			char tmpChar;
			UInt64 firstBlock;
			UInt64 secondBlock;
			UInt64 thirdBlock;
			UInt64 fourthBlock;
			UInt64 fifthBlock;

			std::stringstream ss(str);
			if (ss >> std::hex >> firstBlock >> tmpChar >> secondBlock >> tmpChar >> thirdBlock >> tmpChar >> fourthBlock >> tmpChar >> fifthBlock) {
				uuid->data[0] = (firstBlock << 32) | (secondBlock << 16) | thirdBlock;
				uuid->data[1] = (fourthBlock << 48) | fifthBlock;
			}
		}

		/*
		Parses a UUID from a string.
		Ex: {a799c064-2329-4b22-8d20-1f8970b62376}

		The canonical form is five groups (blocks) in the form: 8-4-4-4-12 for a total of
		36 chars (32 alphanumeric chars and four hypens).
		*/
		void ParseUUID(const std::string &str, UUID *uuid) {
			char tmpChar;
			UInt64 firstBlock;
			UInt64 secondBlock;
			UInt64 thirdBlock;
			UInt64 fourthBlock;
			UInt64 fifthBlock;

			std::stringstream ss(str);
			if (ss >> tmpChar >> std::hex >> firstBlock >> tmpChar >> secondBlock >> tmpChar >> thirdBlock >> tmpChar >> fourthBlock >> tmpChar >> fifthBlock >> tmpChar) {
				uuid->data[0] = (firstBlock << 32) | (secondBlock << 16) | thirdBlock;
				uuid->data[1] = (fourthBlock << 48) | fifthBlock;
			}
		}

		/*
		Parses and returns a UUID. Checks wheter the input is in "raw" format or normal string format.

		The canonical form is five groups (blocks) in the form: 8-4-4-4-12 for a total of
		36 chars (32 alphanumeric chars and four hypens).
		*/
		UUID ParseUUID(const std::string &str) {
			UUID res = {};

			if (str.c_str()[0] == '{')
				ParseUUID(str, &res);
			else
				ParseRawUUID(str, &res);

			return res;
		}
	} // End namespcae UUID
} // End namespace FLCL