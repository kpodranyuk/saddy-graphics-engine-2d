/*! \file glcontext.h
	\author HiddenSeeker

	Contains implementation of OpenGL context
 */
#pragma once
#include "sadpoint.h"

namespace sad
{

namespace os
{
class GLContextImpl;
class GLContextHandle;
class MainLoopImpl;
}

class Renderer;
class Window;

/*! An OpenGL context, which could be created for window 
	or destroyed. Also contains swap buffers function
 */
class GLContext
{
friend class sad::Renderer;
friend class sad::os::MainLoopImpl;
public:
	/*! Creates new invalid context
	 */
	GLContext();
	/*! Frees resources, associated with context
	 */
	~GLContext();
	/*! Checks, whether context is valid
	 */
	bool valid() const;
	/*! Swaps buffers. Must be called, after scene is rendered
	 */
	void swapBuffers();
	/*! Maps a point from client coordinates to OpenGL viewport
		\param[in] p point
		\param[in] ztest whether ztesting should be performed
		\return mapped point in vierport
	 */
	sad::Point3D mapToViewport(const sad::Point2D & p, bool ztest = false);
	/*! Returns current OpenGL context
		\return OpenGL context
	 */
	sad::os::GLContextHandle * handle() const;
	/*! Returns a window, attached to context
		\return window, attached to context
	 */
	sad::Window * window() const;
	/*! Tests, whether OpenGL context is compatible with OpenGL 3.0+ specs
		\return whether it's compatible
	 */
	bool isOpenGL3compatible() const;
//#ifndef DO_NOT_HIDE_RENDERER_METHODS
//protected:
//#endif
	/*! Tries to create context for specified window. Does nothing, if it's
		already created
		\param[in] win a window
		\return whether it was successfull
	 */
	bool createFor(sad::Window * win);
	/*! Destroys a context
	 */
	void destroy();
private:
	/*! A pointer to implementation of OpenGL context
	 */
	sad::os::GLContextImpl * m_dptr;
	/*! Cannot be copied, so this is disabled and not implemented
		\param[in] o other window
	 */
	GLContext(const sad::GLContext & o);
	/*! Cannot be copied, so this is disabled and not implemented
		\param[in] o other window
		\return self-reference
	 */	
	sad::GLContext & operator=(const sad::GLContext & o);
};

}