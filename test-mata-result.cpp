#include <vector>
#include <any>

// 主模板 ，只声明不实现
// 可以由外部指定
template<typename T, bool Iterable>
struct MetaResult;

// 使用偏特化区分需要返回可迭代和
template<typename T>
struct MetaResult<T, false>{
    operator T() const {
        return value;
    }

    T value;
};

// 这用迭代，需要用户自行使用std::any_cast进行类型转换
// 这个T之所以传入 ，只是为了和上面保持一致实际上不需要
template<typename T>
struct MetaResult<T, true>{
    // operator T() const {
    //     return value;
    // }
    std::vector<std::any> values;
};




// template<typename T>
// struct MetaResultIterable{

//     // 构造函数
//     MetaResult(T val) : value(val) {}

//     // 转换运算符，将MetaResult<T>隐式转换为T
//     operator T() const {
//         return value;
//     }

//     // Todo(leo) 支持迭代器
//     std::vector<T> values;
// };
