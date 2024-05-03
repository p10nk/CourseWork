#pragma once
#include <iostream>
#include "Patient.h"
#include <fstream>
#include <sstream>
#include <string>
bool writePatientInFile(Patient& patient);//дописывает пациентов в бд, бд - текстовый файл

bool readPatientsFromFile(std::vector<Patient>& patients); //возвращает массив веткторов, читает из бд
