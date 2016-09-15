#pragma once
#ifndef __ADMINISTRATOR_H__
#define __ADMINISTRATOR_H__
#include "Book.h"
/**
 *	管理者类
 */
class Administrator
{
public:
	/* 管理图书 */
	void putInStorage(Book& book);		// 采编入库
	void getBookMsg();					// 获取图书信息
	void updateBookMsg();				// 修改图书信息
	void deleteBookMsg();				// 删除图书信息

	/* 管理借书者 */
	void getBorrowerMsg();				// 或取借书者信息
	void updateBorrowerMsg();			// 修改借书者信息
	void deleteBorrowerMsg();			// 删除借书者信息
};

#endif // __ADMINISTRATOR_H__
