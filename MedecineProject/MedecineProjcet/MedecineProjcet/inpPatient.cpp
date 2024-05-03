#include "inpPatient.h"
#include <sstream>
#include "writeAndReadCabinetDataFile.h"
#include "writeAndReadPatientDataFile.h"

bool isNumber(const std::string& line) {
    for (char c : line) {
        if (!isdigit(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

bool isValidDateForZapisi(int& d, int& m, int& y)
{
    // Проверяем год
    if (y != 2024) {
        return false;
    }

    // Проверяем месяц
    if (m != 5) {
        return false;
    }

    // Проверяем день
    if (d < 1 || d > 5) {
        return false;
    }

    // Если все проверки прошли, то дата действительна
    return true;
}

static bool isValidName(std::string& name)
{
    if (name.length() > 30) {
        return false;
    }
    for (char c : name) {
        if (std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

static bool isLeapYear(int& year) {
    return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
}

static int daysInMonth(int& month, int& year)
{
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    else {
        return 31;
    }
}

static bool isValidDateBirth(int& d, int& m, int& y)
{
    // Проверяем год
    if (y < 1920 || y > 2024) {
        return false;
    }

    // Проверяем месяц
    if (m < 1 || m > 12) {
        return false;
    }

    // Если год равен 2024, то месяц должен быть не больше 1 (январь)
    if (y == 2024 && m > 1) {
        return false;
    }

    // Проверяем день
    if (d < 1 || d > daysInMonth(m, y)) {
        return false;
    }

    // Если год равен 2024 и месяц равен 1, то день должен быть не больше 10
    if (y == 2024 && m == 1 && d > 10) {
        return false;
    }

    // Если все проверки прошли, то дата рождения действительна
    return true;
}

bool isAvalidId(int a, int b, int n, std::vector<int> myIdies)
{
    //std::cout <<" "<< a << " " << b <<" "<< n << " "<< myIdies.size();
    if (myIdies.size() > n) { return false; }
    //std::cout << "\nyes\n";
    for (auto& el : myIdies) {
        if (el < a || el > b) {
            return false;
        }
    }

    return true;
}

bool addPatient(Patient& patient)
{
	setlocale(LC_ALL, "Ru");

	std::string buf_fname;
    std::string buf_lname;
    std::string buf_surname;
    std::string date;
    int buf_dayBirth;
    int buf_monthBirth;
    int buf_yearBirth;
    int buf_dayZapis;
    int buf_monthZapis;
    int buf_yearZapis;
    int buf_hours;
    int buf_minutes;

    int cabNum;
    

	std::cout << "Введите имя: "; //символы, длина меньше 30
	std::getline(std::cin, buf_fname);
    if (!isValidName(buf_fname)) {
        "Неккоректный ввод имени. Попробуйте снова.";
        return false;
    }

    std::cout << "Введите фамилию: ";
    std::getline(std::cin, buf_lname);
    if (!isValidName(buf_lname)) {
        "Неккоректный ввод фамилии. Попробуйте снова.";
        return false;
    }

    std::cout << "Введите отчество: ";
    std::getline(std::cin, buf_surname);
    if (!isValidName(buf_surname)) {
        "Неккоректный ввод отчества. Попробуйте снова.";
        return false;
    }

    std::cout << "Введите дату рождения в формате ДД.MM.ГГГГ: ";
    std::getline(std::cin, date);
    char dot1; char dot2;
    std::istringstream ss(date);
    ss >> buf_dayBirth >> dot1 >> buf_monthBirth >> dot2 >> buf_yearBirth;
    if ((!ss || dot1 != '.' || dot2 != '.' || buf_monthBirth <= 0 || buf_dayBirth <= 0 || buf_yearBirth <= 0 ||
        buf_monthBirth > 12 || buf_dayBirth > 31) || (!isValidDateBirth(buf_dayBirth, buf_monthBirth, buf_yearBirth))) {
        std::cout << "Неверный формат даты. Попробуйте снова.\n";
        return false;
    }

    std::cout << "Введите номер кабинета: ";
    std::cin >> cabNum; std::cin.ignore();
    if (std::cin.fail()) {
        std::cin.clear(); // очистить флаг ошибки
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорировать оставшийся ввод
        std::cout << "Введено некорректное значение. Пожалуйста, введите число.\n";
        return false;
    }
    if (cabNum < 0 || cabNum > 10) { return false; }

    std::cout << "Введите дату записи формате ДД.MM.ГГГГ: ";
    std::getline(std::cin, date);
    std::istringstream ss1(date);
    ss1 >> buf_dayZapis >> dot1 >> buf_monthZapis >> dot2 >> buf_yearZapis;
    if ((!ss || dot1 != '.' || dot2 != '.' || buf_monthZapis <= 0 || buf_dayZapis <= 0 || buf_yearZapis <= 0 ||
        buf_monthZapis > 12 || buf_dayZapis > 31) || (!isValidDateForZapisi(buf_dayZapis, buf_monthZapis, buf_yearZapis))) {
        std::cout << "Неверный формат даты записи. Попробуйте снова.\n";
        return false;
    }

    //int hours, int minutes;
    std::cout << "Введите время для записи в форматее чч.мм: ";
    std::getline(std::cin, date);
    std::istringstream ss2(date);
    ss2 >> buf_hours >> dot1 >> buf_minutes;
    if (!ss || dot1 != '.' || buf_hours < 0 || buf_minutes < 0 || buf_hours > 23 || buf_minutes > 59) {
        std::cout << "Такой формат времени не возможен. Попробуйте снова.\n";
        return false;
    }

    Date buf_Birth(buf_dayBirth, buf_monthBirth, buf_yearBirth, 0, 0);
    Date buf_Zapis(buf_dayZapis, buf_monthZapis, buf_yearZapis, buf_hours, buf_minutes);
    
    std::vector<Cabinet> cabinets; readCabinetsFromFile(cabinets);
    
    for (size_t i = 0; i < cabinets.size(); i++) {
        if (cabNum == cabinets[i].getNum()) {
            for (size_t j = 1; j < cabinets[i].getZapisi().size(); j++) {
                
                if (buf_dayZapis == cabinets[i].getZapisi()[j].getDate().getDay() &&
                    buf_monthZapis == cabinets[i].getZapisi()[j].getDate().getMonth() &&
                    buf_yearZapis == cabinets[i].getZapisi()[j].getDate().getYear() &&
                    buf_hours == cabinets[i].getZapisi()[j].getDate().getHour() &&
                    buf_minutes == cabinets[i].getZapisi()[j].getDate().getMinutes())
                {
                    Zapis myZ(buf_Zapis, 1);
                    cabinets[i].zapisi[j] = myZ;
                    //cabinets[i].printCabinet();
                    //std::cout << "\n";
                }
            }
        }
    }
    writeCabinetsFromFile(cabinets);
 
    Patient NewPatient(buf_fname, buf_lname, buf_surname, buf_Birth, buf_Zapis);
    patient = NewPatient; patient.setCabForZapisi(cabNum);
    return true;
}

bool dellPatient(std::vector<Patient> patients)
{   
    int numCab;
    int buf_dayZapis;
    int buf_monthZapis;
    int buf_yearZapis;
    int buf_hours;
    int buf_minutes;
    std::string date;
    char dot1, dot2;

    std::cout << "Выберите кабинет: "; 
    std::cin >> numCab;
    if (std::cin.fail()) {
        std::cin.clear(); // очистить флаг ошибки
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорировать оставшийся ввод
        std::cout << "Введено некорректное значение. Пожалуйста, введите число.\n";
        return false;
    }
    std::cin.ignore();
    if (numCab < 1 || numCab > 10) {
        std::cout << "Такого кабинета нет";
        return false;
    }

    setlocale(LC_ALL, "Ru");
    std::cout << "Введите время дату записи в форматее ДД.ММ.ГГГГ: ";
    std::getline(std::cin, date);
    std::istringstream ss1(date);
    ss1 >> buf_dayZapis >> dot1 >> buf_monthZapis >> dot2 >> buf_yearZapis;
    if ((!ss1 || dot1 != '.' || dot2 != '.' || buf_monthZapis <= 0 || buf_dayZapis <= 0 || buf_yearZapis <= 0 ||
        buf_monthZapis > 12 || buf_dayZapis > 31) || (!isValidDateForZapisi(buf_dayZapis, buf_monthZapis, buf_yearZapis))) {
        std::cout << "Неверный формат даты записи. Попробуйте снова.\n";
        return false;
    }


    std::cout << "Введите время для записи в форматее чч.мм: ";
    std::getline(std::cin, date);
    std::istringstream ss2(date);
    ss2 >> buf_hours >> dot1 >> buf_minutes;
    if (!ss2 || dot1 != '.' || buf_hours < 0 || buf_minutes < 0 || buf_hours > 23 || buf_minutes > 59) {
        std::cout << "Такой формат времени не возможен. Попробуйте снова.\n";
        return false;
    }

    std::vector<Cabinet> cabinets; readCabinetsFromFile(cabinets);
    for (size_t j = 0; j < cabinets[numCab - 1].getZapisi().size(); j++) {
        if (buf_dayZapis == cabinets[numCab - 1].getZapisi()[j].getDate().getDay() &&
            buf_monthZapis == cabinets[numCab - 1].getZapisi()[j].getDate().getMonth() &&
            buf_yearZapis == cabinets[numCab - 1].getZapisi()[j].getDate().getYear() &&
            buf_hours == cabinets[numCab - 1].getZapisi()[j].getDate().getHour() &&
            buf_minutes == cabinets[numCab - 1].getZapisi()[j].getDate().getMinutes()) {
            cabinets[numCab - 1].zapisi[j].setBusy(0);
            //cabinets[numCab - 1].zapisi[j].printZapisWithFreeOrNot();
        }
    }

    writeCabinetsFromFile(cabinets);
    std::vector<Patient> myPatients;
    readPatientsFromFile(myPatients);
    std::ofstream file("E:/grsu/Курсовая c++/MedecineProject/MedecineProjcet/MedecineProjcet/patients.txt", std::ios::out);
    file.close();

    for (size_t i = 0; i < myPatients.size(); i++) {
        if (myPatients[i].getCabForZapisi() == numCab &&
            myPatients[i].getDateZapis().getDay() == buf_dayZapis &&
            myPatients[i].getDateZapis().getMonth() == buf_monthZapis &&
            myPatients[i].getDateZapis().getYear() == buf_yearZapis &&
            myPatients[i].getDateZapis().getHour() == buf_hours &&
            myPatients[i].getDateZapis().getMinutes() == buf_minutes) {
            continue;
        }
        writePatientInFile(patients[i]);
    }
    return true;
}

bool takePatient()
{
    int buf_dayZapis;
    int buf_monthZapis;
    int buf_yearZapis;
    int buf_hours;
    int buf_minutes;
    std::string date;
    std::string line;
   
    char dot1, dot2;
    setlocale(LC_ALL, "Ru");
    std::cout << "Выберите кабинет: ";
    int numCab; std::cin >> numCab; std::cin.ignore();
    if (numCab < 0 || numCab > 10) {
        std::cout << "Такого кабинета нет, попробуйте снова.\n";
        return false;
    }

    std::cout << "Введите время записи в формате ДД.ЧЧ.ГГГГ: ";
    std::getline(std::cin, date);
    std::istringstream ss1(date);
    ss1 >> buf_dayZapis >> dot1 >> buf_monthZapis >> dot2 >> buf_yearZapis;
    if ((!ss1 || dot1 != '.' || dot2 != '.' || buf_monthZapis <= 0 || buf_dayZapis <= 0 || buf_yearZapis <= 0 ||
        buf_monthZapis > 12 || buf_dayZapis > 31) || (!isValidDateForZapisi(buf_dayZapis, buf_monthZapis, buf_yearZapis))) {
        std::cout << "Неверный формат даты записи. Попробуйте снова.\n";
        return false;
    }


    std::cout << "Введите время для записи в форматее чч.мм: ";
    std::getline(std::cin, date);
    std::istringstream ss2(date);
    ss2 >> buf_hours >> dot1 >> buf_minutes;
    if (!ss2 || dot1 != '.' || buf_hours < 0 || buf_minutes < 0 || buf_hours > 23 || buf_minutes > 59) {
        std::cout << "Такой формат времени не возможен. Попробуйте снова.\n";
        return false;
    }

    std::vector<Cabinet> cabinets; readCabinetsFromFile(cabinets);
    std::vector<Patient> patients; readPatientsFromFile(patients);

    //Чтение всех ID болезней
    std::ifstream file("E:/grsu/Курсовая c++/MedecineProject/MedecineProjcet/MedecineProjcet/IDdeseases.txt");
    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл" << std::endl;
        return false;
    }
    std::vector<std::string> deseases; std::string desease;
    while (std::getline(file, line)) {
        if (line.substr(0, 7) == "numcab:") {
                std::getline(file, line);
                while (line != "------------------------------------------") {
                    std::istringstream ss(line);
                    ss.ignore(4); ss >> desease;
                    deseases.push_back(desease);
                   // std::cout << desease << "\n";
                    std::getline(file, line);
                }
        }
    }
    file.close();
  
    
    std::cout<<"Врач: "<<cabinets[numCab - 1].getDoctor()<<"\n";
    std::cout << "Выявляемые болезни: ";

    for (int id : cabinets[numCab - 1].getIdDeseases()) {
        std::cout << deseases[id-1] << ";";
    }

    std::ifstream file2("E:/grsu/Курсовая c++/MedecineProject/MedecineProjcet/MedecineProjcet/IDservices.txt");
    if (!file2.is_open()) {
        std::cout << "Не удалось открыть файл" << std::endl;
        return false;
    }
    
    //Чтение всех ID лечений
    std::vector<std::string> services; std::string service;
    while (std::getline(file2, line)) {
        if (line.substr(0, 7) == "numcab:") {
            std::getline(file2, line);
            while (line != "------------------------------------------" && !file2.eof()) {
                size_t pos = line.find("-");
                if (pos != std::string::npos) {
                    service = line.substr(pos + 1);
                }
                services.push_back(service);
                std::getline(file2, line);
            }
        }
    }
    file2.close();
    

    std::cout << "\nОказываемые услуги: ";
    for (int id : cabinets[numCab - 1].getIdServices()) {
        std::cout << services[id-1] << ";";
    }

    int res = -1;
    for (size_t i = 0; i < patients.size(); i++) {
        if (patients[i].getCabForZapisi() == numCab) {
            if (patients[i].getDateZapis().getDay() == buf_dayZapis &&
                patients[i].getDateZapis().getMonth() == buf_monthZapis &&
                patients[i].getDateZapis().getYear() == buf_yearZapis &&
                patients[i].getDateZapis().getHour() == buf_hours &&
                patients[i].getDateZapis().getMinutes() == buf_minutes) {
                res = i;
            }
        }
    }
    if (res != -1) {
      
        std::cout << "\nПациент: " << patients[res].getFname() << " " << patients[res].getSurname() <<" "<< patients[res].getLname() << "\n";
        std::cout << "Дата рождения: "; patients[res].getDateBirth().printDateWithoutHoursAndMinutes();
        std::ifstream file("E:/grsu/Курсовая c++/MedecineProject/MedecineProjcet/MedecineProjcet/IDdeseases.txt");
        if (!file.is_open()) {
            std::cout << "Не удалось открыть файл" << std::endl;
            return false;
        }
        
        std::vector<int> indD; 
        int val_ind;
        std::ifstream file3("E:/grsu/Курсовая c++/MedecineProject/MedecineProjcet/MedecineProjcet/IDdeseases.txt");
        if (!file.is_open()) {
            std::cout << "Не удалось открыть файл" << std::endl;
            return false;
        }
       
        while (std::getline(file, line)) {
            if (line.substr(0, 7) == "numcab:") {
                if (std::stoi(line.substr(7)) == numCab) {
                    std::getline(file, line);
                    while (line != "------------------------------------------") {
                        std::istringstream ss(line);
                        ss >> val_ind;
                        indD.push_back(val_ind);
                        //std::cout << val_ind << "\n";
                        std::getline(file, line);
                    }
                    break;
                }
            }
        }
        file3.close();


        std::cout << "\nВарианты диагноза: \n";
        for (size_t i = 0; i < indD.size(); i++) {
            std::cout << indD[i] <<" - "<< deseases[indD[i]-1]<<"\n";
        }
        std::cout << "Выберите диагно(з/зы) числами в строку: ";
        std::vector<int> myIDforPatient;
        std::string deseasesForPatient; std::getline(std::cin, deseasesForPatient);
        if (isNumber(deseasesForPatient)) {
            //std::cout << "yes\n";
            std::stringstream ss(deseasesForPatient);
            int val;
            while (ss >> val) {
                myIDforPatient.push_back(val);
            }
            
            if (isAvalidId(indD[0], indD[indD.size() - 1],
                indD.size(), myIDforPatient)) {
                //std::cout << "Good for recoder!\n";
                for (size_t i = 0; i < myIDforPatient.size();i++) {
                    patients[res].addDisease(myIDforPatient[i]);
                }
          
            }
            else {
                std::cout << "Индекс в недоступном диапазоне, попробуйте снова.\n";
                return false;
            }
            
        }
        else {
            std::cout << "Введенны не числа, попробуйте снова.\n";
            return false;
        }
        //std::cout << "\n";
    //---------------------------------
        indD.clear();
        
        std::ifstream file4("E:/grsu/Курсовая c++/MedecineProject/MedecineProjcet/MedecineProjcet/IDservices.txt");
        if (!file4.is_open()) {
            std::cout << "Не удалось открыть файл" << std::endl;
            return false;
        }

        while (std::getline(file4, line)) {
            if (line.substr(0, 7) == "numcab:") {
                if (std::stoi(line.substr(7)) == numCab) {
                    std::getline(file4, line);
                    while (line != "------------------------------------------") {
                        std::istringstream ss(line);
                        ss >> val_ind;
                        indD.push_back(val_ind);
                        //std::cout << val_ind << "\n";
                        std::getline(file4, line);
                    }
                    break;
                }
            }
        }
        file4.close();

        
    //---------------------------------
        std::cout << "Варианты диагноза: \n";
        for (size_t i = 0; i < indD.size(); i++) {
            std::cout << indD[i] << " - " << services[indD[i] - 1] << "\n";
        }

        std::cout << "Выберите лечение числами в строку: ";
        myIDforPatient.clear();
        std::string servicesForPatient; std::getline(std::cin, servicesForPatient);
        if (isNumber(servicesForPatient)) {
            //std::cout << "yes\n";
            std::stringstream ss(servicesForPatient);
            int val;
            while (ss >> val) {
                myIDforPatient.push_back(val);
            }

            if (isAvalidId(indD[0], indD[indD.size() - 1],
                indD.size(), myIDforPatient)) {
                //std::cout << "Good for recoder!\n";
                for (size_t i = 0; i < myIDforPatient.size(); i++) {
                    patients[res].addService(myIDforPatient[i]);
                }
            }
            else {
                std::cout << "Индекс в недоступном диапазоне, попробуйте снова.\n";
                return false;
            }
            patients[res].printPatient();

        }
        else {
            std::cout << "Введенны не числа, попробуйте снова.\n";
            return false;
        }

        std::ofstream file5("E:/grsu/Курсовая c++/MedecineProject/MedecineProjcet/MedecineProjcet/patients.txt", std::ios::out);
        file5.close();
        for (size_t i = 0; i < patients.size(); i++) {
            writePatientInFile(patients[i]);
        }
     
        std::cout << "\n";
       
    }
    else {
        std::cout << "\nТакой пациент не найден.\n";
        return false;
    }

    return true;
}
