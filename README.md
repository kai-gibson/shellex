# shellex
## A POSIX scripting library for C++

This library uses:

https://dev.to/aggsol/calling-shell-commands-from-c-8ej

as a template to create a usable C++ library for running shell commands

# Install Instructions
```
git clone https://github.com/kai-gibson/shellex.git
cd shellex
sudo make install
```

# Quickstart
```
#include <shx/shellex.h>
#include <iostream>
#include <string>

int main() {
    std::string std_out = shx::ex("ls -lah");    
    std::cout << std_out << "\n";
}
```


# Performance

An example shell script that creates a lot of files, writes to them
deletes them all can be found in the examples. The output from perf is:

```
 Performance counter stats for './examples/test.sh':

     2,082,895,385      cycles:u                         #    0.284 GHz                       
     1,387,805,111      instructions:u                   #    0.67  insn per cycle            
          7,339.06 msec task-clock:u                     #    0.951 CPUs utilized             

       7.720423053 seconds time elapsed

       4.507877000 seconds user
       3.243972000 seconds sys
```

The equivalent script using this library in c++ (using streams for file
io) gives us:
```

 Performance counter stats for './bin/testing':

        43,699,802      cycles:u                         #    1.626 GHz                       
        59,699,914      instructions:u                   #    1.37  insn per cycle            
             26.87 msec task-clock:u                     #    0.971 CPUs utilized             

       0.027664071 seconds time elapsed

       0.013602000 seconds user
       0.013889000 seconds sys
```

Finally, just for fun, both compiling and running the c++ example:
```
 Performance counter stats for 'g++ examples/testing.cxx /usr/local/lib/libshellex.a -o bin/testing':

     1,132,617,709      cycles:u                         #    3.463 GHz
     1,388,476,548      instructions:u                   #    1.23  insn per cycle
            327.10 msec task-clock:u                     #    0.997 CPUs utilized

       0.328047675 seconds time elapsed

       0.299418000 seconds user
       0.027947000 seconds sys
```

A LOT faster.

(I'm not saying we should write C++ instead of POSIX scripts, just
pointing out the benefits of using C++ for IO heavy scripts)
