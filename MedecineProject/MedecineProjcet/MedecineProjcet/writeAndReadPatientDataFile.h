#pragma once
#include <iostream>
#include "Patient.h"
#include <fstream>
#include <sstream>
#include <string>
bool writePatientInFile(Patient& patient);//���������� ��������� � ��, �� - ��������� ����

bool readPatientsFromFile(std::vector<Patient>& patients); //���������� ������ ���������, ������ �� ��
