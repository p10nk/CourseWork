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
#include <Windows.h>
#undef min
#undef max
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
       
        cout << ":>> "; cin >> command; //enter com
        if (command == "showc") {
            cout << "1. Терапевт"<<endl;
            cout << "2. Хирург"<<endl;
            cout << "3. Кардиолог"<<endl;
            cout << "4. Гастроэнтеролог"<<endl;
            cout << "5. Офтальмолог"<<endl;
            cout << "6. Оториноларинголог"<<endl;
            cout << "7. Дерматолог"<<endl;
            cout << "8. Невролог"<<endl;
            cout << "9. Психиатр"<<endl;
            cout << "10. Стоматолог"<<endl;
            vector<Cabinet> cabinets;
            if (!readCabinetsFromFile(cabinets)) {
                cout << endl<<"Не удалось прочитать кабинета, попробуйте ещё раз.";
            }
            else {
                int num; cout << "Введите номер кабинета: "; cin >> num; cin.ignore();
                if (cin.fail()) {
                    cin.clear(); // очистить флаг ошибки
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                   
                    cout << "Введено некорректное значение. Пожалуйста, введите число." <<endl;
                }
                else if (num > 0 && num < 11) {
                    cabinets[num - 1].printCabinet();
                }
                else {
                    cout << "Такого кабинета нет, попробуйте снова." <<endl;
                }
            }
        }
        if (command == "takp") {
            if (takePatient()) {
                cout << "Приём завершен." <<endl;
            }
            else {
                cout << "Попробуйте ещё раз." << endl;
            }
        }
        if (command == "shallp") {    //add comparing command 
            vector<Patient> myPatients;
            if (readPatientsFromFile(myPatients) == true) {
                if (myPatients.size() == 0) {
                    cout<<"Список пуст." << endl;
                }
                else {
                    int currentPage = 0;  int totalPages = (myPatients.size() + 4) / 5;
                    while (true) {
                        for (int i = currentPage * 5; i < (currentPage + 1) * 5 && i < myPatients.size(); ++i) {
                            myPatients[i].printPatient();
                            cout << endl<<"------------------" << endl;
                        }
                        cout << endl;
                        cout << "Страница " << (currentPage + 1) << " из " << totalPages << endl;
                        cout << "Y - смотреть следующую страницу: ";
                        char choice;
                        cin >> choice;
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if (choice == 'y' || choice == 'Y') {
                            currentPage++;
                            if (currentPage * 5 >= myPatients.size()) {
                                cout << "Это была последняя страница." <<endl;
                                break;
                            }
                        }
                        else {
                            cout << "Просмотр окончен. "<<endl;
                            break;
                        }
                    }
                    /*for (auto patient : myPatients) {
                        patient.printPatient();
                        cout << endl<<"------------------" << endl;
                    }*/

                }
            }
            else {
                cout << endl<<"Не удалось прочитать пациентов, попробуйте ещё раз." << endl;
            }
        }
        if (command == "addp") {    //add comparing command &&
            Patient myPatient;
            bool res = addPatient(myPatient);
            if (res == true && writePatientInFile(myPatient)) {
                //myPatient.printPatient();
                cout << "Запись прошла успешна." << endl;
            }
            else {
                cout << "Попробуйте ещё раз." << endl;
            }
        }
        if (command == "delp") {
            vector<Patient> patients;
            if (readPatientsFromFile(patients)) {
                if (!dellPatient(patients)) {
                    cout << "Попробуйте ещё раз." <<endl;
                }
            }
            else {
                std::cout << "Не удалось считать файл. Попробуйте снова." <<endl;
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
    SetConsoleCP(1251); // Console input encoded in 1251
    SetConsoleOutputCP(1251);
    printGreetingAndInfoCommands();
    RunMedecineService();

    return 0;
}
