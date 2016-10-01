#pragma once

#include <cstdint>
#include <cstddef>

// Defines
#define MOD_SHIFTKEY	0x0001
#define MOD_CONTROLKEY  0x0002
#define MOD_ALTKEY      0x0004
#define MOD_SUPERKEY	0x0008


namespace FLCL {

		using Int8 = std::int8_t;
		using Int16 = std::int16_t;
		using Int32 = std::int32_t;
		using Int64 = std::int64_t;

		using UInt8 = std::uint8_t;
		using UInt16 = std::uint16_t;
		using UInt32 = std::uint32_t;
		using UInt64 = std::uint64_t;

		using Float32 = float;
		using Float64 = double;

		using Size = std::size_t;
		using USize = std::size_t;

		using Bool8 = bool;
		using Bool32 = Int32;

		using IntPtr = std::intptr_t;
		using UIntPtr = std::uintptr_t;

} // namespace FLCL