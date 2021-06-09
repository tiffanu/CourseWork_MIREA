/*
 * Student.cpp
 *
 *      Author: trewu
 */

#include "Utils.h"
#include "Student.h"
#include "Zachetka.h"
#include <string>

#include <iostream>

// конструктор класса "студент"
Student::Student(string sname, string fname, string mname, int gender,  Date bdate, string group, string facul, string kaf, Date edate, Zachetka* zach){
	_sname = sname;
	_fname = fname;
	_mname = mname;
	_gender = gender;
	_bdate = bdate;
	_fac = facul;
	_kaf = kaf;
	_edate = edate;
	_group = group;
	_zach = zach;
}

// деструктор класса "студент"
Student::~Student() {
	delete _zach;
}

// функция, которая формирует строку для экспорта из данных всех студентов
// используется для записи базы данных в файл
string Student::dataForExport() {
	/*
		Структура блока студента имеет вид:
		(переносы строк  и пробелы отсутствуют,
		здесь добавлены для	большей читабельности)

		Фамилия (\1) Имя (\1) Отчество (\1) ПОЛ (\1)					// данные студента
		ДАТА РОЖДЕНИЯ (\1)ГОД ПОСТУПЛЕНИЯ (\1) ФАКУЛЬТЕТ (\1)			// дан-ные студента
		КАФЕДРА (\1) ГРУППА (\1) НОМЕР ЗАЧЁТКИ(\2)						// данные студента
		Subj1 (\2) 5 (\3) Subj2 (\2) 4 (\3)(\1)							// первый семестр с двумя предметами
		(\1)															// второй семестр - нет сессии
		Subj3 (\2) 5 (\3) Subj4 (\2) 4 (\3)(\1)							// третий семестр с двумя предметами
		(\6)															// конец данных студента

	*/

	string result; // строка, в которой формируется результат
	char s = '\1'; // разделитель
	string el = "\2"; // разделитель


	// Основная информация студента
	result.append(this->_sname + s + this->_fname + s + this->_mname + s + to_string(this->_gender)  + s);
	result.append(dateToStr(this->_bdate)  +s + dateToStr(this->_edate) + s +  this->_fac + s);
	result.append(this->_kaf + s + this->_group + s + this->_zach->_num  + el);

	// Информация о предметах и оценках
	result.append(_zach->dump());

	// Конец блока студента
	result.append("\6");

	return result;
}

// конструктор класса "студент" из строки
// используется при чтении данных из файла
Student::Student(string data) {
	int ch = 0;
	char c = '1';
	int i = 0;
	// переменные для хранения полученных из файла данных:
	string sname, fname, mname,
		gender, birth, edate,
		fac, kaf, group, zach_num;

	// цикл по каждому символу строки
	for (i;i < data.length();i++) {
		c = data[i];
		// если встретился разделитель поля личной информации - увеличить счётчик
		if (c == '\1') {
			ch++;
			continue;
		}
		else if (c == '\2')
		{ // (\2) конец личной информации и переход к оценкам
			break;
		}

		switch (ch) { // свитч для полей личной информации
			// структура описана в функции dataForExpotr()
		case 0: { // фамилия
			sname += c;break;
		}
		case 1: { // имя
			fname += c;break;
		}
		case 2: { // отчество
			mname += c;break;
		}
		case 3: { // пол
			gender += c;break;
		}
		case 4: { // дата рождения
			birth += c;break;
		}
		case 5: { // дата поступления
			edate += c;break;
		}
		case 6: { // факультет
			fac += c;break;
		}
		case 7: { // кафедра
			kaf += c;break;
		}
		case 8: { // группа
			group += c;break;
		}
		case 9: { // номер зачётной книжки
			zach_num += c;break;
		}
		default:
			break;
		}
	}

	_sname = sname;
	_fname = fname;
	_mname = mname;
	_gender = stoi(gender);
	_bdate = parseDotDate(birth);
	_fac = fac;
	_kaf = kaf;
	_edate.year = stoi(edate);
	_group = group;

	// Создание указателя на объект зачётки
	Zachetka* zach = new Zachetka(zach_num);

	// чтение следующего "блока" информации - семестры и оценки в них
	c = data[++i];
	while (c != '\6') {
		// создать указатель на новый семестр
		Semestr* sem = new Semestr();

		// чтение строки до конца семестра, который обозначен (\1)
		while (c != '\1' && c != '\6') {
			string stitle="", smark="";
			// запись названия предмета - кончается на (\2)
			while (c != '\2' && c != '\1') {
				stitle += c;
				c = data[++i];
			}
			c = data[++i];
			// запись оценки - кончается на (\3)
			while (c != '\3' && c != '\1') {
				smark += c;
				c = data[++i];
			}
			c = data[++i];

			//if ()
			// создать указатель на новый предмет
			Subj* sub = new Subj(stitle, stoi(smark));
			// добавить предмет в семестр
			sem->addSubj(sub);
		}

		// добавить семестр в зачётку
		zach->addSem(sem);

		c = data[++i];
	}

	_zach = zach;
}

// вывести всю информацию о студенте
void Student::fullIntroduce(){
	Person::fullIntroduce(); // функция вывода информации о человеке
	cout << "Номер зачётной книжки: " << this->_zach->_num << " | Год поступления: " << dateToStr(this->_edate) << endl;
	cout << "Группа: " << this->_group << " | Факультет: " << this->_fac << " | Кафед-ра: " << this->_kaf << endl;
}

// среднее арифметическое всех оценок за все семестры
float Student::fullAvg() {
return _zach->average() == -1 ? 0 : _zach->average(); // вернуть среднее арифметическое из зачётки
}



