/*
 * Student.h
 *
 *      Author: trewu
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#pragma once

#include "Person.h"
#include "Zachetka.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


class Student : public Person {
	// ������-������, ������� ���� �������� ������ � ���������
	// ��������� �������� ��� ����� �������� ��������������
	friend class Univer;
	friend class StudentArray;

	Date _edate; // ���� �����������
	string _group; // ������
	string _fac; // ���������
	string _kaf; // �������
	Zachetka* _zach; // �������
public:
	// ������� ��� ���������� � �������� + � ��������
	void fullIntroduce();

	// ����������� ��������
	// �������, ���, ��������, ���, ���� ��������, ������ ���������, �������, ��� ��-���������, �������
	Student(string, string, string, int, Date, string, string, string, Date, Zachetka*);

	// ����������� �������� �� ������ �������������� �����
	Student(string);

	// ���������� ��������
	~Student();

	// ������� �������������� ���� ������ ��������
	float fullAvg();

	// ������ ��� �������� ������ �������� � ����
	string dataForExport();
};




#endif /* STUDENT_H_ */
