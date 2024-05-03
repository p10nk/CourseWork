#include "writeAndReadCabinetDataFile.h"
#include "Cabinet.h"

bool readCabinetsFromFile(std::vector<Cabinet>& cabinets)
{
    std::ifstream file("E:/grsu/�������� c++/MedecineProject/MedecineProjcet/MedecineProjcet/cabinets.txt");
    if (!file)
    {
        return false;
    }
    
    int cab_number; std::string doctor_name;
    std::string line;
    while (std::getline(file, line)) {
        if (line == "listCabinets:") {
            //std::cout << line << "\n";
            while (std::getline(file, line) && line != "--------------") {
                // ������� ������� 'cab: '
                line = line.substr(5);
  

                // ����� ������� �����
                int pos = line.find(".");

                // ������� ����� �������� � ��� �����
                cab_number = std::stoi(line.substr(0, pos));
                doctor_name = line.substr(pos + 1);

                //std::cout << "����� ��������: " << cab_number << std::endl;
                //std::cout << "��� �����: " << doctor_name << std::endl;

            }
        }
        if (line.substr(0, 7) == "DateCab") {   //��������� ������ � ������� ��� ��������
            char dot; int num;

            Cabinet cab; 
            Date my;
    
            cab.setNum(std::stoi(line.substr(7)));
            
            std::getline(file, line);
            std::istringstream iss(line.substr(5));
            while (iss >> num >> dot) {
                cab.addIDdeseases(num);
                //std::cout << num << ".";
            }
            //std::cout << "\n";
            std::getline(file, line);
            std::istringstream iss1(line.substr(5));
            while (iss1 >> num >> dot) {
                cab.addIDservices(num);
                //std::cout << num << ".";
            }//std::cout << "\n";
            std::getline(file, line);
            cab.setDoctor(line.substr(8));
            //std::cout << line.substr(8);
            //std::cout << "\n------------" << "\n";
            while (line != "--------------") {
                
                Date myDate;
                int temp;
                std::istringstream iss(line);
                iss >> temp >> dot;  myDate.setDay(temp);
                iss >> temp >> dot;  myDate.setMonth(temp);
                iss >> temp >> dot;  myDate.setYear(temp);
                iss >> temp >> dot;  myDate.setHour(temp);
                iss >> temp >> dot;  myDate.setMinutes(temp);
                iss >> temp;  
                cab.addZapis(Zapis(myDate, temp));
                std::getline(file, line);
            }
            cabinets.push_back(cab); 
        
        }


    }

    file.close();
    return true;
}

bool writeCabinetsFromFile(std::vector<Cabinet>& cabinets)
{
    std::ofstream outFile("E:/grsu/�������� c++/MedecineProject/MedecineProjcet/MedecineProjcet/cabinets.txt");
    if (!outFile) {
        std::cout << "�� ������� ������� ���� ��� ������." << std::endl;
        return false;
    }

    outFile << "listCabinets:\n";
    outFile << "cab: 1.��������\n";
    outFile << "cab: 2.������\n";
    outFile << "cab: 3.���������\n";
    outFile << "cab: 4.���������������\n";
    outFile << "cab: 5.�����������\n";
    outFile << "cab: 6.�����������������\n";
    outFile << "cab: 7.����������\n";
    outFile << "cab: 8.��������\n";
    outFile << "cab: 9.��������\n";
    outFile << "cab: 10.����������\n";
    outFile << "--------------\n";

    for (auto& c : cabinets) {
        outFile << "DateCab" << c.getNum() <<":" << std::endl;
        outFile << "IDD: ";
        for (const auto& id : c.getIdDeseases()) {
            outFile << id << ".";
        }
        outFile << std::endl;
        outFile << "IDS: ";
        for (const auto& id : c.getIdServices()) {
            outFile << id << ".";
        }
        outFile << "\ndoctor: " << c.getDoctor() << std::endl;
        for (auto& z : c.getZapisi()) {
            if(z.getDate().getDateStringFormat() != "0.0.0.0.0")
            outFile << z.getDate().getDay() << "." << z.getDate().getMonth() << "."
                << z.getDate().getYear() << "."<< z.getDate().getHour() << "." << z.getDate().getMinutes() << "." << z.isBusy() << "\n";
        }
        outFile << "--------------" << std::endl;
    }

    outFile.close();
    return true;
}
