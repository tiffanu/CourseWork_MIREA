/*
 * Subj.cpp
 *
 *      Author: trewu
 */


#include "Subj.h"
#include "Utils.h"

// конструктор класса "предмет"
// аргументы - название и оценка
Subj::Subj(string title, int mark) {
	// убрать лишние пробелы из названия
	this->title = trim(title);
	this->mark = mark;
}

// конструктор класса "предмет"
// оценка по-умолчанию = 0
// нужен для создания массивов
Subj::Subj()
{
	this->mark = 0;
}


