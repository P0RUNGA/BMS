#include "stdafx.h"
#include "Administrator.h"
#include "Database.h"
#include <iostream>
#include <sstream>
#include <map>
using namespace std;
Database aDB;            //��һ�����ݿ��������

void Administrator::putInStorage(Book& book)
{
	if (aDB.openDatabase())
	{
		// ��ѯ���ݿ⽫���ݷ���map
		aDB.bookTOMap();

		map<string, Book>::iterator iter;
		iter = aDB.bookMap.find(book.name);
		if (iter == aDB.bookMap.end())
		{
			cout << "ͼ��ݲ����ڸ��飬�������ɹ���" << endl;
			// ��֯Sql���
			stringstream strSql;
			strSql << "INSERT INTO book(name, author, publish, page, total, stock) VALUES('";
			strSql << book.name << "','";
			strSql << book.author << "','";
			strSql << book.publish << "',";
			strSql << book.page << ",";
			strSql << book.total << ",";
			strSql << book.stock << ")";
			
			// ִ��Sql���
			aDB.SQLite_query(strSql.str().c_str());
		}
		else
		{
			cout << "ͼ����Ѵ��ڸ��飬���¸�����" << endl;
			// ȡ������ɵ�total
			stringstream strSql0;
			strSql0 << "SELECT total FROM book WHERE name = '" << book.name << "'";
			int oldTotal = aDB.getIntFiled(strSql0.str().c_str());
			// ȡ������ɵ�stock
			stringstream strSql;
			strSql << "SELECT stock FROM book WHERE name = '" << book.name << "'";
			int oldStock = aDB.getIntFiled(strSql.str().c_str());

			// ��֯Sql���
			stringstream strSql1;
			strSql1 << "UPDATE book SET total = " << (oldTotal + book.total) << " ,stock = " << (oldStock + book.stock) << " WHERE name = '" << book.name << "'";
			
			// ִ��Sql���
			aDB.SQLite_query(strSql1.str().c_str());
		}
		//�ر����ݿ�
		aDB.closeDatabase();
	}
}

void Administrator::getBookMsg()
{
	if (aDB.openDatabase())
	{
		// ��֯Sql���
		stringstream strSql;
		strSql << "SELECT * FROM book";

		// ִ��Sql���
		aDB.SQLite_query(strSql.str().c_str(), aDB.selectAllResult);

		//�ر����ݿ�
		aDB.closeDatabase();
	}
}

void Administrator::updateBookMsg()
{
	if (aDB.openDatabase())
	{
		// ��֯Sql���
		stringstream strSql, strSql1;
		string name, author, publish;
		int choice, id, page, total, stock;

		cout << "������Ҫ�޸ĵ�ͼ������:" << endl;
		cin >> id;

		// ��֤�鼮�Ƿ���Ĵ���
		strSql1 << "SELECT name FROM book WHERE id = " << id;
		if (aDB.getStringFiled(strSql1.str().c_str()) == NULL)
		{
			cout<< "ͼ��ݲ����ڸ���ŵ��鼮����ȷ������Ƿ���ȷ��" << endl;
			return;
		}
		else
		{
			cout << "��Ҫ�޸ĸ������һ���ֶΣ�" << endl;
			cout << "1.���� 2.���� 3.������ 4.���ҳ�� 5.���� 6.���" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:
				cout << "�����µ�����:" << endl;
				cin >> name;
				strSql << "UPDATE book SET name = '" << name << "' WHERE id = " << id;
				break;
			case 2:
				cout << "�����µ���������" << endl;
				cin >> author;
				strSql << "UPDATE book SET author = '" << author << "' WHERE id = " << id;
				break;
			case 3:
				cout << "�����µĳ����磺" << endl;
				cin >> publish;
				strSql << "UPDATE book SET publish = '" << publish << "' WHERE id = " << id;
				break;
			case 4:
				cout << "�����µ����ҳ����" << endl;
				cin >> page;
				strSql << "UPDATE book SET page = " << page << " WHERE id = " << id;
				break;
			case 5:
				cout << "�����µ�������" << endl;
				cin >> total;
				strSql << "UPDATE book SET total = " << total << " WHERE id = " << id;
				break;
			case 6:
				cout << "�����µĿ������" << endl;
				cin >> stock;
				strSql << "UPDATE book SET stock = " << stock << " WHERE id = " << id;
				break;
			default:
				cout << "�������" << endl;
				break;
			}
			//ִ��Sql���
			aDB.SQLite_query(strSql.str().c_str());
		}
		//�ر����ݿ�
		aDB.closeDatabase();
	}
}

void Administrator::deleteBookMsg()
{
	if (aDB.openDatabase())
	{
		int id;
		cout<< "������Ҫɾ���������ţ�" << endl;
		cin >> id;

		// ��֤�鼮�Ƿ���Ĵ���
		stringstream strSql1;
		strSql1 << "SELECT name FROM book WHERE id = " << id;
		if (aDB.getStringFiled(strSql1.str().c_str()) == NULL)
		{
			cout << "ͼ��ݲ����ڸ���ŵ��鼮����ȷ������Ƿ���ȷ��" << endl;
			return;
		}
		else
		{
			// ��֯Sql���
			stringstream strSql;
			strSql << "DELETE FROM book WHERE id = " << id;

			//ִ��Sql���
			aDB.SQLite_query(strSql.str().c_str());
		}
		//�ر����ݿ�
		aDB.closeDatabase();
	}
}

void Administrator::getBorrowerMsg()
{
	if (aDB.openDatabase())
	{
		// ��֯Sql���
		stringstream strSql;
		strSql << "SELECT * FROM borrower";

		// ִ��Sql���
		aDB.SQLite_query(strSql.str().c_str(), aDB.selectAllResult);

		//�ر����ݿ�
		aDB.closeDatabase();
	}
}

void Administrator::updateBorrowerMsg()
{
	if (aDB.openDatabase())
	{
		stringstream strSql;
		string name;
		int choice, card, canborrow, have;

		cout << "������Ҫ�޸ĵĽ����ߵĽ���֤:" << endl;
		cin >> card;

		// ��֤�������Ƿ���Ĵ���
		stringstream strSql1;
		strSql1 << "SELECT name FROM borrower WHERE card = " << card;
		if (aDB.getStringFiled(strSql1.str().c_str()) == NULL)
		{
			cout << "�����ڸý���֤����ȷ�Ͻ���֤���Ƿ���ȷ��" << endl;
			return;
		}
		else
		{
			cout << "��Ҫ�޸Ľ����ߵ���һ���ֶΣ�" << endl;
			cout << "1.���� 2.ʣ��ɽ����� 3.�ѽ�����" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:
				cout << "�����µ�����:" << endl;
				cin >> name;
				strSql << "UPDATE borrower SET name = '" << name << "' WHERE card = " << card;
				break;
			case 2:
				cout << "�����µ�ʣ��ɽ�������" << endl;
				cin >> canborrow;
				strSql << "UPDATE borrower SET canborrow = " << canborrow << " WHERE card = " << card;
				break;
			case 3:
				cout << "�����µ��ѽ�������" << endl;
				cin >> have;
				strSql << "UPDATE borrower SET have = " << have << " WHERE card = " << card;
				break;
			default:
				cout << "�������" << endl;
				break;
			}
			//ִ��Sql���
			aDB.SQLite_query(strSql.str().c_str());
		}
		//�ر����ݿ�
		aDB.closeDatabase();
	}
}

void Administrator::deleteBorrowerMsg()
{
	if (aDB.openDatabase())
	{
		int card;
		cout << "������Ҫɾ���Ľ����ߵĽ���֤��" << endl;
		cin >> card;

		// ��֤�������Ƿ���Ĵ���
		stringstream strSql1;
		strSql1 << "SELECT name FROM borrower WHERE card = " << card;
		if (aDB.getStringFiled(strSql1.str().c_str()) == NULL)
		{
			cout << "�����ڸý���֤����ȷ�Ͻ���֤���Ƿ���ȷ��" << endl;
			return;
		}
		else
		{
			// ��֯Sql���
			stringstream strSql;
			strSql << "DELETE FROM borrower WHERE card = " << card;

			//ִ��Sql���
			aDB.SQLite_query(strSql.str().c_str());
		}
		//�ر����ݿ�
		aDB.closeDatabase();
	}
}
