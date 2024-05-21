#include "Cabinet.h"


Zapis::Zapis()
{
}

Zapis::Zapis(Date date, unsigned int busy)
{
	this->dateZapis = date;
	this->busyOrNot = busy;
}

Date Zapis::getDate()
{
	return this->dateZapis;
}

unsigned int Zapis::isBusy()
{
	return this->busyOrNot;
}

void Zapis::setDate(Date& date)
{
	this->dateZapis = date;
}

void Zapis::setBusy(unsigned int busy)
{
	this->busyOrNot = busy;
}

void Zapis::printZapisWithFreeOrNot()
{
	this->dateZapis.printDate();
	std::cout << "." << this->busyOrNot;
}

void Cabinet::setNum(int num)
{
	this->num = num;
}

void Cabinet::setDoctor(std::string doctor)
{
	this->doctor = doctor;
}

void Cabinet::addIDservices(int ind)
{
	this->idServices.push_back(ind); // исправлено здесь
}

void Cabinet::addIDdeseases(int ind)
{
	this->idDeseases.push_back(ind); // исправлено здесь
}

void Cabinet::addZapis(Zapis zapis)
{
	this->zapisi.push_back(zapis);
}

unsigned int Cabinet::getNum()
{
	return this->num;
}

std::string Cabinet::getDoctor()
{
	return this->doctor;
}

std::vector<int> Cabinet::getIdDeseases()
{
	return this->idDeseases;
}

std::vector<int> Cabinet::getIdServices()
{
	return this->idServices;
}

std::vector<Zapis> Cabinet::getZapisi()
{
	return this->zapisi;
}

void Cabinet::printCabinet()
{
	std::string line;
	std::vector<std::string> services; std::string service;
	std::vector<std::string> deseases; std::string desease;
	//Чтение всех ID болезней
	std::ifstream file("E:/grsu/Курсоваяc++/MedecineProject/MedecineProjcet/MedecineProjcet/IDdeseases.txt");
	std::ifstream file1("E:/grsu/Курсоваяc++/MedecineProject/MedecineProjcet/MedecineProjcet/IDservices.txt");
	if (!file.is_open() || !file1.is_open()) {
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

		std::cout << "Номер кабинета: " << this->getNum() << "\n";
		std::cout << "Доктор: " << this->getDoctor() << "\n";
		std::cout << "Выявляемые болезни: ";
		for (int id : this->getIdDeseases()) {
			std::cout << deseases[id - 1] << ".";
		}
		std::cout << "\nОказываемые услуги: ";
		for (int id : this->getIdServices()) {
			std::cout << services[id - 1] << ".";
		}
		std::cout << "\nЗаписи: \n";

		for (Zapis z : this->getZapisi()) {
			if (z.getDate().getDateStringFormat() == "0.0.0.0.0") { continue; }
			std::cout << "Дата: " << z.getDate().getDateStringFormat() << "\n";
			std::cout << "Состояние: " << (z.isBusy() ? "+" : "-") << "\n";

		}
		
	}
	file1.close(); file1.close();
	
}

