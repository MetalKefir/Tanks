#pragma once
#include "Delegate.h"

// ��������� ������ ������ ��� �������� ���������.
#include<iostream>
#include<windows.h>
#include <vector>
#include<string>

using namespace std;

// ��������� Items ������������ ��� ������������� ��������� ����.
struct Items {
	string title_; // ��� ������.

	Delegate used_class_; // ������� ��� �������� ������� � ������

	bool submenu_ = false; // ��������� ������� true-������� �������, false-�������������� ������ �������.
	unsigned int quanty_elem_ = 0; // ���������� ������� �������.

	/*************************
	�������� ����������� ��� ������� �������.

		title - ���.

		*object - ��������� �� ������ ������������ ������.

		void(T::*proc)() - ������ �� ����� ������������ ������.

	*************************/
 template<class T>	Items(string title, T *object, void(T::*proc)()) {
		title_ = title;
		used_class_.Connect(object,proc); // ������������� ��������.
	}

	/*************************
	����������� ��� �������.

		title - ���. 

		Quantity - ���������� ���������.

	*************************/
	Items(string title, unsigned int quanty = 0, bool subitem = true) {
		title_ = title;
		submenu_ = subitem;
		quanty_elem_ = quanty;
	}
};


/******************************************
	������� ����� ���������� ���� � �������.

private:
		MenuItem - ��������� ������������ ��� �������� ��������� ����.

		menu_title_ - ������, ������ ��� ����/�������/��������.

		menu_items - ������, ������ ������ ���������/������� ����������� � ������� �������� ���� ��� ������� �������.

public:
		Menu() - ������� �����������.

		Menu(string menu_title) - �����������.

	/************************************
		void AddMenuItem(string item_title, void(T::*procLink)()) - ����� ���������� �������� � ������� ��� �������.

		item_title - ������, �������� ��� ������.

		void(T::*procLink)() - ��������� �� �����, ������ ��������������� ����� ������������� ������.


	/************************************
		void AddMenuItem(string item_title, Menu *submenu_object, bool subitem) - ����� ���������� ������� � ������� ��� �������.

		item_title - ������, �������� ��� ������.

		*submenu_object - ��������� �� ������ ����������� �������.

		subitem - ����, ��������� ��� ��� ������� (��������� ��� ���� ����������� ����).


	/************************************
		void MenuControl() - ���������� ����.


	/************************************
		void ShowMenu(vector<MenuItem>::iterator iItem) - ����� ������ �� ����� ������� � �������.

		iItem - ������� ������������ ����� ����� ������ ������.


	/************************************
		friend void FillMenu(Menu &someMenu, vector<Items> items) - ������� ���������� ����

		&someMenu- ����� �� ������ ������ Menu, ������������ ����� ������� ����.

		items - ������ �������� ��������� ���� (���, �����) �, ���� �����, ���������� ���������� � ���� ���������.


	/************************************
		friend vector<Items>  FillVector(initializer_list<Items> il) - ������� ���������� ������� ��������� ��������� ����.

		list_init - ��������� ���� initializer_list<Items>

	/************************************
		friend vector<Items>::iterator FillSubItem(Menu *subitem, vector<Items>::iterator &it, vector<Items>::iterator &end, short quanty = 1) - ������� ���������� �������.

		*subitem - ��������� �� ������ �������.

		&it - ������ �� ��������� � �������� ���������� �������.

		&end - ����� ����.

		quanty - ���������� ���������.

		���������� ��������� �� ������ ������� ����� ����� �������.



	 
	initializer_list - http://ru.cppreference.com/w/cpp/utility/initializer_list .

	vector - https://msdn.microsoft.com/ru-ru/library/9xd04bzs.aspx , https://ru.wikipedia.org/wiki/Vector_(C%2B%2B) .

******************************************/
class Menu
{
private:
	// ��������� MenuItem ������������� ��� ������� ��������� ����.
	struct MenuItem
	{
		string title_; // ��� �������� ��� �������.

		Delegate used_class_; // ������� ��� �������� ������� � ������

		bool subitem_ = false; //��������� ������� true-������� �������, false-�������������� ������ �������.

		Menu *sub_object_ = new Menu; //������ ����������� �������.
		
		/*********************************
			����������� ��������� ����/�������.

			title - ��� ������.

			used_class - ������� ������������ ������. 
		*********************************/
		MenuItem(string title, Delegate used_class){
			title_ = title;
			used_class_ = used_class;
		}

		/*********************************
			����������� ������� ����.

			title - ��� �������.

			*sub_object - ��������� �� �������������� ������ ���������� �������.

			subitem_ - ���� �������.
		*********************************/
		MenuItem(string title, Menu *sub_object, bool subitem){
			title_ = title;
			sub_object_ = sub_object;
			subitem_ = subitem;
		}
	};

	string menu_title_; // ������, ������ ��� ����/�������/��������.
	
	vector<MenuItem> menu_items_; // ������ ������ ���������/������� ����������� � ������� �������� ���� ��� ������� �������.

public:
	Menu(); // ������� �����������.
	Menu(string menu_title); // �����������.
	
	void AddMenuItem(string item_title, Delegate used_class); // ����� ���������� �������� � ������� ���� ��� �������.
	void AddMenuItem(string item_title, Menu *submenu_object, bool subitem); // ����� ���������� ������� � ������� ���� ��� ������ �������.

    void MenuControl(); // ���������� ����.

	void ShowMenu(vector<MenuItem>::iterator iItem); // ����� ������ �� ����� ������� � �������.

	friend vector<Items>::iterator FillSubItem(Menu *subitem,vector<Items>::iterator &it, vector<Items>::iterator &end, short quanty = 1); // ������� ���������� �������.
	friend void FillMenu(Menu &someMenu, vector<Items> items); // ������� ���������� ���� 
	friend vector<Items>  FillVector(initializer_list<Items> list_init); // ������� ���������� ������� ��������� ��������� ����.
};