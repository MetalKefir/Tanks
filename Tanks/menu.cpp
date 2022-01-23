#include "menu.h"

// неявный конструктор.
Menu::Menu() {
	menu_title_ = "Главное меню";
};

// конструктор.
Menu::Menu(string menu_title_){
	this->menu_title_ = menu_title_;
}

// метод добавления элемента в главное меню или подменю.
void Menu::AddMenuItem(string itemTitle, Delegate used_class){
	menu_items_.push_back(*(new MenuItem(itemTitle, used_class)));
}

// метод добавления подменю в главное меню или другое подменю.
void Menu::AddMenuItem(string itemTitle, Menu *menu_object, bool sub) {
	menu_items_.push_back(*(new MenuItem(itemTitle, menu_object, sub)));
}

// метод вывода на экран пунктов и подменю.
void Menu::ShowMenu(vector<MenuItem>::iterator iItem_)
{
	system("cls");
	for (vector<MenuItem>::iterator it = menu_items_.begin(); it != menu_items_.end(); it++)
	{
		cout << (iItem_ == it ? "->" : " ") << it->title_ <<(it->subitem_  ? "...":" ") << endl;
	}
}

// функция заполнение вектора хранящего структуру меню.
vector<Items> FillVector(initializer_list<Items> il) {

	vector<Items> items;
	items.assign(il);

	return items;
}

//функция заполнение подменю
vector<Items>::iterator FillSubItem(Menu *subitem, vector<Items>::iterator &it, vector<Items>::iterator &end, short quanty) 
{

	for (short i = 0; i < quanty && it != end; i++, it++) 
	{

		if (!it->submenu_)
			subitem->AddMenuItem(it->title_, it->used_class_);

		else {

			Menu *subitem_ = new Menu;
			subitem->AddMenuItem(it->title_, subitem_, it->submenu_);

			it = FillSubItem(subitem_, it + 1, end, it->quanty_elem_);
		}
	}
	return it-1;
}

// функция заполнение меню 
void FillMenu(Menu &someMenu, vector<Items> items)
{
	
	for (vector<Items>::iterator it = items.begin(); it != items.end(); it++) 
	{

		if (!it->submenu_)
			someMenu.AddMenuItem(it->title_, it->used_class_);

		else {
			Menu *subitem = new Menu;
			someMenu.AddMenuItem(it->title_, subitem, it->submenu_);
			
			it = FillSubItem(subitem, it+1, items.end(), it->quanty_elem_);
		}
	}
}

/*****************
Управление меню.

iItem - начало вектора.

nLast - конец вектора.

*****************/
void Menu::MenuControl()
{
	vector<MenuItem>::iterator iItem = menu_items_.begin();
	vector<MenuItem>::iterator nLast = menu_items_.end() - 1;

	ShowMenu(iItem); // рендер меню

	while (TRUE)
	{
		if (GetAsyncKeyState(VK_UP)) // фиксируем нажатие кнопки.
		{
			keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0); // "отжимаем" кнопку. 
			
			if (menu_items_.begin() < iItem) // если не дошли до верха, то идем выше. Иначе переходим к последнему.
				iItem = iItem - 1;
			else
				iItem = nLast; 

			ShowMenu(iItem); // рендер меню
		}

		if (GetAsyncKeyState(VK_DOWN)) // фиксируем нажатие кнопки.
		{
			keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0); // "отжимаем" кнопку. 
			
			if (iItem < nLast) // если не дошли до низа, то идем ниже. Иначе переходим к первому.
				iItem = iItem + 1;
			else
				iItem = menu_items_.begin();

			ShowMenu(iItem); // рендер меню.
		}

		if (GetAsyncKeyState(VK_RIGHT)) // фиксируем нажатие кнопки.
		{
			keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0); // "отжимаем" кнопку.

			system("cls");

			if (!iItem->subitem_) // если это элемент вызываем для объекта подключенного класса хранящийся в пункте метод.
			{
				iItem->used_class_(); // вызов метода.

				cout << endl;

				Sleep(500); // ждем потверждение для продолжения
			}

			else // если это подменю, то для объекта класса меню вызываем метод управления.
			{
				iItem->sub_object_->MenuControl(); // вызов метода управления.
			}

			ShowMenu(iItem); // рендер меню. перересовка после исполнения команды.
		}

		if (GetAsyncKeyState(VK_LEFT)) // фиксируем нажатие кнопки.
		{
			keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0); // "отжимаем" кнопку. 

			if (this->menu_title_ != "Main menu") return; // если мы не в главном меню, то возвращаемся на шаг назад. 
		}

		if (GetAsyncKeyState(VK_ESCAPE)) // фиксируем нажатие кнопки.
		{
			keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0); // "отжимаем" кнопку. 
			exit(0); // выход.
		}	
	}
}