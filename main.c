#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Функція обчислення інтеграла
// методом лівих прямокутників
double num_comput_integral_l_re(double left_boundary_a,
    double right_boundary_b, unsigned int intervals);

// Функція обчислення інтеграла
// методом правих прямокутників
double num_comput_integral_r_re(double left_boundary_a,
    double right_boundary_b, unsigned int intervals);

// Функція обчислення інтеграла
// методом Симпсона
double num_comput_integral_Simps(double left_boundary_a,
    double right_boundary_b, unsigned int intervals);

// Основна функція f(x)
double integrand_expression(double x);


int main()
{
    // Ліва та права межі інтегрування
    double left_boundary_a = 0;
    double right_boundary_b = 0;

    // Допустима похибка обчислення інтеграла
    double measurement_error = 0;

    // Результати двох послідовних обчислень
    double I1 = 0;
    double I2 = 0;

    // Кількість інтервалів розбиття
    unsigned int intervals;

    // Номер обраного методу
    unsigned int var;

    // Змінна циклу
    unsigned int i;

    // Результат обчислення інтеграла
    double integral_s = 0;


    // Основний цикл програми
    while (1)
    {
        // Введення лівої межі інтегрування
        printf("\n\tEnter the left boundary \n X(first)=");
        scanf("%lf", &left_boundary_a);

        // Введення правої межі інтегрування
        printf("\n\tEnter the right boundary \n X(last)=");
        scanf("%lf", &right_boundary_b);


        // Введення кількості інтервалів розбиття
        // Кількість інтервалів повинна бути більшою за нуль
        do
        {
            printf("\tEnter the number of partition intervals (N>0)\nN=");
            scanf("%u", &intervals);

        } while (intervals <= 0);


        // Введення допустимої похибки
        printf("\n\tEnter the measurment error of integration\n");
        printf(" Measurment error=");
        scanf("%lf", &measurement_error);


        // Вибір методу обчислення інтеграла
        do
        {
            printf("\nChoose the method of calculating:\n");
            printf("\t1. By Left Rectangles :\n");
            printf("\t2. By Right Rectangles:\n");
            printf("\t3. By Integral Simpson's method (parabola method):\n");

            scanf("%u", &var);

            // Перевірка правильності вибору
            if (var != 1 && var != 2 && var != 3)
                printf("\nYou are mistaken\n");

        } while (var != 1 && var != 2 && var != 3);


        // Очищення консолі
        system("cls");


        // Вибір методу обчислення
        switch (var)
        {
            // Метод лівих прямокутників
            case 1:
            {
                // Виклик функції обчислення інтеграла
                // методом лівих прямокутників
                integral_s = num_comput_integral_l_re(left_boundary_a, right_boundary_b, intervals);

                printf("\n\n\t*Left Rectangles method*\n");

                printf("\n\ta = %.2lf \n\tb = %.2lf \n\tIntegral = %.8lf \n\tN = %u", left_boundary_a, right_boundary_b, integral_s, intervals);
            }
            break;

            // Метод правих прямокутників
            case 2:
            {
                printf("\n\n\t======*Right Rectangles method*======\n");

                // Перше обчислення інтеграла
                I1 = num_comput_integral_r_re(left_boundary_a, right_boundary_b, intervals);


                // Збільшуємо кількість інтервалів,
                // поки похибка не стане допустимою
                for (i = 0; i < 2; i++)
                {
                    if (i == 1)
                    {
                        // Збільшуємо кількість інтервалів
                        intervals += 2;

                        // Повторно обчислюємо інтеграл
                        I2 = num_comput_integral_r_re(left_boundary_a, right_boundary_b, intervals);

                        // Перевіряємо похибку
                        if (fabs(I1 - I2) <= measurement_error)
                        {
                            break;
                        }
                    }
                    else
                    {
                        // Повертаємося до наступної ітерації
                        i = 0;
                    }
                }


                printf("\n\ta = %.2lf \n\tb = %.2lf \n\tIntegral = %.8lf \n\tN = %u", left_boundary_a, right_boundary_b, I2, intervals);
            }
            break;

            // Метод Симпсона
            case 3:
            {
                // Виклик функції обчислення інтеграла
                // методом Симпсона
                integral_s = num_comput_integral_Simps(left_boundary_a, right_boundary_b, intervals);

                printf("\n\n\t======*Simpson's method*======\n");

                printf("\n\ta = %.2lf \n\tb = %.2lf \n\tIntegral = %.8lf \n\tN = %u", left_boundary_a, right_boundary_b, integral_s, intervals);
            }
            break;
        }
    }

    return 0;
}


// Функція обчислення інтеграла
// методом лівих прямокутників

double num_comput_integral_l_re(double left_boundary_a, double right_boundary_b, unsigned int intervals)
{
    double integral_s = 0;
    double x = 0;
    double h;

    unsigned int i;


    // Обчислюємо довжину одного інтервалу
    //
    // h = (b - a) / n
    h = (right_boundary_b - left_boundary_a) / intervals;

    // Починаємо з лівої межі
    x = left_boundary_a;

    // Проходимо по всіх інтервалах
    for (i = 0; i < intervals; i++)
    {
        // Додаємо значення функції
        // у лівій точці поточного інтервалу
        integral_s += integrand_expression(x);

        // Переходимо до наступної точки
        x += h;
    }

    // Помножуємо суму на довжину інтервалу
    return integral_s * h;
}

// Функція обчислення інтеграла
// методом правих прямокутників

double num_comput_integral_r_re(double left_boundary_a, double right_boundary_b, unsigned int n)
{
    double integral_s = 0;
    double x = 0;
    double h;

    unsigned int i;

    // Обчислюємо довжину одного інтервалу
    h = (right_boundary_b - left_boundary_a) / n;

    // Для методу правих прямокутників
    // починаємо з першої правої точки
    x = left_boundary_a + h;

    // Проходимо по всіх інтервалах
    for (i = 0; i < n; i++)
    {
        // Додаємо значення функції
        // у правій точці поточного інтервалу
        integral_s += integrand_expression(x);

        // Переходимо до наступної точки
        x += h;
    }

    // Помножуємо суму на довжину інтервалу
    return integral_s * h;
}

// Функція обчислення інтеграла
// методом Симпсона

double num_comput_integral_Simps(double left_boundary_a, double right_boundary_b, unsigned int n)
{
    // Для методу Симпсона кількість інтервалів
    // повинна бути парною.
    // Якщо n непарне, збільшуємо його на 1.
    if (n % 2 != 0)
        n++;

    // Обчислюємо довжину одного інтервалу
    double h = (right_boundary_b - left_boundary_a) / n;

    // Початкова сума містить значення функції
    // на лівій та правій межах
    //
    // f(a) + f(b)
    double integral_s = integrand_expression(left_boundary_a) + integrand_expression(right_boundary_b);

    // Проходимо по внутрішніх точках
    for (unsigned int i = 1; i < n; i++)
    {
        // Обчислюємо координату поточної точки
        double x = left_boundary_a + i * h;

        // Для парних номерів точок
        // використовується коефіцієнт 2
        if (i % 2 == 0)
        {
            integral_s += 2 * integrand_expression(x);
        }

        // Для непарних номерів точок
        // використовується коефіцієнт 4
        else
        {
            integral_s += 4 * integrand_expression(x);
        }
    }

    // Формула методу Симпсона:
    //
    // I = h / 3 * [f(a) + f(b)
    //      + 4f(x1) + 2f(x2)
    //      + 4f(x3) + ...]
    return integral_s * h / 3;
}

// Основна функція f(x)

double integrand_expression(double x)
{
    // Функція, інтеграл якої обчислюємо:
    //
    // f(x) = (x^3/20) - 5*x^2 + 1000

    return pow(x, 3)/20.0 - 5*pow(x, 2) + 1000;
}