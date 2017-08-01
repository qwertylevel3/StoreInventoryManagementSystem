#pragma once

#include<string>

using namespace std;

//��Ʒ������
struct Inventory_date
{
	int year;
	int month;
	int day;
	Inventory_date(int y=0,int m=0,int d=0):year(y),month(m),day(d){}
	Inventory_date(const Inventory_date& d)
	{
		year = d.year;
		month = d.month;
		day = d.day;
	}
	Inventory_date& operator=(const Inventory_date& d)
	{
		year = d.year;
		month = d.month;
		day = d.day;
		return *this;
	}
};
bool operator<(const Inventory_date& left,const Inventory_date& right)
{
	if(left.year<right.year)
		return true;
	else if(left.year>right.year)
		return false;
	else
	{
		if(left.month<right.month)
			return true;
		else if(left.month>right.month)
			return false;
		else
		{
			if(left.day<right.day)
				return true;
			else if(left.day>right.day)
				return false;
			else
				return true;

		}
	}
}
ostream& operator<<(ostream& os,const Inventory_date& d)
{
	os<<d.year<<"/"<<d.month<<"/"<<d.day;
	return os;
}
istream& operator>>(istream& in,Inventory_date& d)
{
	int year;
	int month;
	int day;
	in>>year>>month>>day;
	if(in)
	{
		d.day=day;
		d.month=month;
		d.year=year;
	}
	else
		d=Inventory_date();
	return in;
}
//��Ʒ��
class Inventory
{
protected:
	string name;				//��Ʒ����
	Inventory_date ManufDate;	//��������
	Inventory_date BestBefore;	//��������
	string ProducingArea;		//����
public:
	Inventory(string n="",Inventory_date md=0,Inventory_date bb=0,string pa=""):
		name(n),ManufDate(md),BestBefore(bb),ProducingArea(pa){}
	Inventory(string n,int mdy,int mdm,int mdd,int bby,int bbm,int bbd,string pa):
		name(n),ManufDate(mdy,mdm,mdd),BestBefore(bby,bbm,bbd),ProducingArea(pa){}
	Inventory(const Inventory& i)
	{
		name = i.name;
		ManufDate = i.ManufDate;
		BestBefore = i.BestBefore;
		ProducingArea = i.ProducingArea;
	}
	Inventory& operator=(const Inventory& i)
	{
		name = i.name;
		ManufDate = i.ManufDate;
		BestBefore = i.BestBefore;
		ProducingArea = i.ProducingArea;
		return *this;
	}

	//�����ӿ�
	string get_name() const{ return name;}
	Inventory_date get_ManufDate() const{ return ManufDate;}
	Inventory_date get_BestBefore() const{ return BestBefore;}
	string get_ProducingArea() const{ return ProducingArea;}

	void set_name(const string n) { name=n;}
	void set_ManufDate(const Inventory_date d) {  ManufDate=d;}
	void set_BestBefore(const Inventory_date d) {  BestBefore=d;}
	void set_ProducingArea(string p) { ProducingArea=p;}

	friend ostream& operator<<(ostream&,const Inventory&);

};
ostream& operator<<(ostream& os,const Inventory& i)
{
	os<<"Inventory name:"<<i.get_name()<<"|"
		<<"ProducingArea:"<<i.get_ProducingArea()<<"|"
		<<"Best Before:"<<i.get_BestBefore()<<"|"
		<<"Manuf.Date:"<<i.get_ManufDate()<<"|";
	return os;
}
bool operator<(const Inventory& left, const Inventory& right)
{
	return left.get_ManufDate()<right.get_ManufDate();
}