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

double calculator(double electric, double ammonia, string pH) {
    if (electric <= 5 and ammonia <= 1 and pH == "Is Acidic pH") {
        return 'Get New Rock';
    } else {
        return 'Wait for change new rock';
    }
}
 
int main() {
    double electric, ammonia, ph;
    string pH_Water;
    string calculator_;
    // double ph = (rand() % 140 + 1) / 10.0;


    cout << "Currently pH number is: " + to_string(ph) << endl;
    cout << "Currently electric number is: " + to_string(electric) << endl;
    cout << "Currently ammonia number is: " + to_string(ammonia) << endl;


    pH_Water = pH_(ph);
    calculator_ = calculator(electric, ammonia, pH_Water);

    if (calculator_ == "Get New Rock") {
        cout << "Waiting For Change New Rock";
    } else {
        cout << calculator_;
    }
    return 0;
}
