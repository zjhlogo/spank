
// (C) ATI Research, Inc. 2006 All rights reserved. 
// Not sure what we want as for a public header to this file

#ifndef __gl2atiext_h_
#define __gl2atiext_h_

#ifdef __cplusplus
extern "C" {
#endif

/* ATI_3Dc */
#define GL_3Dc_X_ATI                               0x87F9
#define GL_3Dc_XY_ATI                              0x87FA

/* ATI_texture_compression_atitc */
#define GL_COMPRESSED_RGB_ATI_TC                   0x8C92
#define GL_COMPRESSED_RGBA_ATI_TC                  0x8C93

/* ATI_data_type_10_10_10_2 */
#define GL_UNSIGNED_INT_10_10_10_2_OES             0x8036
#define GL_UNSIGNED_INT_10_10_10_OES               0x6003   // TEMP
#define GL_INT_10_10_10_2_OES                      0x6004   // TEMP

/* OES_depth_texture */
#define GL_UNSIGNED_INT_24_OES                     0x6005   // TEMP

#ifdef RM_ETC3_ETC5
/* Ericsson_ETC3_ETC5_compressed_texture */
#define GL_ETC3_RGBA8_Ericsson                     0x6007   // TEMP
#define GL_ETC5_RGBA8_Ericsson                     0x6008   // TEMP
#endif //RM_ETC3_ETC5

/* OES_visibility_query */
#define GL_ANY_SAMPLES_PASSED_OES                  0x8C2F
#define GL_SAMPLES_PASSED_OES                      0x8914
#define GL_QUERY_COUNTER_BITS_OES                  0x8864
#define GL_CURRENT_QUERY_OES                       0x8865
#define GL_RESULT_OES                              0x8866
#define GL_RESULT_AVAILABLE_OES                    0x8867

#ifdef RM_Z_QUERIES
GL_APICALL void GL_APIENTRY glBeginQueryOES(GLenum target, GLuint id);
GL_APICALL void GL_APIENTRY glEndQueryOES(GLenum target);
GL_APICALL void GL_APIENTRY glGenQueriesOES(GLsizei n, GLuint *ids);
GL_APICALL void GL_APIENTRY glDeleteQueriesOES(GLsizei n, const GLuint *ids);
GL_APICALL GLboolean GL_APIENTRY glIsQueryOES(GLuint id);
GL_APICALL void GL_APIENTRY glGetQueryivOES(GLenum target, GLenum pname, GLint *params);
GL_APICALL void GL_APIENTRY glGetQueryObjectivOES(GLuint id, GLenum pname, GLint *params);
GL_APICALL void GL_APIENTRY glGetQueryObjectuivOES(GLuint id, GLenum pname, GLuint *params);

/* OES_conditional_query */
#define GL_QUERY_WAIT_OES                             0x8C30
#define GL_QUERY_NO_WAIT_OES                          0x8C31
#define GL_QUERY_BY_REGION_WAIT_OES                   0x8C32
#define GL_QUERY_BY_REGION_NO_WAIT_OES                0x8C33
#define GL_CONDITIONAL_RENDER_OES                     0x8C34
#define GL_CONDITIONAL_RENDER_QUERY_OES               0x8C35
#define GL_MAX_CONDITIONAL_QUERIES_OES                0x600E   // TEMP
#define GL_CONDITIONAL_QUERIES_AVAILABLE_OES          0x600F   // TEMP

GL_APICALL void GL_APIENTRY glBeginConditionalRenderOES(GLuint id, GLenum mode);
GL_APICALL void GL_APIENTRY glEndConditionalRenderOES();
#endif // RM_Z_QUERIES

/* binary shader stuff */
#define GL_BINARY_FORMAT_OPENGL_ES_2_0_ATI_EMULATOR   0x6012   // TEMP
#define GL_BINARY_FORMAT_OPENGL_ES_2_0_ATI            0x897F

/* EXT_texture_filter_anisotropic */
#define GL_TEXTURE_MAX_ANISOTROPY_EXT                 0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT             0x84FF


/* these are missing from gl2.h */
#define GL_MAX_COLOR_ATTACHMENT                       0x6017   // TEMP

#ifdef __cplusplus
}
#endif

#endif // __gl2atiext_h_