#pragma once
#include <iostream>
#include "Patient.h"
#include <string>
#include "Date.h"

bool isNumber(const std::string& line);

bool isAvalidId(int a, int b, int n, std::vector<int> myIdies);

bool addPatient(Patient& patient);

bool dellPatient(std::vector<Patient> patients);

bool takePatient();

