# WhaleProject

***

>
> Supported compilers: `MSVC`.<br>
> ISO C++ 20.<br>
>

## Whale

>
> 主要功能动态库。<br>
>

## 代码规范

### 不建议的

+ 不建议使用[user_literal]。
+ 不建议使用[except_spec]。
+ 不建议使用[global_function]或[global_variable]。
+ 不建议使用[exceptions]。

### 命名规范

+ 除[user_literal]之外，避免名称以下划线'_'开头。
+ 无[namespace]限制的全局名称以模块名称开头。
+ 从名称上体现**作用域**[scope]，全局变量名以 `g_` 开头，成员变量名以 `m_` 开头。

|        type        |  naming convention   | prefix | postfix |
|:------------------:|:--------------------:|:------:|---------|
|      [macro]       | SCREAMING_SNAKE_CASE | WHALE_ |         |
|    [namespace]     |      PascalCase      |        |         |
|      [class]       |      PascalCase      |        |         |
|      [struct]      |      PascalCase      |   F    |         |
|       [enum]       |      PascalCase      |   E    |         |
|     [typedef]      |      PascalCase      |        |         |
|      [union]       |      PascalCase      |   U    |         |
| [member_functions] |      PascalCase      |        |         |
|   [member_field]   |      camelCase       |   m_   |         |
| [global_function]  |      PascalCase      |        |         |
| [global_variable]  |      camelCase       |   g_   |         |
|    [parameter]     |      camelCase       |        |         |
|  [local_variable]  |      camelCase       |        |         |

### 遵循统一的空格风格

+ 与运算符、标点符、关键字相关的空格应遵循统一风格，过于随意的空格会干扰阅读，甚至会造成笔误。

### 遵循统一的大括号风格

+ 大括号应遵循统一的换行和缩进风格，否则不利于阅读和维护，甚至会造成笔误。

### 遵循统一的缩进风格

+ 缩进方式不统一会使代码结构混乱，严重降低可读性，也易导致逻辑错误。

### 避免多余的括号

+ 重复的或与优先级无关的括号使代码显得繁琐，应去掉。
+ 宏定义([macro])中的括号不受本规则限制。

### 避免多余的分号

+ 多余的分号使代码显得繁琐，也可能意味着某种错误，应去掉。

## Test

>
> 测试用例。<br>
>

# End

>
> 在此往下是链接定义，预览时应不可见。<br>
>

[user_literal]: https://en.cppreference.com/w/cpp/language/user_literal

[scope]: https://en.cppreference.com/w/cpp/language/scope

[namespace]: https://en.cppreference.com/w/cpp/language/namespace

[macro]: https://en.cppreference.com/w/cpp/preprocessor/replace

[class]: https://en.cppreference.com/w/cpp/language/class

[struct]: https://en.cppreference.com/w/c/language/struct

[enum]: https://en.cppreference.com/w/cpp/language/enum

[typedef]: https://en.cppreference.com/w/cpp/language/typedef

[union]: https://en.cppreference.com/w/cpp/language/union

[member_functions]: https://en.cppreference.com/w/cpp/language/member_functions

[member_field]: https://en.cppreference.com/w/cpp/language/data_members

[except_spec]: https://en.cppreference.com/w/cpp/language/except_spec

[exceptions]: https://en.cppreference.com/w/cpp/language/exceptions

[global_function]: ./NoFindInCpprefernce.md

[global_variable]: ./NoFindInCpprefernce.md

[parameter]: ./NoFindInCpprefernce.md

[local_variable]: ./NoFindInCpprefernce.md
