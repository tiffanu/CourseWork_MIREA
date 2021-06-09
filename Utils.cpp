/*
 * Utils.cpp
 *
 *      Author: trewu
 */

#include "Utils.h"
#include "Date.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// ������� ��� ����� �������� ������
// ������, 0=������/1=������� �������
string strCase(string s, int f) {
	// ������ ������
	int size = s.size();
	// ����� ������ ��� ����������
	// ����������� �������� ������, ����� �������� ������ ��� �� �����
	string r = s;

	// ���������, � ����� ������� ����� ��������� �����
	if (f) {
		// ����������� ��������� ����� � ������� �������
		for (int i = 0; i < size; i++) {
			r[i] = char(toupper(s[i]));
		}
	}
	else {
		// ����������� ��������� ����� � ������ �������
		for (int i = 0; i < size; i++) {
			r[i] = char(tolower(s[i]));
		}
	}
	// ���������� ����� ������
	return r;
}

// ������� ���� � ������
string dateToStr(Date d) {
	// ���������� ��� ����������
	string ret = "";

	// �������� ��� - ���� ���� �� ���
	// ������, �� ��-��������� �� ����� 0
	if (d.day > 0) {
		// �������� ���� ����� ��������� ���,
		// ���� ��� ������ ������
		if (d.day < 10)
			ret.append("0");
		ret.append(to_string(d.day));
	}

	// ���� ���������� ���������, �� ���� ����
	// ��� ������, �� �������� ����� ����� ����
	if (ret != "")
		ret.append(".");

	// � ������� ������� ��� ��, ��������� ��� �������
	if (d.mon > 0) {
		// �������� ���� ����� ��������� ������,
		// ���� ��� ������ ������
		if (d.mon < 10)
			ret.append("0");
		ret.append(to_string(d.mon));
	}

	if (ret != "")
		ret.append(".");

	if (d.year > 0)
		ret.append(to_string(d.year));

	return ret;
}

// ������� ������ ������� {��.��.����} � ����
Date parseDotDate(string sdate) {
	Date r;
	Date bad = Date(-1, -1, -1);

	int len = sdate.length();
	// �������� � ����� ������ �� ����������� ������, ����� �� ����� ��� ������
	sdate.append("a");

	// ������� ������ ���������� ������� � �������� ���������� �������
	// ���� �� ������� - ������ � �������� ��� ���� ������������ �������
	if (sdate.find_first_not_of("0123456789.")!=len)
		return bad; // ���������� ����, ��������� ����������� -1

	// ������� � ����� ������ ����������� ������
	sdate = sdate.substr(0, sdate.length() - 1);

	// ������ ��������� ���� ������ �� ������� ������ � ���������� ������ ��������
	// (+1 ��� ����-�������)
	char *c_st = new char[sdate.length()+1];
	// �������� �������� �� ������ � =��������� ������� ������
	strcpy(c_st, sdate.c_str());

	// ������ ��������� ���� ������ ��� ������ �������
	char *part, *posn;
	// ������� ���������� ������� �������� �� �����, ����������� ��������� ���������-���
	part = strtok_r(c_st, ".", &posn);

	int c = 0;
	// ������������ ���������� ������� ������
	while (part != NULL) {
		switch (c)
		{
		case 0:
			r.day = stoi(part);
			break;
		case 1:
			r.mon = stoi(part);
			break;
		case 2:
			r.year = stoi(part);
			break;
		default:
			break;
		}
		// ��������� � ���������� �������
		part = strtok_r(NULL, ".", &posn);
		c++;
	}

	delete c_st;
	delete part;
	posn = nullptr;

	// ���� �������� ���������� ������ ���, ������
	// ������ ������������ �������, ������� ������ ����
	// ������� � ����������� ��������� ���������
	if (c != 3)
		return bad;

	return r;// ����� ������� �������������� �� ������ ����
}

// �������� ������ �� ����������� ��������������� � ������������� �����
int isValidInt(string num) {
	// ���� ������ ����� ��� ��������� max int, �� ������� 0
	if (num == "" || num.length() > 9)
		return 0;
	// �������� ��������� ������, ����� ��������� � ���, ��� ������� ����� ������
	num.append("a");
	// ���������, ��� �������� ������ ��������� ������ � ����� ������, ����
	// ��� �������� ���� �������
	if (num.find_first_not_of("0123456789") != num.length()-1)
		return 0;
	return 1;
}

// �������� ������ �� ������� ������������ ��������
// ���������� 1, ���� �� ������
int checkSpec(string name, int type) {
	name.append("$"); // �������� � ����� ������ ������������ ������
	name = strCase(name, 0); // �������������� ������ � ������ �������
	switch (type) // �������� ���� ��������. 0=����� � ����,  1=������ � ����, ��� ��-��� ��������� �����, ���� � �����
	{
	case 0: // name
		return (name.find_first_not_of("abcdefghijklmnopqrstuvwxyz��������������������������������") == name.length() - 1);
	case 1: // group
		return (name.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789.-��������������������������������") == name.length() - 1);
	default:
		break;
	}

	return 0;
}

// ������ ������� � ����� � ������ ������
string trim(string str) {
	string result = ""; // ������ ��� ���������� ����������
	if (str == "") return "";

	int rLen = str.length(); // ����� ������������ ������
	char c = str[0]; // �������� ������ ������ ������ � ���������� ���� ������
	int count = 0;
	while (c == ' ') { // ���������, ������� �������� ���������� � ������ ������
		count++;
		c = str[count];
	}
	str = str.substr(count, rLen - count ); // �������� ������� � ������ ������

	c = str[rLen - count - 1]; // ���������, ������� �������� ���������� � ����� ����-��
	while (c == ' ') {
		rLen--;
		c = str[rLen - count - 1];
	}
	str = str.substr(0, rLen - count); // �������� ������� � ����� ������

	return str;
}



