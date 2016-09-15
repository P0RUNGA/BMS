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
	static int selectAllResult(void *NotUsed, int argc, char **argv, char **azColName);	// �ص�����
	void SQLite_query(const char* sql, int(*callback)(void *, int, char**, char**) = NULL); // ��ѯ����
	bool isEnough(const char* name);	// �ж�int���ֶ�ֵ�Ƿ�Ϊ0
	int  getIntFiled(const char *strSql);	// ȡ�����ݿ��е�int���ֶ�
	const char*  getStringFiled(const char *strSql);	// ȡ�����ݿ��е��ַ����ֶ�
	void subFiled(const char* filed1, const char* table, const char* filed2, const char* limit);  // ʹ���ݿ��е��ֶμ�һ
	void addFiled(const char* filed1, const char* table, const char* filed2, const char* limit);  // ʹ���ݿ��е��ֶ���һ
	void subFiled(const char* filed1, const char* table, const char* filed2, int limit);  // ʹ���ݿ��е��ֶμ�һ�����أ�
	void addFiled(const char* filed1, const char* table, const char* filed2, int limit);  // ʹ���ݿ��е��ֶ���һ�����أ�
	void bookTOMap();	  // ��book���ݷ����ֵ�
	void borrowerTOMap(); // ��borrower���ݷ����ֵ�
	void listTOMap();	  // ��list���ݷ����ֵ�
};

#endif	//__DATABASE_H__
