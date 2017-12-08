#include "brain.h"

void my_sort_comb(std::vector<Developers> &backet, int p, int start, int end);

Database::Database(std::string nameFile) {
	std::ifstream fin;
	Developers x;
	fin.open(nameFile);
	if (fin) {
		while (!fin.eof()) {
			fin >> x.firmName >> x.adres >> x.numhouse >> x.series >> x.yearConstruction >> x.floors;
			table.push_back(x);
		}
		fin.close();
	}
	else {
		std::cout << "Ошибка открытия файла" << std::endl;
	}
}
void Database::showDatebase() const {
	drawLine();
	std::cout << std::setw(20) << "Фирма застройщика" << std::setw(20) << "Адресс" << std::setw(10) << "дом#" << std::setw(10) << "Серия" << std::setw(10) << "Год" << std::setw(10) << "Этажей" << std::endl;
	drawLine();
	for (int i = 0; i < table.size(); i++)
		std::cout << std::setw(20) << table[i].firmName << std::setw(20) <<
		table[i].adres << std::setw(10) << table[i].numhouse << std::setw(10) << table[i].series << std::setw(10) << table[i].yearConstruction << std::setw(10) <<
		table[i].floors << std::endl;
}

void Database::addData() {
	Developers temp;
	std::cout << "Фирма застройщика: ";
	std::cin >> temp.firmName;
	std::cout << "Адрес: ";
	std::cin >> temp.adres;
	do {
		std::cout << "Номер дома: ";
		std::cin >> temp.numhouse;
	} while (!chekNumhouse(temp.numhouse));
	do {
		std::cout << "Серия: ";
		std::cin >> temp.series;
	} while (!chekSeries(temp.series));
	do {
		std::cout << "Год постройки: ";
		std::cin >> temp.yearConstruction;
	} while (!chekYear(temp.yearConstruction));
	do {
		std::cout << "Количество этажей: ";
		std::cin >> temp.floors;
	} while (!chekFloors(temp.floors));
	table.push_back(temp);
	std::cout << "Данные успешно введены...";
}

void Database::showPage(int st, int page) const {
	int i, r, allPage;
	if (st <= 0 || page <= 0) {
		std::cout << "Некорректные данные...";
		_getch();
		return;
	}
	i = st * (page - 1);
	r = i + st;
	allPage = getDatasize() / st;
	if ((getDatasize() % st) > 0) allPage++;
	if (page > allPage) {
		std::cout << "Такой страницы не существует...";
		_getch();
		return;
	}
	drawLine();
	std::cout << std::setw(20) << "Фирма застройщика" << std::setw(20) << "Адресс" << std::setw(10) << "дом#" << std::setw(10) << "Серия" << std::setw(10) << "Год" << std::setw(10) << "Этажей" << std::endl;
	drawLine();
	drawPage();
	std::cout << "\t\t\t\t\t Page # " << page << std::endl;
	drawPage();
	while (i < r && i < getDatasize()) {
		std::cout << std::setw(20) << table[i].firmName << std::setw(20) <<
			table[i].adres << std::setw(10) << table[i].numhouse << std::setw(10) << table[i].series << std::setw(10) << table[i].yearConstruction << std::setw(10) <<
			table[i].floors << std::endl;
		i++;
	}
	_getch();
}
bool chekNumhouse(int num) {
	if (num <= 0 || num > 1000) {
		std::cout << "Некорректный номер дома. Попробуйте еще раз" << std::endl;
		return 0;
	}
	return 1;
}
bool chekSeries(int series) {
	if (series < 0) {
		std::cout << "Некорректная серия постройки. Попробуйте еще раз" << std::endl;
		return 0;
	}
	return 1;
}
bool chekFloors(int floors) {
	if (floors <= 0 || floors > 163) {
		std::cout << "Некорректное количество этажей. Попробуйте еще раз" << std::endl;
		return 0;
	}
	return 1;
}
bool chekYear(int year) {
	if (year < 1990 || year > 2020) {
		std::cout << "Некорректный год постройки. Попробуйте еще раз" << std::endl;
		return 0;
	}
	return 1;
}
void drawLine() {
	for (int i = 0; i < 47; i++)
		std::cout << "--";
	std::cout << "\n";
}
void drawPage() {
	for (int i = 0; i < 47; i++)
		std::cout << "**";
	std::cout << "\n";
}
void Database::showDuplicate() {
	int i, r, flag;
	int question;
	drawLine();
	std::cout << std::setw(20) << "Фирма застройщика" << std::setw(20) << "Адресс" << std::setw(10) << "дом#" << std::setw(10) << "Серия" << std::setw(10) << "Год" << std::setw(10) << "Этажей" << std::setw(10) << "Дублей" << std::endl;
	drawLine();
	for (i = 0; i < (int)table.size(); i++) {
		flag = 0;
		if (nestingmass(i, dupl)) {
			continue;
		}
		else {
			for (r = 0; r < (int)table.size(); r++) {
				if (table[i] == table[r] && i != r && !nestingmass(r, dupl)) {
					dupl.push_back(r);
					flag++;
				}
			}
		}
		if (flag > 0) {
			std::cout << std::setw(20) << table[i].firmName << std::setw(20) <<
				table[i].adres << std::setw(10) << table[i].numhouse << std::setw(10) << table[i].series << std::setw(10) << table[i].yearConstruction << std::setw(10) <<
				table[i].floors << std::setw(10) << flag << std::endl;
		}
	}
	if (dupl.empty()) {
		std::cout << "Дубликатов не найдено..." << std::endl;
	}
	else {
		drawLine();
		std::cout << "\nХотите удалить дубликаты? (1 - да/0 - нет)" << std::endl;
		do {
			std::cin >> question;
			switch (question)
			{
			case 1:
				deleteDuplicate();
				break;
			case 0:
				std::cout << "Дубликаты не были удалены...";
				dupl.clear();
				break;
			default:
				std::cout << "Неверный пункт меню...\n";
				break;
			}
		} while (question != 0 && question != 1);
	}
}
bool nestingmass(int a, std::vector<int> b) {
	for (int i = 0; i < (int)b.size(); i++)
		if (a == b[i]) return 1;
	return 0;
}
void Database::deleteDuplicate() {
	sort(dupl.begin(), dupl.end());
	for (int i = 0; i < dupl.size(); i++) {
		table.erase(table.begin() + dupl[i]);
		for (int r = 0; r < dupl.size(); r++)dupl[r]--;
	}
	dupl.erase(dupl.begin(), dupl.end());
	std::cout << "Дубликаты удалены...";
}

void Database::q_sort(int left, int right, int pole) {
	int i = left, j = right;
	auto pivot = table[(left + right) / 2].get_poleStr(pole);
	while (i <= j) {
		while (table[i].get_poleStr(pole) < pivot)i++;
		while (table[j].get_poleStr(pole) > pivot)j--;
		if (i <= j)	std::swap(table[i++], table[j--]);
	}
	if (left < j)q_sort(left, j, pole);
	if (i < right)q_sort(i, right, pole);
}

void Database::b_sort(int pole) {

	using std::cout;

	int n = table.size();
	int iter, rang;

	std::vector<std::vector<Developers>> backets(n);

	int max_elem, min_elem;
	max_elem = table[0].get_poleInt(pole);
	min_elem = table[0].get_poleInt(pole);

	for (int i = 0; i < table.size(); i++) {
		if (table[i].get_poleInt(pole) > max_elem)max_elem = table[i].get_poleInt(pole);
		if (table[i].get_poleInt(pole) < min_elem)min_elem = table[i].get_poleInt(pole);
	}

	rang = max_elem - min_elem;

	for (int i = 0; i < n; i++) {
		iter = ((n-1)*(table[i].get_poleInt(pole)- min_elem) / rang);
		backets[iter].push_back(table[i]);
	}

	for (int k = 0; k < backets.size(); k++) my_sort(backets[k], pole);
	table.clear();
	for (int i = 0; i < backets.size(); i++)
		for (int j = 0; j < backets[i].size(); j++) table.push_back(backets[i][j]);
}

void my_sort(std::vector<Developers> &backet, int p) {
	for (int i = 0; i < backet.size(); i++)
		for (int j = backet.size() - 1; j > i; j--)
			if (backet[i].get_poleInt(p)>backet[j].get_poleInt(p)) std::swap(backet[i],backet[j]);
}



void Database::combo_sort() {
	int start, end;

	for (int i = 0; i < table.size() - 1; i++) {

		if (table[i].firmName == table[i + 1].firmName) {
			start = i;
			while (table[i].firmName == table[i + 1].firmName) {
				end = i;
				i++;
			}
			end++;
			my_sort_comb(table, 6, start, end);
		}
	}
}

void my_sort_comb(std::vector<Developers> &backet, int p, int start, int end) {
	for (int i = start; i < end; i++)
		for (int j = end; j > i; j--)
			if (backet[i].get_poleInt(p)>backet[j].get_poleInt(p)) std::swap(backet[i], backet[j]);
}