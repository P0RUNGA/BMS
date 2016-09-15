#include "stdafx.h"
#include "Borrower.h"
#include "Database.h"
#include "Date.h"
#include <iostream>
#include <sstream>
using namespace std;
const int LIMIT = 20;
Database bDB;            //��һ�����ݿ��������

Borrower::Borrower()
{
	this->card = 0;
	this->name = "";
	this->canBorrow = 0;
	this->have = 0;
}

Borrower::Borrower(int card, const char * name, int canBorrow, int have)
{
	this->card = card;
	this->name = name;
	this->canBorrow = canBorrow;
	this->have = have;
}

void Borrower::createBorrower(string name)
{
	this->name = name;
	this->canBorrow = LIMIT;
	this->have = 0;

	// ����Ϣд�����ݿ�
	if (bDB.openDatabase())
	{
		// ��֯Sql���
		stringstream strSql;
		strSql << "INSERT INTO borrower(name, canborrow, have) VALUES('";
		strSql << name << "'," << LIMIT << "," << have << ")";
		
		//ִ��Sql��ѯ
		bDB.SQLite_query(strSql.str().c_str());

		// ��֯Sql���
		stringstream strSql1;
		strSql1 << "SELECT * FROM borrower WHERE name = '" << name << "'";

		cout << "�����������Ϣ�����μ���Ľ���֤�ţ������Ļ�����ϵ����Ա��" << endl;

		//ִ��Sql��ѯ
		bDB.SQLite_query(strSql1.str().c_str(), bDB.selectAllResult);

		// �ر����ݿ�
		bDB.closeDatabase();
	}
}

void Borrower::getBookMsg()
{
	if (bDB.openDatabase())
	{
		// ��֯Sql���
		stringstream strSql;
		strSql << "SELECT * FROM book";

		// ִ��Sql���
		bDB.SQLite_query(strSql.str().c_str(), bDB.selectAllResult);

		// �ر����ݿ�
		bDB.closeDatabase();
	}
}

void Borrower::qureyBookByFiled()
{
	if (bDB.openDatabase())
	{
		int choice, intFiled = 0;
		string strFiled = "";
		stringstream strSql, strSql1, strSql2;

		cout << "1.��� 2.���� 3.������ 4.������" << endl;
		cout << "������Ҫ�����ĸ��ֶβ�ѯ�鼮��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "������ţ�" << endl;
			cin >> intFiled;
			strSql << "SELECT * FROM book WHERE id =" << intFiled;
			strSql1 << "SELECT * FROM book WHERE id =" << intFiled;
			break;
		case 2:
			cout << "����������" << endl;
			cin >> strFiled;
			strSql << "SELECT * FROM book WHERE name = '" << strFiled << "'";
			strSql2 << "SELECT name FROM book WHERE name = '" << strFiled << "'";
			break;
		case 3:
			cout << "������������" << endl;
			cin >> strFiled;
			strSql << "SELECT * FROM book WHERE author = '" << strFiled << "'";
			strSql2 << "SELECT name FROM book WHERE author = '" << strFiled << "'";
			break;
		case 4:
			cout << "��������磺" << endl;
			cin >> strFiled;
			strSql << "SELECT * FROM book WHERE publish = '" << strFiled << "'";
			strSql2 << "SELECT name FROM book WHERE publish = '" << strFiled << "'";
			break;
		default:cout << "�������" << endl; break;
		}
		// ���ж��Ƿ���ڸ���
		if (bDB.getStringFiled(strSql1.str().c_str()) != NULL || bDB.getStringFiled(strSql2.str().c_str()) != NULL)
		{
			// ִ��Sql���
			bDB.SQLite_query(strSql.str().c_str(), bDB.selectAllResult);
		}
		else
		{
			cout << "ͼ��ݲ����ڸ��ֶε��鼮��" << endl;
			return;
		}
		// �ر����ݿ�
		bDB.closeDatabase();
	}
}

void Borrower::borrowBook()
{
	if (bDB.openDatabase())
	{
		string bookname;
		string borrowername;
		int card;

		cout << "��������Ҫ���ĵ����������" << endl;
		cin >> bookname;
		
		// �ж�ͼ����Ƿ��и��鼮
		bDB.bookTOMap();
		map<string, Book>::iterator iter;
		iter = bDB.bookMap.find(bookname);
		if (iter == bDB.bookMap.end())
		{
			cout << "��Ǹ��ͼ���û�и��鼮��" << endl;
		}
		else
		{
			// ��֯Sql���
			stringstream strSql;
			strSql << "SELECT stock FROM book WHERE name = '" << bookname << "'";

			if (bDB.isEnough(strSql.str().c_str()))
			{
				cout << "��������Ľ���֤(û����֤����ȥע�����֤)��" << endl;
				cin >> card;
				cout << "���������������" << endl;
				cin >> borrowername;

				// ��֯Sql���
				stringstream strSql;
				strSql << "SELECT canborrow FROM borrower WHERE card = " << card << " AND name ='" << borrowername << "'";
				if (bDB.isEnough(strSql.str().c_str()))
				{
					// �����ݿ����ݷŽ�map
					bDB.listTOMap();
					map<string, List>::iterator iter;
					iter = bDB.listMap.find(bookname);
					if (iter == bDB.listMap.end())
					{
						// ����stock����Ӧ�ü���1
						bDB.subFiled("stock", "book", "name", bookname.c_str());

						// ����canborrow����Ӧ�ü���1
						bDB.subFiled("canborrow", "borrower", "name", borrowername.c_str());

						// ����have����Ӧ������1
						bDB.addFiled("have", "borrower", "name", borrowername.c_str());

						// ��ȡ��ǰ����
						Date date;
						string bdate = date.getBDate();
						string rdate = date.getRDate();
						// ��֯Sql���
						stringstream strSql;
						strSql << "INSERT INTO list(card, name, bid, books, bdate, rdate) VALUES(" << card << ",'" << borrowername << "'," << bDB.bookMap.at(bookname).id << ",'" << bookname << "','" << bdate << "','" << rdate << "')";

						// ִ��Sql���
						bDB.SQLite_query(strSql.str().c_str());

						cout << "����ɹ�" << endl;
					}
					else
					{
						cout << "���Ѿ�������飬�޷���ν��ģ�" << endl;
					}
				}
				else
				{
					cout << "����������ޣ��޷����飡" << endl;
				}
			}
			else
			{
				cout << "��Ǹ�������治�㣬����ʧ�ܣ�" << endl;
			}
		}
		// �ر����ݿ�
		bDB.closeDatabase();
	}
}

void Borrower::returnBook()
{
	if (bDB.openDatabase())
	{
		int card;
		string bookname, borrowername;
		
		cout << "������Ҫ�������������" << endl;
		cin >> bookname;
		cout << "���������������" << endl;
		cin >> borrowername;
		cout<< "��������Ľ���֤��" << endl;
		cin >> card;

		// �ж������Ƿ�������
		bDB.listTOMap();
		map<string, List>::iterator iter;
		iter = bDB.listMap.find(bookname);

		if (iter != bDB.listMap.end() && bDB.listMap.at(bookname).card == card && bDB.listMap.at(bookname).name == borrowername)
		{
			// ����stock����Ӧ������1
			bDB.addFiled("stock", "book", "name", bookname.c_str());

			// ����have����Ӧ�ü���1
			bDB.subFiled("have", "borrower", "card", card);

			// ����canborrower����Ӧ������1
			bDB.addFiled("canborrow", "borrower", "card", card);

			// ��֯Sql���
			stringstream strSql;
			strSql << "DELETE FROM list WHERE books ='" << bookname << "' AND card = " << card;

			// ִ��Sql���
			bDB.SQLite_query(strSql.str().c_str());

			cout << "����ɹ���" << endl;
		}
		else
		{
			cout<< "�㲢û�н��Ĺ����飬�������ʧ�ܣ�" << endl;
		}
		// �ر����ݿ�
		bDB.closeDatabase();
	}
}

void Borrower::getBorrowerMsg()
{
	if (bDB.openDatabase())
	{
		int card;

		cout << "��������Ľ���֤�ţ����ǽ���֤������ϵ����Ա����" << endl;
		cin >> card;

		// ��֤�������Ƿ���Ĵ���
		stringstream strSql1;
		strSql1 << "SELECT name FROM borrower WHERE card = " << card;
		if (bDB.getStringFiled(strSql1.str().c_str()) == NULL)
		{
			cout << "����������λ�����ߣ���ȷ�ϵ������֤���Ƿ���ȷ��" << endl;
			return;
		}
		else
		{
			// ��֯Sql���
			stringstream strSql;
			strSql << "SELECT * FROM borrower WHERE card = " << card;

			// ִ��Sql���
			bDB.SQLite_query(strSql.str().c_str(), bDB.selectAllResult);
		}
		// �ر����ݿ�
		bDB.closeDatabase();
	}
	
}

void Borrower::getListMsg()
{
	if (bDB.openDatabase())
	{
		int card;

		cout << "��������Ľ���֤��" << endl;
		cin >> card;

		// ��֤�������Ƿ���Ĵ���
		stringstream strSql1;
		strSql1 << "SELECT name FROM borrower WHERE card = " << card;
		if (bDB.getStringFiled(strSql1.str().c_str()) == NULL)
		{
			cout << "����������λ�����ߣ���ȷ�ϵ������֤���Ƿ���ȷ��" << endl;
			return;
		}
		else
		{
			// ��֯Sql���
			stringstream strSql;
			strSql << "SELECT * FROM list WHERE card = " << card;

			// ִ��Sql���
			bDB.SQLite_query(strSql.str().c_str(), bDB.selectAllResult);

			// �ر����ݿ�
			bDB.closeDatabase();
		}
		// �ر����ݿ�
		bDB.closeDatabase();
	}
}
