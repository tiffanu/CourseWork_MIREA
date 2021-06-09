/*
 * Semestr.cpp
 *
 *      Author: trewu
 */
#include "Utils.h"
#include "Semestr.h"

//Конструктор класса "семестр"
Semestr::Semestr	() {
	sc = 0;
}

// функция добавления предмета в семестр
int Semestr::addSubj(Subj* s) {
	// нельзя добавить больше 10 предметов в семестр
	if (sc == 10)
		return 0;

	// проверить, что такого предмета еще не существует
	if (!hasSubj(s->title)) {
		_subjects[sc] = s;
		sc++;
		return 1;
	}

	return 0;
}

// подсчёт средней оценки за семестр
float Semestr::average()
{
	int sum = 0, count = 0;
	// цикл по всем предметам, подсчёт кол-ва оценок и их суммы
	if (sc!=0) // чтобы не упасть при отсутствии предметов
		for (int i = 0;i < sc;i++) {
			if (abs(_subjects[i]->mark) == 1) { // пересдача=1, пустая сессия=-1, поэтому модуль
				sum += 0; // пересдача и пустой семестр считается как 0, но в кол-во входит
			}
			else {
				sum += _subjects[i]->mark; // просто оценка
			}
			count++;

		}

	return count == 0 ? -1 : sum * 1.0 / count; // возвращаем среднее арифметическое или -1, если оценок не было
}

// проверить, существует ли такой предмет в этом семестре
int Semestr::hasSubj(string title) {
	// цикл по всем предметам в массиве, сверяем названия
	// на всякий случай переводим в нижний регистр и убираем
	// лишние пробелы во избежании двух одинаковых предметов
	// с буквами разного регистра в названиях
	for (int i = 0; i < sc;i++) {
		if (trim(strCase(_subjects[i]->title, 0)) == trim(strCase(title, 0)))
			return 1;
	}
	return 0;
}

// получить указатель но объект предмета по его названию
Subj* Semestr::getByTitle(string title)
{
	// цикл по массиву всех предметов, в котором сверяем названия
	// (на всякий случай убирая лишние пробелы)
	for (int i = 0;i < sc;i++) {
		if (trim(_subjects[i]->title) == trim(title))
			return _subjects[i];
	}

	return nullptr;
}




