/*
 * Subj.h
 *
 *      Author: trewu
 */

#ifndef SUBJ_H_
#define SUBJ_H_

#pragma once
#include <string>

using namespace std;
class Subj {
public:
	string title; // название предмета
	int mark; // оценка

	// Конструктор предмета
	// Название, оценка
	Subj(string, int);

	// КОнструктор предмета для массивов
	Subj();
};




#endif /* SUBJ_H_ */
