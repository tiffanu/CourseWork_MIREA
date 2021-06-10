/*
 * StudentArray.cpp
 *
 *      Author: trewu
 */

#include "StudentArray.h"
#include <iostream>
#include <string>
using namespace std;


// Конструктор списка студентов
StudentArray::StudentArray() {
	length = 0; // инициализация кол-ва студентов
}

// Перегрузка оператора индексации
Student& StudentArray::operator[] (const int index)
{
	// есл индекс выходит за границы списка - вызвать исключение
	if (index<0 || index >= length)
		throw out_of_range("Индекс находится за пределами списка");
	else {
		pCurrent = pStart;
		// В цикле выполняем столько итераций, какой индекс был получен
		// тем самым получаем i-й элемент списка
		for (int i = 0; i < index; i++)
		{
			pCurrent = pCurrent->next_item;
		}
		return *pCurrent->val;
	}
}

// Деструктор списка студентов
StudentArray::~StudentArray() {
	// Удалить всех студентов в списке, освободить память
	for (int i = 0; i < length; i++)
	{
		pTemp = pStart->next_item;
		delete pStart->val;
		delete pStart;
		pStart = pTemp;
	}
}

// Добавить студента в список
void StudentArray::addItem(Student* value)
{
	pCurrent = new ListItem; // создать новый элемент списка
	pCurrent->val = value; // занести в него адрес студента

	if (!length) // если это первый элемент списка
	{
		pStart = pCurrent;
		pCurrent->previous_item = pCurrent;
		pCurrent->next_item = pCurrent;
		pTemp = pCurrent;
	}
	else // остальные элементы
	{
		pCurrent->previous_item = pTemp;
		pCurrent->next_item = pTemp->next_item;
		pTemp->next_item = pCurrent;
		pTemp = pCurrent;
	}

	length++; // увеличить счётчик кол-ва студентов в списке
}

// удалить студента из списка
void StudentArray::removeItem(string zach) {

	pCurrent = pStart;

	for (int i = 0; i <= length; i++)
	{
		if (pCurrent->val->_zach->_num == zach) // ищем студента по номеру зачётки
		{
			if (i == 0) {
				pStart = pCurrent->next_item;

				pCurrent->next_item->previous_item = nullptr;
 			} else if (i == length - 1) {
 				pTemp = pCurrent->previous_item;

 				pCurrent->previous_item->next_item = nullptr;


			}
			else {
				// берем в найденном элементе адрес предыдущего и в поле сле-дующего
				// предыдущего элемента записываем значение следующего из найденного
				pCurrent->previous_item->next_item = pCurrent->next_item;

				//берем в найденном элементе адрес последующего и в поле предыдущего
				//следующего элемента записываем значение предыдущего из найденного
				pCurrent->next_item->previous_item = pCurrent->previous_item;
			}

			delete pCurrent->val;
			delete pCurrent;

			length--;
			return;
		}
		else
			pCurrent = pCurrent->next_item;
	}
}
