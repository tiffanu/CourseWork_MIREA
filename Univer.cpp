/*
 * Univer.cpp
 *
 *      Author: trewu
 */


#include "Univer.h"
#include "Utils.h"
#include "Student.h"
#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// ����������� ������������
Univer::Univer(string title) {
	_title = title;
	// ������� ������ ��������� � �������� ��� ����� � ���������
	_students = new StudentArray();
	N = 0;
}
// ��������� ������, ���������� � ���� ��� ������ � ���������
// ��� ���������� ������ � ���� ���� ������
string Univer::exportAll() {
	/*
				��������� ����� ����� ���:
		(�������� �����  � ������� �����������,
		����� ��������� ���	������� �������������)

		\1\3\3\7 ������� (\1) ��� (\1) �������� (\1) ��� (\1)			// ���-��� ��������, \1\3\3\7 = ��������� ��� ��������
		���� �������� (\1)��� ����������� (\1) ��������� (\1)			// ���-��� ��������
		������� (\1) ������ (\1) ����� ��ר���(\2)						// ������ ��������
		Subj1 (\2) 5 (\3) Subj2 (\2) 4 (\3)(\1)							//  ������ ������� � ����� ����������
		(\1)															// ������ ������� - ��� ������
		Subj3 (\2) 5 (\3) Subj4 (\2) 4 (\3)(\1)							// ������ ������� � ����� ����������
		(\6)															// ����� ������ ��������, ����� ����� ���� ����� �� ����
		......															// ������ �������� ������ �� ����
		(\0)
	*/
	string result; // ���������� ��� ���������� ������
	for (int i = 0; i < _students->length; i++) {
		// ���� �� ���� ��������� ������, �������� ������ ������� �� ���
		result.append((*_students)[i].dataForExport());
	}
	return result;
}

// ��������� ������ ��������� � ����
void Univer::saveAll()
{
	string* str1 = new string(exportAll());
	writeOut(str1);
	delete str1;
}

// ������� ������ ��������� �� �����
void Univer::loadAll()
{
	string data = readContents(); // ������ ������

	string oneStud; // ���������� ��� �������� ������ ������ ��������
	int i = 0;
	char c = data[i];
	while (c != '\0') {
		oneStud = "";
		// ���� ������ �������� ��������� �������� \6
		// �� ���� � ��� ���� while
		while (c != '\6' && c != '\0') {
			c = data[i];
			oneStud += c;
			i++;
		}
		c = data[i];

		// ������� �������� � �������� � �����������
		Student* ns = new Student(oneStud);
		addStudent(ns);
	}
}

// ���������� ������������
Univer::~Univer() {
	delete _students;
}

// �������� ������ ��������� ���������� ����������� ��������
void Univer::showStudentChangeDialog(string zn) {
	Student* s = getByZach(zn); // �������� ��������� �� �������� �� ������ �������
	cout << "������� ����� ������, � ������� ������ ������ ���������:" << endl;
	cout << "1. ������� (" << s->_sname << ")" << endl;
	cout << "2. ��� (" << s->_fname << ")" << endl;
	cout << "3. �������� (" << s->_mname << ")" << endl;
	cout << "4. ��� (" << to_string(s->_gender) << ")" << endl;
	cout << "5. ���� �������� (" << dateToStr(s->_bdate) << ")" << endl;
	cout << "6. ��� ����������� (" << to_string(s->_edate.year) << ")" << endl;
	cout << "7. ��������� (" << s->_fac << ")" << endl;
	cout << "8. ������� (" << s->_kaf << ")" << endl;
	cout << "9. ������ (" << s->_group << ")" << endl;
	cout << "10. ����� ������� (" << s->_zach->_num << ")" << endl;
	cout << "11. �������" << endl;
	cout << "0. ����� � ������� ����" << endl;
	cout << "> ";

	n3g:
	string n; // ����������, � ������� ����� ������ ��������� ����� ����
	getline(cin, n); // ���� ������
	// �������� ��������� ������ �� ������������ ����� �� ���������
	if (!isValidInt(n) || stoi(n) > 12 || stoi(n) < -1) {
		cls;
		goto n3g;
	}

	// ���� ������ ����� � ���� - ����������� �������
	// ��������� �������� � ������������ � ����
	if (n == "0")
	{
		cls;
		return;
	}

	// � ���� ������ �������� ������� ��������� ����������� ����
	// � ������� "�������"
	changeStudent(zn, stoi(n));
	cls;
	return;
}

// ������� ��� ��������� ���������� � ��������
// ��������� ����� �������� ������ � ����� ����, ������� ���������� ��������
void Univer::changeStudent(string zach_num, int field) {
		string tmp; // ���������� ��� ����� ������ �� ����� ����
		Student* t = getByZach(zach_num); // �������� ��������� �� ����������� ���-�����

		switch (field)
		{
		case 1: { // �������
		sne:
			cout << EXITHINT << endl; // EXITHINT - define �� ��������� �����
			cout << "������� (" << t->_sname << ") > ";
			getline(cin, tmp); // ���� �������
			checkReturn(zach_num); // ������-������� �� define � Utils.h
			// ���������, ���� � tmp ����� 0, ����� ���� ������������ ������-�����
			// ���������� �������������� ����

			// �������� ������� �� ���� �������
			if (!checkSpec(tmp, 0)) {
				cout << CHR_ERR << endl; // CHR_ERR - define �� ��������� ���-��
				goto sne;
			}
			t->_sname = tmp; break;
		}
		case 2: { // ���
		fne:
			cout << EXITHINT << endl;
			cout << "��� (" << t->_fname << ") > ";
			getline(cin, tmp); // ���� �����
			checkReturn(zach_num); // �������� 0

			// �������� ������������
			if (!checkSpec(tmp, 0)) {
				cout << CHR_ERR << endl;
				goto fne;
			}
			t->_fname = tmp; break;
		}
		case 3: { // ��������
		mne:
			cout << EXITHINT << endl;
			cout << "�������� (" << t->_mname << ") > ";
			getline(cin, tmp); // ���� ��������
			checkReturn(zach_num); // �������� 0

			// �������� ������������
			if (!checkSpec(tmp, 0)) {
				cout << CHR_ERR << endl;
				goto mne;
			}
			t->_mname = tmp; break;
		}
		case 4: { // ���
		gender_input:
			cout << "��� [�,�] (" << to_string(t->_gender) << ") > ";
			getline(cin, tmp); // ���� ����
			checkReturn(zach_num); // �������� 0
			// ��������, ��� ��������� �������� �������� ������ � ��� ��� 1 ��� 0
			if ((strCase(tmp, 0) != "�") && (strCase(tmp, 0) != "�")) {
				cout << INVINP;
				goto gender_input;
			}

			tmp = (strCase(tmp, 0) == "�" ? "1" : "0");
			t->_gender = stoi(tmp); break;

		}
		case 5: { // ���� ��������
			Date bday;
		bdate_input:
			cout << EXITHINT << endl;
			cout << "���� �������� {��.��.����} (" << dateToStr(t->_bdate = bday) << ") > ";
			getline(cin, tmp); // ���� ���� �������� � ��������� �������
			checkReturn(zach_num);

			// �������� ��������� ������ �� ������������ ������� � ������������ ����
			if (!bday.isValid(parseDotDate(tmp)) || parseDotDate(tmp).year >= t->_edate.year ) {
				cout << INVINP << " (�������� ���� �������� ��������� ���� �����������)" << endl;
				goto bdate_input;
			}

			bday = parseDotDate(tmp);

			t->_bdate = bday; break;
		}
		case 6: { // ��� �����������
			Date jdate;

		jdate_input:
			cout << EXITHINT << endl;
			cout << "��� ����������� {����} (" << to_string(t->_edate.year) << ") > ";
			getline(cin, tmp); // ���� ���� �����������
			checkReturn(zach_num);

			// �������� ����, ��� ��� �������� ������ � �������� � ��������� ���-�����
			if (!isValidInt(tmp) || stoi(tmp) < 0 || stoi(tmp) > 9999 || stoi(tmp) <= t->_bdate.year ) {
				cout << INVINP << " (�������� ���� �������� ������ ���� ��-���������)" << endl;
				goto jdate_input;
			}

			jdate.year = stoi(tmp);
			t->_edate = jdate; break;
		}
		case 7: { // ���������
			cout << EXITHINT << endl;
			cout << "��������� > ";
			getline(cin, tmp);  // ���� ����������
			checkReturn(zach_num);

			// ������ ������ �������
			tmp = trim(tmp);
			t->_fac = tmp;
			break;
		}
		case 8: { // �������
			cout << EXITHINT << endl;
			cout << "������� > ";
			getline(cin, tmp);  // ���� �������
			checkReturn(zach_num);

			// ������ ������ �������
			tmp = trim(tmp);
			t->_kaf = tmp;
			break;
		}
		case 9: { // ������
		gri:
			cout << EXITHINT << endl;
			cout << "������ > ";
			getline(cin, tmp); // ���� ������
			checkReturn(zach_num);

			// �������� �������� �� ������������ ��������
			if (!checkSpec(tmp, 1)) {
				cout << CHR_ERR << endl;
				goto gri;
			}
			t->_group = tmp;  break;

		}
		case 10: { // ����� �������
		zang:
			cout << EXITHINT << endl;
			cout << "����� ������� (" << t->_zach->_num << ") > ";
			getline(cin, tmp); // ���� ������ �������
			checkReturn(zach_num);

			// �������� ������������ � ���������� ��������� � ����� �� ������� �������
			if (checkSpec(tmp, 0) || !hasStudent(tmp))
				t->_zach->_num = tmp;
			else {
				cout << "����� ����� �������� ������ ��� ���������� ��� �����-��� ������������ �������!" << endl;
				goto zang;
			}
			 break;
		}
		case 11: { // �������/������
			cout << EXITHINT << endl;
		semnum:
			cout << "����� �������� > ";
			getline(cin, tmp); // ����� ��������, � ������� ����� ���������� �������
			checkReturn(zach_num);

			// �������� �������� �� ��������� � �������� �������� (��������� ���-�� 12)
			if (!isValidInt(tmp) || stoi(tmp) > 12 || stoi(tmp) < 1) {
				cout << INVINP << endl;
				goto semnum;
			}

			// ������� ��������� �� ��������� ������������� �������
			Semestr* tsem = t->_zach->_sems[stoi(tmp) - 1]; // ������ -1, ������ ��� ��������� ��� �� ����
			if (tsem->sc == 0) {
				cout << "� ���� ������ ��������� ���!" << endl;
				system("pause");
				cls;
				goto semnum;
			}
cstitle:
			cout << "�������� ��������, ������� �� ������ �������� > ";
			getline(cin, tmp); // ���� �������� ��������
			checkReturn(zach_num);

			// �������� ������� �������� � ����� ���������
			if (!tsem->hasSubj(tmp)) {
				cout << "������� �� ������!" << endl;
				goto cstitle;
			}

			// ������� ��������� �� �������, ������� ����� ��������
			Subj* tsub = tsem->getByTitle(tmp);

		subjmenu:
			cls;
			cout << "�� ������ ��������: " << endl;
			cout << "1. ��������" << endl;
			cout << "2. ������" << endl;
			cout << "> ";
			getline(cin, tmp); // ������ ����� ����
			checkReturn(zach_num);

			// ��������� ��������� ����� ���� �� ������������ ��������
			if (!isValidInt(tmp) || stoi(tmp) < 1 || stoi(tmp) > 2) {
				cout << INVINP << endl;
				goto subjmenu;
			}

			// ���� ������� ��������
			if (tmp == "1") {
			nstitle:
				cout << "����� �������� �������� > ";
				getline(cin, tmp); // ���� ������ ��������
				checkReturn(zach_num);

				// ���������, ��� �������� �� ������ � �� ���� ������� �����
				if (!tsem->hasSubj(tmp) && tmp != "") {
					tsub->title = trim(tmp);
				}
				else {
					cout << "������� � ����� ��������� ��� ���������� � ������ ������!" << endl;
					goto cstitle;
				}
			}
			else { // ������� ������
				cout << "����� ������ (1=���������, 2-5=������) > ";
				getline(cin, tmp); // ���� ������
				checkReturn(zach_num);

				// ���������, ��� ������ �������� � �������� ��������
				if (!isValidInt(tmp) || stoi(tmp) < 1 || stoi(tmp) > 5) {
					cout << INVINP << endl;
					goto cstitle;
				}
				else {
					tsub->mark = stoi(tmp);
				}
			}
			cls;
			break;

		}
		default:
			break;
		}

	return;
}


// �������� �������� � �����������
void Univer::addStudent(Student* S) {
	if (!hasStudent(S)) { // ���������, ��� �������� � ����� �������� �� ���� �����
		_students->addItem(S); // ��������
		N++; // ��������� ������� ������ ���-�� ���������
	}
	else {
		return;
	}
}

// ������� �������� �� ������������
void Univer::removeStudent(string zach) {
	_students->removeItem(zach);
	N--;
	system("pause");
}

// �������� ������� �������� � ������
int Univer::hasStudent(Student* S) {
		return hasStudent(S->_zach->_num);

	return 0;
}

// �������� ������� �������� � ������
int Univer::hasStudent(string zach_num) {
	if (N) // ���������, ��� ���� ���� �� ���� �������, ����� �� ������ � ����� ������
		   // ��������� ������� ������������ ��� ���������� ����� ���������
		for (int i = 0; i < _students->length; i++) { // ���� �� ���� ���������
			if (strCase((*_students)[i]._zach->_num, 0) == strCase(zach_num, 0)) {
				return 1;
			}
		}
	return 0;
}

// �������� ����� "��������" �� ������ �������
Student* Univer::getByZach(string zn) {
	for (int i = 0; i < _students->length; i++) {
		if (strCase((*_students)[i]._zach->_num, 0) == strCase(zn, 0)) {
			return &(*_students)[i];
		}
	}
}


// ������� ���������� ���� ��������� ������������
void Univer::showStudents() {
	// ���� �� ���� ��������� � ������
	for (int i = 0; i < _students->length; i++) {
		(*_students)[i].fullIntroduce();
		cout << "�������: "<<endl;
		(*_students)[i]._zach->showAll();
		cout << "------------------------------------------------------------------------" << endl;
	}
}

/*

	������� 10.
	������������� ���� ��������� �� ��������
	����������� ���������� ����� �� 1� � 2�
	��������

*/


float Univer::Threes(Student* tmpS){

	float count = 0, threes = 0;
	for (int j = 0; j < tmpS->_zach->sc;j++) {
		if (j > 1) {
			break;
		}
		for (int k = 0;k < tmpS->_zach->_sems[j]->sc;k++) {
			if (tmpS->_zach->_sems[j]->_subjects[k]->mark == 3) {
				threes++;
			}
			count++;
		}
	}
	if (count == 0) return 0;
	return threes/count;
}

void Univer::var10query() {
	float threes[N];
	float threes_sort[N];

	for (int i = 0; i < N; ++i){
		threes[i] = Threes(&((*_students)[i]));
		threes_sort[i] = Threes(&((*_students)[i]));
	}

	for (int j = 1; j < N; ++j){
		for (int i = 0; i < N-1; ++i){
			if (threes_sort[i] <  threes_sort[i+1]){
				float tmp = threes_sort[i];
				threes_sort[i] = threes_sort[i+1];
				threes_sort[i+1] = tmp;
			}
		}
	}

	for (float f1 : threes_sort){
		int i = 0;
		for (float f2 : threes){
			if (f1 == f2){
				(*_students)[i].fullIntroduce();
				cout << "�������: "<<endl;
				(*_students)[i]._zach->showAll();
				cout << "------------------------------------------------------------------------" << endl;
				break;
			}
			i++;
		}
	}

}



