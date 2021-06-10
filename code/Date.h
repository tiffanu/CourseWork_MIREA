/*
 * Date.h
 *
 *      Author: trewu
 */

#ifndef DATE_H_
#define DATE_H_


#pragma once
#include <string>
using  namespace std;
class Date
{
public:
	int day=0, mon=0, year=0; // день, месяц, год - составляющие даты

	// Проверка даты на валидность
	// День, месяц, год
	int isValid(int, int, int);

	// Проверка даты на валидность
	// Строка формата [дд.мм.ГГГГ]
	int isValid(string);

	// Проверка даты на валидность
	// Принимает дату
	int isValid(Date);

	// Конструктор даты для использования в массивах
	// или в качестве типа данных
	Date();

	// Конструктор даты для создания конкретной даты
	Date(int, int, int);
};



#endif /* DATE_H_ */
