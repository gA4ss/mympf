# mympf
浮点大数运算算法。

# 编译

在编译本库之前请先安装`cmake`、`gtest`库以及[_*mympz*_](https://github.com/gA4ss/mympz)库，在安装完成后，使用如下命令进行编译。

```bash
mkdir build
cd build
cmake ..
make
```

编译完成后，可以使用`make install`进行安装。

# 使用说明

在使用时，仅需包含头文件`#include <mympf/mympf.h>`即可使用。下面分别介绍大数结构以及相关功能函数列表。随后进行链接库文件`libmympf.a`即可。

## 浮点大数结构

描述数值时，会使用`mympz`中的`bignum_t`结构直接保存整数与浮点数为一个大数。精度的表示使用`precision`来表示，基础运算还是通过`mympz`中的运算得到，计算完毕后通过`precision`变量控制精度。

```c++
  typedef struct
  {
    mympz::bignum_t number;
    size_t precision;

    int neg() const { return number.neg; }
    void set_neg(int neg = 0) { number.neg = neg; }
  } float_t;
```

## 函数列表

|名称|说明|
|---|----|
|`create`|*三个版本*通过字单元；字符串；`bignum_t`创建大数结构|
|`cmp`|比较|
|`ucmp`|无符号比较|
|`add`|加法|
|`uadd`|无符号加法|
|`sub`|减法|
|`usub`|无符号减法|
|`mul`|乘法|
|`sqr`|平方运算|
|`exp`|指数函数|
|`div`|除法返回商与余数|
|`idiv`|除法仅返回商|
|`mod`|模运算|
|`integer_part`|取整数部分|
|`decimal_part`|取小数部分|
|`floor`|四舍五入|
|`ceil`|上取整|
|`round`|下取整|
|`print_string`|打印大数为字符串|
|`const_null`|*常数变量*，大数结构的空值|
|`const_0`|*常数变量*，浮点大数结构的0|
|`const_1`|*常数变量*，浮点大数结构的1|
|`const_10`|*常数变量*，浮点大数结构的10|

# 异常说明

|异常|说明|
|---|----|
|指数过长|仅发生在`exp`函数中，最大为$2^64$，因为这个数字基本够用了，虽然`mympz`中提供了采用大数结构作为指数的支持，但是目前计算机本身可能无法达到任意大的进度运算。|

其余异常发生由`mympz`抛出。

# 测试文件

|测试文件|说明|
|-------|---|
|`test/test_addsub.cc`|对加减法进行测试|
|`test/test_create.cc`|对创建大数进行测试|
|`test/test_div.cc`|对除法进行测试|
|`test/test_exp.cc`|对指数进行测试|
|`test/test_mod.cc`|对模数进行测试|
|`test/test_mul.cc`|对乘法进行测试|
|`test/test_cmp.cc`|对比较进行测试|