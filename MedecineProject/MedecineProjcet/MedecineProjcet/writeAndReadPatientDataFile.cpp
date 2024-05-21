#include "writeAndReadPatientDataFile.h"
using namespace std;

bool writePatientInFile(Patient& patient)
{
    setlocale(LC_ALL, "Ru");
    ofstream file("E:/grsu/Курсоваяc++/MedecineProject/MedecineProjcet/MedecineProjcet/patients.txt", std::ios::app);
    if (!file)
    {
        cout << "Не удалось открыть файл. "<<endl;
        return false;
    }
    file << endl<<"------------------" << endl;
    file << "fname:" << patient.getFname()  << endl
        << "lname:" << patient.getLname() << endl
        << "surname:" << patient.getSurname() << endl
        << "dateBirth: " << patient.getDateBirth().getDateStringFormat() << endl
        << "cabForZapisi: " << patient.getCabForZapisi() << endl
        << "dateZapis: " << patient.getDateZapis().getDateStringFormat() << endl
        << "IDDeseases: ";

    for (int id : patient.getidDiseases())
    {
        file << id << ", ";
    }
    file << endl;

    file << "IDServices: ";
    for (int id : patient.getidServices())
    {
        file << id << ", ";
    }
    

    file.close();
    return true;
}

bool readPatientsFromFile(std::vector<Patient>& patients) {
    setlocale(LC_ALL, "Ru");
    ifstream file("E:/grsu/Курсоваяc++/MedecineProject/MedecineProjcet/MedecineProjcet/patients.txt");
    if (!file.is_open()) {
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line == "------------------") {
            Patient myPatient;
            getline(file, line);
            //std::cout << "Reading from file: " << line.substr(line.find(":") + 1)<<endl;
            myPatient.setFname(line.substr(line.find(":") + 1));    //fname

            std::getline(file, line);
            //std::cout << "Reading from file: " << line.substr(line.find(": ") + 1)<<endl;
            myPatient.setLname(line.substr(line.find(":") + 1));  //lname

            getline(file, line);
            //std::cout << "Reading from file: " << line.substr(line.find(": ") + 1)<<endl;
            myPatient.setSurname(line.substr(line.find(":") + 1));  //surname

            
            getline(file, line);    //std::cout << "Reading from file: " << line << endl;
            char dot;
            unsigned int buf_day, buf_month, buf_year, buf_hour, buf_minutes;   //initilazation
            istringstream ss1(line.substr(line.find(": ") + 1));
            ss1 >> buf_day >> dot >> buf_month >> dot >> buf_year;
            myPatient.setDateBirth(Date(buf_day, buf_month, buf_year, 0, 0));

            getline(file, line);   int num = std::stoi(line.substr(line.find(": ") + 1));
            //std::cout << "Reading from file2: " << num << endl;
            myPatient.setCabForZapisi(num);
      

            getline(file, line);
            //std::cout << "Reading from file: " << line << endl;
            istringstream ss2(line.substr(line.find(": ") + 1));
            ss2 >> buf_day >> dot >> buf_month >> dot >> buf_year >> dot >> buf_hour >> dot >> buf_minutes;
            myPatient.setDateZapis(Date(buf_day, buf_month, buf_year, buf_hour, buf_minutes));

            getline(file, line);
            stringstream ss3(line.substr(line.find(": ") + 1));
            
            for (int i; ss3 >> i;) {
                myPatient.addDisease(i);
                if (ss3.peek() == ',')
                    ss3.ignore();
            }
            

            getline(file, line);
            stringstream ss4(line.substr(line.find(": ") + 1));
            for (int i; ss4 >> i;) {
                myPatient.addService(i);
                if (ss4.peek() == ',')
                    ss4.ignore();
            }
            
            //std::cout << endl<<"========="<<endl;
            patients.push_back(myPatient);
        }
    }

    file.close();
    return true;
}


