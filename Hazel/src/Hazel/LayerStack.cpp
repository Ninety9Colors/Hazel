#include "hzpch.h"

#include "LayerStack.h"

namespace Hazel {

LayerStack::LayerStack() : layer_insert_(layers_.begin()){};

LayerStack::~LayerStack() {
  for (Layer* layer : layers_) {
    delete layer;
  }
}

void LayerStack::push_layer(Layer* layer) {
  layer_insert_ = layers_.emplace(layer_insert_, layer);
  layer->on_attach();
}

void LayerStack::push_overlay(Layer* overlay) {
  layers_.emplace_back(overlay);
  overlay->on_attach();
}

void LayerStack::pop_layer(Layer* layer) {
  layers_.erase(std::find(layers_.begin(), layers_.end(), layer));
  layer->on_detach();
}

void LayerStack::pop_overlay(Layer* overlay) {
  layers_.erase(std::find(layers_.begin(), layers_.end(), overlay));
  overlay->on_detach();
}

void LayerStack::on_event(Event& e) {
  for (Layer* layer : layers_) {
    layer->on_event(e);
    if (e.is_handled())
      break;
  }
}

void LayerStack::on_update() {
  for (Layer* layer : layers_) {
    layer->on_update();
  }
}

}// namespace Hazel
