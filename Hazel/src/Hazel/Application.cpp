#include "hzpch.h"
#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

namespace Hazel {
  Application::Application()
  {
    window_ = std::unique_ptr<Window>(Window::create()); 
    window_->set_event_callback([this] (Event& e) { on_event(e); });
  }

  Application::~Application()
  {
  }

  void Application::run()
  {
    while (running_) {
      glClearColor(1, 1, 1, 0);
      glClear(GL_COLOR_BUFFER_BIT);
      layer_stack_.on_update();
      window_->on_update();
    }
  }

  void Application::on_event(Event& e) {
    EventDispatcher dispatcher { e };
    dispatcher.dispatch<WindowCloseEvent>([this] (WindowCloseEvent event) {
        return on_window_close_event(event);
      });

    HZ_CORE_TRACE("{0}", e);
    layer_stack_.on_event(e);
  }

  bool Application::on_window_close_event(WindowCloseEvent& e) {
    running_ = false;
    return true;
  }

}