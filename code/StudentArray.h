/*
 * StudentArray.h
 *
 *      Author: trewu
 */

#ifndef STUDENTARRAY_H_
#define STUDENTARRAY_H_


#pragma once
#include <iostream>
#include <string>
#include "Student.h"
using namespace std;

// Динамический список студентов
class StudentArray {
	// структура одного элемента списка
	struct ListItem
	{
		ListItem *previous_item; // указатель на предыдущий элемент
		Student* val; // указатель на объект студента
		ListItem *next_item;
	};
	ListItem *pStart, // указатель на первый элемент
		*pCurrent, // указатель на текущий элемент
		*pTemp, // временный указатель для промежуточных значений
		*pPrev; // указатель на предыдущий элемент
public:
	int length; // длина списка

	// Добавить студента в список
	void addItem(Student*);

	// Удалить студента из списка
	void removeItem(string);

	// Конструктор списка студентов
	StudentArray();

	// Деструктор списка студентов
	~StudentArray();

	// Перегрузка оператора индексации для более удобного использования
	Student& operator[] (const int index);
};



#endif /* STUDENTARRAY_H_ */
