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

	cout << "������� ��� �����: ";
	cin >> nameFile;
	Database myData(nameFile);
	cout << "\n� ����� ���� ������� " << myData.getDatasize() << " �����";
	_getch();
	
	while (flag != 0) {
		system("cls");
		cout << "0 - �����" << endl;
		cout << "1 - �������� ������" << endl;
		cout << "2 - ������� ��" << endl;
		cout << "3 - ������� �������� ���� ������" << endl;
		cout << "4 - ������� ���������" << endl;
		cout << "5 - C���������" << endl;
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
			cout << "���������� ������� �� ��������: ";
			cin >> strok;
			cout << "����� �������� ��� ������: ";
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
				cout << "1 - �� ���������� ����" << endl;
				cout << "2 - �� ��������� ����" << endl;
				cout << "3 - ���������������" << endl;
				cout << "0 - ��������� � ����" << endl;
				cin >> s_menu;
				switch (s_menu)
				{
				case 1:
					system("cls");
					cout << "1 - �������� ����� �����������\n2 - �������� �����\nsort pole: ";
					cin >> poleq;
					if (poleq != 1 && poleq != 2) {
						cout << "����������� ������� ����..." << endl;
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
					cout << "1 - �������� ����� �����������\n";
					cin >> poleq;
					if (poleq != 1) {
						cout << "����������� ������� ����..." << endl;
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
					cout << "������������ ����� ����...";
					_getch();
					break;
				}
			}
			s_menu = -1;
			break;
		default:
			system("cls");
			cout << "������������ ����� ����... ��� ����������� ������� ����� �������";
			_getch();
			break;
		}

	}
	_getch();
	return 0;
}