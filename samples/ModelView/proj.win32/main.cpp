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
#include <ModelViewApp.h>

class FrameworkWin32 : public spank::Framework {};

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// initialize device
	spank::DeviceWin32 device;
	if (!device.initialize(hInstance, 960, 640, "MODEL_VIEW", "Model View"))
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
	framework.getRenderer()->resize(device.getWidth(), device.getHeight());

	// initialize app
	ModelViewApp app;
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
	while (true)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) break;

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
