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
	cout << "书号为:" << this->id << endl;
	cout << "书名为:" << this->name << endl;
	cout << "书的作者是:" << this->author << endl;
	cout << "书的出版社是:" << this->publish << endl;
	cout << "书本的页数:" << this->page << endl;
	cout << "书的总数:" << this->total << endl;
	cout << "书的库存:" << this->stock << endl;
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
