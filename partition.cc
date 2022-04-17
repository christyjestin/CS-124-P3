#include <cassert>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int flag = atoi(argv[1]);
    assert(flag == 0 && argc == 4);
    int algorithm = atoi(argv[2]);
}