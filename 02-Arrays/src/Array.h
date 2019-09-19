



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
