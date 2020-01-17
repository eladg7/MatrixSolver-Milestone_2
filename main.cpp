#include "Server/boot.h"

using namespace boot;

int main() {
    boot::ParallelServerMain::main(5600);
    return 0;
}