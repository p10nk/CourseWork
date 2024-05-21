#include "inpPatient.h"
#include <sstream>
#include "writeAndReadCabinetDataFile.h"
#include "writeAndReadPatientDataFile.h"
using namespace std;

bool isNumber(const string& line) {
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
    if (d < 24 || d > 27) {
        return false;
    }

    // Если все проверки прошли, то дата действительна
    return true;
}

static bool isValidName(string& name)
{
    if (name.length() > 30) {
        return false;
    }
    for (char c : name) {
        if (isdigit(c)) {
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
    if (y == 2024 && m > 5) {
        return false;
    }

    // Проверяем день
    if (d < 1 || d > daysInMonth(m, y)) {
        return false;
    }

    // Если год равен 2024 и месяц равен 1, то день должен быть не больше 10
    if (y == 2024 && m == 5 && d > 24) {
        return false;
    }

    // Если все проверки прошли, то дата рождения действительна
    return true;
}

bool isAvalidId(int a, int b, int n, vector<int> myIdies)
{
    //cout <<" "<< a << " " << b <<" "<< n << " "<< myIdies.size();
    if (myIdies.size() > n) { return false; }
    //std::cout << endl<<"yes"<<endl;
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

	string buf_fname;
    string buf_lname;
    string buf_surname;
    string date;
    int buf_dayBirth;
    int buf_monthBirth;
    int buf_yearBirth;
    int buf_dayZapis;
    int buf_monthZapis;
    int buf_yearZapis;
    int buf_hours;
    int buf_minutes;
    int cabNum;
    
	cout << "Введите имя: "; //символы, длина меньше 30
	//std::getline(std::cin, buf_fname);
    cin >> buf_fname;
    if (!isValidName(buf_fname)) {
        cout<<"Неккоректный ввод имени. ";
        return false;
    }

    cout << "Введите фамилию: ";
    //std::getline(std::cin, buf_lname);
    cin >> buf_lname;
    if (!isValidName(buf_lname)) {
        cout<<"Неккоректный ввод фамилии. ";
        return false;
    }

    cout << "Введите отчество: ";
    //std::getline(std::cin, buf_surname);
    cin >> buf_surname;
    if (!isValidName(buf_surname)) {
        cout<<"Неккоректный ввод отчества. ";
        return false;
    }

    cout << "Введите дату рождения в формате ДД.MM.ГГГГ: ";
    cin >> date;
    char dot1; char dot2;
    istringstream ss(date);
    ss >> buf_dayBirth >> dot1 >> buf_monthBirth >> dot2 >> buf_yearBirth;
    if ((!ss || dot1 != '.' || dot2 != '.' || buf_monthBirth <= 0 || buf_dayBirth <= 0 || buf_yearBirth <= 0 ||
        buf_monthBirth > 12 || buf_dayBirth > 31) || (!isValidDateBirth(buf_dayBirth, buf_monthBirth, buf_yearBirth))) {
        cout << "Некорректный формат даты рождения. ";
        return false;
    }

    cout << "Введите номер кабинета: ";
    cin >> cabNum;
  
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    cout << cabNum<<endl;
    
    
    if (cin.fail()) {
        cin.clear(); // очистить флаг ошибки
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
       // игнорировать оставшийся ввод
        cout << "Введено некорректное значение. ";
        return false;
    }
   
    if (cabNum < 0 || cabNum > 10) { 
        cout << "Такого кабинета не существует. ";
        return false; 
    }

    cout << "Введите дату записи формате ДД.MM.ГГГГ: ";
    cin >> date;
    istringstream ss1(date);
    ss1 >> buf_dayZapis >> dot1 >> buf_monthZapis >> dot2 >> buf_yearZapis;
    if ((!ss || dot1 != '.' || dot2 != '.' || buf_monthZapis <= 0 || buf_dayZapis <= 0 || buf_yearZapis <= 0 ||
        buf_monthZapis > 12 || buf_dayZapis > 31) || (!isValidDateForZapisi(buf_dayZapis, buf_monthZapis, buf_yearZapis))) {
        cout << "Некорректный формат даты записи. ";
        return false;
    }

    //int hours, int minutes;
    cout << "Введите время для записи в форматее чч.мм: ";
    cin >> date;
    istringstream ss2(date);
    ss2 >> buf_hours >> dot1 >> buf_minutes;
    if (!ss || dot1 != '.' || buf_hours < 0 || buf_minutes < 0 || buf_hours > 23 || buf_minutes > 59) {
        cout << "Такой формат времени не возможен. ";
        return false;
    }

    Date buf_Birth(buf_dayBirth, buf_monthBirth, buf_yearBirth, 0, 0);
    Date buf_Zapis(buf_dayZapis, buf_monthZapis, buf_yearZapis, buf_hours, buf_minutes);
    
    vector<Cabinet> cabinets; readCabinetsFromFile(cabinets);
    vector<Patient> patients; readPatientsFromFile(patients);

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

    for (size_t i = 0; i < patients.size(); i++) {
        if (patients[i].getCabForZapisi() == cabNum &&
            patients[i].getDateZapis().getDay() == buf_Zapis.getDay() &&
            patients[i].getDateZapis().getMonth() == buf_Zapis.getMonth() &&
            patients[i].getDateZapis().getYear() == buf_Zapis.getYear() &&
            patients[i].getDateZapis().getHour() == buf_Zapis.getHour() &&
            patients[i].getDateZapis().getMinutes() == buf_Zapis.getMinutes()) {
            cout << "Запись занята.";
            return false;
        }
    }
    writeCabinetsFromFile(cabinets);
 
    Patient NewPatient(buf_fname, buf_lname, buf_surname, buf_Birth, buf_Zapis);
    patient = NewPatient; patient.setCabForZapisi(cabNum);
    return true;
}

bool dellPatient(vector<Patient> patients)
{
    int numCab;
    int buf_dayZapis;
    int buf_monthZapis;
    int buf_yearZapis;
    int buf_hours;
    int buf_minutes;
    string date;
    char dot1, dot2;

    cout << "Выберите кабинет: ";
    cin >> numCab;
    if (cin.fail()) {
        cin.clear(); // очистить флаг ошибки
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорировать оставшийся ввод
        cout << "Введено некорректное значение. ";
        return false;
    }
    cin.ignore();
    if (numCab < 1 || numCab > 10) {
        cout << "Такого кабинета нет. ";
        return false;
    }

    cout << "Введите время дату записи в форматее ДД.ММ.ГГГГ: ";
    cin >> date;
    istringstream ss1(date);
    ss1 >> buf_dayZapis >> dot1 >> buf_monthZapis >> dot2 >> buf_yearZapis;
    if ((!ss1 || dot1 != '.' || dot2 != '.' || buf_monthZapis <= 0 || buf_dayZapis <= 0 || buf_yearZapis <= 0 ||
        buf_monthZapis > 12 || buf_dayZapis > 31) || (!isValidDateForZapisi(buf_dayZapis, buf_monthZapis, buf_yearZapis))) {
        cout << "Неверный формат даты записи. ";
        return false;
    }


    cout << "Введите время для записи в форматее чч.мм: ";
    cin >> date;
    istringstream ss2(date);
    ss2 >> buf_hours >> dot1 >> buf_minutes;
    if (!ss2 || dot1 != '.' || buf_hours < 0 || buf_minutes < 0 || buf_hours > 23 || buf_minutes > 59) {
        cout << "Такой формат времени не возможен. ";
        return false;
    }

    bool resDel = false;
    vector<Cabinet> cabinets; readCabinetsFromFile(cabinets);
    for (size_t j = 0; j < cabinets[numCab - 1].getZapisi().size(); j++) {
        if (buf_dayZapis == cabinets[numCab - 1].getZapisi()[j].getDate().getDay() &&
            buf_monthZapis == cabinets[numCab - 1].getZapisi()[j].getDate().getMonth() &&
            buf_yearZapis == cabinets[numCab - 1].getZapisi()[j].getDate().getYear() &&
            buf_hours == cabinets[numCab - 1].getZapisi()[j].getDate().getHour() &&
            buf_minutes == cabinets[numCab - 1].getZapisi()[j].getDate().getMinutes()) {
            if (cabinets[numCab - 1].zapisi[j].isBusy() == 1) {
                cabinets[numCab - 1].zapisi[j].setBusy(0);
                resDel = true;
                }
            //cabinets[numCab - 1].zapisi[j].printZapisWithFreeOrNot();
        }
    }
    if (resDel == false) {
        cout << "Запись не найдена. " <<endl;
    }
    else {
        cout << "Запись очищена. " <<endl;
    }


    writeCabinetsFromFile(cabinets);
    vector<Patient> myPatients;
    readPatientsFromFile(myPatients);
    ofstream file("E:/grsu/Курсоваяc++/MedecineProject/MedecineProjcet/MedecineProjcet/patients.txt", std::ios::out);
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
    string date;
    string line;
    int numCab;
    char dot1, dot2;
    cout << "Выберите кабинет: ";
    cin >> numCab;
    if (cin.fail()) {
        cin.clear(); // очистить флаг ошибки
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // игнорировать оставшийся ввод
        cout << "Введено некорректное значение. ";
        return false;
    }
    cin.ignore();
    if (numCab < 1 || numCab > 10) {
        cout << "Такого кабинета нет. ";
        return false;
    }

    cout << "Введите время записи в формате ДД.ММ.ГГГГ: ";
    cin >> date;
    istringstream ss1(date);
    ss1 >> buf_dayZapis >> dot1 >> buf_monthZapis >> dot2 >> buf_yearZapis;
    if ((!ss1 || dot1 != '.' || dot2 != '.' || buf_monthZapis <= 0 || buf_dayZapis <= 0 || buf_yearZapis <= 0 ||
        buf_monthZapis > 12 || buf_dayZapis > 31) || (!isValidDateForZapisi(buf_dayZapis, buf_monthZapis, buf_yearZapis))) {
        cout << "Неверный формат даты записи. ";
        return false;
    }


    cout << "Введите время для записи в форматее чч.мм: ";
    cin>> date;
    istringstream ss2(date);
    ss2 >> buf_hours >> dot1 >> buf_minutes;
    if (!ss2 || dot1 != '.' || buf_hours < 0 || buf_minutes < 0 || buf_hours > 23 || buf_minutes > 59) {
        cout << "Такой формат времени не возможен. ";
        return false;
    }

    vector<Cabinet> cabinets; readCabinetsFromFile(cabinets);
    vector<Patient> patients; readPatientsFromFile(patients);

    //Чтение всех ID болезней
    ifstream file("E:/grsu/Курсоваяc++/MedecineProject/MedecineProjcet/MedecineProjcet/IDdeseases.txt");
    if (!file.is_open()) {
        cout << "Не удалось открыть файл" << endl;
        return false;
    }
    vector<string> deseases; string desease;
    while (getline(file, line)) {
        if (line.substr(0, 7) == "numcab:") {
                getline(file, line);
                while (line != "------------------------------------------") {
                    istringstream ss(line);
                    ss.ignore(4); ss >> desease;
                    deseases.push_back(desease);
                   // std::cout << desease << "\n";
                    getline(file, line);
                }
        }
    }
    file.close();
  
    
    cout<<"Врач: "<<cabinets[numCab - 1].getDoctor()<<endl;
    cout << "Выявляемые болезни: ";

    for (int id : cabinets[numCab-1].getIdDeseases()) {
        cout << deseases[id-1] << ";";
    }

    ifstream file2("E:/grsu/Курсоваяc++/MedecineProject/MedecineProjcet/MedecineProjcet/IDservices.txt");
    if (!file2.is_open()) {
        cout << "Не удалось открыть файл" << endl;
        return false;
    }
    
    //Чтение всех ID лечений
    vector<string> services; string service;
    while (getline(file2, line)) {
        if (line.substr(0, 7) == "numcab:") {
            getline(file2, line);
            while (line != "------------------------------------------" && !file2.eof()) {
                size_t pos = line.find("-");
                if (pos != string::npos) {
                    service = line.substr(pos + 1);
                }
                services.push_back(service);
                getline(file2, line);
            }
        }
    }
    file2.close();
    

    cout << endl<<"Оказываемые услуги: ";
    for (int id : cabinets[numCab - 1].getIdServices()) {
        cout << services[id-1] << ";";
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
      
        cout << endl<<"Пациент: " << patients[res].getFname() << " " << patients[res].getSurname() <<" "<< patients[res].getLname() << endl;
        cout << "Дата рождения: "; patients[res].getDateBirth().printDateWithoutHoursAndMinutes();
        ifstream file("E:/grsu/Курсоваяc++/MedecineProject/MedecineProjcet/MedecineProjcet/IDdeseases.txt");
        if (!file.is_open()) {
            cout << "Не удалось открыть файл" << endl;
            return false;
        }
        
        vector<int> indD; 
        int val_ind;
        ifstream file3("E:/grsu/Курсоваяc++/MedecineProject/MedecineProjcet/MedecineProjcet/IDdeseases.txt");
        if (!file.is_open()) {
            cout << "Не удалось открыть файл" << endl;
            return false;
        }
       
        while (getline(file, line)) {
            if (line.substr(0, 7) == "numcab:") {
                if (stoi(line.substr(7)) == numCab) {
                    getline(file, line);
                    while (line != "------------------------------------------") {
                        istringstream ss(line);
                        ss >> val_ind;
                        indD.push_back(val_ind);
                        //std::cout << val_ind << endl;
                        getline(file, line);
                    }
                    break;
                }
            }
        }
        file3.close();


        cout << endl<<"Варианты диагноза: "<<endl;
        for (size_t i = 0; i < indD.size(); i++) {
            cout << indD[i] <<" - "<< deseases[indD[i]-1]<<endl;
        }
        cout << "Выберите диагно(з/зы) числами в строку: ";
        vector<int> myIDforPatient;
        string deseasesForPatient; cin>> deseasesForPatient;
        if (isNumber(deseasesForPatient)) {
            //std::cout << "yes"<<endl;
            stringstream ss(deseasesForPatient);
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
                cout << "Индекс в недоступном диапазоне. "<<endl;
                return false;
            }
            
        }
        else {
            cout << "Введенны не числа. "<<endl;
            return false;
        }
        //std::cout << "\n";
    //---------------------------------
        indD.clear();
        
        ifstream file4("E:/grsu/Курсоваяc++/MedecineProject/MedecineProjcet/MedecineProjcet/IDservices.txt");
        if (!file4.is_open()) {
            cout << "Не удалось открыть файл" << endl;
            return false;
        }

        while (getline(file4, line)) {
            if (line.substr(0, 7) == "numcab:") {
                if (stoi(line.substr(7)) == numCab) {
                    getline(file4, line);
                    while (line != "------------------------------------------") {
                        istringstream ss(line);
                        ss >> val_ind;
                        indD.push_back(val_ind);
                        //std::cout << val_ind << endl;
                        getline(file4, line);
                    }
                    break;
                }
            }
        }
        file4.close();

        
    //---------------------------------
        cout << "Варианты лечения: "<<endl;
        for (size_t i = 0; i < indD.size(); i++) {
            cout << indD[i] << " - " << services[indD[i] - 1] << endl;
        }

        cout << "Выберите лечение числами в строку: ";
        myIDforPatient.clear();
        string servicesForPatient; cin>> servicesForPatient;
        if (isNumber(servicesForPatient)) {
            //std::cout << "yes\n";
            stringstream ss(servicesForPatient);
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
                cout << "Индекс в недоступном диапазоне. ";
                return false;
            }
            patients[res].printPatient();

        }
        else {
            cout << "Введенны не числа. "<<endl;
            return false;
        }

        ofstream file5("E:/grsu/Курсоваяc++/MedecineProject/MedecineProjcet/MedecineProjcet/patients.txt", std::ios::out);
        file5.close();
        for (size_t i = 0; i < patients.size(); i++) {
            writePatientInFile(patients[i]);
        }
     
        cout << endl;
       
    }
    else {
        cout << endl<<"Такой пациент не найден. "<<endl;
        return false;
    }

    return true;
}
