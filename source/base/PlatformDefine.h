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

typedef std::vector<char> BUFFER_DATA;

#define SAFE_DELETE(x) if (x) {delete x; x=nullptr;}
#define SAFE_DELETE_ARRAY(x) if (x) {delete[] x; x=nullptr;}
