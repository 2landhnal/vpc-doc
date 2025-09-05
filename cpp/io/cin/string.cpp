#include <iostream>

using namespace std;

int main(){
    std::string name;
    std::getline(std::cin, name);
    std::cout << "Hello, " << name << "!\n";
    return 0;
}