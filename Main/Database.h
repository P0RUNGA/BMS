#pragma once
#ifndef __DATABASE_H__
#define __DATABASE_H__
#include "sqlite3.h"
#include "Book.h"
#include "Borrower.h"
#include <string>
#include <map>

struct List
{
	int id;
	int card;
	std::string name;
	int bid;
	std::string books;
	std::string bdate;
	std::string rdate;
};

class Database
{
public:
	sqlite3* pDB;
	std::map<std::string, Book> bookMap;
	std::map<int, Borrower> borrowerMap;
	std::map<std::string, List> listMap;
public:
	bool openDatabase();
	void closeDatabase();
	static int selectAllResult(void *NotUsed, int argc, char **argv, char **azColName);	// 回调函数
	void SQLite_query(const char* sql, int(*callback)(void *, int, char**, char**) = NULL); // 查询函数
	bool isEnough(const char* name);	// 判断int型字段值是否为0
	int  getIntFiled(const char *strSql);	// 取出数据库中的int型字段
	const char*  getStringFiled(const char *strSql);	// 取出数据库中的字符型字段
	void subFiled(const char* filed1, const char* table, const char* filed2, const char* limit);  // 使数据库中的字段减一
	void addFiled(const char* filed1, const char* table, const char* filed2, const char* limit);  // 使数据库中的字段增一
	void subFiled(const char* filed1, const char* table, const char* filed2, int limit);  // 使数据库中的字段减一（重载）
	void addFiled(const char* filed1, const char* table, const char* filed2, int limit);  // 使数据库中的字段增一（重载）
	void bookTOMap();	  // 将book数据放入字典
	void borrowerTOMap(); // 将borrower数据放入字典
	void listTOMap();	  // 将list数据放入字典
};

#endif	//__DATABASE_H__
