#ifdef HZ_PLATFORM_WINDOWS
  #ifdef HZ_BUILD_DLL
    #define HAZEL_API __declspec(dllexport)
  #else
    #define HAZEL_API __declspec(dllimport)
  #endif // HZ_BUILD_DLLs
#else
  #error Hazel only supports windows!
#endif // HZ_PLATFORM_WINDWOS