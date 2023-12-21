#ifndef TYPES_H 
#define TYPES_H

using int8 = char;
using uint8 = unsigned char;
using int16 = short;
using uint16 = unsigned short;
using int32 = int;
using uint32 = unsigned int;
using int64 = long long;
using uint64 = unsigned long long;

using float32 = float;
using float64 = double;

#define UINT8_MAX  0xff
#define UINT16_MAX 0xffff
#define UINT32_MAX 0xffffffff
#define UINT64_MAX 0xffffffffffffffff

#define INT8_MAX  0x7f
#define CHAR_MAX  INT8_MAX
#define INT16_MAX 0x7fff
#define INT32_MAX 0x7fffffff
#define INT64_MAX 0x7fffffffffffffff

#define INT8_MIN  0xff
#define INT16_MIN 0xffff
#define INT32_MIN 0xffffffff
#define INT64_MIN 0xffffffffffffffff
#endif