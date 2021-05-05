#include <iostream>
#include "graphics.hpp"

using namespace std;
using namespace genv;

int main() {
    std::cout << "Hello, World!" << std::endl;
    gout.open(200, 200);
    gout<<move_to(10,10)<<box_to(50, 50)<<refresh;
    event ev;
    while(gin>>ev){}
    return 0;
}
