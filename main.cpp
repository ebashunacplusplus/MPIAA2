#include <iostream>
#include <Windows.h>
#include <locale>
#include <conio.h>
#include "brain.h"

using namespace std;

int main() {
	string nameFile;
	int flag = -1,poleq, strok, page,s_menu = -1;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	double elapsed_seconds;
	std::chrono::time_point<std::chrono::system_clock> start, end;

	cout << "Введите имя файла: ";
	cin >> nameFile;
	Database myData(nameFile);
	cout << "\nС файла было считано " << myData.getDatasize() << " строк";
	_getch();
	
	while (flag != 0) {
		system("cls");
		cout << "0 - Выход" << endl;
		cout << "1 - Добавить данные" << endl;
		cout << "2 - Вывести всё" << endl;
		cout << "3 - Вывести страницу базы данных" << endl;
		cout << "4 - Вывести дубликаты" << endl;
		cout << "5 - Cортировки" << endl;
		cout << "-------------------------" << endl;
		cin >> flag;
		switch (flag)
		{
		case 6:
			myData.standart_sort();
			system("pause");
			break;
		case 0:
			exit(1);
		case 1:
			system("cls");
			myData.addData();
			break;
		case 2:
			system("cls");
			myData.showDatebase();
			_getch();
			break;
		case 3:
			system("cls");
			cout << "Количество записей на странице: ";
			cin >> strok;
			cout << "Номер страницы для вывода: ";
			cin >> page;
			myData.showPage(strok, page);
			break;
		case 4:
			system("cls");
			myData.showDuplicate();
			_getch();
			break;
		case 5:
			while (s_menu!=0) {
				system("cls");
				cout << "1 - По строковому полю" << endl;
				cout << "2 - По числовому полю" << endl;
				cout << "3 - Комбинированная" << endl;
				cout << "0 - Вернуться в меню" << endl;
				cin >> s_menu;
				switch (s_menu)
				{
				case 1:
					system("cls");
					cout << "1 - Название фирмы застройщика\n2 - Название улицы\nsort pole: ";
					cin >> poleq;
					if (poleq != 1 && poleq != 2) {
						cout << "Неправильно введено поле..." << endl;
						_getch();
						break;
					}

					start = std::chrono::system_clock::now();
					//myData.q_sort(0, myData.getDatasize() - 1, poleq);
					sort(myData.get_vector().begin(), myData.get_vector().end(), [](Developers& a, Developers& b) {return a.floors < b.floors; });
					end = std::chrono::system_clock::now();

					elapsed_seconds = std::chrono::duration<double>(end - start).count();

					printf("N: %d, time: %.5f sec\n", myData.getDatasize(), elapsed_seconds);

					//myData.showDatebase();
					_getch();
					break;
				case 2:
					system("cls");
					cin >> poleq;

					start = std::chrono::system_clock::now();
					//myData.b_sort(poleq);
					end = std::chrono::system_clock::now();
					elapsed_seconds = std::chrono::duration<double>(end - start).count();
					printf("N: %d, time: %.5f sec\n", myData.getDatasize(), elapsed_seconds);

					_getch();
					break;
				case 3:
					system("cls");
					cout << "1 - Название фирмы застройщика\n";
					cin >> poleq;
					if (poleq != 1) {
						cout << "Неправильно введено поле..." << endl;
						_getch();
						break;
					}
					myData.q_sort(0, myData.getDatasize() - 1, poleq);
					myData.combo_sort();
					break;
				case 0 :
					break;
				default:
					system("cls");
					cout << "Некорректный пункт меню...";
					_getch();
					break;
				}
			}
			s_menu = -1;
			break;
		default:
			system("cls");
			cout << "Некорректный пункт меню... Для продолжения нажмите любую клавишу";
			_getch();
			break;
		}

	}
	_getch();
	return 0;
}