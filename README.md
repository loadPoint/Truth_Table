# Truth_Table
源代码就是这个文件，用C++实现的.可以处理大多数表达式，并且指出像是两个原子命题之间没有连接词的情况,以及使用了不合法字符的情况如 P(Q->P) 或者p/\Q W->Q.
程序在处理输入的时候会自动把/\之类两个字符的连接词换成一个字符来处理，所以使用#（代替双蕴涵），￥（代替蕴涵），&（代表合取），|（代表析取）程序是不会报错的 比如P&Q和P/\Q结果是一样的
输入不对连接词的也会报错，如P<-Q也会提示非法。

Present by 马治斌
