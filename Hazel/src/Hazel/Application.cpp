#include "hzpch.h"

#include "Application.h"

#include "Events/MouseEvent.h"
#include "Log.h"

namespace Hazel {
	Application::Application() {}
	Application::~Application() {}

	void Application::run() {
    MouseMovedEvent e(100,100);
    HZ_TRACE(e.ToString());
		while (true);
	}

}//namespace Hazel
