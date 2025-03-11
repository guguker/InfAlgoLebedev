#include <iostream>
#include <cmath>
#include <iomanip>

// формула симпсона
double simpson_rule(double (*f)(double), double a, double b, int n) {
    if (n % 2 == 1) n++; // n-ки делаем чёткими
    double h = (b - a) / n;
    double sum = f(a) + f(b);

    for (int i = 1; i < n; i += 2)
        sum += 4 * f(a + i * h);

    for (int i = 2; i < n - 1; i += 2)
        sum += 2 * f(a + i * h);

    return (h / 3) * sum;
}

double integrand(double x) {
    if (x <= 6)
        return x - 4;      // для x = [4,6], то есть участок задаваемый разностью (0.5x+1) и (-0.5x+5)
    else
        return -x + 8;     // для x = [6,8], то есть участок задаваемый разностью (-0.5x+7) и (0.5x-1)
}

int main() {
    // интегрируем функцию от x = 4 до x = 8
    double area = simpson_rule(integrand, 4, 8, 100000);
    std::cout << std::setprecision(20) << "Approximately area of the shape: " << area << std::endl;
    system("pause");
    return 0;
}


