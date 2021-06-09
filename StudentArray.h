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

// ������������ ������ ���������
class StudentArray {
	// ��������� ������ �������� ������
	struct ListItem
	{
		ListItem *previous_item; // ��������� �� ���������� �������
		Student* val; // ��������� �� ������ ��������
		ListItem *next_item;
	};
	ListItem *pStart, // ��������� �� ������ �������
		*pCurrent, // ��������� �� ������� �������
		*pTemp, // ��������� ��������� ��� ������������� ��������
		*pPrev; // ��������� �� ���������� �������
public:
	int length; // ����� ������

	// �������� �������� � ������
	void addItem(Student*);

	// ������� �������� �� ������
	void removeItem(string);

	// ����������� ������ ���������
	StudentArray();

	// ���������� ������ ���������
	~StudentArray();

	// ���������� ��������� ���������� ��� ����� �������� �������������
	Student& operator[] (const int index);
};



#endif /* STUDENTARRAY_H_ */
