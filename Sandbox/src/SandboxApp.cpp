#include <Hazel.h>

class ExampleLayer : public Hazel::Layer {
public:
  ExampleLayer() : Layer("ExampleLayer") {}

  void on_attach() {
    HZ_INFO("ExampleLayer attached");
  }
  void on_detach() {
    HZ_INFO("ExampleLayer detached");
  }
  void on_event(Hazel::Event& e) override {
    HZ_TRACE(e);
  }
  void on_update() override {
  }
};

class Sandbox : public Hazel::Application {
public:
  Sandbox() {
    ExampleLayer* layer = new ExampleLayer{};
    push_layer(layer);
  }
  ~Sandbox() {}
};

Hazel::Application* Hazel::create_application() {

  return new Sandbox;
}