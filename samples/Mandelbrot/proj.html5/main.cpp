/*!
 * \file main.cpp
 * \date 10-11-2014 13:20:03
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <MandelbrotApp.h>
#include <utils/LogUtil.h>
#include <utils/esUtil.h>
#include <emscripten/emscripten.h>

#define WINDOW_WIDTH (960)
#define WINDOW_HEIGHT (640)

class FrameworkHtml5 : public spank::Framework {};
FrameworkHtml5* g_pFrameworkHtml5 = nullptr;
MandelbrotApp* g_pMandelbrotApp = nullptr;

void step()
{
	g_pMandelbrotApp->step();
}

int main(int argc, char *argv[])
{
	ESContext esContext;
	esInitContext(&esContext);

	esCreateWindow(&esContext, "HelloGLES3", WINDOW_WIDTH, WINDOW_HEIGHT, ES_WINDOW_RGB);

	LOGD("GameEntry initialize");

	// initialize framework
	g_pFrameworkHtml5 = new FrameworkHtml5();
	if (!g_pFrameworkHtml5->initialize())
	{
		g_pFrameworkHtml5->terminate();
		SAFE_DELETE(g_pFrameworkHtml5);
		return 0;
	}

	g_pFrameworkHtml5->getRenderer()->resize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// initialize app
	g_pMandelbrotApp = new MandelbrotApp();
	g_pMandelbrotApp->setFramework(g_pFrameworkHtml5);
	if (!g_pMandelbrotApp->initialize())
	{
		g_pMandelbrotApp->terminate();
		SAFE_DELETE(g_pMandelbrotApp);

		g_pFrameworkHtml5->terminate();
		SAFE_DELETE(g_pFrameworkHtml5);

		return 0;
	}

	emscripten_set_main_loop(step, 0, 0);

	return 0;
}
