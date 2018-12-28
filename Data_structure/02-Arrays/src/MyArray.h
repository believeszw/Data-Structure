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
    MyArray();                                  // 无参构造函数
    MyArray(int Capacity);                      // 构造函数，传入容量Capacity
    MyArray(const MyArray& arr);                // 拷贝构造
    MyArray &operator= (const MyArray arr);     // 重载赋值操作符
    T &operator[](int index);                   // 重载[]操作赋
    ~MyArray();                                 // 析构函数

    //友元函数实现 重载输出 << 操作符
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
    //友元函数实现 输入 >> 操作符
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

    bool isEmpty();                             // 判断数组是否为空
    bool isFull();                              // 判断数组是否已满
    int  find(T t);                             // 查找元素 t 的下标
    bool contain(T t);                          // 判断是否包含元素 t
    int  getSize();                             // 获取数组元素个数
    int  getCapacity();                         // 获取数组容量
    void pushFront(T t);                        // 头部添加元素
    void pushBack(T t);                         // 尾部添加元素
    void insert(int index, T t);                // 在指定位置插入元素 t
    T    remove(int index);                     // 删除指定位元素
    T    removeFront();                         // 删除第一个元素
    T    removeBack();                          // 删除最后一个元素
    void removeElement(T t);                    // 删除元素 t
    void set(int index, T t);                   // 将指定位置元素设为 t
    T    get(int index);                        // 查看 index 位置的元素
    T    getBack();                             // 返回最后一个元素
    void resize(int newCapacity);               // 重新分配空间
};

// 构造函数
template <typename T>
MyArray<T>::MyArray(int Capacity)
{
    cout << "调用 MyArray(int) 构造 " << endl;
    if (Capacity <= 0)
        throw "传入容量有误！";
    mSize     = 0;
    mCapacity = Capacity;
    data      = new T[Capacity];
};

// 无参构造函数
template <typename T>
MyArray<T>::MyArray()
{
    cout << "调用 MyArray() 构造 " << endl;
    mSize     = 0;
    mCapacity = 10;
    data      = new T[10];
};

// 拷贝构造
template <typename T>
MyArray<T>::MyArray(const MyArray<T>& arr)
{
    cout << "调用拷贝构造 " << endl;
    this->mSize     = arr.mSize;
    this->mCapacity = arr.mCapacity;
    this->data      = new T[arr.mCapacity];
    // 拷贝数据
    for (int i = 0; i < arr.mSize; ++i) {
        this->data[i] = arr.data[i];
    }
}

// 重载赋值操作符
template <typename T>
MyArray<T> &MyArray<T>::operator= (const MyArray<T> arr)
{
    cout << "调用 = 赋值操作 " << endl;
    if (this->data != NULL)
    {
        delete[] this->data;
        this->data = NULL;
    }
    //分配内存
    this->mSize     = arr.mSize;
    this->mCapacity = arr.mCapacity;
    this->data      = new T[arr.mCapacity];
    //拷贝数据
    for(int i = 0; i < this->mSize; i++)
    {
        //如果是自定义的复杂数据类型，必须对 = 运算赋进行重载,  operator=
        this->data[i] = arr.data[i];
    }

    return *this;
}

// 重载[]操作赋
template <typename T>
T &MyArray<T>::operator[](int index)
{
    if (index < 0 || index > this->mSize - 1)
        throw "索引非法！";

    return this->data[index];
}

// 析构函数
template <typename T>
MyArray<T>::~MyArray()
{
    cout << "调用析构函数 " << endl;
    if (this->data != NULL)
    {
        delete[] this->data;
        this->data  = NULL;
    }
    this->mSize     = 0;
    this->mCapacity = 0;
}


// 判断数组是否为空
template <typename T>
bool MyArray<T>::isEmpty()
{
    return mSize == 0;
};

// 判断数组是否已满
template <typename T>
bool MyArray<T>::isFull()
{
    return mSize == mCapacity;
};

// 查找元素 t 的下标
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

// 查找是否包含元素 t
template <typename T>
bool MyArray<T>::contain(T t)
{
    return find(t) == -1 ? false : true;
}

// 获取数组元素个数
template <typename T>
int  MyArray<T>::getSize()
{
    return mSize;
}

// 获取数组容量
template <typename T>
int  MyArray<T>::getCapacity()
{
    return mCapacity;
}

// 头部添加元素
template <typename T>
void MyArray<T>::pushFront(T t)
{
    insert(0, t);
}

// 尾部添加元素
template <typename T>
void MyArray<T>::pushBack(T t)
{
    insert(mSize, t);
}

// 在指定位置插入元素 t
template <typename T>
void MyArray<T>::insert(int index, T t)
{
    if (index < 0 || index > mSize) // 判断下标是否有误
        throw 0;
    if (isFull())                   // 数组已满则重新分配空间
        resize(2 * mCapacity);
    for (int i = mSize; i > index ; --i)
    {
        data[i] = data[i - 1];
    }
    data[index] = t;
    mSize++;
}

// 删除指定位元素
template <typename T>
T MyArray<T>::remove(int index)
{
    if (index < 0 || index >= mSize)                    // 判断下标是否合法
        throw 0;
    if (mSize == mCapacity / 4 && mCapacity / 2 != 0)   // 空闲空间太大，重新分配空间
        resize(mCapacity / 2);

    // 删除 index 位置的元素并返回
    T ret = data[index];
    for (int i = index; i < mSize - 1; ++i) {
        data[i] = data[i + 1];
    }
    mSize--;
    return ret;
}

// 删除第一个元素
template <typename T>
T MyArray<T>::removeFront()
{
    return remove(0);
}

// 删除最后一个元素
template <typename T>
T MyArray<T>::removeBack()
{
    return remove(mSize - 1);
}

// 删除元素 e
template <typename T>
void MyArray<T>::removeElement(T t)
{
    int index = find(t);
    index != -1 && remove(index);
}

// 将制定位置元素设为 t
template <typename T>
void MyArray<T>::set(int index, T t)
{
    if (index < 0 || index >= mSize)
        throw 0;
    data[index] = t;
}

// 返回 index 位置的元素
template <typename T>
T MyArray<T>::get(int index)
{
    if (index < 0 || index >= mSize)
        throw "index is illegal!";
    return data[index];
}

// 返回最后一个元素
template <typename T>
T MyArray<T>::getBack()
{
    return get(mSize - 1);
}

// 重新分配空间
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
