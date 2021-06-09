/*
 * Semestr.h
 *
 *      Author: trewu
 */

#ifndef SEMESTR_H_
#define SEMESTR_H_

#pragma once
#include <string>
#include "Subj.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

class Semestr
{
	// ������-������, ������� ���� �������� ������ � ���������
	// ��������� �������� ��� ����� �������� ��������������
	friend class Student;
	friend class Zachetka;
	friend class Univer;

	Subj* _subjects[10]; // ������ �� 10 ��������� ��������� � �������� (������)

public:
	int sc=0; // ���-�� ��������� ���������
	// ����������� ������ �������
	Semestr();
	// ��������� ������� �������� � ��������
	// 1=����������, 0=�� ����������
	int hasSubj(string);
	// �������� ����� �������� �� ��� ��������
	Subj* getByTitle(string);
	// �������� ������� � �������
	int addSubj(Subj*);
	// ������� �������������� ������ �� �������
	float average();
};




#endif /* SEMESTR_H_ */
