#include "menu.h"

// ������� �����������.
Menu::Menu() {
	menu_title_ = "������� ����";
};

// �����������.
Menu::Menu(string menu_title_){
	this->menu_title_ = menu_title_;
}

// ����� ���������� �������� � ������� ���� ��� �������.
void Menu::AddMenuItem(string itemTitle, Delegate used_class){
	menu_items_.push_back(*(new MenuItem(itemTitle, used_class)));
}

// ����� ���������� ������� � ������� ���� ��� ������ �������.
void Menu::AddMenuItem(string itemTitle, Menu *menu_object, bool sub) {
	menu_items_.push_back(*(new MenuItem(itemTitle, menu_object, sub)));
}

// ����� ������ �� ����� ������� � �������.
void Menu::ShowMenu(vector<MenuItem>::iterator iItem_)
{
	system("cls");
	for (vector<MenuItem>::iterator it = menu_items_.begin(); it != menu_items_.end(); it++)
	{
		cout << (iItem_ == it ? "->" : " ") << it->title_ <<(it->subitem_  ? "...":" ") << endl;
	}
}

// ������� ���������� ������� ��������� ��������� ����.
vector<Items> FillVector(initializer_list<Items> il) {

	vector<Items> items;
	items.assign(il);

	return items;
}

//������� ���������� �������
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

// ������� ���������� ���� 
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
���������� ����.

iItem - ������ �������.

nLast - ����� �������.

*****************/
void Menu::MenuControl()
{
	vector<MenuItem>::iterator iItem = menu_items_.begin();
	vector<MenuItem>::iterator nLast = menu_items_.end() - 1;

	ShowMenu(iItem); // ������ ����

	while (TRUE)
	{
		if (GetAsyncKeyState(VK_UP)) // ��������� ������� ������.
		{
			keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0); // "��������" ������. 
			
			if (menu_items_.begin() < iItem) // ���� �� ����� �� �����, �� ���� ����. ����� ��������� � ����������.
				iItem = iItem - 1;
			else
				iItem = nLast; 

			ShowMenu(iItem); // ������ ����
		}

		if (GetAsyncKeyState(VK_DOWN)) // ��������� ������� ������.
		{
			keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0); // "��������" ������. 
			
			if (iItem < nLast) // ���� �� ����� �� ����, �� ���� ����. ����� ��������� � �������.
				iItem = iItem + 1;
			else
				iItem = menu_items_.begin();

			ShowMenu(iItem); // ������ ����.
		}

		if (GetAsyncKeyState(VK_RIGHT)) // ��������� ������� ������.
		{
			keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0); // "��������" ������.

			system("cls");

			if (!iItem->subitem_) // ���� ��� ������� �������� ��� ������� ������������� ������ ���������� � ������ �����.
			{
				iItem->used_class_(); // ����� ������.

				cout << endl;

				Sleep(500); // ���� ������������ ��� �����������
			}

			else // ���� ��� �������, �� ��� ������� ������ ���� �������� ����� ����������.
			{
				iItem->sub_object_->MenuControl(); // ����� ������ ����������.
			}

			ShowMenu(iItem); // ������ ����. ����������� ����� ���������� �������.
		}

		if (GetAsyncKeyState(VK_LEFT)) // ��������� ������� ������.
		{
			keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0); // "��������" ������. 

			if (this->menu_title_ != "Main menu") return; // ���� �� �� � ������� ����, �� ������������ �� ��� �����. 
		}

		if (GetAsyncKeyState(VK_ESCAPE)) // ��������� ������� ������.
		{
			keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0); // "��������" ������. 
			exit(0); // �����.
		}	
	}
}