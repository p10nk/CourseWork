#include "writeAndReadPatientDataFile.h"

bool writePatientInFile(Patient& patient)
{
    std::ofstream file("E:/grsu/Курсовая c++/MedecineProject/MedecineProjcet/MedecineProjcet/patients.txt", std::ios::app);
    if (!file)
    {
        return false;
    }
    file << "\n------------------\n";
    file << "fname:" << patient.getFname() << "\n"
        << "lname:" << patient.getLname() << "\n"
        << "surname:" << patient.getSurname() << "\n"
        << "dateBirth: " << patient.getDateBirth().getDateStringFormat() << "\n"
        << "cabForZapisi: " << patient.getCabForZapisi() << "\n"
        << "dateZapis: " << patient.getDateZapis().getDateStringFormat() << "\n"
        << "IDDeseases: ";

    for (int id : patient.getidDiseases())
    {
        file << id << ", ";
    }
    file << "\n";

    file << "IDServices: ";
    for (int id : patient.getidServices())
    {
        file << id << ", ";
    }
    

    file.close();
    return true;
}

bool readPatientsFromFile(std::vector<Patient>& patients) {
    std::ifstream file("E:/grsu/Курсовая c++/MedecineProject/MedecineProjcet/MedecineProjcet/patients.txt");
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line == "------------------") {
            Patient myPatient;
            std::getline(file, line);
            //std::cout << "Reading from file: " << line.substr(line.find(":") + 1)<<"\n";
            myPatient.setFname(line.substr(line.find(":") + 1));    //fname

            std::getline(file, line);
            //std::cout << "Reading from file: " << line.substr(line.find(": ") + 1)<<"\n";
            myPatient.setLname(line.substr(line.find(":") + 1));  //lname

            std::getline(file, line);
            //std::cout << "Reading from file: " << line.substr(line.find(": ") + 1)<<"\n";
            myPatient.setSurname(line.substr(line.find(":") + 1));  //surname

            
            std::getline(file, line);    //std::cout << "Reading from file: " << line << "\n";
            char dot;
            unsigned int buf_day, buf_month, buf_year, buf_hour, buf_minutes;   //initilazation
            std::istringstream ss1(line.substr(line.find(": ") + 1));
            ss1 >> buf_day >> dot >> buf_month >> dot >> buf_year;
            myPatient.setDateBirth(Date(buf_day, buf_month, buf_year, 0, 0));

            std::getline(file, line);
            //std::cout << "Reading from file: " << std::stoi(line.substr(line.find(": ") + 1)) << "\n";
            myPatient.setCabForZapisi(std::stoi(line.substr(line.find(": ") + 1))); 
      

            std::getline(file, line);
            //std::cout << "Reading from file: " << line << "\n";
            std::istringstream ss2(line.substr(line.find(": ") + 1));
            ss2 >> buf_day >> dot >> buf_month >> dot >> buf_year >> dot >> buf_hour >> dot >> buf_minutes;
            myPatient.setDateZapis(Date(buf_day, buf_month, buf_year, buf_hour, buf_minutes));

            std::getline(file, line);
            std::stringstream ss3(line.substr(line.find(": ") + 1));
            
            for (int i; ss3 >> i;) {
                myPatient.addDisease(i);
                if (ss3.peek() == ',')
                    ss3.ignore();
            }
            

            std::getline(file, line);
            std::stringstream ss4(line.substr(line.find(": ") + 1));
            for (int i; ss4 >> i;) {
                myPatient.addService(i);
                if (ss4.peek() == ',')
                    ss4.ignore();
            }
            
            //std::cout << "\n=========\n";
            patients.push_back(myPatient);
        }
    }

    file.close();
    return true;
}


