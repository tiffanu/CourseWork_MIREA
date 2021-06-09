/*
 * Subj.cpp
 *
 *      Author: trewu
 */


#include "Subj.h"
#include "Utils.h"

// ����������� ������ "�������"
// ��������� - �������� � ������
Subj::Subj(string title, int mark) {
	// ������ ������ ������� �� ��������
	this->title = trim(title);
	this->mark = mark;
}

// ����������� ������ "�������"
// ������ ��-��������� = 0
// ����� ��� �������� ��������
Subj::Subj()
{
	this->mark = 0;
}


