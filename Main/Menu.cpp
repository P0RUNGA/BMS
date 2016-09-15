#include "stdafx.h"
#include "Menu.h"
#include "Book.h"
#include "Database.h"
#include <iostream>
const int PW = 123456;
using namespace std;
Database db;

Menu::Menu()
{
	admin = Administrator();
	borrower = Borrower();
}

void Menu::showMainMenu()
{
	int choice;
	do
	{
		cout << "****************ͼ�����ϵͳ***************" << endl;
		cout << "*                1. ������                *" << endl;
		cout << "*                2. ������                *" << endl;
		cout << "*                0.�˳�ϵͳ               *" << endl;
		cout << "*******************************************" << endl;
		cout << "���������ѡ��" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:showBorrowerMenu(); break;
		case 2:showAdministratorMenu(); break;
		case 0:break;
		default: break;
		}
	} while (choice != 0);
	cout << "Bye!" << endl;
}

void Menu::showBorrowerMenu()
{
	int choice;
	string name;
	do
	{
		cout << "****************������ҳ��****************" << endl;
		cout << "*              1. ע�����֤             *" << endl;
		cout << "*              2. �鿴�鼮��Ϣ           *" << endl;
		cout << "*              3. �鿴������Ϣ           *" << endl;
		cout << "*              4. �鿴�����б�           *" << endl;
		cout << "*              5. �����鼮               *" << endl;
		cout << "*              6. ����                   *" << endl;
		cout << "*              7. ����                   *" << endl;
		cout << "*              0. ����                   *" << endl;
		cout << "******************************************" << endl;

		cout << "������Ҫִ�еĲ�����" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "�������������" << endl;
			cin >> name;
			borrower.createBorrower(name);
			break;
		case 2:borrower.getBookMsg(); break;
		case 3:borrower.getBorrowerMsg(); break;
		case 4:borrower.getListMsg(); break;
		case 5:borrower.qureyBookByFiled(); break;
		case 6:borrower.borrowBook(); break;
		case 7:borrower.returnBook(); break;
		case 0:return;
		default:break;
		}
	} while (choice != 0);
}

void Menu::showAdministratorMenu()
{
	int choice, password, page, total, stock;
	string name, author, publish;
	Book book;

	cout << "������������룺" << endl;
	cin >> password;
	if (password == PW)
	{
		do
		{
			cout << "****************������ҳ��****************" << endl;
			cout << "*              1. �������               *" << endl;
			cout << "*              2. ��ʾ�鼮��Ϣ           *" << endl;
			cout << "*              3. �޸��鼮��Ϣ           *" << endl;
			cout << "*              4. ɾ���鼮��Ϣ           *" << endl;
			cout << "******************************************" << endl;
			cout << "*              5. ��ʾ��������Ϣ         *" << endl;
			cout << "*              6. �޸Ľ�������Ϣ         *" << endl;
			cout << "*              7. ɾ����������Ϣ         *" << endl;
			cout << "*              0. ����                   *" << endl;
			cout << "******************************************" << endl;

			cout << "������Ҫִ�еĲ�����" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:
				cout << "�����²ɱ����������Ϣ:" << endl;
				cout << "���������� ";	cin >> name;
				cout << "������������ ";	cin >> author;
				cout << "�����鼮�����磺 "; cin >> publish;
				cout << "�����鱾ҳ���� "; cin >> page;
				cout << "����ɱ���鼮��������"; cin >> total;
				stock = total;
				book.SetBookMsg(name, author, publish, page, total, stock);
				admin.putInStorage(book);
				break;
			case 2:admin.getBookMsg(); break;
			case 3:admin.updateBookMsg(); break;
			case 4:admin.deleteBookMsg(); break;
			case 5:admin.getBorrowerMsg(); break;
			case 6:admin.updateBorrowerMsg(); break;
			case 7:admin.deleteBorrowerMsg(); break;
			case 0:return;
			default:break;
			}
		} while (choice != 0);
	}
	else
	{
		cout << "�������" << endl;
		return;
	}
}
