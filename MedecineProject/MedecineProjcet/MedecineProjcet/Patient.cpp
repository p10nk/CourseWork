#include "Patient.h"
#include <iostream>

Patient::Patient(std::string fname, std::string lname, std::string surname, Date dateBirth, Date dateZapis)
{
	this->setFname(fname);
	this->setLname(lname);
	this->setSurname(surname);
	this->setDateBirth(dateBirth);
	this->setDateZapis(dateZapis);
}

Patient::Patient()
{
	this->setFname("none");
	this->setFname("none");
	this->setSurname("none");
	this->setDateBirth(Date()); // предполагая, что у Date есть конструктор по умолчанию
	this->setDateZapis(Date());
}

std::string Patient::getFname() const
{
	return fname;
}

std::string Patient::getLname() const
{
	return lname;
}

std::string Patient::getSurname() const
{
	return surname;
}

Date Patient::getDateBirth() const
{
	return dateBirth;
}

Date Patient::getDateZapis() const
{
	return dateZapis;
}

std::vector<int> Patient::getidDiseases() const
{
	return this->idDiseases;
}

std::vector<int> Patient::getidServices() const
{
	return this->idServices;
}

int Patient::getCabForZapisi()
{
	return this->cabForZapisi;
}

void Patient::setCabForZapisi(int num)
{
	this->cabForZapisi = num;
}

void Patient::setFname(std::string fname)
{
	this->fname = fname;
}

void Patient::setLname(std::string lname)
{
	this->lname = lname;
}

void Patient::setSurname(std::string surname)
{
	this->surname = surname;
}

void Patient::setDateBirth(Date dateBirth)
{
	this->dateBirth = dateBirth;
}

void Patient::setDateZapis(Date dateZapis)
{
	this->dateZapis = dateZapis;
}

void Patient::setidDiseases(std::vector<int> idDiseases)
{
	this->idDiseases = idDiseases;
}

void Patient::setidServices(std::vector<int> idServices)
{
	this->idServices = idServices;
}

void Patient::addDisease(int id)
{
	this->idDiseases.push_back(id);
}

void Patient::addService(int id)
{
	this->idServices.push_back(id);
}

void Patient::printPatient()
{
	std::string line;
	std::vector<std::string> services; std::string service;
	std::vector<std::string> deseases; std::string desease;
	//Чтение всех ID болезней
	std::ifstream file("E:/grsu/Курсовая c++/MedecineProject/MedecineProjcet/MedecineProjcet/IDdeseases.txt");
	std::ifstream file1("E:/grsu/Курсовая c++/MedecineProject/MedecineProjcet/MedecineProjcet/IDservices.txt");
	if (!file.is_open() || !file.is_open()) {
		std::cout << "Не удалось открыть файл для чтения ID." << std::endl;
	}
	else {
		//Чтение всех ID болезней
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

		//Чтение всех ID лечений
		while (std::getline(file1, line)) {
			if (line.substr(0, 7) == "numcab:") {
				std::getline(file1, line);
				while (line != "------------------------------------------" && !file1.eof()) {
					size_t pos = line.find("-");
					if (pos != std::string::npos) {
						service = line.substr(pos + 1);
					}
					services.push_back(service);
					std::getline(file1, line);
				}
			}
		}
		std::cout << "ФИО: " << this->getFname() << " " << this->getLname() << " " << this->getSurname();
		std::cout << "\nДата рождения: ";  this->dateBirth.printDateWithoutHoursAndMinutes();
		std::cout << "\nДата записи: ";  this->dateZapis.printDate();
		std::cout << "\nID Болезни: ";
		for (const auto& id : this->getidDiseases()) {
			std::cout << deseases[id-1] << '.';
		}
		std::cout << "\nID Услуг: ";
		for (const auto& id : this->getidServices()) {
			std::cout << services[id-1] << '.';
		}
		

	}
	file1.close(); file1.close();

}

Patient::~Patient()
{
}


