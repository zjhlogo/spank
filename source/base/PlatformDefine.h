/*!
 * \file PlatformDefine.h
 *
 * \author zjhlogo
 * \date 2014/10/12
 *
 * 
 */
#pragma once

#include <vector>
#include <string>
#include <cstdint>

typedef int8_t      int8;
typedef uint8_t     uint8;
typedef int16_t     int16;
typedef uint16_t    uint16;
typedef int32_t     int32;
typedef uint32_t    uint32;
typedef int64_t     int64;
typedef uint64_t    uint64;

typedef unsigned int uint;

typedef std::vector<int8> BUFFER_DATA;

#define SAFE_DELETE(x) if (x) {delete x; x=nullptr;}
#define SAFE_DELETE_ARRAY(x) if (x) {delete[] x; x=nullptr;}
