#include "comm.hpp"

int main() {
    int wfd = open(NAMED_PIPE, O_WRONLY);
    if (wfd < 0) exit(1);
    //write
    char buffer[1024];
    while (true) {
        cout << "please Say# ";
        fgets(buffer, sizeof(buffer), stdin);
        ssize_t n = write(wfd, buffer, strlen(buffer));
        assert(n == strlen(buffer));
        (void)n;

    }

    close(wfd);
    return 0;
}