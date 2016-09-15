#pragma once
#ifndef __BORROWER_H__
#define __BORROWER_H__
#include <string>

class Borrower
{
public:
	int card;			     //�����ߵĽ���֤
	std::string name;	     //�����ߵ�����
	int canBorrow;		     //�����Խ輸����
	int have;		         //�����м�����
public:
	Borrower();
	Borrower(int card, const char* name, int canBorrow, int have);
	void createBorrower(std::string name);	//����һ��������
	void getBookMsg();						//�鿴�鼮��Ϣ
	void qureyBookByFiled();				//�����ض��ֶβ����鼮
	void borrowBook();						//����
	void returnBook();						//����
	void getBorrowerMsg();					//�鿴�����߸�����Ϣ
	void getListMsg();						//�鿴���˽������
};

#endif	//__BORROWER_H__
