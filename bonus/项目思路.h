/*
课程大作业
模拟搜索引擎搜索系统
*/
//1.提取关键词:出现每个文档中次数,出现在过多少个文档里, 计算出现频率; 要求:出现在字典中不出现在停用词表里, 大写转小写
//关键词k, 文档编号d, 文档总数N
//k在d中出现次数:TNkd, d的总词数:TNd, d文档中k的词频为:TFkd = (TNkd/TNd)*100
//出现k的总文档数:DNk, 逆词频为log10(N/DNk)
//相关度:Simd = Sum(ki)[TFkd * IDFki], d指相关度是关于文档而言, ki指所有搜索中的关键词

enum BOOL{FALSE, TRUE};

/* [5/1] 字典预,停用词预处理: 为了使用查表法, 必须写个程序先把字典节点的偏移量找出来
利用哈希表快查, 文件版本的折半查找法*/
//! [5/13] 现用字典树代替查表法, 以上方法抛弃. 主题树全部采用字典树
enum BOOL InDict(char *);
enum BOOL InStopDict(char *);
enum BOOL IsLetter(char *);

//!搜索结果为num, 开辟一个num*struct的空间, 然后不断进行比对, 永远只保留最前面num个网站数据(无法实现)
int key_num;
int doc_num;
struct KEY_WORD{
    int key_appear_doc_num;
    int single_doc_key_num;
    int single_doc_key_freq;
    int anti_key_freq;
};
struct WEBSITE{
    int no_num;//编号
    char no_serial;//文档内编号
    int total_word_num;//总词数
    int doc_sim;
    // struct KEY_WORD * array;
    // int array_element_num;//告诉这个array指针可以偏移多少位 
};
//读取一个文档例程: article.c
/*
为了尽可能缩短时间:
    1. 时间检测中使用数组二叉树的形式:
    2. 正确性使用普通二叉树
    3. 扩展性时使用avl
*/

/*working flow:
1. 读入, 开辟doc_num*struct空间, 和关键词数key_num*struct2空间
2. 第一遍处理文档:
    只记录总数, 和各文档开始位置
3. 第二遍循环处理每个文档:
- 对循环每个文档:
    记录每个文档的:编号(即角标)
        - 逆向寻找最后一个文章编号, 从而决定开辟多大数组 //todo 逆向寻找很难实现
        - 总词数(什么意思?是总单词数嘛)
    寻找每个文档中关键词的信息:
        - 出现次数
    计算词频
- 循环始终:
    文档总数(这个可以用逆向读取实现)
    出现k的文档数(key_num个信息)
4. 计算相关度, 总体排序取前NUM位
*/
