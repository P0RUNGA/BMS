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
		cout << "****************图书管理系统***************" << endl;
		cout << "*                1. 借书者                *" << endl;
		cout << "*                2. 管理者                *" << endl;
		cout << "*                0.退出系统               *" << endl;
		cout << "*******************************************" << endl;
		cout << "请输入你的选择：" << endl;
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
		cout << "****************借书者页面****************" << endl;
		cout << "*              1. 注册借书证             *" << endl;
		cout << "*              2. 查看书籍信息           *" << endl;
		cout << "*              3. 查看个人信息           *" << endl;
		cout << "*              4. 查看借书列表           *" << endl;
		cout << "*              5. 查找书籍               *" << endl;
		cout << "*              6. 借书                   *" << endl;
		cout << "*              7. 还书                   *" << endl;
		cout << "*              0. 返回                   *" << endl;
		cout << "******************************************" << endl;

		cout << "输入你要执行的操作：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "输入你的姓名：" << endl;
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

	cout << "输入管理者密码：" << endl;
	cin >> password;
	if (password == PW)
	{
		do
		{
			cout << "****************管理者页面****************" << endl;
			cout << "*              1. 新书入库               *" << endl;
			cout << "*              2. 显示书籍信息           *" << endl;
			cout << "*              3. 修改书籍信息           *" << endl;
			cout << "*              4. 删除书籍信息           *" << endl;
			cout << "******************************************" << endl;
			cout << "*              5. 显示借书者信息         *" << endl;
			cout << "*              6. 修改借书者信息         *" << endl;
			cout << "*              7. 删除借书者信息         *" << endl;
			cout << "*              0. 返回                   *" << endl;
			cout << "******************************************" << endl;

			cout << "输入你要执行的操作：" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:
				cout << "输入新采编入库的书的信息:" << endl;
				cout << "输入书名： ";	cin >> name;
				cout << "输入作者名： ";	cin >> author;
				cout << "输入书籍出版社： "; cin >> publish;
				cout << "输入书本页数： "; cin >> page;
				cout << "输入采编该书籍的总量："; cin >> total;
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
		cout << "密码错误！" << endl;
		return;
	}
}
