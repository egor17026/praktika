#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <ctime>
#include <iomanip>
#include <limits>

using namespace std;

// Функция для логирования действий
void logAction(const string& action) {
    ofstream logFile("/home/liveuser/Desktop/math_log.txt", ios::app);
    if (logFile.is_open()) {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        logFile << "[" << 1900 + ltm->tm_year << "-"
                << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
                << setw(2) << setfill('0') << ltm->tm_mday << " "
                << setw(2) << setfill('0') << ltm->tm_hour << ":"
                << setw(2) << setfill('0') << ltm->tm_min << ":"
                << setw(2) << setfill('0') << ltm->tm_sec << "] "
                << action << endl;
        logFile.close();
    }
}

// Решение квадратного уравнения
void solveQuadraticEquation() {
    double a, b, c;
    cout << "Введите коэффициенты квадратного уравнения (a b c): ";
    cin >> a >> b >> c;

    if (a == 0) {
        cout << "Это не квадратное уравнение (a = 0)!" << endl;
        logAction("Попытка решить линейное уравнение вместо квадратного");
        return;
    }

    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        double x1 = (-b + sqrt(discriminant)) / (2 * a);
        double x2 = (-b - sqrt(discriminant)) / (2 * a);
        cout << "Два действительных корня: x1 = " << x1 << ", x2 = " << x2 << endl;
        logAction("Решено квадратное уравнение: два корня");
    } else if (discriminant == 0) {
        double x = -b / (2 * a);
        cout << "Один действительный корень: x = " << x << endl;
        logAction("Решено квадратное уравнение: один корень");
    } else {
        double realPart = -b / (2 * a);
        double imaginaryPart = sqrt(-discriminant) / (2 * a);
        cout << "Комплексные корни: x1 = " << realPart << " + " << imaginaryPart << "i, "
             << "x2 = " << realPart << " - " << imaginaryPart << "i" << endl;
        logAction("Решено квадратное уравнение: комплексные корни");
    }
}

// Решение системы линейных уравнений 2x2
void solveLinearSystem() {
    double a1, b1, c1, a2, b2, c2;
    cout << "Введите коэффициенты первого уравнения (a1 b1 c1): ";
    cin >> a1 >> b1 >> c1;
    cout << "Введите коэффициенты второго уравнения (a2 b2 c2): ";
    cin >> a2 >> b2 >> c2;

    double determinant = a1 * b2 - a2 * b1;

    if (determinant == 0) {
        cout << "Система не имеет единственного решения (определитель = 0)" << endl;
        logAction("Попытка решить вырожденную систему уравнений");
        return;
    }

    double x = (c1 * b2 - c2 * b1) / determinant;
    double y = (a1 * c2 - a2 * c1) / determinant;

    cout << "Решение системы: x = " << x << ", y = " << y << endl;
    logAction("Решена система линейных уравнений");
}

// Вычисление факториала
void calculateFactorial() {
    int n;
    cout << "Введите целое неотрицательное число: ";
    cin >> n;

    if (n < 0) {
        cout << "Факториал определен только для неотрицательных чисел!" << endl;
        logAction("Попытка вычислить факториал отрицательного числа");
        return;
    }

    unsigned long long factorial = 1;
    for (int i = 1; i <= n; ++i) {
        if (factorial > numeric_limits<unsigned long long>::max() / i) {
            cout << "Переполнение при вычислении факториала!" << endl;
            logAction("Переполнение при вычислении факториала");
            return;
        }
        factorial *= i;
    }

    cout << n << "! = " << factorial << endl;
    logAction("Вычислен факториал числа " + to_string(n));
}

// Генерация чисел Фибоначчи
void generateFibonacci() {
    int n;
    cout << "Введите количество чисел Фибоначчи: ";
    cin >> n;

    if (n <= 0) {
        cout << "Количество чисел должно быть положительным!" << endl;
        logAction("Попытка сгенерировать неположительное количество чисел Фибоначчи");
        return;
    }

    vector<unsigned long long> fibSequence;
    fibSequence.push_back(0);
    if (n > 1) fibSequence.push_back(1);

    for (int i = 2; i < n; ++i) {
        unsigned long long next = fibSequence[i-1] + fibSequence[i-2];
        if (next < fibSequence[i-1]) { // Проверка на переполнение
            cout << "Переполнение при вычислении чисел Фибоначчи!" << endl;
            logAction("Переполнение при генерации чисел Фибоначчи");
            return;
        }
        fibSequence.push_back(next);
    }

    cout << "Последовательность Фибоначчи: ";
    for (int i = 0; i < fibSequence.size(); ++i) {
        cout << fibSequence[i];
        if (i != fibSequence.size() - 1) cout << ", ";
    }
    cout << endl;
    logAction("Сгенерирована последовательность Фибоначчи длиной " + to_string(n));
}

// Главное меню
void showMenu() {
    cout << "\nМеню математической программы:\n";
    cout << "1. Решение квадратного уравнения\n";
    cout << "2. Решение системы линейных уравнений 2x2\n";
    cout << "3. Вычисление факториала\n";
    cout << "4. Генерация чисел Фибоначчи\n";
    cout << "5. Выход\n";
    cout << "Выберите действие: ";
}

int main() {
    logAction("Программа запущена");

    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                solveQuadraticEquation();
                break;
            case 2:
                solveLinearSystem();
                break;
            case 3:
                calculateFactorial();
                break;
            case 4:
                generateFibonacci();
                break;
            case 5:
                cout << "Выход из программы..." << endl;
                logAction("Программа завершена");
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
                logAction("Неверный выбор в меню");
                break;
        }
    } while (choice != 5);

    return 0;
}
