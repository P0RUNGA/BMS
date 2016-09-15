#include "stdafx.h"
#include "Administrator.h"
#include "Database.h"
#include <iostream>
#include <sstream>
#include <map>
using namespace std;
Database aDB;            //绑定一个数据库操作对象

void Administrator::putInStorage(Book& book)
{
	if (aDB.openDatabase())
	{
		// 查询数据库将数据放入map
		aDB.bookTOMap();

		map<string, Book>::iterator iter;
		iter = aDB.bookMap.find(book.name);
		if (iter == aDB.bookMap.end())
		{
			cout << "图书馆不存在该书，新书入库成功！" << endl;
			// 组织Sql语句
			stringstream strSql;
			strSql << "INSERT INTO book(name, author, publish, page, total, stock) VALUES('";
			strSql << book.name << "','";
			strSql << book.author << "','";
			strSql << book.publish << "',";
			strSql << book.page << ",";
			strSql << book.total << ",";
			strSql << book.stock << ")";
			
			// 执行Sql语句
			aDB.SQLite_query(strSql.str().c_str());
		}
		else
		{
			cout << "图书馆已存在该书，更新该书库存" << endl;
			// 取出该书旧的total
			stringstream strSql0;
			strSql0 << "SELECT total FROM book WHERE name = '" << book.name << "'";
			int oldTotal = aDB.getIntFiled(strSql0.str().c_str());
			// 取出该书旧的stock
			stringstream strSql;
			strSql << "SELECT stock FROM book WHERE name = '" << book.name << "'";
			int oldStock = aDB.getIntFiled(strSql.str().c_str());

			// 组织Sql语句
			stringstream strSql1;
			strSql1 << "UPDATE book SET total = " << (oldTotal + book.total) << " ,stock = " << (oldStock + book.stock) << " WHERE name = '" << book.name << "'";
			
			// 执行Sql语句
			aDB.SQLite_query(strSql1.str().c_str());
		}
		//关闭数据库
		aDB.closeDatabase();
	}
}

void Administrator::getBookMsg()
{
	if (aDB.openDatabase())
	{
		// 组织Sql语句
		stringstream strSql;
		strSql << "SELECT * FROM book";

		// 执行Sql语句
		aDB.SQLite_query(strSql.str().c_str(), aDB.selectAllResult);

		//关闭数据库
		aDB.closeDatabase();
	}
}

void Administrator::updateBookMsg()
{
	if (aDB.openDatabase())
	{
		// 组织Sql语句
		stringstream strSql, strSql1;
		string name, author, publish;
		int choice, id, page, total, stock;

		cout << "输入你要修改的图书的书号:" << endl;
		cin >> id;

		// 验证书籍是否真的存在
		strSql1 << "SELECT name FROM book WHERE id = " << id;
		if (aDB.getStringFiled(strSql1.str().c_str()) == NULL)
		{
			cout<< "图书馆不存在该书号的书籍，请确认书号是否正确！" << endl;
			return;
		}
		else
		{
			cout << "你要修改该书的哪一个字段？" << endl;
			cout << "1.书名 2.作者 3.出版社 4.书的页数 5.总量 6.库存" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:
				cout << "输入新的书名:" << endl;
				cin >> name;
				strSql << "UPDATE book SET name = '" << name << "' WHERE id = " << id;
				break;
			case 2:
				cout << "输入新的作者名：" << endl;
				cin >> author;
				strSql << "UPDATE book SET author = '" << author << "' WHERE id = " << id;
				break;
			case 3:
				cout << "输入新的出版社：" << endl;
				cin >> publish;
				strSql << "UPDATE book SET publish = '" << publish << "' WHERE id = " << id;
				break;
			case 4:
				cout << "输入新的书的页数：" << endl;
				cin >> page;
				strSql << "UPDATE book SET page = " << page << " WHERE id = " << id;
				break;
			case 5:
				cout << "输入新的总数：" << endl;
				cin >> total;
				strSql << "UPDATE book SET total = " << total << " WHERE id = " << id;
				break;
			case 6:
				cout << "输入新的库存量：" << endl;
				cin >> stock;
				strSql << "UPDATE book SET stock = " << stock << " WHERE id = " << id;
				break;
			default:
				cout << "输入错误！" << endl;
				break;
			}
			//执行Sql语句
			aDB.SQLite_query(strSql.str().c_str());
		}
		//关闭数据库
		aDB.closeDatabase();
	}
}

void Administrator::deleteBookMsg()
{
	if (aDB.openDatabase())
	{
		int id;
		cout<< "输入你要删除的书的书号：" << endl;
		cin >> id;

		// 验证书籍是否真的存在
		stringstream strSql1;
		strSql1 << "SELECT name FROM book WHERE id = " << id;
		if (aDB.getStringFiled(strSql1.str().c_str()) == NULL)
		{
			cout << "图书馆不存在该书号的书籍，请确认书号是否正确！" << endl;
			return;
		}
		else
		{
			// 组织Sql语句
			stringstream strSql;
			strSql << "DELETE FROM book WHERE id = " << id;

			//执行Sql语句
			aDB.SQLite_query(strSql.str().c_str());
		}
		//关闭数据库
		aDB.closeDatabase();
	}
}

void Administrator::getBorrowerMsg()
{
	if (aDB.openDatabase())
	{
		// 组织Sql语句
		stringstream strSql;
		strSql << "SELECT * FROM borrower";

		// 执行Sql语句
		aDB.SQLite_query(strSql.str().c_str(), aDB.selectAllResult);

		//关闭数据库
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

		cout << "输入你要修改的借书者的借书证:" << endl;
		cin >> card;

		// 验证借书者是否真的存在
		stringstream strSql1;
		strSql1 << "SELECT name FROM borrower WHERE card = " << card;
		if (aDB.getStringFiled(strSql1.str().c_str()) == NULL)
		{
			cout << "不存在该借书证，请确认借书证号是否正确！" << endl;
			return;
		}
		else
		{
			cout << "你要修改借书者的哪一个字段？" << endl;
			cout << "1.姓名 2.剩余可借书数 3.已借书数" << endl;
			cin >> choice;
			switch (choice)
			{
			case 1:
				cout << "输入新的姓名:" << endl;
				cin >> name;
				strSql << "UPDATE borrower SET name = '" << name << "' WHERE card = " << card;
				break;
			case 2:
				cout << "输入新的剩余可借书数：" << endl;
				cin >> canborrow;
				strSql << "UPDATE borrower SET canborrow = " << canborrow << " WHERE card = " << card;
				break;
			case 3:
				cout << "输入新的已借书数：" << endl;
				cin >> have;
				strSql << "UPDATE borrower SET have = " << have << " WHERE card = " << card;
				break;
			default:
				cout << "输入错误！" << endl;
				break;
			}
			//执行Sql语句
			aDB.SQLite_query(strSql.str().c_str());
		}
		//关闭数据库
		aDB.closeDatabase();
	}
}

void Administrator::deleteBorrowerMsg()
{
	if (aDB.openDatabase())
	{
		int card;
		cout << "输入你要删除的借书者的借书证：" << endl;
		cin >> card;

		// 验证借书者是否真的存在
		stringstream strSql1;
		strSql1 << "SELECT name FROM borrower WHERE card = " << card;
		if (aDB.getStringFiled(strSql1.str().c_str()) == NULL)
		{
			cout << "不存在该借书证，请确认借书证号是否正确！" << endl;
			return;
		}
		else
		{
			// 组织Sql语句
			stringstream strSql;
			strSql << "DELETE FROM borrower WHERE card = " << card;

			//执行Sql语句
			aDB.SQLite_query(strSql.str().c_str());
		}
		//关闭数据库
		aDB.closeDatabase();
	}
}
