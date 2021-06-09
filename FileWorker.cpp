/*
 * FileWorkek.cpp
 *
 *      Author: trewu
 */


#include "FilesWorker.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

using namespace std;

// ���������, ������������ ��� �������� �������������� �����
string fheader = "\1\3\3\7";

// �������� ������������� ����� �� ��� �����
int fileExists(string name) {
	FILE *file = fopen("data.txt", "r");
	// ������� ������� ���� � ����� ������
	if (file) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}

// �������� ������ � ���� ������
int writeOut(string* str) {
	FILE *out = fopen("data.txt", "w");
	// ������� ���� ���� ������ ��� ������

	// �������� ��������� � ������ �����
	str->insert(0, fheader);

	char c = '1';
	for (int t = 0;t < str->length();t++) {
		c = (*str)[t];
		fwrite(&c, 1, 1, out);
	}

	// �������� ������� ��������� �����
	c='\0';
	fwrite(&c, 1, 1, out);

	// ���������� ������������� ����� � ���������� ���
	fclose(out);

	return 1;
}

string readContents() {
	FILE *in = fopen("data.txt", "r");;
	// ������� ���� ���� ������ ��� ������

	// ������ ��� ���������� ����������
	string result = "";
	char c = '1';

	// ���������� ��������� � ������ �����
	fseek(in, 0, 0);
	for (int i = 0;i < 4;i++) {
		fread(&c, 1, 1, in);
		if (c != fheader[i]) {
			cout << "������������ ��������� �����!" << endl;
			system("pause");
			exit(0);
		}
	}

	// ���������� ��������� �� ��������� ������ ����� ���������
	fseek(in, 4, 0);
	while (c != '\0') {
		fread(&c, 1, 1, in);
		result += c;
	}

	// ���������� ������������� ����� � ���������� ���
	fclose(in);

	// ������� ������, ��������� �� �����
	return result;
}


