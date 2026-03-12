#include <stdio.h>
#include <math.h>

double f1(double xi, double y) {
    return y;
}

double f2(double xi, double y, double R) {
    // return y - (xi * xi) - (R * xi);

    return -(R*R)*xi;
}

double f_phase(double xi, double y, double R) {
    // Защита от деления на ноль в точках y=0
    // if (fabs(y) < 1e-12) return 0; 
    // return  (y-xi*xi-R*xi)/y;
    return -(R*R)*xi/y;
    
}

int main() {
    double R, h, xi_start, y_start;
    int steps, num_traj;

    fprintf(stderr, "Вариант 13\n");
    fprintf(stderr, "Введите параметр R (например, 0.5): ");
    scanf("%lf", &R);
    fprintf(stderr, "Введите шаг по времени h: ");
    scanf("%lf", &h);
    fprintf(stderr, "Введите количество шагов: ");
    scanf("%d", &steps);
    fprintf(stderr, "Сколько траекторий построить для портрета? ");
    scanf("%d", &num_traj);

    printf("tr_id,tau,xi,y_sys,y_phase\n");

    for (int tr = 0; tr < num_traj; tr++) {
        fprintf(stderr, "\nТраектория %d\n", tr);
        fprintf(stderr, "Начальное xi: "); scanf("%lf", &xi_start);
        fprintf(stderr, "Начальное y: ");
        scanf("%lf", &y_start);

        double tau = 0.0;
        double xi = xi_start;
        double y_sys = y_start;
        double y_phase = y_start;

        for (int i = 0; i <= steps; i++) {
            // траектория, время, координата, скорость(система), скорость(фаз.уравнение)
            printf("%d,%f,%f,%f,%f\n", tr, tau, xi, y_sys, y_phase);

            // рк4 для системы
            double k1x, k1y, k2x, k2y, k3x, k3y, k4x, k4y;

            k1x = f1(xi, y_sys);
            k1y = f2(xi, y_sys, R);

            k2x = f1(xi + 0.5 * h * k1x, y_sys + 0.5 * h * k1y);
            k2y = f2(xi + 0.5 * h * k1x, y_sys + 0.5 * h * k1y, R);

            k3x = f1(xi + 0.5 * h * k2x, y_sys + 0.5 * h * k2y);
            k3y = f2(xi + 0.5 * h * k2x, y_sys + 0.5 * h * k2y, R);

            k4x = f1(xi + h * k3x, y_sys + h * k3y);
            k4y = f2(xi + h * k3x, y_sys + h * k3y, R);

            // следующее состояние
            double d_xi = (h / 6.0) * (k1x + 2.0 * k2x + 2.0 * k3x + k4x);
            double d_y   = (h / 6.0) * (k1y + 2.0 * k2y + 2.0 * k3y + k4y);

             // рк4 для фазового портрета 
             // шаг d_i 
            double m1 = f_phase(xi, y_phase, R);
            double m2 = f_phase(xi + 0.5 * d_xi, y_phase + 0.5 * d_xi * m1, R);
            double m3 = f_phase(xi + 0.5 * d_xi, y_phase + 0.5 * d_xi * m2, R);
            double m4 = f_phase(xi + d_xi, y_phase + d_xi * m3, R);

            y_phase = y_phase + (d_xi / 6.0) * (m1 + 2.0 * m2 + 2.0 * m3 + m4);

            xi += d_xi;
            y_sys += d_y;
            tau += h;
        }
        printf("\n");    }

    fprintf(stderr, "\nРасчет завершен успешно.\n");
    return 0;
}
