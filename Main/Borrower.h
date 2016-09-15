#pragma once
#ifndef __BORROWER_H__
#define __BORROWER_H__
#include <string>

class Borrower
{
public:
	int card;			     //借书者的借书证
	std::string name;	     //借书者的姓名
	int canBorrow;		     //还可以借几本书
	int have;		         //现在有几本书
public:
	Borrower();
	Borrower(int card, const char* name, int canBorrow, int have);
	void createBorrower(std::string name);	//创建一个借书者
	void getBookMsg();						//查看书籍信息
	void qureyBookByFiled();				//根据特定字段查找书籍
	void borrowBook();						//借书
	void returnBook();						//还书
	void getBorrowerMsg();					//查看借书者个人信息
	void getListMsg();						//查看个人借书情况
};

#endif	//__BORROWER_H__
