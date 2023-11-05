#pragma once
#ifdef HZ_PLATFORM_WINDOWS
extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, int** argv) {
  Hazel::Log::init();
  HZ_CORE_WARN("Initialized Logger!");

  Hazel::Application* app = Hazel::CreateApplication();
  app->run();
  delete app;
}

#endif // HZ_PLATFORM_WINDOWS