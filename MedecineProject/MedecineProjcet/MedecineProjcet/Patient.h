#pragma once
#include <string>
#include "Date.h"
#include <vector>
#include <fstream>
#include <sstream>


struct Patient {
private:
	std::string fname; //first name
	std::string lname;
	std::string surname;
	Date dateBirth;
	Date dateZapis;
	std::vector<int> idDiseases = std::vector<int>(0, 0);
	std::vector<int> idServices = std::vector<int>(0, 0);
	
public:
	Patient(std::string fname, std::string lname, std::string surname, Date dateBirth, Date dateZapis);
	Patient();
	int cabForZapisi;
	// Геттеры
	
	std::string getFname() const;
	std::string getLname() const;
	std::string getSurname() const;
	Date getDateBirth() const;
	Date getDateZapis() const;
	std::vector<int> getidDiseases() const;
	std::vector<int> getidServices() const;
	int getCabForZapisi();

	// Сеттеры
	void setCabForZapisi(int num);
	void setFname(std::string fname);
	void setLname(std::string lname);
	void setSurname(std::string surname);
	void setDateBirth(Date dateBirth);
	void setDateZapis(Date dateZapis);
	void setidDiseases(std::vector<int> idDiseases);
	void setidServices(std::vector<int> idServices);

	//добавить эл в вектор
	void addDisease(int id);
	void addService(int id);

	// Вывести данные на консоль
	void printPatient();
	
		 
	// Деструктор
	~Patient();

};

