/*
 * Person.h
 *
 *      Author: trewu
 */

#ifndef PERSON_H_
#define PERSON_H_


#pragma once
#include <string>
#include <ctime>
#include "Date.h"
#include <iostream>

using namespace std;
class Person {
protected:
	string _sname; // Фамилия
	string _fname; // Имя
	string _mname; // Отчество
	Date _bdate; // Дата рождения
	int _gender; // Пол: 0=Ж, 1=М
public:
	// Вывод информации о человеке
	void fullIntroduce();
};



#endif /* PERSON_H_ */
