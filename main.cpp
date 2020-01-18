#include "Server/boot.h"

using namespace boot;

int main() {
    boot::ParallelServerMain::main(5601);
    return 0;
}