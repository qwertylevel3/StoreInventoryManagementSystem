#pragma once
#include<memory.h>
#define DEFAULT_CAPACITY 100

template<class T> class MyVector
{
protected:
	int size;					//内容大小
	int capacity;				//最大容量
	T* storage;					//储存指针
	void expand()				//扩容
	{
		T* tempstorage = new T[capacity*2];
		memcpy(tempstorage,storage,size*sizeof(T));
		delete[] storage;
		storage = tempstorage;
		capacity*=2;
	}
public:
	MyVector():size(0),capacity(DEFAULT_CAPACITY) { storage = new T[DEFAULT_CAPACITY];}//构造函数
	~MyVector(){delete[] storage;}														//析构函数
	
	
	//push函数
	void push(T element)							
	{
		if(size == capacity)//如有必要，扩容
			expand();
		storage[size] = element;
		size++;
	}
	//删除末尾元素
	void pop()										
	{
		size--;
	}
	void remove(int position);						//删除位置为position的元素
	void insert(T element,int position);			//从位置在position处插入
	int find(T element) const;						//查找，假定已重载==运算符,返回位置

	void bubble_sort();								//气泡排序，假设T以重载<运算符
	bool empty() const { return size == 0?true:false;}//是否为空
	int get_size() const { return size;}					//获取大小
	int get_capacity() const { return capacity;}			//获取容量
	T read(int position) const { return storage[position];}//读取位置为position的元素
	T getFirst() const {  return storage[0];}//得到第一个元素
	T getLast() const { return storage[size-1];}//得到第二个元素
	void read_all() const;									//输出全部元素，假设T以重载<<运算符

	T& operator[](const size_t index)
	{
		return storage[index];
	}
	const T& operator[] (const size_t index) const
	{
		return storage[index];
	}

};
template<class T>
void MyVector<T>::insert(T element,int position)
{
	if(size == capacity)//如有必要，扩容
		expand();
	if(position<0 || position > capacity)
	{
		std::cerr<<"error"<<std::endl;
	}
	for(int i=size;i>position;--i)
	{
		storage[i] = storage[i-1];
	}
	storage[position] = element;
	size++;
}
template<class T>
void MyVector<T>::remove(int position)
{
	for(int i = position;i<size-1;++i)
	{
		storage[i] = storage[i+1];
	}
	size--;
}
template<class T>
void MyVector<T>::bubble_sort()//气泡排序，假设T以重载<运算符
{
	bool flag = false;
	for(int j = 1;j<size;++j)
	{
		flag = true;
		for(int i=0;i<size-j;++i)
		{
			if(storage[i+1]<storage[i])
			{
				flag = false;
				T temp = storage[i];
				storage[i] = storage[i+1];
				storage[i+1] = temp;
			}
		}
		if(flag) break;
	}
}
template<class T>
void MyVector<T>::read_all() const //输出全部元素，假设T以重载<<运算符
{
	std::cout<<"All element:"<<endl;
	for(int i=0;i<size;i++)
	{
		std::cout<<storage[i]<<std::endl;
	}
}

template<class T>
int MyVector<T>::find(T element) const
{
	for(int i = 0;i!=size;++i)
	{
		if(storage[i] == element)
			return i;
	}
	return 0;
}