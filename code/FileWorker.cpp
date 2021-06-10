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

// Заголовок, используется для проверки оригинальности файла
string fheader = "\1\3\3\7";

// проверка существования файла по его имени
int fileExists(string name) {
	FILE *file = fopen("data.txt", "r");
	// попытка открыть файл с таким именем
	if (file) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}

// записать строку в базу данных
int writeOut(string* str) {
	FILE *out = fopen("data.txt", "w");
	// открыть файл базы данных для записи

	// Добавить заголовок в начало файла
	str->insert(0, fheader);

	char c = '1';
	for (int t = 0;t < str->length();t++) {
		c = (*str)[t];
		fwrite(&c, 1, 1, out);
	}

	// Добавить признак окончания файла
	c='\0';
	fwrite(&c, 1, 1, out);

	// Прекратить использование файла и освободить его
	fclose(out);

	return 1;
}

string readContents() {
	FILE *in = fopen("data.txt", "r");;
	// открыть файл базы данных для чтения

	// строка для накопления результата
	string result = "";
	char c = '1';

	// установить указатель в начало файла
	fseek(in, 0, 0);
	for (int i = 0;i < 4;i++) {
		fread(&c, 1, 1, in);
		if (c != fheader[i]) {
			cout << "Некорректный заголовок файла!" << endl;
			system("pause");
			exit(0);
		}
	}

	// установить указатель на селдующий символ после заголовка
	fseek(in, 4, 0);
	while (c != '\0') {
		fread(&c, 1, 1, in);
		result += c;
	}

	// прекратить использование файла и освободить его
	fclose(in);

	// вернуть строку, считанную из файла
	return result;
}


