/*!
 * \file main.cpp
 *
 * \author zjhlogo
 * \date 2014/10/02
 *
 * 
 */
#include "main.h"
#include "DeviceWin32.h"
#include <Framework.h>
#include <HelloGLES3App.h>

class FrameworkWin32 : public spank::Framework {};

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// initialize device
	spank::DeviceWin32 device;
	if (!device.initialize(hInstance, 960, 640))
	{
		device.terminate();
		return 0;
	}

	// initialize framework
	FrameworkWin32 framework;
	if (!framework.initialize())
	{
		framework.terminate();
		device.terminate();
		return 0;
	}
	device.setFramework(&framework);

	// initialize app
	HelloGLES3App app;
	app.setFramework(&framework);
	if (!app.initialize())
	{
		app.terminate();
		framework.terminate();
		device.terminate();
		return 0;
	}

	// start message loop
	MSG msg;
	memset(&msg, 0, sizeof(msg));
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		app.step();

		eglSwapBuffers(device.getEglDisplay(), device.getEglSurface());
	}

	// terminate app
	app.terminate();

	// terminate framework
	framework.terminate();

	// terminate device
	device.terminate();

	return 0;
}
