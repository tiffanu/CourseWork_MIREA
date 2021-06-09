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

// функция для смены регистра текста
// строка, 0=нижний/1=верхний регистр
string strCase(string s, int f) {
	// размер строки
	int size = s.size();
	// новая строка для результата
	// присваиваем значение старой, чтобы получить строку той же длины
	string r = s;

	// проверяем, в какой регистр нужно перевести текст
	if (f) {
		// посимвольно переводим текст в верхний регистр
		for (int i = 0; i < size; i++) {
			r[i] = char(toupper(s[i]));
		}
	}
	else {
		// посимвольно переводим текст в нижний регистр
		for (int i = 0; i < size; i++) {
			r[i] = char(tolower(s[i]));
		}
	}
	// возвращаем новую строку
	return r;
}

// Перевод даты в строку
string dateToStr(Date d) {
	// переменная для результата
	string ret = "";

	// проверка дня - если день не был
	// указан, то по-умолчанию он равен 0
	if (d.day > 0) {
		// добавить ноль перед значением дня,
		// если оно меньше десяти
		if (d.day < 10)
			ret.append("0");
		ret.append(to_string(d.day));
	}

	// если результата изменился, то есть день
	// был указан, то добавить точку после него
	if (ret != "")
		ret.append(".");

	// с месяцем принцип тот же, проверяем его наличие
	if (d.mon > 0) {
		// добавить ноль перед значением месяца,
		// если оно меньше десяти
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

// Перевод строки формата {дд.мм.ГГГГ} в дату
Date parseDotDate(string sdate) {
	Date r;
	Date bad = Date(-1, -1, -1);

	int len = sdate.length();
	// добавить в конец строки не разрешенный символ, чтобы он точно был найден
	sdate.append("a");

	// сверить индекс найденного символа с индексом последнего символа
	// если не совпали - значит в значении уже были некорректные символы
	if (sdate.find_first_not_of("0123456789.")!=len)
		return bad; // возвращаем дату, полностью заполненную -1

	// убираем с конца строки проверочный символ
	sdate = sdate.substr(0, sdate.length() - 1);

	// создаём указатель типа символ на область памяти с идентичным строке размером
	// (+1 для нуль-символа)
	char *c_st = new char[sdate.length()+1];
	// копируем значение из строки в =созданную область памяти
	strcpy(c_st, sdate.c_str());

	// создаём указатели типа символ для работы функции
	char *part, *posn;
	// функция разделения массива символов на блоки, разделенные указанным разделите-лем
	part = strtok_r(c_st, ".", &posn);

	int c = 0;
	// обрабатываем полученные отрезки строки
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
		// переходим к следующему отрезку
		part = strtok_r(NULL, ".", &posn);
		c++;
	}

	delete c_st;
	delete part;
	posn = nullptr;

	// если отрезков получилось больше трёх, значит
	// данные сформированы неверно, вернуть плохую дату
	// которую в последствии забракует валидатор
	if (c != 3)
		return bad;

	return r;// иначе вернуть сформированную из строки дату
}

// Проверка строки на возможность конвертирования в положительное число
int isValidInt(string num) {
	// если строка пуста или превышает max int, то вернуть 0
	if (num == "" || num.length() > 9)
		return 0;
	// добавить сторонний символ, чтобы убедиться в том, что таковой будет найден
	num.append("a");
	// проверить, что неверный символ находится только в конце строки, куда
	// его добавила сама функция
	if (num.find_first_not_of("0123456789") != num.length()-1)
		return 0;
	return 1;
}

// Проверка строки на наличие недопустимых символов
// возвращает 1, если всё хорошо
int checkSpec(string name, int type) {
	name.append("$"); // добавить в конец строки недопустимый символ
	name = strCase(name, 0); // конвертировать строку в нижний регистр
	switch (type) // проверка типа значения. 0=имена и проч,  1=группа и проч, что мо-жет содержать точки, тире и цифры
	{
	case 0: // name
		return (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzйцукенгшщзхъфывапролджэячсмитьбю") == name.length() - 1);
	case 1: // group
		return (name.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789.-йцукенгшщзхъфывапролджэячсмитьбю") == name.length() - 1);
	default:
		break;
	}

	return 0;
}

// Убрать пробелы с конца и начала строки
string trim(string str) {
	string result = ""; // строка для накопления результата
	if (str == "") return "";

	int rLen = str.length(); // длина оригинальной строки
	char c = str[0]; // записать первый символ строки в переменную типа символ
	int count = 0;
	while (c == ' ') { // посчитать, сколько пробелов встретится в начале строки
		count++;
		c = str[count];
	}
	str = str.substr(count, rLen - count ); // обрезать пробелы в начале строки

	c = str[rLen - count - 1]; // посчитать, сколько пробелов встретится в конце стро-ки
	while (c == ' ') {
		rLen--;
		c = str[rLen - count - 1];
	}
	str = str.substr(0, rLen - count); // обрезать пробелы в конце строки

	return str;
}



