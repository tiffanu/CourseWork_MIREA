/*
 * Person.cpp
 *
 *      Author: trewu
 */

#include "Utils.h"
#include "Person.h"
#include <string>
#include <iostream>

using namespace std;

// ������� ��� ���������� � ��������
void Person::fullIntroduce() {
	cout << "�������: " << this->_sname << " ���: " << this->_fname << " ��������: " << this->_mname << endl;
	cout << "���: " << (this->_gender?"�":"�") << " | ���� ��������: " << dateToStr(this->_bdate) << endl;
}



