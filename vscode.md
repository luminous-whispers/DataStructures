# 常用快捷键:
**shift+ space 控制中文输入法的英文全半角状态**
<br>

**ctrl+ . 控制输入法 标点全半角状态**
<br>

**ctrl+ shift+ p 全局命令行** //输入?可快速获取帮助

## 窗口快捷键

* 选择主题 ctrl+k, ctrl+t
* 快捷键页 ctrl+k, ctrl+s  
* 打开文件 ctrl+ o
* 保存 ctrl+ s / 另存为 ctrl+　shift+ s
* ctrl+ < 打开设置
* ctrl+ shift+ D 打开debug面板
* alt+ 上方菜单的字母 快速打开上方菜单
* 打开关闭控制台 ctrl+ j
* 浏览最近打开过的项目　ctrl+ r


* 隐藏左侧栏目窗口　ctrl+ b
* 隐藏开启终端窗口 ctrl+ ` /ctrl+ shift+ ` 创建新窗口
* 给建议 ctrl+ i
* find ctrl+ f
    全局搜索: shift+ ctrl+ f

***
* 分屏:
    ctrl+ |
    ctrl+ 1/2/3 拓展分屏数量( 1-> 2-> 3)
    当前分屏左右上下移动 ctrl+ k+ Arrow
    正交拆分窗口 ctrl+ k, ctrl+ \ (直接上下拆分)
    直接拆分当前窗口 ctrl+　k, ctrl+ shift+ \
    关闭分屏 ctrl+ w
    在不同文件间移动 ctrl+ tab

* 折叠
    折叠 ctrl+ shift+ [  
    展开 ctrl+ shift+ ]
    展开:
        ctrl+k, ctrl+= 展开除选中外所有区域
        ctrl+k，ctrl+ 9 展开所有区域
    折叠:
        折叠所有区域 ctrl+ k, ctrl+ 8
        折叠不同等级 ctrl+ k, ctrl+ 1-7

* 窗口:
    打开文件,并固定在窗口栏 double-click (字体会由斜体变正)
    打开文件, 不固定(打开新文件会覆盖当前文档) single-click
    窗口切换:　ctrl+ pageup
    聚焦导航大纲 ctrl+ shift+ .


## 代码编辑快捷键
1. 注释:
    * 多行: "alt+ shift+ a"
    * 末尾: "ctrl+ /"
2. 行操作   
    * 快速移动行 alt+ up/dowm
        ctrl+ [ , ] 控制整行缩进( 任意位置 )
        快速复制行　alt+ shift+ Arrow
    * 删除整行 ctrl+ shift+ k
    * 选择整行　ctrl+ l
    * 光标在任意位置换行 ctrl+ entre
    * 在行中新起一行 ctrl+ entre
3. 光标操作
    退回上一次编辑的光标位置 alt+ left/ right
    插入多个光标
        alt+ click
        shift+ alt+ *拖动鼠标* 拖动区域行末加入光标
        ctrl+ shift+ ArrowKey 插入多行光标(方向键控制)
4. 查找与替换
    查找 ctrl+ f
    替换 ctrl+ h
5. 移动s
    快速移动至文件底部/上方ctrl+ end/home 
    快速上下翻屏: pageup/pagedown (+shift 快速选中)
    跳转到自定行: ctrl+ g
    * 光标快速移动: alt+h/j/k/l ( the same as vim , created by myself)
                alt+ i== END; alt+ u== HOME; 
                alt+ d 向左删除
                alt+ o 开新行
    * 光标在不同编辑器窗口跳转 ctrl+ 1/2/3
6. 复制黏贴 
    整行复制 光标插在某行中, ctrl+ c即可
    整行黏贴 复制整行后, 目标位置ctrl+ v

## 调试
* 添加/解除断点 f9
* 启用调试 f5
* 单步跳过 f10
* 单步进入/跳出 f11/ shift+ f11
* 显示悬停: ctrl+ k, ctrl+ i
* 添加到监视 alt+ s( 自定)

<br>

* 快速查看函数定义 alt+ f12 (这个没有移动光标的快捷键,只能用鼠标)/ 摁esc关闭速览窗口
* 开辟新窗口看定义 ctrl+ k, f12 ( 这样就有办法移动光标了)
* 直接跳转到定义文件看定义 f12( 再摁一次会在声明和定义间跳转, 但不会返回主函数 )
* 后退( 返回主函数 ) alt+ y (自定)

## 书签
开关: alt+ b
上下跳跃 alt+ b+ -/=



## Markdown语法
没有microsoft和vnote里的ctrl系列文本快捷键了
但是vscode可以选中后,自动在两侧加surround类标点, 比如{} *,
利用这一点可以快速实现加粗,斜体等操作.

<br>

vscode会自动补全[],但是当你遇到 ]时,再摁一次],不会再打一个], 而是会很人性化的跳过.
* markdown下 "entre"不会换行, 可以用数字或*等标识符强制换行
或者在行末加几个空格  
* "ctrl+k, v" 编译md文件, 分屏查看
    shift+ ctrl+ V全局查看md文件
* 注意markdown的surround型标点语法,比如加粗/url等需要紧贴两端的内容
