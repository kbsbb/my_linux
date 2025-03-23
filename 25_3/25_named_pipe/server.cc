#include "comm.hpp"

int main() {
    bool r = creatFifo(NAMED_PIPE);
    assert(r);
    (void)r;

    int rfd = open(NAMED_PIPE, O_RDONLY);
    if (rfd < 0) exit(1);
    //read
    char buffer[1024];
    while (true) {
        ssize_t s = read(rfd, buffer, sizeof(buffer));
        if (s > 0) {
            buffer[s] = '\0';
            cout << "client->server# " << buffer << endl;
        }
        else if (s == 0) {
            cout << "client quit, me too!" << endl;
            break;
        }
        else {
            cout << "error" << endl;
            break;
        }


    }

    close(rfd);

    removeFifo(NAMED_PIPE);
    return 0;
}