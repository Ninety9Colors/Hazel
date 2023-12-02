#include "hzpch.h"

#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "WindowsWindow.h"

namespace Hazel {

  static bool s_GLFWInitialized = false;

  static void glfw_error_callback(int error_code, const char* description) {
    HZ_CORE_ERROR("GLFW Error {0}: {1}", error_code, description);
  }

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

    // set GLFW event callbacks

    glfwSetErrorCallback([](int error_code, const char* description) {
      glfw_error_callback(error_code, description);
      });

    glfwSetWindowCloseCallback(window_, [] (GLFWwindow* window) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        WindowCloseEvent event {};
        data.EventCallback(event);
      });

    glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width, int height) {
        WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
        data.Width = width;
        data.Height = height;

        WindowResizeEvent event {(unsigned int) width, (unsigned int) height};
        data.EventCallback(event);
        
      });

    glfwSetMouseButtonCallback(window_, [] (GLFWwindow* window, int button, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        
        switch (action) {
          case GLFW_PRESS: {
            MouseButtonReleasedEvent event { button };
            data.EventCallback(event);
            break;
          }
          case GLFW_RELEASE: {
            MouseButtonPressedEvent event { button };
            data.EventCallback(event);
            break;

          }
        }
      });

    glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action) {
          case GLFW_PRESS: {
            KeyPressedEvent event { key, 0 };
            data.EventCallback(event);
            break;
          }
          case GLFW_RELEASE: {
            KeyReleasedEvent event { key };
            data.EventCallback(event);
            break;
          }
          case GLFW_REPEAT: {
            KeyPressedEvent event  { key,1 };
            data.EventCallback(event);
            break;

          }
        }
      });

    glfwSetScrollCallback(window_, [](GLFWwindow* window, double xoffset, double yoffset) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseScrolledEvent event { (float) xoffset, (float) yoffset };
        data.EventCallback(event);

      });

    glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double xpos, double ypos) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseMovedEvent event { (float) xpos, (float) ypos};
        data.EventCallback(event);

      });
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