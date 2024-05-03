// MedecineProjcet.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstring>
#include <cstdlib> // для завершения я закрытия программы
#include <string>
#include "inpPatient.h"
#include "Patient.h"
#include "writeAndReadPatientDataFile.h"
#include "Cabinet.h"
#include "writeAndReadCabinetDataFile.h"

using namespace std;

void printGreetingAndInfoCommands() {
    cout << ".................................................." << endl;
    cout << ": Добро пожаловать в систему <<MedecineService>> :" << endl;
    cout << "::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
    cout << ":                                                :" << endl;
    cout << ": записать пациента на приём - addp              :" << endl;
    cout << ": показать карточки всех пациентов - shallp      :" << endl;
    cout << ": очистить очередь на приём - delp               :" << endl;
    cout << ": принять на приём пациента - takp               :" << endl;
    cout << ": получить информацию о кабинетах - showc        :" << endl;
    cout << ": Для завершения работы программы введите - exit :" << endl;
    cout << ":                                                :" << endl;
    cout << ".................................................." << endl;
}


void RunMedecineService() {

    string command; 
    do {
        cout << ":>> "; getline(cin, command); //enter com
        if (command == "showc") {
            std::cout << "1. Терапевт\n";
            std::cout << "2. Хирург\n";
            std::cout << "3. Кардиолог\n";
            std::cout << "4. Гастроэнтеролог\n";
            std::cout << "5. Офтальмолог\n";
            std::cout << "6. Оториноларинголог\n";
            std::cout << "7. Дерматолог\n";
            std::cout << "8. Невролог\n";
            std::cout << "9. Психиатр\n";
            std::cout << "10. Стоматолог\n";
            std::vector<Cabinet> cabinets;
            if (!readCabinetsFromFile(cabinets)) {
                cout << "\nНе удалось прочитать кабинета, попробуйте ещё раз.";
            }
            else {
                int num; std::cout << "Введите номер кабинета: "; std::cin >> num; std::cin.ignore();
                if (std::cin.fail()) {
                    std::cin.clear(); // очистить флаг ошибки
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорировать оставшийся ввод
                    std::cout << "Введено некорректное значение. Пожалуйста, введите число.\n";
                }
                else if (num > 0 && num < 11) {
                    cabinets[num - 1].printCabinet();
                }
                else {
                    std::cout << "Такого кабинета нет, попробуйте снова.\n";
                }
            }
        }
        if (command == "takp") {
            if (takePatient()) {
                std::cout << "Приём завершен.\n";
            }
        }
        if (command == "shallp") {    //add comparing command 
            vector<Patient> myPatients;
            if (readPatientsFromFile(myPatients) == true) {
                for (auto patient : myPatients) {
                    patient.printPatient();
                    cout << "\n------------------" << endl;
                }
            }
            else {
                cout << "\nНе удалось прочитать пациентов, попробуйте ещё раз." << endl;
            }
        }
        if (command == "addp") {    //add comparing command &&
            Patient myPatient;
            bool res = addPatient(myPatient);
            if (res == true && writePatientInFile(myPatient)) {
                //myPatient.printPatient();
                cout << "\nЗапись прошла успешна." << endl;
            }
            else {
                cout << "\nНе удалось записать пациента в бд, попробуйте ещё раз." << endl;
            }
        }
        if (command == "delp") {
            std::vector<Patient> patients;
            if (readPatientsFromFile(patients)) {
                dellPatient(patients);
            }
            else {
                std::cout << "Не удалось очистить запись, попробуйте снова.";
            }
        }
        
        if (command != "exit" && command != "addp" && command != "shallp" && command != "showc" &&
            command != "delp" && command != "takp") {    //add comparing command &&
            cout << "Неизвестная команда. Попробуйте ещё раз." << endl;
        }
        else if (command == "exit") {
            cout << "Завершение программы." << endl;
            exit(0); // завершает выполнение программы
        }
    } while (command != "exit");
}


int main()
{
    setlocale(LC_ALL, "Ru");
    printGreetingAndInfoCommands();
    RunMedecineService();

    return 0;
}
