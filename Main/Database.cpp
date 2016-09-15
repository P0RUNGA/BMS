#include "stdafx.h"
#include "Database.h"
#include <iostream>
#include <sstream>
using namespace std;
const char * DB_NAME = "mian.db";

bool Database::openDatabase()
{
	// 开启数据库
	this->pDB = NULL;
	int nRes = sqlite3_open(DB_NAME, &pDB);
	if (nRes != SQLITE_OK)
	{
		cout << "开启数据库失败: " << sqlite3_errmsg(pDB);
		sqlite3_close(pDB);
		return false;
	}
	else
	{
		// 开启数据库成功
		return true;
	}
}

void Database::closeDatabase()
{
	/* 关闭数据库 */
	sqlite3_close(this->pDB);
}

int Database::selectAllResult(void * NotUsed, int argc, char ** argv, char ** azColName)
{
	/* 回调函数 */
	for (int i = 0; i < argc; i++)
	{
		cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "  ";
	}
	cout << endl;

	return 0;
}

void Database::SQLite_query(const char * sql, int(*callback)(void *, int, char**, char**))
{
	char* cErrMsg;
	int nRes = sqlite3_exec(pDB, sql, callback, NULL, &cErrMsg);
	if (nRes != SQLITE_OK)
	{
		cout << "数据库操作失败： " << cErrMsg << endl;
		sqlite3_free(cErrMsg);
		sqlite3_close(pDB);
	}
	else
	{
		cout << "数据库操作成功！ " << endl;
	}
}

/*可以判断书本库存，也可以判断借书者可借书的数量*/
bool Database::isEnough(const char * strSql)
{
	int is_bEnough;

	is_bEnough = getIntFiled(strSql);

	if (is_bEnough == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int Database::getIntFiled(const char * strSql)
{
	int filed;
	sqlite3_stmt* stmt;
	int nRes = sqlite3_prepare(pDB, strSql, -1, &stmt, NULL);

	if (nRes != SQLITE_OK)
	{
		cout << "数据库操作错误！" << sqlite3_errmsg(pDB) << endl;
		return -1;
		sqlite3_finalize(stmt);
		sqlite3_close(pDB);
	}
	else
	{
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			filed = sqlite3_column_int(stmt, 0);
			break;
		}
		sqlite3_finalize(stmt);
		return filed;
	}
}

const char* Database::getStringFiled(const char * strSql)
{
	char* filed = nullptr;
	sqlite3_stmt* stmt;
	int nRes = sqlite3_prepare(pDB, strSql, -1, &stmt, NULL);

	if (nRes != SQLITE_OK)
	{
		cout << "数据库操作错误！" << sqlite3_errmsg(pDB) << endl;
		return NULL;
		sqlite3_finalize(stmt);
		sqlite3_close(pDB);
	}
	else
	{
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			filed = (char *)sqlite3_column_text(stmt, 0);
			break;
		}
		sqlite3_finalize(stmt);
		return filed;
	}
}

void Database::subFiled(const char* filed1, const char* table, const char* filed2, const char* limit)
{
	// 取出旧的value
	stringstream strSql1;
	strSql1 << "SELECT " << filed1 << " FROM " << table << " WHERE " << filed2 << " = '" << limit << "'";
	int oValue = getIntFiled(strSql1.str().c_str());

	// 插入新的value
	stringstream strSql2;
	strSql2 << "UPDATE " << table << " SET " << filed1 << " = " << (oValue - 1) << " WHERE " << filed2 << " = '" << limit << "'";
	SQLite_query(strSql2.str().c_str());
}

void Database::addFiled(const char * filed1, const char * table, const char * filed2, const char * limit)
{
	// 取出旧的value
	stringstream strSql1;
	strSql1 << "SELECT " << filed1 << " FROM " << table << " WHERE " << filed2 << " = '" << limit << "'";
	int oValue = getIntFiled(strSql1.str().c_str());

	// 插入新的value
	stringstream strSql2;
	strSql2 << "UPDATE " << table << " SET " << filed1 << " = " << (oValue + 1) << " WHERE " << filed2 << " = '" << limit << "'";
	SQLite_query(strSql2.str().c_str());
}

void Database::subFiled(const char * filed1, const char * table, const char * filed2, int limit)
{
	// 取出旧的value
	stringstream strSql1;
	strSql1 << "SELECT " << filed1 << " FROM " << table << " WHERE " << filed2 << " = " << limit;
	int oValue = getIntFiled(strSql1.str().c_str());

	// 插入新的value
	stringstream strSql2;
	strSql2 << "UPDATE " << table << " SET " << filed1 << " = " << (oValue - 1) << " WHERE " << filed2 << " = " << limit;
	SQLite_query(strSql2.str().c_str());
}

void Database::addFiled(const char * filed1, const char * table, const char * filed2, int limit)
{
	// 取出旧的value
	stringstream strSql1;
	strSql1 << "SELECT " << filed1 << " FROM " << table << " WHERE " << filed2 << " = " << limit;
	int oValue = getIntFiled(strSql1.str().c_str());

	// 插入新的value
	stringstream strSql2;
	strSql2 << "UPDATE " << table << " SET " << filed1 << " = " << (oValue + 1) << " WHERE " << filed2 << " = " << limit;
	SQLite_query(strSql2.str().c_str());
}

void Database::bookTOMap()
{
	// 清空原先的map
	bookMap.erase(bookMap.begin(), bookMap.end());

	int id, page, total, stock;
	string name, author, publish;
	sqlite3_stmt* stmt;
	
	int nRes = sqlite3_prepare(pDB, "SELECT * FROM book", -1, &stmt, NULL);
	if (nRes != SQLITE_OK)
	{
		cout << "数据库操作错误！" << sqlite3_errmsg(pDB) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(pDB);
	}
	else
	{
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			// 获取各个字段数据
			id = sqlite3_column_int(stmt, 0);
			name = (char* )sqlite3_column_text(stmt, 1);
			author = (char* )sqlite3_column_text(stmt, 2);
			publish = (char* )sqlite3_column_text(stmt, 3);
			page = sqlite3_column_int(stmt, 4);
			total = sqlite3_column_int(stmt, 5);
			stock = sqlite3_column_int(stmt, 6);

			// 先放入Book对象
			Book book;
			book.SetBookMsg(name, author, publish, page, total, stock, id);
			// 插入map
			bookMap.insert(map<string, Book>::value_type(name, book));
		}
		sqlite3_finalize(stmt);
	}
}

void Database::borrowerTOMap()
{
	// 清空原先的map
	borrowerMap.erase(borrowerMap.begin(), borrowerMap.end());

	int card, canborrow, have;
	string name;
	sqlite3_stmt* stmt;

	int nRes = sqlite3_prepare(pDB, "SELECT * FROM borrower", -1, &stmt, NULL);
	if (nRes != SQLITE_OK)
	{
		cout << "数据库操作错误！" << sqlite3_errmsg(pDB) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(pDB);
	}
	else
	{
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			// 获取各个字段数据
			card = sqlite3_column_int(stmt, 0);
			name = (char*)sqlite3_column_text(stmt, 1);
			canborrow = sqlite3_column_int(stmt, 2);
			have = sqlite3_column_int(stmt, 3);

			// 先放入Borrower对象
			Borrower borrower(card, name.c_str(), canborrow, have);
			// 插入map
			borrowerMap.insert(map<int, Borrower>::value_type(card, borrower));
		}
		sqlite3_finalize(stmt);
	}
}

void Database::listTOMap()
{
	// 清空原先的map
	listMap.erase(listMap.begin(), listMap.end());

	int id, bid, card;
	string name, books, bdate, rdate;
	sqlite3_stmt* stmt;

	int nRes = sqlite3_prepare(pDB, "SELECT * FROM list", -1, &stmt, NULL);
	if (nRes != SQLITE_OK)
	{
		cout << "数据库操作错误！" << sqlite3_errmsg(pDB) << endl;
		sqlite3_finalize(stmt);
		sqlite3_close(pDB);
	}
	else
	{
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			// 获取各个字段数据
			id = sqlite3_column_int(stmt, 0);
			card = sqlite3_column_int(stmt, 1);
			name = (char*)sqlite3_column_text(stmt, 2);
			bid = sqlite3_column_int(stmt, 3);
			books = (char*)sqlite3_column_text(stmt, 4);
			bdate = (char*)sqlite3_column_text(stmt, 5);
			rdate = (char*)sqlite3_column_text(stmt, 6);

			// 先放入List结构体对象
			List list = { id, card, name, bid, books, bdate, rdate };
			// 插入map
			listMap.insert(map<string, List>::value_type(books, list));
		}
		sqlite3_finalize(stmt);
	}
}
