#ifndef BRAIN_H
#define BRAIN_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <algorithm>
#include <chrono>

struct Developers
{
	std::string firmName;
	std::string adres;
	int numhouse;
	int series;
	int yearConstruction;
	int floors;
	bool operator== (Developers one) {
		if ((firmName == one.firmName) && (adres == one.adres) && (numhouse == one.numhouse) && (floors == one.floors) && (series == one.series) && (yearConstruction == one.yearConstruction)) return 1;
		return 0;
	}
	std::string get_poleStr(int i) {
		if (i == 1)return firmName;
		if (i == 2)return adres;
		return firmName;
	}
	int get_poleInt(int i) {
		if (i == 3)return numhouse;
		if (i == 4)return series;
		if (i == 5)return yearConstruction;
		if (i == 6)return floors;
		return numhouse;
	}
};

class Database {

public:
	Database(std::string nameFile);
	~Database()
	{
	}
	void combo_sort();
	void b_sort(int pole);
	void q_sort(int left, int right, int pole);
	void deleteDuplicate();
	void showDuplicate();
	void showPage(int, int) const; // это так чисто для отладки
	void showDatebase() const; // печатает всю базу данных
	void addData(); // добавляет элемент в базу данных
	int getDatasize() const { return table.size(); } // очевидно
	//int get_floors(int i) { return table[i].floors; }

	std::vector<Developers> get_vector() { return table; }

private:
	std::vector<Developers> table;
	std::vector<int> dupl;// индексы дублей в таблице
};


bool chekNumhouse(int num);
bool chekSeries(int series);
bool chekFloors(int floors);
bool chekYear(int year);
void drawLine();
void drawPage();
bool nestingmass(int a, std::vector<int> b);
void my_sort(std::vector<Developers>& backet, int p);

#endif // !BRAIN_H

