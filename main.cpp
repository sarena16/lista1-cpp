#include <iostream>
#include <cmath>

double heron (double a, double b, double c) {
    double p = (a + b + c) / 2.0;
    return std::sqrt (p * (p - a) * (p - b) * (p - c));
}

int main () {
    std:: cout << heron (3,4,5) << "\n";
    return 0;
}