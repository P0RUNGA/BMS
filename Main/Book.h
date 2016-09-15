#pragma once

#ifndef __BOOK_H__
#define __BOOK_H__
#include <string>

/**
*	图书类
*/
class Book
{
public:
	Book();
	void ShowBookMsg() const;	// 显示书本的信息
	void SetBookMsg(std::string name, std::string author, std::string publish, int page, int total, int stock, int id = 0);	//	设置属性成员
public:
	int id;	               //书号
	std::string name;      //书名
	std::string author;    //作者
	std::string publish;   //出版社
	int page;		       //书本的页数
	int total;             //图书馆藏书数
	int stock;			   //剩余库存数
};

#endif	//__BOOK_H__
