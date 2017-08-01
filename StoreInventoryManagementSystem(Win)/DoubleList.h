#pragma once
#include<iostream>

using namespace std;

template<class T>
class MyList
{
	class Node//内嵌节点类
	{
	public:
		Node* pre;
		Node* suc;
		T data;
		Node(T d,Node* p = 0,Node* s = 0):data(d),pre(p),suc(s){}
		Node(){}
	};
	Node* head;//头节点
	Node* trail;//尾节点
	int size;
public:
	MyList(const MyList& list)
	{

		head = new Node;
		trail = new Node;
		head->suc = trail;head->pre = NULL;
		trail->pre = head;trail->suc = NULL;
		size = 0;
		for(int i = 0;i<list.GetSize();i++)
			push(list.read(i))
	}
	MyList()//构造函数
	{

		head = new Node;
		trail = new Node;
		head->suc = trail;head->pre = NULL;
		trail->pre = head;trail->suc = NULL;
		size = 0;
	}
	MyList& operator=(const MyList& list)
	{

		head = new Node;
		trail = new Node;
		head->suc = trail;head->pre = NULL;
		trail->pre = head;trail->suc = NULL;
		size = 0;
		for(int i = 0;i<list.GetSize();i++)
			push(list.read(i));
		return *this;
	}
	~MyList()//析构函数
	{ 
		clear();
		delete head;
		delete trail;
	}

	void insert(T data,int position);//插入data于position位置
	void push(T data);//从后加入
	void remove(int position);//移除位置为position的元素
	T read(int position) const;//读位置为position的数据,假设T已重载<<运算符
	void clear();//清空
	int find(T data) const;//查找数据为data的位置,假设T已重载==运算符
	void insertionSort();//插入排序，假设T已重载<运算符

	int GetSize() const{ return size;}
	bool empty() const { return (size == 0 ? true:false); }

	
	T& operator[](const size_t index)
	{
		if(index >= size)
			cerr<<"out of range"<<endl;
		else
		{
			Node* p = head;
			for(int i=0;i<index;++i)
				p=p->suc;
			return p->suc->data;
		}
	}
	const T& operator[](const size_t index) const
	{
		if(index >= size)
			cerr<<"out of range"<<endl;
		else
		{
			Node* p = head;
			for(int i=0;i<index;++i)
				p=p->suc;
			return p->suc->data;
		}
	}
};

template<class T>
void MyList<T>::insert(T data,int position)
{
	Node* p = head;
	Node* temp = new Node(T);
	if(opsition>size)
		cerr<<"error,out of range"<<endl;
	else
	{
		for(int i=0;i<position;++i)
			p = p->suc;
		temp->suc = p->suc;
		temp->pre = p;
		p->suc->pre = temp;
		p->suc = temp;
		size++;
	}
}
template<class T>
void MyList<T>::push(T data)
{
	Node* temp = new Node(data);
	temp->suc = trail;
	temp->pre = trail->pre;
	trail->pre->suc = temp;
	trail->pre = temp;
	size++;
}
template<class T>
void MyList<T>::remove(int position)
{
	Node* p = head;
	if(position>size)
		cerr<<"out of range"<<endl;
	else
	{
		Node* temp  = head;
		for(int i=0;i<=position;++i)
			temp=temp->suc;
		temp->suc->pre = temp->pre;
		temp->pre->suc = temp->suc;
		delete temp;
		--size;
	}
}
template<class T>
T MyList<T>::read(int position) const
{
	Node* p = head;
	if(position>size)
		cerr<<"out of range"<<endl;
	else
	{
		return operator[](position);
	}
}
template<class T>
void MyList<T>::clear()
{
	if(size !=0)
	{
		Node* p = head;
		while(p->suc != trail)
		{
			Node* temp = p->suc;
			p->suc = temp->suc;
			temp->suc->pre = p;
			delete temp;
		}
		size = 0;
	}
	
}
template<class T>
int MyList<T>::find(T data) const
{
	Node* p = head->suc;
	for(int i = 0;i<size;++i)
	{
		if(p->data == data)
			return i;
	}
	return -1;
}
template<class T>
void MyList<T>::insertionSort()
{
	MyList* const t=this;
	Node* temp;
	Node* p;
	Node* q = head->suc->suc;
	if(!empty())
	{
		while(q != trail)
		{
			temp = q;
			q = q->suc;
			temp->pre->suc = q;
			q->pre = temp->pre;

			p = head->suc;
			bool flag = false;
			while(p!= q)
			{
				if(temp->data<p->data)
				{
					temp->pre = p->pre;
					temp->suc = p;
					p->pre->suc = temp;
					p->pre = temp;
					flag = true;
					break;
				}
				else
				{
					p = p->suc;
				}
			}
			if(!flag)
			{
				temp->pre = p->pre;
				temp->suc = p;
				p->pre->suc = temp;
				p->pre = temp;
			}
		}
	}
}