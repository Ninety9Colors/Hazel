#pragma once

#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "LayerStack.h"
#include "Window.h"

namespace Hazel {

  class HAZEL_API Application
  {
  public:
    Application();
    virtual ~Application();

    void run();
    void on_event(Event& e);
    bool on_window_close_event(WindowCloseEvent& e);

    void push_layer(Layer* layer) { layer_stack_.push_layer(layer); };
    void push_overlay(Layer* overlay) { layer_stack_.push_overlay(overlay); };
    void pop_layer(Layer* layer) { layer_stack_.pop_layer(layer); }
    void pop_overlay(Layer* layer) { layer_stack_.pop_overlay(layer); }

  private:
    LayerStack layer_stack_;
    std::unique_ptr<Window> window_;
    bool running_ = true;
  };

  // To be defined in CLIENT
  Application* create_application();

}// namespace Hazel