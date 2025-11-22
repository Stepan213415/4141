#define WIN32_LEAN_AND_MEAN // <--- Додайте це
#include <windows.h>


// 2. Потім стандартні бібліотеки C++
#include <iostream>
#include <iomanip>
#include <locale.h>

// 3. В самому кінці — ваші власні файли
#include "lift.hpp"

using namespace std;

void clearScreen() {
    system("cls");
}

void printLiftState(const Lift& lift) {
    cout << "---------------------------------\n";
    cout << "           СТАН ЛІФТА          \n";
    cout << "---------------------------------\n";
    cout << " Загальний стан: " << lift.GetGeneralStateName() << "\n";
    cout << " Стан двигуна: " << lift.GetEngineStateName() << "\n";
    cout << " Стан дверей: " << lift.GetDoorStateName() << "\n";
    cout << " Поточний поверх: " << lift.GetCurrentFloor() << "\n";
    cout << " Цільовий поверх: " << lift.GetTargetFloor() << "\n";
    cout << fixed << setprecision(1);
    cout << " Навантаження: " << lift.GetCurrentLoad() << " кг\n";
    cout << "---------------------------------\n\n";
}

void printMenu() {
    cout << "         ПУЛЬТ КЕРУВАННЯ (варіант 5)         \n";
    cout << "1. Старт виклику   →  lift(поверх); ++lift\n";
    cout << "2. Кінець виклику  →  --lift\n";
    cout << "3. Завантаження    →  lift += вага\n";
    cout << "4. Запуск з кабіни (на поверх)\n";
    cout << "5. Стоп (прибуття)\n";
    cout << "0. Скинути стан (Reset)\n";
    cout << "q. Вихід\n\n";
    cout << "Ваш вибір: ";
}

int main() {
    setlocale(LC_ALL, "Ukrainian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Lift myLift;
    char choice;
    int floor;
    double load;

    do {
        clearScreen();
        printLiftState(myLift);
        printMenu();

        cin >> choice;

        switch (choice) {
            case '1': { // Старт виклику через оператори
                cout << "Введіть цільовий поверх (1-24): ";
                cin >> floor;
                myLift(floor);   // встановлюємо цільовий поверх
                ++myLift;        // старт виклику
                break;
            }
            case '2': // Кінець виклику
                --myLift;
                break;

            case '3': // Завантаження кабіни
                cout << "Введіть навантаження (кг): ";
                cin >> load;
                myLift += load;
                break;

            case '4': // Запуск з кабіни (залишаємо старий метод)
                cout << "Введіть цільовий поверх (1-24): ";
                cin >> floor;
                myLift.Start(floor);
                break;

            case '5':
                myLift.Stop();
                break;

            case '0':
                myLift.Reset();
                break;

            case 'q':
            case 'Q':
                cout << "Завершення роботи.\n";
                break;

            default:
                cout << "Некоректний вибір. Натисніть Enter...";
                cin.clear();
                cin.ignore(10000, '\n');
                cin.get();
                break;
        }

    } while (choice != 'q' && choice != 'Q');

    cout << "\nНатисніть Enter для виходу...";
    cin.get();
    return 0;
}
