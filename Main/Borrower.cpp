#include "stdafx.h"
#include "Borrower.h"
#include "Database.h"
#include "Date.h"
#include <iostream>
#include <sstream>
using namespace std;
const int LIMIT = 20;
Database bDB;            //绑定一个数据库操作对象

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

	// 将信息写入数据库
	if (bDB.openDatabase())
	{
		// 组织Sql语句
		stringstream strSql;
		strSql << "INSERT INTO borrower(name, canborrow, have) VALUES('";
		strSql << name << "'," << LIMIT << "," << have << ")";
		
		//执行Sql查询
		bDB.SQLite_query(strSql.str().c_str());

		// 组织Sql语句
		stringstream strSql1;
		strSql1 << "SELECT * FROM borrower WHERE name = '" << name << "'";

		cout << "下面是你的信息，请牢记你的借书证号，遗忘的话请联系管理员！" << endl;

		//执行Sql查询
		bDB.SQLite_query(strSql1.str().c_str(), bDB.selectAllResult);

		// 关闭数据库
		bDB.closeDatabase();
	}
}

void Borrower::getBookMsg()
{
	if (bDB.openDatabase())
	{
		// 组织Sql语句
		stringstream strSql;
		strSql << "SELECT * FROM book";

		// 执行Sql语句
		bDB.SQLite_query(strSql.str().c_str(), bDB.selectAllResult);

		// 关闭数据库
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

		cout << "1.书号 2.书名 3.作者名 4.出版社" << endl;
		cout << "输入你要根据哪个字段查询书籍：" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "输入书号：" << endl;
			cin >> intFiled;
			strSql << "SELECT * FROM book WHERE id =" << intFiled;
			strSql1 << "SELECT * FROM book WHERE id =" << intFiled;
			break;
		case 2:
			cout << "输入书名：" << endl;
			cin >> strFiled;
			strSql << "SELECT * FROM book WHERE name = '" << strFiled << "'";
			strSql2 << "SELECT name FROM book WHERE name = '" << strFiled << "'";
			break;
		case 3:
			cout << "输入作者名：" << endl;
			cin >> strFiled;
			strSql << "SELECT * FROM book WHERE author = '" << strFiled << "'";
			strSql2 << "SELECT name FROM book WHERE author = '" << strFiled << "'";
			break;
		case 4:
			cout << "输入出版社：" << endl;
			cin >> strFiled;
			strSql << "SELECT * FROM book WHERE publish = '" << strFiled << "'";
			strSql2 << "SELECT name FROM book WHERE publish = '" << strFiled << "'";
			break;
		default:cout << "输入错误！" << endl; break;
		}
		// 先判断是否存在该书
		if (bDB.getStringFiled(strSql1.str().c_str()) != NULL || bDB.getStringFiled(strSql2.str().c_str()) != NULL)
		{
			// 执行Sql语句
			bDB.SQLite_query(strSql.str().c_str(), bDB.selectAllResult);
		}
		else
		{
			cout << "图书馆不存在该字段的书籍！" << endl;
			return;
		}
		// 关闭数据库
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

		cout << "请输入你要借阅的书的书名：" << endl;
		cin >> bookname;
		
		// 判断图书馆是否有该书籍
		bDB.bookTOMap();
		map<string, Book>::iterator iter;
		iter = bDB.bookMap.find(bookname);
		if (iter == bDB.bookMap.end())
		{
			cout << "抱歉，图书馆没有该书籍！" << endl;
		}
		else
		{
			// 组织Sql语句
			stringstream strSql;
			strSql << "SELECT stock FROM book WHERE name = '" << bookname << "'";

			if (bDB.isEnough(strSql.str().c_str()))
			{
				cout << "请输入你的借书证(没借书证的先去注册借书证)：" << endl;
				cin >> card;
				cout << "请输入你的姓名：" << endl;
				cin >> borrowername;

				// 组织Sql语句
				stringstream strSql;
				strSql << "SELECT canborrow FROM borrower WHERE card = " << card << " AND name ='" << borrowername << "'";
				if (bDB.isEnough(strSql.str().c_str()))
				{
					// 将数据库数据放进map
					bDB.listTOMap();
					map<string, List>::iterator iter;
					iter = bDB.listMap.find(bookname);
					if (iter == bDB.listMap.end())
					{
						// 更新stock，它应该减少1
						bDB.subFiled("stock", "book", "name", bookname.c_str());

						// 更新canborrow，它应该减少1
						bDB.subFiled("canborrow", "borrower", "name", borrowername.c_str());

						// 更新have，它应该增加1
						bDB.addFiled("have", "borrower", "name", borrowername.c_str());

						// 获取当前日期
						Date date;
						string bdate = date.getBDate();
						string rdate = date.getRDate();
						// 组织Sql语句
						stringstream strSql;
						strSql << "INSERT INTO list(card, name, bid, books, bdate, rdate) VALUES(" << card << ",'" << borrowername << "'," << bDB.bookMap.at(bookname).id << ",'" << bookname << "','" << bdate << "','" << rdate << "')";

						// 执行Sql语句
						bDB.SQLite_query(strSql.str().c_str());

						cout << "借书成功" << endl;
					}
					else
					{
						cout << "你已经借过该书，无法多次借阅！" << endl;
					}
				}
				else
				{
					cout << "到达借书上限，无法借书！" << endl;
				}
			}
			else
			{
				cout << "抱歉，该书库存不足，借书失败！" << endl;
			}
		}
		// 关闭数据库
		bDB.closeDatabase();
	}
}

void Borrower::returnBook()
{
	if (bDB.openDatabase())
	{
		int card;
		string bookname, borrowername;
		
		cout << "输入你要还的书的书名：" << endl;
		cin >> bookname;
		cout << "请输入你的姓名：" << endl;
		cin >> borrowername;
		cout<< "请输入你的借书证：" << endl;
		cin >> card;

		// 判断作者是否借过该书
		bDB.listTOMap();
		map<string, List>::iterator iter;
		iter = bDB.listMap.find(bookname);

		if (iter != bDB.listMap.end() && bDB.listMap.at(bookname).card == card && bDB.listMap.at(bookname).name == borrowername)
		{
			// 更新stock，它应该增加1
			bDB.addFiled("stock", "book", "name", bookname.c_str());

			// 更新have，它应该减少1
			bDB.subFiled("have", "borrower", "card", card);

			// 更新canborrower，它应该增加1
			bDB.addFiled("canborrow", "borrower", "card", card);

			// 组织Sql语句
			stringstream strSql;
			strSql << "DELETE FROM list WHERE books ='" << bookname << "' AND card = " << card;

			// 执行Sql语句
			bDB.SQLite_query(strSql.str().c_str());

			cout << "还书成功！" << endl;
		}
		else
		{
			cout<< "你并没有借阅过该书，还书操作失败！" << endl;
		}
		// 关闭数据库
		bDB.closeDatabase();
	}
}

void Borrower::getBorrowerMsg()
{
	if (bDB.openDatabase())
	{
		int card;

		cout << "请输入你的借书证号（忘记借书证号请联系管理员）：" << endl;
		cin >> card;

		// 验证借书者是否真的存在
		stringstream strSql1;
		strSql1 << "SELECT name FROM borrower WHERE card = " << card;
		if (bDB.getStringFiled(strSql1.str().c_str()) == NULL)
		{
			cout << "并不存在这位借书者，请确认的你借书证号是否正确！" << endl;
			return;
		}
		else
		{
			// 组织Sql语句
			stringstream strSql;
			strSql << "SELECT * FROM borrower WHERE card = " << card;

			// 执行Sql语句
			bDB.SQLite_query(strSql.str().c_str(), bDB.selectAllResult);
		}
		// 关闭数据库
		bDB.closeDatabase();
	}
	
}

void Borrower::getListMsg()
{
	if (bDB.openDatabase())
	{
		int card;

		cout << "请输入你的借书证：" << endl;
		cin >> card;

		// 验证借书者是否真的存在
		stringstream strSql1;
		strSql1 << "SELECT name FROM borrower WHERE card = " << card;
		if (bDB.getStringFiled(strSql1.str().c_str()) == NULL)
		{
			cout << "并不存在这位借书者，请确认的你借书证号是否正确！" << endl;
			return;
		}
		else
		{
			// 组织Sql语句
			stringstream strSql;
			strSql << "SELECT * FROM list WHERE card = " << card;

			// 执行Sql语句
			bDB.SQLite_query(strSql.str().c_str(), bDB.selectAllResult);

			// 关闭数据库
			bDB.closeDatabase();
		}
		// 关闭数据库
		bDB.closeDatabase();
	}
}
