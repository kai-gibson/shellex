#include <iostream>
#include <shx/shellex.h>

int main() {
    shx::return_data return_data = shx::ex_more("test");

    std::cout << "exit code: " << return_data.exit_code << "\n";
    std::cout << "std out: " << return_data.std_out << "\n";
    std::cout << "std err: " << return_data.std_err << "\n";
}
