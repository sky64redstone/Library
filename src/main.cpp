#include "macros.hpp"
#include "types.hpp"

#if defined(macros_os_windows)

  #include <windows.h>
  #include <iostream>

  int WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    std::cout << "Hello World from WinMain!" << std::endl;
    return 0;
  }

#elif defined(macros_os_linux)

  #include <iostream>

  int main() {
    std::cout << "Hello World from linux!" << std::endl;
    using type = lib::type_from_size<sizeof(int), true>;
    type i = 0;
    i++;
    return --i;
  }

#endif
