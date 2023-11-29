#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Hazel {

  class HAZEL_API Application
  {
  public:
    Application();
    virtual ~Application();

    void run();

  private:
    std::unique_ptr<Window> window_;
    bool running_ = true;
  };

  // To be defined in CLIENT
  Application* create_application();

}// namespace Hazel