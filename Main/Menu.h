#pragma once
#ifndef __MENU_H__
#define __MENU_H__
#include "Administrator.h"
#include "Borrower.h"

class Menu
{
public:
	Administrator admin;
	Borrower borrower;

	Menu();
	void showMainMenu();
	void showBorrowerMenu();
	void showAdministratorMenu();
};

#endif	//__MENU_H__
