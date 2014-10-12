/*!
 * \file MacroDefine.h
 * \date 10-11-2014 15:22:34
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#pragma once

#define SAFE_DELETE(x) if (x) {delete x; x=nullptr;}
#define SAFE_DELETE_ARRAY(x) if (x) {delete[] x; x=nullptr;}
