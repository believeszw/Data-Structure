//
// Created by PC-Saw on 2018/12/19.
//

#ifndef DATA_STRUCTURE_MYARRAY_H
#define DATA_STRUCTURE_MYARRAY_H

#include <iostream>

using namespace std;

template <typename T>
class MyArray {
private:
    int mSize;
    int mCapacity;
    T*  data;
public:
    MyArray();                                  // �޲ι��캯��
    MyArray(int Capacity);                      // ���캯������������Capacity
    MyArray(const MyArray& arr);                // ��������
    MyArray &operator= (const MyArray arr);     // ���ظ�ֵ������
    T &operator[](int index);                   // ����[]������
    ~MyArray();                                 // ��������

    //��Ԫ����ʵ�� ������� << ������
    friend ostream & operator << (ostream &out, MyArray<T> &obj)
    {
        out << "MyArray size = " << obj.mSize << ", Capacity = " << obj.mCapacity << endl;
        out << "MyArray: [";
        for (int i = 0; i < obj.mSize; ++i)
        {
            out << obj.data[i];
            if (i != obj.mSize - 1)
                out << ", ";
        }
        out << "] ";

        return out;
    }
    //��Ԫ����ʵ�� ���� >> ������
    friend istream & operator >> (istream &in, MyArray<T> &obj)
    {
        for (int i = 0; i < obj.mSize; ++i) {
            in << obj.data[i];
        }

        if (!in)
        {
            obj = new MyArray();
        }
        return in;
    }

    bool isEmpty();                             // �ж������Ƿ�Ϊ��
    bool isFull();                              // �ж������Ƿ�����
    int  find(T t);                             // ����Ԫ�� t ���±�
    bool contain(T t);                          // �ж��Ƿ����Ԫ�� t
    int  getSize();                             // ��ȡ����Ԫ�ظ���
    int  getCapacity();                         // ��ȡ��������
    void pushFront(T t);                        // ͷ�����Ԫ��
    void pushBack(T t);                         // β�����Ԫ��
    void insert(int index, T t);                // ��ָ��λ�ò���Ԫ�� t
    T    remove(int index);                     // ɾ��ָ��λԪ��
    T    removeFront();                         // ɾ����һ��Ԫ��
    T    removeBack();                          // ɾ�����һ��Ԫ��
    void removeElement(T t);                    // ɾ��Ԫ�� t
    void set(int index, T t);                   // ��ָ��λ��Ԫ����Ϊ t
    T    get(int index);                        // �鿴 index λ�õ�Ԫ��
    T    getBack();                             // �������һ��Ԫ��
    void resize(int newCapacity);               // ���·���ռ�
};

// ���캯��
template <typename T>
MyArray<T>::MyArray(int Capacity)
{
    cout << "���� MyArray(int) ���� " << endl;
    if (Capacity <= 0)
        throw "������������";
    mSize     = 0;
    mCapacity = Capacity;
    data      = new T[Capacity];
};

// �޲ι��캯��
template <typename T>
MyArray<T>::MyArray()
{
    cout << "���� MyArray() ���� " << endl;
    mSize     = 0;
    mCapacity = 10;
    data      = new T[10];
};

// ��������
template <typename T>
MyArray<T>::MyArray(const MyArray<T>& arr)
{
    cout << "���ÿ������� " << endl;
    this->mSize     = arr.mSize;
    this->mCapacity = arr.mCapacity;
    this->data      = new T[arr.mCapacity];
    // ��������
    for (int i = 0; i < arr.mSize; ++i) {
        this->data[i] = arr.data[i];
    }
}

// ���ظ�ֵ������
template <typename T>
MyArray<T> &MyArray<T>::operator= (const MyArray<T> arr)
{
    cout << "���� = ��ֵ���� " << endl;
    if (this->data != NULL)
    {
        delete[] this->data;
        this->data = NULL;
    }
    //�����ڴ�
    this->mSize     = arr.mSize;
    this->mCapacity = arr.mCapacity;
    this->data      = new T[arr.mCapacity];
    //��������
    for(int i = 0; i < this->mSize; i++)
    {
        //������Զ���ĸ����������ͣ������ = ���㸳��������,  operator=
        this->data[i] = arr.data[i];
    }

    return *this;
}

// ����[]������
template <typename T>
T &MyArray<T>::operator[](int index)
{
    if (index < 0 || index > this->mSize - 1)
        throw "�����Ƿ���";

    return this->data[index];
}

// ��������
template <typename T>
MyArray<T>::~MyArray()
{
    cout << "������������ " << endl;
    if (this->data != NULL)
    {
        delete[] this->data;
        this->data  = NULL;
    }
    this->mSize     = 0;
    this->mCapacity = 0;
}


// �ж������Ƿ�Ϊ��
template <typename T>
bool MyArray<T>::isEmpty()
{
    return mSize == 0;
};

// �ж������Ƿ�����
template <typename T>
bool MyArray<T>::isFull()
{
    return mSize == mCapacity;
};

// ����Ԫ�� t ���±�
template <typename T>
int  MyArray<T>::find(T t)
{
    for (int i = 0; i < mSize; ++i)
    {
        if (data[i] == t)
            return i;
    }
    return -1;
}

// �����Ƿ����Ԫ�� t
template <typename T>
bool MyArray<T>::contain(T t)
{
    return find(t) == -1 ? false : true;
}

// ��ȡ����Ԫ�ظ���
template <typename T>
int  MyArray<T>::getSize()
{
    return mSize;
}

// ��ȡ��������
template <typename T>
int  MyArray<T>::getCapacity()
{
    return mCapacity;
}

// ͷ�����Ԫ��
template <typename T>
void MyArray<T>::pushFront(T t)
{
    insert(0, t);
}

// β�����Ԫ��
template <typename T>
void MyArray<T>::pushBack(T t)
{
    insert(mSize, t);
}

// ��ָ��λ�ò���Ԫ�� t
template <typename T>
void MyArray<T>::insert(int index, T t)
{
    if (index < 0 || index > mSize) // �ж��±��Ƿ�����
        throw 0;
    if (isFull())                   // �������������·���ռ�
        resize(2 * mCapacity);
    for (int i = mSize; i > index ; --i)
    {
        data[i] = data[i - 1];
    }
    data[index] = t;
    mSize++;
}

// ɾ��ָ��λԪ��
template <typename T>
T MyArray<T>::remove(int index)
{
    if (index < 0 || index >= mSize)                    // �ж��±��Ƿ�Ϸ�
        throw 0;
    if (mSize == mCapacity / 4 && mCapacity / 2 != 0)   // ���пռ�̫�����·���ռ�
        resize(mCapacity / 2);

    // ɾ�� index λ�õ�Ԫ�ز�����
    T ret = data[index];
    for (int i = index; i < mSize - 1; ++i) {
        data[i] = data[i + 1];
    }
    mSize--;
    return ret;
}

// ɾ����һ��Ԫ��
template <typename T>
T MyArray<T>::removeFront()
{
    return remove(0);
}

// ɾ�����һ��Ԫ��
template <typename T>
T MyArray<T>::removeBack()
{
    return remove(mSize - 1);
}

// ɾ��Ԫ�� e
template <typename T>
void MyArray<T>::removeElement(T t)
{
    int index = find(t);
    index != -1 && remove(index);
}

// ���ƶ�λ��Ԫ����Ϊ t
template <typename T>
void MyArray<T>::set(int index, T t)
{
    if (index < 0 || index >= mSize)
        throw 0;
    data[index] = t;
}

// ���� index λ�õ�Ԫ��
template <typename T>
T MyArray<T>::get(int index)
{
    if (index < 0 || index >= mSize)
        throw "index is illegal!";
    return data[index];
}

// �������һ��Ԫ��
template <typename T>
T MyArray<T>::getBack()
{
    return get(mSize - 1);
}

// ���·���ռ�
template <typename T>
void MyArray<T>::resize(int newCapacity)
{
    if (newCapacity <= 0)
        throw 0;
    T* tmp = new T[newCapacity];
    for (int i = 0; i < mSize; ++i)
    {
        tmp[i] = data[i];
    }
    delete[] data;
    data = tmp;
    mCapacity = newCapacity;
}

#endif //DATA_STRUCTURE_MYARRAY_H
