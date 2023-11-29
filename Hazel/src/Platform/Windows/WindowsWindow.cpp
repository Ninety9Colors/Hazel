#include "hzpch.h"
#include "WindowsWindow.h"

namespace Hazel {

  static bool s_GLFWInitialized = false;

  Window* Window::create(const WindowProps& props)
  {
    return new WindowsWindow(props);
  }

  WindowsWindow::WindowsWindow(const WindowProps& props)
  {
    init(props);
  }

  WindowsWindow::~WindowsWindow()
  {
    shutdown();
  }

  void WindowsWindow::init(const WindowProps& props)
  {
    data_.Title = props.Title;
    data_.Width = props.Width;
    data_.Height = props.Height;

    HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

    if (!s_GLFWInitialized)
    {
      // TODO: glfwTerminate on system shutdown
      int success = glfwInit();
      HZ_CORE_ASSERT(success, "Could not intialize GLFW!");

      s_GLFWInitialized = true;
    }

    window_ = glfwCreateWindow((int)props.Width, (int)props.Height, data_.Title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window_);
    glfwSetWindowUserPointer(window_, &data_);
    set_vsync(true);
  }

  void WindowsWindow::shutdown()
  {
    glfwDestroyWindow(window_);
  }

  void WindowsWindow::update()
  {
    glfwPollEvents();
    glfwSwapBuffers(window_);
  }

  void WindowsWindow::set_vsync(bool enabled)
  {
    if (enabled)
      glfwSwapInterval(1);
    else
      glfwSwapInterval(0);

    data_.VSync = enabled;
  }

  bool WindowsWindow::is_vsync() const
  {
    return data_.VSync;
  }

}