#pragma once

#ifndef __BOOK_H__
#define __BOOK_H__
#include <string>

/**
*	ͼ����
*/
class Book
{
public:
	Book();
	void ShowBookMsg() const;	// ��ʾ�鱾����Ϣ
	void SetBookMsg(std::string name, std::string author, std::string publish, int page, int total, int stock, int id = 0);	//	�������Գ�Ա
public:
	int id;	               //���
	std::string name;      //����
	std::string author;    //����
	std::string publish;   //������
	int page;		       //�鱾��ҳ��
	int total;             //ͼ��ݲ�����
	int stock;			   //ʣ������
};

#endif	//__BOOK_H__
