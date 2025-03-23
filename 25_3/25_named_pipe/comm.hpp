#include <iostream>
#include <cstring>
#include <string>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


using namespace std;

#define NAMED_PIPE "./mypipe"

//创建命名管道
bool creatFifo(const string& path) {
    umask(0);
    int n = mkfifo(path.c_str(), 0600);
    if (n == 0) return true;
    else {
        cout << "errno: " << errno << "err string: " << strerror(errno) << endl;
        return false;
    }
}

//删除命名管道
void removeFifo(const string& path) {
    int n = unlink(path.c_str());
    assert(n == 0);
    (void)n;
}