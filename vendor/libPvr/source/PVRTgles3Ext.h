/*!****************************************************************************

 @file         OGLES3/PVRTgles3Ext.h
 @ingroup      API_OGLES3
 @copyright    Copyright (c) Imagination Technologies Limited.
 @brief        OpenGL ES 3.0 extensions

******************************************************************************/
#ifndef _PVRTgles3Ext_H_
#define _PVRTgles3Ext_H_

#include <GLES3/gl3.h>

/*!
 @addtogroup   API_OGLES3
 @{
*/

/****************************************************************************
** Build options
****************************************************************************/

#define GL_PVRTGLESEXT_VERSION 3

/**************************************************************************
****************************** GL EXTENSIONS ******************************
**************************************************************************/

/*!**************************************************************************
 @class         CPVRTgles3Ext
 @brief         A class for initialising and managing OGLES3 extensions
****************************************************************************/
class CPVRTgles3Ext
{
public:
	/*!***********************************************************************
	@brief		Initialises IMG extensions
	*************************************************************************/
	void LoadExtensions();

	/*!***********************************************************************
	@brief		Queries for support of an extension
	@param[in]	extension    Extension to query for
	@return		True if the extension is supported
	*************************************************************************/
	static bool IsGLExtensionSupported(const char * const extension);
};

/*! @} */

#endif /* _PVRTgles3Ext_H_ */

/*****************************************************************************
 End of file (PVRTgles3Ext.h)
*****************************************************************************/

