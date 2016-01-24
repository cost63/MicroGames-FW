#pragma once

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

// Make sure that C++ types can be used instead of OpenGL typedefs
static_assert(sizeof(bool)  == sizeof(GLboolean), "C++ and OpenGL types do not match");
static_assert(sizeof(int8_t) == sizeof(GLbyte), "C++ and OpenGL types do not match");
static_assert(sizeof(uint8_t) == sizeof(GLubyte), "C++ and OpenGL types do not match");
static_assert(sizeof(short) == sizeof(GLshort), "C++ and OpenGL types do not match");
static_assert(sizeof(unsigned short) == sizeof(GLushort), "C++ and OpenGL types do not match");
static_assert(sizeof(int) == sizeof(GLint), "C++ and OpenGL types do not match");
static_assert(sizeof(uint32_t) == sizeof(GLuint), "C++ and OpenGL types do not match");
static_assert(sizeof(int64_t) == sizeof(GLint64), "C++ and OpenGL types do not match");
static_assert(sizeof(uint64_t) == sizeof(GLuint64), "C++ and OpenGL types do not match");
static_assert(sizeof(uint32_t) == sizeof(GLenum), "C++ and OpenGL types do not match");
static_assert(sizeof(float) == sizeof(GLfloat), "C++ and OpenGL types do not match");
static_assert(sizeof(double) == sizeof(GLdouble), "C++ and OpenGL types do not match");
