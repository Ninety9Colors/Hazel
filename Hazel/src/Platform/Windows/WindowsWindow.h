#pragma once

#include "Hazel/Window.h"

#include <GLFW/glfw3.h>

namespace Hazel {

  class WindowsWindow : public Window
  {
  public:
    WindowsWindow(const WindowProps& props);
    virtual ~WindowsWindow();

    void on_update() override;

    inline unsigned int get_width() const override { return data_.Width; }
    inline unsigned int get_height() const override { return data_.Height; }

    // Window attributes
    inline void set_event_callback(const EventCallbackFn& callback) override { data_.EventCallback = callback; }
    void set_vsync(bool enabled) override;
    bool is_vsync() const override;
  private:
    virtual void init(const WindowProps& props);
    virtual void shutdown();

    GLFWwindow* window_;

    struct WindowData
    {
      std::string Title;
      unsigned int Width, Height;
      bool VSync;

      EventCallbackFn EventCallback;
    };

    WindowData data_;
  };

}