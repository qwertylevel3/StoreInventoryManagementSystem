#pragma once

#include"TVector.h"
#include"DoubleList.h"
#include"Inventory.h"
#include<fstream>
#include<sstream>

struct InventoryIndex
{
	string name;
	MyList<Inventory>* InventoryList;
	InventoryIndex(string n="")
	{
		name=n;
		InventoryList = new MyList<Inventory>;
	}
};


class InventoryManagement
{
public:
	MyVector<InventoryIndex> management;
	InventoryManagement(){}

	
	int findInventoryType(string name);		//����ĳ����Ʒ�����ڷ��ر�ţ������ڷ���-1
	
	void sortInventory(string name);		//����ĳ����Ʒ������������

	void addInventoryType(string name);		//������Ʒ����

	int removeInventoryType(string name);	//�Ƴ�ĳ����Ʒ����
	int removeInventoryType(int index);
	
	void addInevntory(Inventory it,int n);	//����ĳ����Ʒ����
	
	int getInventory(Inventory it,int n);	//ȡ��ĳ����Ʒ,�ɹ�����0,ʧ�ܷ���-1
	int getInventory(string it,int n);
	
	string getInventoryMessage(Inventory it);	//��ѯĳ����Ʒ��Ϣ
	string getInventoryMessage(string it);
	string getInventoryMessage(int index);
	
	void save();							//�������вֿⱨ��(������Ϣ��)

	string getInventoryName(int index);		//��ȡ��Ʒ��
	void read();							//��ȡ�ֿ���Ϣ
	int GetSize(); 							//�õ��ֿ���Ʒ������
	
};

int InventoryManagement::GetSize()
{
	return management.get_size();
}
int InventoryManagement::findInventoryType(string name)
{
	for(int i=0;i<management.get_size();i++)
	{
		string test=management[i].name;
		if(name == test)
		{
			return i;
		}
	}
	return -1;
}
void InventoryManagement::sortInventory(string name)
{
	int index = findInventoryType(name);
	if(index!=-1)
	{
		management[index].InventoryList->insertionSort();
	}
}

void InventoryManagement::addInventoryType(string name)
{
	if(findInventoryType(name)!=-1)
	{
		return;
	}
	else
	{
		InventoryIndex in;
		in.name = name;
		management.push(in);
	}
	
	
}

int InventoryManagement::removeInventoryType(string name)
{
	int index=findInventoryType(name);
	if(index==-1)
	{
		return -1;
	}
	else
	{
		management[index].InventoryList->clear();
		management.remove(index);
		return index;
	}

}
int InventoryManagement::removeInventoryType(int index)
{
	if(index>=0 && index<management.get_size())
	{	
		management[index].InventoryList->clear();
		management.remove(index);
		return index;
	}
	return -1;
}

void InventoryManagement::addInevntory(Inventory it,int n)
{
	int index = findInventoryType(it.get_name());
	if(index!=-1)
	{
		for(int i=0;i<n;i++)
		{
			management[index].InventoryList->push(it);
		}
	}
	else
	{
		InventoryIndex in;
		in.name = it.get_name();
		management.push(in);
		for(int i=0;i<n;i++)
		{
			management.getLast().InventoryList->push(it);
		}
		
	}
}
int InventoryManagement::getInventory(Inventory it,int n)
{
	int index = findInventoryType(it.get_name());
	if(index!=-1)
	{
		management[index].InventoryList->insertionSort();
		if(n<management[index].InventoryList->GetSize())
		{
			for(int i=0;i<n;i++)
			{
				management[index].InventoryList->remove(0);
			}
		}
		else
			management[index].InventoryList->clear();
		return 0;
	}
	else
		return -1;
}
int InventoryManagement::getInventory(string it,int n)
{
	int index = findInventoryType(it);
	if(index!=-1)
	{
		management[index].InventoryList->insertionSort();
		if(n<management[index].InventoryList->GetSize())
		{
			for(int i=0;i<n;i++)
			{
				management[index].InventoryList->remove(0);
			}
		}
		else
			management[index].InventoryList->clear();
		return 0;
	}
	else
		return -1;
}

string InventoryManagement::getInventoryMessage(Inventory it)
{
	stringstream strm;
	int index = findInventoryType(it.get_name());
	if(index!=-1)
	{
		strm<<"We have "<<management[index].InventoryList->GetSize()<<" "
			<<management[index].name<<endl;
		for(int i=0;i<management[index].InventoryList->GetSize();i++)
		{
			strm<<management[index].InventoryList->read(i)<<endl;
		}
	}
	return strm.str();
}

string InventoryManagement::getInventoryMessage(string it)
{
	ostringstream strm;
	int index = findInventoryType(it);
	if(index!=-1)
	{
		strm<<"We have "<<management[index].InventoryList->GetSize()<<" "
			<<management[index].name<<endl;
		for(int i=0;i<management[index].InventoryList->GetSize();i++)
		{
			strm<<management[index].InventoryList->read(i)<<endl;
		}
	}
	return strm.str();
}
string InventoryManagement::getInventoryMessage(int index)
{
	ostringstream strm;
	if(index!=-1)
	{
		strm<<"We have "<<management[index].InventoryList->GetSize()<<" "
			<<management[index].name<<endl;
		for(int i=0;i<management[index].InventoryList->GetSize();i++)
		{
			strm<<management[index].InventoryList->read(i)<<endl;
		}
	}
	return strm.str();
}
void InventoryManagement::save()
{
	ofstream data("data.txt");
	for(int i=0;i<management.get_size();i++)
	{
		data<<"<"<<management[i].name<<">"<<endl;
		for(int j=0;j<management[i].InventoryList->GetSize();j++)
		{
			data<<management[i].InventoryList->read(j)<<endl;
		}
	}
}
void InventoryManagement::read()
{
	for(int i=0;i<management.get_size();i++)
	{
		management[i].InventoryList->clear();
		management.remove(i);
	}
	ifstream data("data.txt");
	string line;
	string inventory_type;
	string name;
	Inventory_date bb;
	Inventory_date md;
	string pa;
	while(getline(data,line))
	{
		int i=line.find('<');
		int j=line.find('>');
		if(i!=string::npos && j!=string::npos)
		{
			inventory_type=line.substr(i+1,j-i-1);
			addInventoryType(inventory_type);
		}
		else
		{
			i=line.find(':');
			j=line.find('|');
			name=line.substr(i+1,j-i-1);
			i=line.find(':',i+1);
			j=line.find('|',j+1);
			pa=line.substr(i+1,j-i-1);

			i=line.find(':',i+1);
			j=line.find('/',j+1);
			bb.year=atoi(line.substr(i+1,j-i-1).c_str());
			i=j;
			j=line.find('/',j+1);
			bb.month=atoi(line.substr(i+1,j-i).c_str());
			i=j;
			j=line.find('|',j+1);
			bb.day=atoi(line.substr(i+1,j-i).c_str());

			i=line.find(':',i+1);
			j=line.find('/',j+1);
			md.year=atoi(line.substr(i+1,j-i-1).c_str());
			i=j;
			j=line.find('/',j+1);
			md.month=atoi(line.substr(i+1,j-i).c_str());
			i=j;
			j=line.find('|',j+1);
			md.day=atoi(line.substr(i+1,j-i).c_str());
			
			Inventory i(name,md,bb,pa);
			addInevntory(i,1);
		}
	}
}
string InventoryManagement::getInventoryName(int index)
{
	
	return management[index].name;
	
}