#include <iostream>
#include <string>
using namespace std;

string pH_(double ph_number) {
    if (ph_number >= 6.9 && ph_number <= 7.1) {
        return "Is Natural pH";
    } else if (ph_number > 7) {
        return "Is Alkaline pH";
    } else {
        return "Is Acidic pH";
    }
}

 
int main() {
    string pH_Water;
    double ph = (rand() % 140 + 1) / 10.0;

    cout << "Currently pH number is: " + to_string(ph) << endl;
    pH_Water = pH_(ph);
    
    cout << pH_Water << endl;

    return 0;
}
