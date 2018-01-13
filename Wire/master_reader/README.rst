..  Copyright (c) 2014-present IntoRobot <support@intorobot.com>
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
       http://www.apache.org/licenses/LICENSE-2.0
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

如何编译工程
=====================================

1. `安装intoyuniot <>`
2. 运行如下命令:

.. code-block:: bash

    # 进入工程目录
    > cd 'your_project'

    # 编译工程
    > intoyuniot run

    # 编译并下载程序
    > intoyuniot run --target upload

    # 编译指定板子
    > intoyuniot run -e 'board_name'

    # 编译并下载指定板子
    > intoyuniot run -e 'board_name' --target upload

    # 清除编译文件
    > intoyuniot run --target clean
