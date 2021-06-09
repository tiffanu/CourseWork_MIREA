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
	// ������-������, ������� ���� �������� ������ � ���������
	// ��������� �������� ��� ����� �������� ��������������
	friend class StudentArray;
	friend class Student;
	friend class Univer;
	string _num; // ����� �������
	Semestr* _sems[12]; // 12 ���������
	int sc = 0; // ���-�� ��������� ���������
public:
	// ����������� �������
	// ��������� ����� �������
	Zachetka(string);
	// ������� � ���� ������� ��� �������� � �������� � ��������
	void showAll();
	// ���������� �������
	~Zachetka();
	// �������� ������� � �������
	int addSem(Semestr*);
	// ������� ������ �� ���� �������
	float average();
	// �������� ������ ��� �������� � ����
	string dump();
};



#endif /* ZACHETKA_H_ */
