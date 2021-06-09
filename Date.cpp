/*
 * Date.cpp
 *
 *      Author: trewu
 */


#include "Date.h"
#include "Utils.h"
#include <string>
using  namespace std;

//  онструктор даты дл€ использовани€ в качестве
// типа данных или при инициализации массива
Date::Date() {
	this->day = 0;
	this->mon = 0;
	this->year = 0;
}

//  онструктор даты с указанием элементов даты
Date::Date(int _day, int _mon, int _year) {
	this->day = _day;
	this->mon = _mon;
	this->year = _year;
}

// ѕроверка даты на правильность (по част€м)
int Date::isValid(int day, int mon, int year) {
	return ((day > 0) && (day <= 31) && (mon > 0) && (mon <= 12) && (year >= 0) && (year <= 9999));
}

// ѕроверка даты на правильность (из строки)
int Date::isValid(string sdate) {
	Date d = parseDotDate(sdate);
	return isValid(d);
}

// ѕроверка даты на правильность
int Date::isValid(Date d) {
	return ((d.day > 0) && (d.day <= 31) && (d.mon > 0) && (d.mon <= 12) && (d.year >= 0) && (d.year <= 9999));
}


