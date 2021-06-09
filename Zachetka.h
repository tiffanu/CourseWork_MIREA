/*
 * Zachetka.h
 *
 *      Author: trewu
 */

#ifndef ZACHETKA_H_
#define ZACHETKA_H_


#pragma once
#include <string>
#include "Semestr.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
class Zachetka
{
	// классы-друзья, которые могу получить доступ к приватным
	// элементам семестра для более удобного взаимодействия
	friend class StudentArray;
	friend class Student;
	friend class Univer;
	string _num; // номер зачётки
	Semestr* _sems[12]; // 12 семестров
	int sc = 0; // кол-во имеющихся семестров
public:
	// Конструктор зачётки
	// Принимает номер зачётки
	Zachetka(string);
	// Вывести в окно консоли все семестры и предметы с оценками
	void showAll();
	// Деструктор зачётки
	~Zachetka();
	// Добавить семестр в зачётку
	int addSem(Semestr*);
	// Средняя оценка по всей зачётке
	float average();
	// Получить данные для экспорта в файл
	string dump();
};



#endif /* ZACHETKA_H_ */
