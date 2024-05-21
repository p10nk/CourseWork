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
	// �����������
	Date() = default;
	Date(unsigned int day, unsigned int month, unsigned int year, unsigned int hour, unsigned int minutes);

	// �������
	unsigned int getDay() const;
	unsigned int getMonth() const;
	unsigned int getYear() const;
	unsigned int getHour() const;
	unsigned int getMinutes() const;

	// ������� �������� ������� � ������� ������, ��� ������ � ����
	std::string getDateStringFormat();

	// �������
	void setDay(unsigned int day);
	void setMonth(unsigned int month);
	void setYear(unsigned int year);
	void setHour(unsigned int hour);
	void setMinutes(unsigned int minutes);

	//����� ����
	void printDate();
	void printDateWithoutHoursAndMinutes();

	// ����������
	~Date();

};
