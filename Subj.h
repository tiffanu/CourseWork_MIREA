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
	string title; // �������� ��������
	int mark; // ������

	// ����������� ��������
	// ��������, ������
	Subj(string, int);

	// ����������� �������� ��� ��������
	Subj();
};




#endif /* SUBJ_H_ */
