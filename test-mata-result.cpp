#include <iostream>
#include <vector>
#include <any>
#include <type_traits>

template<typename T, bool IsIterable>
struct MetaBase
{
    using result_type = std::conditional<IsIterable, std::vector<T>, T>::type;
    result_type data_;
};

template<typename T, bool IsIterable>
struct MetaResult:public MetaBase< T, IsIterable>
{
    
};

// 使用偏特化区分需要返回可迭代和
template<typename T>
struct MetaResult<T, false>:public MetaBase< T, false>
{
    operator T() const {
        return this->data_;
    }
};


// 这用迭代，需要用户自行使用std::any_cast进行类型转换
template<typename T>
struct MetaResult<T, true>:public MetaBase< T, true>
{
    static_assert(std::is_same< typename MetaBase< T, true>::result_type, std::vector<T> >::value, "该MetaResult不可以迭代");
    // 支持迭代器迭代
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    iterator begin() {
        // 继承模板类需要用作用域解析符如 MetaBase< T, true>::data_，或者使用this指针
        return this->data_.begin();
    }

    iterator end() {
        return this->data_.end();
    }

    const_iterator begin() const {
        return this->begin();
    }

    const_iterator end() const {
        return this->data_.end();
    }
};


int main(){
    MetaResult<int, false> a;
    a.data_ = 1;
    std::cout << "Type of result: " << typeid(a.data_).name() << std::endl;
    int b = 0;
    b = a;
    std::cout << "test type connvert b value is : " << b << std::endl;
    MetaResult<int, true> d;
    std::cout << "Type of result: " << typeid(d.data_).name() << std::endl;
    d.data_.push_back(1);
    d.data_.push_back(2);
    for(int a : d){
        std::cout << a << " " << std::endl;
    }
    // b = d; d不支持隐式转换
    // 使用std::any可以支持异质数组

}