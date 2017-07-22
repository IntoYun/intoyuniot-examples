该目录用于存放工程使用的私有库

intoyuniot 将编译该目录下的私有库，生成私有库静态库并链接生成执行文件

每个库的源代码文件需放在独立的目录下，如"lib/private_lib/[源代码文件]".

例如，工程使用'Foo' 和 'Bar'这两个库, 工程目录结构如下:

|--lib
|  |--Bar
|  |  |--docs
|  |  |--examples
|  |  |--src
|  |     |- Bar.cpp
|  |     |- Bar.h
|  |--Foo
|  |  |- Foo.cpp
|  |  |- Foo.h
|  |- readme.txt --> 当前文件
|- intoyuniot.ini
|--src
   |- main.cpp

其中'src/main.cpp' 文件需添加头文件

#include <Foo.h>
#include <Bar.h>

intoyuniot 将自动查找库并编译工程

