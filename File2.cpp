#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "lift.hpp"

using namespace std;

void clearScreen() {
    system("cls");
}

void printLiftState(const Lift& lift) {
    cout << "---------------------------------\n";
    cout << "           СТАН ЛІФТА           \n";
    cout << "---------------------------------\n";
    cout << " Загальний стан: " << lift.GetGeneralStateName() << "\n";
    cout << " Стан двигуна:   " << lift.GetEngineStateName() << "\n";
    cout << " Стан дверей:    " << lift.GetDoorStateName() << "\n";
    cout << " Поточний поверх:" << lift.GetCurrentFloor() << "\n";
    cout << " Цільовий поверх:" << lift.GetTargetFloor() << "\n";
    cout << fixed << setprecision(1);
    cout << " Навантаження:   " << lift.GetCurrentLoad() << " кг\n";
    cout << "---------------------------------\n\n";
}

void printMenu() {
    cout << "          ПУЛЬТ КЕРУВАННЯ         \n";
    cout << "1. Старт виклику  (lift(поверх); ++lift)\n";
    cout << "2. Кінець виклику (--lift)\n";
    cout << "3. Завантаження   (lift += вага)\n";
    cout << "4. Запуск з кабіни\n";
    cout << "5. Стоп (прибуття)\n";
    cout << "0. Скинути (Reset)\n";
    cout << "q. Вихід\n\n";
    cout << "Ваш вибір: ";
}

int main() {
    system("chcp 1251 > nul");

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
            case '1': {
                cout << "Введіть поверх (1-24): ";
                cin >> floor;
                myLift(floor);
                ++myLift;
                break;
            }
            case '2':
                --myLift;
                break;

            case '3':
                cout << "Введіть вагу (кг): ";
                cin >> load;
                myLift += load;
                break;

            case '4':
                cout << "Введіть поверх (1-24): ";
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
                cout << "До побачення!\n";
                break;

            default:
                cout << "Невірний вибір. Натисніть Enter...";
                cin.clear();
                cin.ignore(10000, '\n');
                cin.get();
                break;
        }

    } while (choice != 'q' && choice != 'Q');

    return 0;
}
