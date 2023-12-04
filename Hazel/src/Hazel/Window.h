#pragma once

#include "hzpch.h"

#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel {

  struct WindowProps
  {
    std::string Title;
    unsigned int Width;
    unsigned int Height;

    WindowProps(const std::string& title = "Hazel Engine",
      unsigned int width = 1280,
      unsigned int height = 720)
      : Title(title), Width(width), Height(height)
    {
    }
  };

  // Interface representing a desktop system based Window
  class HAZEL_API Window
  {
  public:
    using EventCallbackFn = std::function<void(Event&)>;

    virtual ~Window() {}

    virtual void on_update() = 0;

    virtual unsigned int get_width() const = 0;
    virtual unsigned int get_height() const = 0;

    // Window attributes
    virtual void set_event_callback(const EventCallbackFn& callback) = 0;
    virtual void set_vsync(bool enabled) = 0;
    virtual bool is_vsync() const = 0;

    static Window* create(const WindowProps& props = WindowProps{});
  };

}