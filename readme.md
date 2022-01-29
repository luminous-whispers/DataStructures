# notice
* 自定函数名 以及宏定义 用驼峰法，第一个首字母小写，其余部分首字母大写
* 自定变量名 全部首字母皆大写. 隐藏的指针末尾需要加_
* 英文半角标点符号后需要加一个空格, 且当有括号时, 括号内每个字符内都要加空格
    >vscode启用了拓展"中文标点符号转英文",所以不需要麻烦地来回切换输入法来在中文模式下使用markdown语法.
* 按照惯例, typedef定义的新类型名需要全大写, 如果需要隐藏指针, 那么最后加上下滑线_.
* 库声明命名  _库_H
* 宏定义 _全部大写加两边下划线_
    (注:　虽然全大写命名很麻烦,　但是vscode是支持小写也能补全大写的啦)

***

* 对书中的每种算法都建立了专门的库, 这样虽然繁复, 但是对内容可以一目了然, 即方便了查找, 也方便后期补充和完善
* 同样每种数据结构建立了专门的文件夹
* 因此只建立了少数运行文件( .c )

* 后期完善后会考虑用git控制版本, 并上传至github(异或百度网盘, 奈何后者实时同步功能太差, 甚至经常出现假同步, 即根本不能追踪细节上的改动), 方便随时调用


>附launch.json文件的某些说明: 
```c
{
    "version": "0.2.0",
    "configurations": [

        {{
    "version": "0.2.0",
    "configurations": [

        {
            "name": "C/C++",// 配置名称，将会在启动配置的下拉菜单中显示  
            "type": "cppdbg", // 配置类型，这里只能为cppdbg  
            "request": "launch",// 请求配置类型，可以为launch（启动）或attach（附加）  
            "program": "${fileDirname}/${fileBasenameNoExtension}.exe",// 将要进行调试的程序的路径  
            "args": [],// 程序调试时传递给程序的命令行参数，一般设为空即可 
            "stopAtEntry": false,// 设为true时程序将暂停在程序入口处，一般设置为false  
            "cwd": "${workspaceFolder}",// 调试程序时的工作目录，一般为${workspaceFolder}即代码所在目录  
            "environment": [],
            "externalConsole": false,// 调试时是否显示控制台窗口，一般设置为true显示控制台  
            "MIMode": "gdb",
            "miDebuggerPath": "F:\\mingw\\bin\\gdb.exe", // miDebugger的路径，注意这里要与MinGw的路径对应  
            //"preLaunchTask": "compile",//和tasks中label保持一致
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
        },
    ]
}
```

> vscode 文件夹是用来配置调试环境的, 但只适用于该文件夹, 当换文件目录时, 复制到新文件去就行.

***
