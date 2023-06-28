#ifndef SHELLEX_H
#define SHELLEX_H

#include <string>
#include <array>

namespace shx {
    std::string ex(std::string cmd, std::string std_in = "");
    std::tuple<std::string, std::string, int> ex_more(std::string cmd, std::string std_in = "");
    
    class Shellex {
        public:
            int exit_status;
            std::string cmd;
            std::string std_in;
            std::string std_out;
            std::string std_err;
    
            // Methods
            Shellex();
            void execute();
    
        private:
            // Constants
            static const int READ_END;
            static const int WRITE_END;
    
            int in_fd[2];
            int out_fd[2];
            int err_fd[2];
    
            int rc; 
    
            pid_t pid;
            int status;
            std::array<char, 256> buffer;
            ssize_t bytes;
    };
}

#endif
