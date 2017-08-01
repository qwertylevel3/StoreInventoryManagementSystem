#pragma once
#include<memory.h>
#define DEFAULT_CAPACITY 100

template<class T> class MyVector
{
protected:
	int size;					//���ݴ�С
	int capacity;				//�������
	T* storage;					//����ָ��
	void expand()				//����
	{
		T* tempstorage = new T[capacity*2];
		memcpy(tempstorage,storage,size*sizeof(T));
		delete[] storage;
		storage = tempstorage;
		capacity*=2;
	}
public:
	MyVector():size(0),capacity(DEFAULT_CAPACITY) { storage = new T[DEFAULT_CAPACITY];}//���캯��
	~MyVector(){delete[] storage;}														//��������
	
	
	//push����
	void push(T element)							
	{
		if(size == capacity)//���б�Ҫ������
			expand();
		storage[size] = element;
		size++;
	}
	//ɾ��ĩβԪ��
	void pop()										
	{
		size--;
	}
	void remove(int position);						//ɾ��λ��Ϊposition��Ԫ��
	void insert(T element,int position);			//��λ����position������
	int find(T element) const;						//���ң��ٶ�������==�����,����λ��

	void bubble_sort();								//�������򣬼���T������<�����
	bool empty() const { return size == 0?true:false;}//�Ƿ�Ϊ��
	int get_size() const { return size;}					//��ȡ��С
	int get_capacity() const { return capacity;}			//��ȡ����
	T read(int position) const { return storage[position];}//��ȡλ��Ϊposition��Ԫ��
	T getFirst() const {  return storage[0];}//�õ���һ��Ԫ��
	T getLast() const { return storage[size-1];}//�õ��ڶ���Ԫ��
	void read_all() const;									//���ȫ��Ԫ�أ�����T������<<�����

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
	if(size == capacity)//���б�Ҫ������
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
void MyVector<T>::bubble_sort()//�������򣬼���T������<�����
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
void MyVector<T>::read_all() const //���ȫ��Ԫ�أ�����T������<<�����
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