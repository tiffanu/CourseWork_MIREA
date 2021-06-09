/*
 * Utils.h
 *
 *      Author: trewu
 */

#ifndef UTILS_H_
#define UTILS_H_

#pragma once
#define clean cin.clear(); cin.ignore(cin.rdbuf()->in_avail()); _flushall();
#define cls system("cls");
#define checkReturn(zn) if(tmp=="0"){cls;showStudentChangeDialog(zn);break;};
#include <string>
#include "Date.h"
#include "FilesWorker.h"
#include "StudentArray.h"
#include "LanguageDefinitions.h"
using namespace std;
// Перевести строку в регистр
// Строка, регистр: 0=нижний, 1=верхний
string strCase(string, int);
// Перевести дату в строку
string dateToStr(Date d);
// Перевести строку формата [дд.мм.ГГГГ] в дату
Date parseDotDate(string);
// Проверить, является ли значение в строке числом
int isValidInt(string);
// Проверить строку на наличие нежелательных символов
// Возвращает 1=всё хорошо, 0=имеются нежелательные символы
int checkSpec(string, int);
// Убрать пробелы с конца и начала строки
string trim(string);




#endif /* UTILS_H_ */
