#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Layer.h"

namespace Hazel {

class HAZEL_API LayerStack {
public:
  LayerStack();
  ~LayerStack();

  void push_layer(Layer* layer);
  void push_overlay(Layer* overlay);
  void pop_layer(Layer* layer);
  void pop_overlay(Layer* layer);

  void on_event(Event& e);
  void on_update();

  std::vector<Layer*>::iterator begin() { return layers_.begin(); };
  std::vector<Layer*>::iterator end() { return layers_.end(); };
private:
  std::vector<Layer*> layers_;
  std::vector<Layer*>::iterator layer_insert_;
};

}// namespace Hazel
