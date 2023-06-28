# shellex
## A POSIX scripting library for C++

This library uses [this](ps://dev.to/aggsol/calling-shell-commands-from-c-8ej) as a template to create a usable C++ library for running shell commands

Quickstart:
```
#include <shx/shellex.h>
#include <iostream>
#include <string>
#include <tuple>

int main() {
    std::string std_out = shx::ex("ls -lah");    
    std::cout << std_out << "\n";
}
```


