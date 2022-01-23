#pragma once
#include "Delegate.h"

// поддержка класса вектор для хранения элементов.
#include<iostream>
#include<windows.h>
#include <vector>
#include<string>

using namespace std;

// Структура Items используется для представления структуры меню.
struct Items {
	string title_; // имя пункта.

	Delegate used_class_; // делегат для хранения объекта и метода

	bool submenu_ = false; // индикатор подменю true-элемент подменю, false-соответственно просто функция.
	unsigned int quanty_elem_ = 0; // количество пунктов подменю.

	/*************************
	шаблоный конструктор для обычных пунктов.

		title - имя.

		*object - указатель на объект подключеного класса.

		void(T::*proc)() - ссылка на метод подключеного класса.

	*************************/
 template<class T>	Items(string title, T *object, void(T::*proc)()) {
		title_ = title;
		used_class_.Connect(object,proc); // инициализация делигата.
	}

	/*************************
	конструктор для подменю.

		title - имя. 

		Quantity - количество элементов.

	*************************/
	Items(string title, unsigned int quanty = 0, bool subitem = true) {
		title_ = title;
		submenu_ = subitem;
		quanty_elem_ = quanty;
	}
};


/******************************************
	Базовый класс реализации меню и подменю.

private:
		MenuItem - структура используется для хранения структуры меню.

		menu_title_ - строка, хранит имя меню/подменю/элемента.

		menu_items - вектор, хранит список элементов/подменю относящихся к объекту главного меню или другого подменю.

public:
		Menu() - неявный конструктор.

		Menu(string menu_title) - конструктор.

	/************************************
		void AddMenuItem(string item_title, void(T::*procLink)()) - метод добавления элемента в главное или подменю.

		item_title - строка, передает имя пункта.

		void(T::*procLink)() - указатель на метод, хранит соответствующий метод подключенного класса.


	/************************************
		void AddMenuItem(string item_title, Menu *submenu_object, bool subitem) - метод добавления подменю в главное или подменю.

		item_title - строка, передает имя пункта.

		*submenu_object - указатель на объект реализующий подменю.

		subitem - флаг, указывает что это подменю (требуется для авто составления меню).


	/************************************
		void MenuControl() - управление меню.


	/************************************
		void ShowMenu(vector<MenuItem>::iterator iItem) - метод вывода на экран пунктов и подменю.

		iItem - счетчик показывающий какой пункт сейчас выбран.


	/************************************
		friend void FillMenu(Menu &someMenu, vector<Items> items) - функция заполнение меню

		&someMenu- сылка на объект класса Menu, представляет собой главное меню.

		items - вектор хранящий структуру меню (имя, метод) и, если нужно, количество подпунктов и флаг подпункта.


	/************************************
		friend vector<Items>  FillVector(initializer_list<Items> il) - функция заполнение вектора хранящего структуру меню.

		list_init - переменая типа initializer_list<Items>

	/************************************
		friend vector<Items>::iterator FillSubItem(Menu *subitem, vector<Items>::iterator &it, vector<Items>::iterator &end, short quanty = 1) - функция заполнения подменю.

		*subitem - указатель на объект подменю.

		&it - ссылка на интератор с которого начинается подменю.

		&end - конец меню.

		quanty - количество элементов.

		Возвращает интератор на первый элемент после конца подменю.



	 
	initializer_list - http://ru.cppreference.com/w/cpp/utility/initializer_list .

	vector - https://msdn.microsoft.com/ru-ru/library/9xd04bzs.aspx , https://ru.wikipedia.org/wiki/Vector_(C%2B%2B) .

******************************************/
class Menu
{
private:
	// Структура MenuItem используеться для харания структуры меню.
	struct MenuItem
	{
		string title_; // имя элемента или подменю.

		Delegate used_class_; // делегат для хранения объекта и метода

		bool subitem_ = false; //индикатор подменю true-элемент подменю, false-соответственно просто функция.

		Menu *sub_object_ = new Menu; //объект реализующий подменю.
		
		/*********************************
			Конструктор элементов меню/подменю.

			title - имя пункта.

			used_class - делегат подключеного класса. 
		*********************************/
		MenuItem(string title, Delegate used_class){
			title_ = title;
			used_class_ = used_class;
		}

		/*********************************
			Конструктор подменю меню.

			title - имя подменю.

			*sub_object - указатель на соотвествующий объект реализации подменю.

			subitem_ - флаг подменю.
		*********************************/
		MenuItem(string title, Menu *sub_object, bool subitem){
			title_ = title;
			sub_object_ = sub_object;
			subitem_ = subitem;
		}
	};

	string menu_title_; // строка, хранит имя меню/подменю/элемента.
	
	vector<MenuItem> menu_items_; // хранит список элементов/подменю относящихся к объекту главного меню или другого подменю.

public:
	Menu(); // неявный конструктор.
	Menu(string menu_title); // конструктор.
	
	void AddMenuItem(string item_title, Delegate used_class); // метод добавления элемента в главное меню или подменю.
	void AddMenuItem(string item_title, Menu *submenu_object, bool subitem); // метод добавления подменю в главное меню или другое подменю.

    void MenuControl(); // управление меню.

	void ShowMenu(vector<MenuItem>::iterator iItem); // метод вывода на экран пунктов и подменю.

	friend vector<Items>::iterator FillSubItem(Menu *subitem,vector<Items>::iterator &it, vector<Items>::iterator &end, short quanty = 1); // функция заполнение подменю.
	friend void FillMenu(Menu &someMenu, vector<Items> items); // функция заполнение меню 
	friend vector<Items>  FillVector(initializer_list<Items> list_init); // функция заполнение вектора хранящего структуру меню.
};