#include "Date.h"
#include <iostream>
#include <vector>


Date::Date(unsigned int day, unsigned int month, unsigned int year, unsigned int hour, unsigned int minutes):
	day(day), month(month), year(year), hour(hour), minutes(minutes) {}

unsigned int Date::getDay() const
{
	return this->day;
}

unsigned int Date::getMonth() const
{
	return this->month;
}

unsigned int Date::getYear() const
{
	return this->year;
}

unsigned int Date::getHour() const
{
	return this->hour;
}

unsigned int Date::getMinutes() const
{
	return this->minutes;
}

std::string Date::getDateStringFormat()
{
	return std::to_string(this->getDay())+"."+std::to_string(this->getMonth())+"."+std::to_string(this->getYear())+
		"."+std::to_string(this->getHour())+"."+std::to_string(this->getMinutes());
}


void Date::setDay(unsigned int day)
{
	this->day = day;
}

void Date::setMonth(unsigned int month)
{
	this->month = month;
}

void Date::setYear(unsigned int year)
{
	this->year = year;
}

void Date::setHour(unsigned int hour)
{
	this->hour = hour;
}

void Date::setMinutes(unsigned int minutes)
{
	this->minutes = minutes;
}

void Date::printDate()
{
	std::cout << this->getDay() << "." << this->getMonth() << "." << this->getYear()<<"."<<this->getHour()<<"."<<this->getMinutes();
}

void Date::printDateWithoutHoursAndMinutes()
{
	std::cout << this->getDay() << "." << this->getMonth() << "." << this->getYear();
}

Date::~Date()
{
}

