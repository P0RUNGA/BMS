#pragma once
#ifndef __ADMINISTRATOR_H__
#define __ADMINISTRATOR_H__
#include "Book.h"
/**
 *	��������
 */
class Administrator
{
public:
	/* ����ͼ�� */
	void putInStorage(Book& book);		// �ɱ����
	void getBookMsg();					// ��ȡͼ����Ϣ
	void updateBookMsg();				// �޸�ͼ����Ϣ
	void deleteBookMsg();				// ɾ��ͼ����Ϣ

	/* ��������� */
	void getBorrowerMsg();				// ��ȡ��������Ϣ
	void updateBorrowerMsg();			// �޸Ľ�������Ϣ
	void deleteBorrowerMsg();			// ɾ����������Ϣ
};

#endif // __ADMINISTRATOR_H__
