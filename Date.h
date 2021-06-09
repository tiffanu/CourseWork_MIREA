/*
 * Date.h
 *
 *      Author: trewu
 */

#ifndef DATE_H_
#define DATE_H_


#pragma once
#include <string>
using  namespace std;
class Date
{
public:
	int day=0, mon=0, year=0; // ����, �����, ��� - ������������ ����

	// �������� ���� �� ����������
	// ����, �����, ���
	int isValid(int, int, int);

	// �������� ���� �� ����������
	// ������ ������� [��.��.����]
	int isValid(string);

	// �������� ���� �� ����������
	// ��������� ����
	int isValid(Date);

	// ����������� ���� ��� ������������� � ��������
	// ��� � �������� ���� ������
	Date();

	// ����������� ���� ��� �������� ���������� ����
	Date(int, int, int);
};



#endif /* DATE_H_ */
