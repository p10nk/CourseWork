#pragma once
#include <sstream>

struct Date {
private:
	unsigned int day;
	unsigned int month;
	unsigned int year;
	unsigned int hour;
	unsigned int minutes;
public:
	// Конструктор
	Date() = default;
	Date(unsigned int day, unsigned int month, unsigned int year, unsigned int hour, unsigned int minutes);

	// Геттеры
	unsigned int getDay() const;
	unsigned int getMonth() const;
	unsigned int getYear() const;
	unsigned int getHour() const;
	unsigned int getMinutes() const;

	// Вернуть значение времени в формате строки, для записи в файл
	std::string getDateStringFormat();

	// Сеттеры
	void setDay(unsigned int day);
	void setMonth(unsigned int month);
	void setYear(unsigned int year);
	void setHour(unsigned int hour);
	void setMinutes(unsigned int minutes);

	//Вывод даты
	void printDate();
	void printDateWithoutHoursAndMinutes();

	// Деструктор
	~Date();

};
