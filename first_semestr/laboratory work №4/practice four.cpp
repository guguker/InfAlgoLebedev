#include <iostream>
#include <cmath>
#include <algorithm>

int main()
{
    float x, y;

    std::cout << "Input x and y values: ";
    std::cin >> x >> y;

    double R = sqrt(pow(x, 2) + pow(y, 2)) / pow(2, log2(x));
    double S = log(x) * tan(y);
    double C = std::max(R, S);


    std::cout << "R = " << R << "\n";
    std::cout << "S = " << S << "\n";
    std::cout << "C = " << C << "\n";

    std::cout << "Press Enter to end...";
    system("pause");

    return 0;
}
