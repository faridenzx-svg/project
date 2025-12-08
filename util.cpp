#include <iostream>
#include <string>
using namespace std;

template<typename... Args>
void print(Args... args) {
    (cout << ... << args);
    cout << "\n";
}
