#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Hazel {
class HAZEL_API Layer {
public:
  Layer(const std::string& name = "Layer");
  virtual ~Layer();

  virtual void on_attach() {}
  virtual void on_detach() {}
  virtual void on_update() {}
  virtual void on_event(Event& e) {}
private:
  std::string debug_name_;
};
}// namespace Hazel
