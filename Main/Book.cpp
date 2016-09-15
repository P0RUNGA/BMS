#include "stdafx.h"
#include "Book.h"
#include <iostream>
using namespace std;

Book::Book()
{
	this->id = 0;
	this->name = "";
	this->author = "";
	this->publish = "";
	this->page = 0;
	this->total = 0;
	this->stock = 0;
}

void Book::ShowBookMsg() const
{
	cout << "���Ϊ:" << this->id << endl;
	cout << "����Ϊ:" << this->name << endl;
	cout << "���������:" << this->author << endl;
	cout << "��ĳ�������:" << this->publish << endl;
	cout << "�鱾��ҳ��:" << this->page << endl;
	cout << "�������:" << this->total << endl;
	cout << "��Ŀ��:" << this->stock << endl;
}

void Book::SetBookMsg(std::string name, std::string author, std::string publish, int page, int total, int stock, int id)
{
	this->id = id;
	this->name = name;
	this->author = author;
	this->publish = publish;
	this->page = page;
	this->total = total;
	this->stock = stock;
}
