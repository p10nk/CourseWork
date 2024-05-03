#pragma once
#include <vector>
#include "Cabinet.h"
#include <fstream>
#include <sstream>

//bool writePatientInFile() {}

bool readCabinetsFromFile(std::vector<Cabinet>& cabinets);

bool writeCabinetsFromFile(std::vector<Cabinet>& cabinets);