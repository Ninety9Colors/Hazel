#include <Hazel.h>

class Sandbox : public Hazel::Application {
public:
  Sandbox() {}
  ~Sandbox() {}
};

Hazel::Application* Hazel::create_application() {
  return new Sandbox();
}