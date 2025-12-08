#include <iostream>
#include <string>
using namespace std;

template<typename... Args>
void print(Args... args) {
    (cout << ... << args);
    cout << "\n";
}

int main() {
    string myname;
    cout << "Enter Your Name: ";
    cin >> myname;
    print("My Name Is ", myname,".");
}
