// StoreInventoryManagementSystem.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"InventoryManagement.h"
#include <conio.h>

void prompt()
{
	cout<<"InventoryManagement:"<<endl;
	cout<<"what do you want?"<<endl;
	cout<<"1.get inventory message"<<endl;
	cout<<"2.add inventory type"<<endl;
	cout<<"3,add inventory"<<endl;
	cout<<"4.get inventory"<<endl;
	cout<<"5.save"<<endl;
	cout<<"6.quit"<<endl;
}

void management()
{
	InventoryManagement manage;
	manage.read();
	prompt();
	char a=getch();
	string str="";
	Inventory it;
	Inventory_data da;
	int num;
	while(true)
	{
		switch(a)
		{
		case'1':
			system("cls");
			cout<<"input the inventory you want to find"<<endl;
			cin>>str;
			manage.getInventoryMessage(str);
			system("pause");
			system("cls");
			prompt();
			break;
		case'2':
			system("cls");
			cout<<"input the inventory type you want to add"<<endl;
			cin>>str;
			manage.addInventoryType(str);
			system("pause");
			system("cls");
			prompt();
			break;
		case'3':
			system("cls");
			cout<<"input the inventory name you want to add"<<endl;
			cin>>str;
			it.set_name(str);
			cout<<"input the ProducingArea"<<endl;
			cin>>str;
			it.set_ProducingArea(str);
			cout<<"input the manuf.date"<<endl;
			cin>>da;
			it.set_ManufDate(da);
			cout<<"input the bestbefore date"<<endl;
			cin>>da;
			it.set_BestBefore(da);
			cout<<"input the number you want to store"<<endl;
			cin>>num;
			manage.addInevntory(it,num);
			cout<<"we have stored "<<num<<" "<<it.get_name()<<endl;
			system("pause");
			system("cls");
			prompt();
			break;
		case'4':
			system("cls");
			cout<<"input the inventory you want to get"<<endl;
			cin>>str;
			cout<<"input the number you want to get"<<endl;
			cin>>num;
			manage.getInventory(str,num);
			system("pause");
			system("cls");
			prompt();
			break;
		case'5':
			system("cls");
			manage.save();
			cout<<"It has been saved"<<endl;
			system("pause");
			system("cls");
			prompt();
			break;
		case'6':
			return;
		}
		a=getch();
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	management();
	return 0;
}

