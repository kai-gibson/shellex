#include <shx/shellex.h>
#include <cstring>
#include <iostream>
#include <string>
//#include <fmt/format.h>
//#include <fmt/os.h>
#include <fstream>
#include <sstream>

//void using_fmt() {
//    std::cout << "fmt\n";
//
//    std::string filename = "abc/";
//    shx::ex("mkdir " + filename);
//
//    for (int i=0; i<5000; i++) {
//        auto out = fmt::output_file(fmt::format("{}{}", filename, i));
//        out.print("{}proc_1", i);
//    }
//
//    shx::ex("grep 2", shx::ex("cat abc/*"));
//    shx::ex("rm -rf abc");
//}

void using_std() {
    std::cout << "std\n";

    std::stringstream ss;
    shx::ex("mkdir abc/");

    for (int i=0; i<5000; i++) {
        ss << "abc/" << i;

        std::ofstream o(ss.str());
        o << i << "_proc";
    }

    shx::ex("grep 2", shx::ex("cat abc/*"));
    shx::ex("rm -rf abc");
}

//
int main(int argc, char** argv){
    //if (argc > 0) {

    //    std::stringstream ss;
    //    for (int i=1; i<argc; i++) { ss << argv[i] << " "; }

    //    auto retval = shx::ex_more(ss.str());

    //    std::cout << "exit status: " << std::get<2>(retval) << "\n";

    //    if (std::get<2>(retval) == 0 || std::get<2>(retval) == 1) {
    //        std::cout << std::get<0>(retval) << "\n";
    //    }
    //    else {
    //        std::cout << std::get<1>(retval) << "\n";
    //    }
    //}

    using_std();
    //if (argc > 0) {
    //    if (strcmp("std", argv[1]) == 0) {
    //        using_std();
    //    }
    //    else if (strcmp("fmt", argv[1]) == 0) {
    //        using_fmt();
    //    }
    //}

    return 0;
}

