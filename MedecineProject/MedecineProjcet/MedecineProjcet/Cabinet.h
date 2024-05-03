#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Date.h"
#include <sstream>
#include <fstream>

struct Zapis {

	Date dateZapis;
	unsigned int busyOrNot = 0; // 1 - busy, 0 - free
	Zapis();
	Zapis(Date date, unsigned int busy);

	Date getDate();
	unsigned int isBusy();

	void setDate(Date& date);
	void setBusy(unsigned int busy);

	void printZapisWithFreeOrNot();

};

struct Cabinet {
private:
	unsigned int num;
	std::string doctor;
	std::vector<int> idDeseases;
	std::vector<int> idServices;
	
public:
	std::vector<Zapis> zapisi;
	void setNum(int num);
	void setDoctor(std::string doctor);
	void addIDservices(int ind);
	void addIDdeseases(int ind);
	void addZapis(Zapis zapis);

	unsigned int getNum();
	std::string getDoctor();
	std::vector<int> getIdDeseases();
	std::vector<int> getIdServices();
	std::vector<Zapis> getZapisi();
	
	void printCabinet();
};

