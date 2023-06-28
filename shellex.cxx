#include "shellex.h"
#include <wait.h>
#include <cstring>
#include <iostream>
#include <tuple>

std::string shx::ex(std::string cmd, std::string std_in) {
    // Create instance of shellex
    Shellex shell;
    shell.cmd = cmd;
    shell.std_in = std_in;

    shell.execute();

    // Output errors & warnings to console
    if (shell.exit_status != 0) {
        std::cout << shell.std_err << "\n";
    }

    return shell.std_out;
}

std::tuple<std::string, std::string, int> shx::ex_more(std::string cmd, std::string std_in) {
    // Create instance of shellex
    Shellex shell;
    shell.cmd = cmd;
    shell.std_in = std_in;

    shell.execute();

    return {shell.std_out, shell.std_err, shell.exit_status};
}


// Init constants
const int shx::Shellex::READ_END = 0;
const int shx::Shellex::WRITE_END = 1;

shx::Shellex::Shellex() 
:in_fd {0, 0}, out_fd {0, 0}, err_fd {0, 0} 
{
    //cmd = cmd;
    //if (std_in != "") { std_in = std_in; }
   
    exit_status = 0;
}

void shx::Shellex::execute() {
    auto cleanup = [&]() {
        close(in_fd[READ_END]);
        close(in_fd[WRITE_END]);

        close(out_fd[READ_END]);
        close(out_fd[WRITE_END]);

        close(err_fd[READ_END]);
        close(err_fd[WRITE_END]);  
    };

    rc = pipe(in_fd);
    if (rc < 0) {
        throw std::runtime_error(std::strerror(errno));
    }

    rc = pipe(out_fd);
    if (rc < 0) {
        close(in_fd[READ_END]);
        close(in_fd[WRITE_END]);
        throw std::runtime_error(std::strerror(errno));
    }

    rc = pipe(err_fd);
    if (rc < 0) {
        close(in_fd[READ_END]);
        close(in_fd[WRITE_END]);

        close(out_fd[READ_END]);
        close(out_fd[WRITE_END]);
        throw std::runtime_error(std::strerror(errno));
    }

    pid = fork();
    if (pid > 0) {      //PARENT
        close(in_fd[READ_END]);    // Parent does not read from stdin
        close(out_fd[WRITE_END]);  // Parent does not write to stdout
        close(err_fd[WRITE_END]);  // Parent does not write to stderr

        if (write(in_fd[WRITE_END], 
                    std_in.data(), 
                    std_in.size()) < 0) {
            throw std::runtime_error(std::strerror(errno));
        }
        close(in_fd[WRITE_END]); // Done writing
    }
    else if (pid == 0) { //CHILD
        dup2(in_fd[READ_END], STDIN_FILENO);
        dup2(out_fd[WRITE_END], STDOUT_FILENO);
        dup2(err_fd[WRITE_END], STDERR_FILENO);

        close(in_fd[WRITE_END]);   // Child does not write to stdin
        close(out_fd[READ_END]);   // Child does not read from stdout
        close(err_fd[READ_END]);   // Child does not read from stderr

        //system(cmd.c_str());
        execl("/bin/sh", "sh", "-c", cmd.c_str(), nullptr);
        exit(EXIT_SUCCESS);
    }

    // PARENT
    if (pid < 0) {
        cleanup();
        throw std::runtime_error("Failed to fork");
    } 

    int status = 0;

    waitpid(pid, &status, 0);

    ssize_t bytes = 0;
    do {
        bytes = read(out_fd[READ_END], buffer.data(), buffer.size());
        std_out.append(buffer.data(), bytes);
    }
    while(bytes > 0);

    do {
        bytes = read(err_fd[READ_END], buffer.data(), buffer.size());
        std_err.append(buffer.data(), bytes);
    }
    while (bytes > 0);

    if (WIFEXITED(status)) {
        exit_status = WEXITSTATUS(status);
    }

    cleanup();
}

