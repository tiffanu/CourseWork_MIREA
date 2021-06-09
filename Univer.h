/*
 * Univer.h
 *
 *      Author: trewu
 */

#ifndef UNIVER_H_
#define UNIVER_H_

#pragma once
#include "StudentArray.h"
#include "Student.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

class Univer {
	string _title; // �������� ������������
	StudentArray* _students; // ������ ���������
public:
	int N; // ������� ���-�� ���������

	// ����������� ������������
	// ��������
	Univer(string);

	// �������� ��������
	void addStudent(Student*);

	// ������� ��������
	void removeStudent(string);

	// �������� ���������� ��������
	// ����� �������� ������ � ����� ���� ��� ���������
	void changeStudent(string, int);

	// ������� ���������� � ������ �������� ������������
	void showStudents();


	// �������� ������ ��������� ������ ��������
	// ��������� ����� �������
	void showStudentChangeDialog(string);

	// �������� ����� "��������" �� ������ �������
	Student* getByZach(string);

	// ��������� ������� �������� � ������������
	int hasStudent(Student*);
	// ��������� ������� �������� � ������������ �� ������ �������
	int hasStudent(string);
	// ���������� ������������
	~Univer();

	// ��������� ������ ��� ����������� �������� � ����
	string exportAll();
	// ��������� ���� ������ � ����
	void saveAll();
	// ��������� ���� ������ �� �����
	void loadAll();

	void var10query();

	float Threes(Student* std);
};




#endif /* UNIVER_H_ */
