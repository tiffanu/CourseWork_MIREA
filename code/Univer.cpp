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

// Конструктор университета
Univer::Univer(string title) {
	_title = title;
	// создать список студентов и записать его адрес в указатель
	_students = new StudentArray();
	N = 0;
}
// Получение строки, содержащей в себе все данные о студентах
// для дальнейшей записи в файл базы данных
string Univer::exportAll() {
	/*
				Структура файла имеет вид:
		(переносы строк  и пробелы отсутствуют,
		здесь добавлены для	большей читабельности)

		\1\3\3\7 Фамилия (\1) Имя (\1) Отчество (\1) ПОЛ (\1)			// дан-ные студента, \1\3\3\7 = заголовок для проверки
		ДАТА РОЖДЕНИЯ (\1)ГОД ПОСТУПЛЕНИЯ (\1) ФАКУЛЬТЕТ (\1)			// дан-ные студента
		КАФЕДРА (\1) ГРУППА (\1) НОМЕР ЗАЧЁТКИ(\2)						// данные студента
		Subj1 (\2) 5 (\3) Subj2 (\2) 4 (\3)(\1)							//  первый семестр с двумя предметами
		(\1)															// второй семестр - нет сессии
		Subj3 (\2) 5 (\3) Subj4 (\2) 4 (\3)(\1)							// третий семестр с двумя предметами
		(\6)															// конец данных студента, далее может быть такой же блок
		......															// другие студенты такого же вида
		(\0)
	*/
	string result; // переменная для накопления данных
	for (int i = 0; i < _students->length; i++) {
		// цикл по всем студентам списка, получаем данные каждого из них
		result.append((*_students)[i].dataForExport());
	}
	return result;
}

// Сохранить список студентов в файл
void Univer::saveAll()
{
	string* str1 = new string(exportAll());
	writeOut(str1);
	delete str1;
}

// Считать список студентов из файла
void Univer::loadAll()
{
	string data = readContents(); // чтение данных

	string oneStud; // переменная для хранения данных одного студента
	int i = 0;
	char c = data[i];
	while (c != '\0') {
		oneStud = "";
		// Блок одного студента кончается символом \6
		// до него и идёт цикл while
		while (c != '\6' && c != '\0') {
			c = data[i];
			oneStud += c;
			i++;
		}
		c = data[i];

		// создать студента и добавить в университет
		Student* ns = new Student(oneStud);
		addStudent(ns);
	}
}

// Деструктор университета
Univer::~Univer() {
	delete _students;
}

// Показать диалог изменения информации конкретного студента
void Univer::showStudentChangeDialog(string zn) {
	Student* s = getByZach(zn); // получить указатель на студента по номеру зачётки
	cout << "Введите номер пункта, в который хотите внести изменения:" << endl;
	cout << "1. Фамилия (" << s->_sname << ")" << endl;
	cout << "2. Имя (" << s->_fname << ")" << endl;
	cout << "3. Отчество (" << s->_mname << ")" << endl;
	cout << "4. Пол (" << to_string(s->_gender) << ")" << endl;
	cout << "5. День рождения (" << dateToStr(s->_bdate) << ")" << endl;
	cout << "6. Год поступления (" << to_string(s->_edate.year) << ")" << endl;
	cout << "7. Факультет (" << s->_fac << ")" << endl;
	cout << "8. Кафедра (" << s->_kaf << ")" << endl;
	cout << "9. Группа (" << s->_group << ")" << endl;
	cout << "10. Номер зачётки (" << s->_zach->_num << ")" << endl;
	cout << "11. Предмет" << endl;
	cout << "0. Выйти в главное меню" << endl;
	cout << "> ";

	n3g:
	string n; // переменная, в которую будет введен выбранный пункт меню
	getline(cin, n); // ввод пункта
	// проверка введенной строки на соответствие числу из интервала
	if (!isValidInt(n) || stoi(n) > 12 || stoi(n) < -1) {
		cls;
		goto n3g;
	}

	// Если выбран выход в меню - заканчиваем функцию
	// изменения студента и возвращаемся в меню
	if (n == "0")
	{
		cls;
		return;
	}

	// В ином случае вызываем функцию изменения конкретного поля
	// в объекте "студент"
	changeStudent(zn, stoi(n));
	cls;
	return;
}

// Функция для изменения информации о студенте
// Принимает номер зачётной книжки и номер поля, которое необходимо изменить
void Univer::changeStudent(string zach_num, int field) {
		string tmp; // переменная для ввода любого из полей ниже
		Student* t = getByZach(zach_num); // записать указатель на изменяемого сту-дента

		switch (field)
		{
		case 1: { // фамилия
		sne:
			cout << EXITHINT << endl; // EXITHINT - define из языкового файла
			cout << "Фамилия (" << t->_sname << ") > ";
			getline(cin, tmp); // ввод фамилии
			checkReturn(zach_num); // псевдо-функция из define в Utils.h
			// Проверяет, если в tmp введён 0, чтобы дать пользователю возмож-ность
			// прекратить редактирование поля

			// проверка фамилии на спец символы
			if (!checkSpec(tmp, 0)) {
				cout << CHR_ERR << endl; // CHR_ERR - define из языкового фай-ла
				goto sne;
			}
			t->_sname = tmp; break;
		}
		case 2: { // имя
		fne:
			cout << EXITHINT << endl;
			cout << "Имя (" << t->_fname << ") > ";
			getline(cin, tmp); // ввод имени
			checkReturn(zach_num); // проверка 0

			// проверка спецсимволов
			if (!checkSpec(tmp, 0)) {
				cout << CHR_ERR << endl;
				goto fne;
			}
			t->_fname = tmp; break;
		}
		case 3: { // отчество
		mne:
			cout << EXITHINT << endl;
			cout << "Отчество (" << t->_mname << ") > ";
			getline(cin, tmp); // ввод отчества
			checkReturn(zach_num); // проверка 0

			// проверка спецсимволов
			if (!checkSpec(tmp, 0)) {
				cout << CHR_ERR << endl;
				goto mne;
			}
			t->_mname = tmp; break;
		}
		case 4: { // пол
		gender_input:
			cout << "Пол [Ж,М] (" << to_string(t->_gender) << ") > ";
			getline(cin, tmp); // ввод пола
			checkReturn(zach_num); // проверка 0
			// проверка, что введенное значение является числом и при это 1 или 0
			if ((strCase(tmp, 0) != "ж") && (strCase(tmp, 0) != "м")) {
				cout << INVINP;
				goto gender_input;
			}

			tmp = (strCase(tmp, 0) == "м" ? "1" : "0");
			t->_gender = stoi(tmp); break;

		}
		case 5: { // дата рождения
			Date bday;
		bdate_input:
			cout << EXITHINT << endl;
			cout << "Дата рождения {дд.мм.ГГГГ} (" << dateToStr(t->_bdate = bday) << ") > ";
			getline(cin, tmp); // ввод даты рождения в указанном формате
			checkReturn(zach_num);

			// проверка введенной строки на соответствие шаблону и правильности даты
			if (!bday.isValid(parseDotDate(tmp)) || parseDotDate(tmp).year >= t->_edate.year ) {
				cout << INVINP << " (возможно дата рождения превышает дату поступления)" << endl;
				goto bdate_input;
			}

			bday = parseDotDate(tmp);

			t->_bdate = bday; break;
		}
		case 6: { // год поступления
			Date jdate;

		jdate_input:
			cout << EXITHINT << endl;
			cout << "Год поступления {ГГГГ} (" << to_string(t->_edate.year) << ") > ";
			getline(cin, tmp); // ввод года поступления
			checkReturn(zach_num);

			// проверка того, что год является числом и попадает в указанный диа-пазон
			if (!isValidInt(tmp) || stoi(tmp) < 0 || stoi(tmp) > 9999 || stoi(tmp) <= t->_bdate.year ) {
				cout << INVINP << " (возможно дата рождения больше даты по-ступления)" << endl;
				goto jdate_input;
			}

			jdate.year = stoi(tmp);
			t->_edate = jdate; break;
		}
		case 7: { // факультет
			cout << EXITHINT << endl;
			cout << "Факультет > ";
			getline(cin, tmp);  // ввод факультета
			checkReturn(zach_num);

			// убрать лишние пробелы
			tmp = trim(tmp);
			t->_fac = tmp;
			break;
		}
		case 8: { // кафедра
			cout << EXITHINT << endl;
			cout << "Кафедра > ";
			getline(cin, tmp);  // ввод кафедры
			checkReturn(zach_num);

			// убрать лишние пробелы
			tmp = trim(tmp);
			t->_kaf = tmp;
			break;
		}
		case 9: { // группа
		gri:
			cout << EXITHINT << endl;
			cout << "Группа > ";
			getline(cin, tmp); // ввод группы
			checkReturn(zach_num);

			// проверка значения на соответствие фильтрам
			if (!checkSpec(tmp, 1)) {
				cout << CHR_ERR << endl;
				goto gri;
			}
			t->_group = tmp;  break;

		}
		case 10: { // номер зачётки
		zang:
			cout << EXITHINT << endl;
			cout << "Номер зачётки (" << t->_zach->_num << ") > ";
			getline(cin, tmp); // ввод номера зачётки
			checkReturn(zach_num);

			// проверка спецсимволов и отсутствия студентов с таким же номером зачётки
			if (checkSpec(tmp, 0) || !hasStudent(tmp))
				t->_zach->_num = tmp;
			else {
				cout << "Такой номер зачётной книжки уже существует или содер-жит недопустимые символы!" << endl;
				goto zang;
			}
			 break;
		}
		case 11: { // предмет/оценка
			cout << EXITHINT << endl;
		semnum:
			cout << "Номер семестра > ";
			getline(cin, tmp); // номер семестра, в котором будет изменяться предмет
			checkReturn(zach_num);

			// проверка значения на попадание в заданный диапазон (семестров все-го 12)
			if (!isValidInt(tmp) || stoi(tmp) > 12 || stoi(tmp) < 1) {
				cout << INVINP << endl;
				goto semnum;
			}

			// создать указатель на выбранный пользователем семестр
			Semestr* tsem = t->_zach->_sems[stoi(tmp) - 1]; // индекс -1, потому что нумерация идёт от нуля
			if (tsem->sc == 0) {
				cout << "В этой сессии предметов нет!" << endl;
				system("pause");
				cls;
				goto semnum;
			}
cstitle:
			cout << "Название предмета, который вы хотите изменить > ";
			getline(cin, tmp); // ввод названия предмета
			checkReturn(zach_num);

			// проверка наличия предмета с таким названием
			if (!tsem->hasSubj(tmp)) {
				cout << "Предмет не найден!" << endl;
				goto cstitle;
			}

			// создать указатель на предмет, который будем изменять
			Subj* tsub = tsem->getByTitle(tmp);

		subjmenu:
			cls;
			cout << "Вы хотите изменить: " << endl;
			cout << "1. Название" << endl;
			cout << "2. Оценка" << endl;
			cout << "> ";
			getline(cin, tmp); // ввести пункт меню
			checkReturn(zach_num);

			// проверить введенный пункт меню на соответствие правилам
			if (!isValidInt(tmp) || stoi(tmp) < 1 || stoi(tmp) > 2) {
				cout << INVINP << endl;
				goto subjmenu;
			}

			// если выбрано название
			if (tmp == "1") {
			nstitle:
				cout << "Новое название предмета > ";
				getline(cin, tmp); // ввод нового названия
				checkReturn(zach_num);

				// проверить, что название не пустое и не было введено ранее
				if (!tsem->hasSubj(tmp) && tmp != "") {
					tsub->title = trim(tmp);
				}
				else {
					cout << "Предмет с таким названием уже существует в данной сессии!" << endl;
					goto cstitle;
				}
			}
			else { // выбрана оценка
				cout << "Новая оценка (1=пересдача, 2-5=оценка) > ";
				getline(cin, tmp); // ввод оценки
				checkReturn(zach_num);

				// проверить, что оценка попадает в заданный диапазон
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


// добавить студента в университет
void Univer::addStudent(Student* S) {
	if (!hasStudent(S)) { // проверить, что студента с такой зачёткой не было ранее
		_students->addItem(S); // добавить
		N++; // увеличить счётчик общего кол-ва студентов
	}
	else {
		return;
	}
}

// удалить студента из университета
void Univer::removeStudent(string zach) {
	_students->removeItem(zach);
	N--;
	system("pause");
}

// проверка наличия студента в списке
int Univer::hasStudent(Student* S) {
		return hasStudent(S->_zach->_num);

	return 0;
}

// проверка наличия студента в списке
int Univer::hasStudent(string zach_num) {
	if (N) // проверить, что есть хотя бы один студент, чтобы не упасть в самом начале
		   // поскольку функция используется при добавлении новых студентов
		for (int i = 0; i < _students->length; i++) { // цикл по всем студентам
			if (strCase((*_students)[i]._zach->_num, 0) == strCase(zach_num, 0)) {
				return 1;
			}
		}
	return 0;
}

// получить адрес "студента" по номеру зачётки
Student* Univer::getByZach(string zn) {
	for (int i = 0; i < _students->length; i++) {
		if (strCase((*_students)[i]._zach->_num, 0) == strCase(zn, 0)) {
			return &(*_students)[i];
		}
	}
}


// вывести информацию всех студентов университета
void Univer::showStudents() {
	// цикл по всем студентам в списке
	for (int i = 0; i < _students->length; i++) {
		(*_students)[i].fullIntroduce();
		cout << "Зачётка: "<<endl;
		(*_students)[i]._zach->showAll();
		cout << "------------------------------------------------------------------------" << endl;
	}
}

/*

	Вариант 10.
	Отсортировать всех студентов по убыванию
	процентного содержания троек за 1й и 2й
	семестры

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
				cout << "Зачётка: "<<endl;
				(*_students)[i]._zach->showAll();
				cout << "------------------------------------------------------------------------" << endl;
				break;
			}
			i++;
		}
	}

}



