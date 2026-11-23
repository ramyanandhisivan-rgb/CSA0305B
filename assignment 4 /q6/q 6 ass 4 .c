#include <stdio.h>
#include <math.h>

int main() {
    double P = 24.0;
    double V = 415.0;
    double pf1 = 0.72;
    double pf2 = 0.90;

    double kva1 = P / pf1;
    double kva2 = P / pf2;

    double q1 = P * tan(acos(pf1));
    double q2 = P * tan(acos(pf2));
    double capacitor = q1 - q2;

    double i1 = (kva1 * 1000) / (sqrt(3) * V);
    double i2 = (kva2 * 1000) / (sqrt(3) * V);

    double reduction = ((i1 - i2) / i1) * 100;

    printf("Initial kVA Demand = %.2f kVA\n", kva1);
    printf("Target kVA Demand = %.2f kVA\n", kva2);
    printf("Capacitor Bank = %.2f kVAR\n", capacitor);
    printf("Initial Line Current = %.2f A\n", i1);
    printf("Final Line Current = %.2f A\n", i2);
    printf("Current Reduction = %.2f%%\n", reduction);

    return 0;
}