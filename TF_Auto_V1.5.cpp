//程序作者：	马治斌
//学号：		2021010757
//本程序为1.5版本 目前的功能有：
//计算表达式的真值表，并对大多数非法表达式给出提示

//开发日志
//V1.5:现在它可以识别形如(P/\S)P之类的非法表达式，但是对于括号不匹配还是没办法
//V1.4:修复了1.3版在括号处理方面的问题
//V1.3:修复了1.2版的bug；规范化了一些语句
#include<iostream>
#include<stdio.h>
#include<stack>

using namespace std;
// 调试区域
#define TEST_PRE_ANS	false
#define TEST_PRE		false
#define TEST_STACK		false
#define TEST_POLAND_ANS	false
#define TEST_POLAND		false
#define TEST_COUNT		false
#define TEST_CALU		false
//END

//这部分是基础数据与数据类型
char s[258];
int  len;
char TF_char[5];
int  num_of_func = 0;
//数据结构
stack<char> operate;//运算符堆栈
stack<char> operand;//操作数堆栈
//END-------------------------------------------------------------------------------------------------------------

//这部分为了美化和I/O格式
//使用说明部分
void format()
{
	printf("求解规范：\n");
	printf("使用P,Q,R,S,K依次表示各个原子命题\n");
	printf("否定使用 '!',合取使用'/\\', 析取使用'\\/',蕴含使用'->'\n");
	printf("双蕴含也支持，请使用'<>'\n");
	printf("注意所有符号都是英文的符号,最多输入256个字符,不能含有空格\n");
	printf("present by 马治斌 >_<\n");
	printf("\n\n请输入表达式:  ");
	return;
}
//结果输出部分
//输出表头
void output_format()
{
	for (int i = 0; i < num_of_func; ++i)
	{
		printf(" %c  ", TF_char[i]);
	}
	printf("ANSWER\n");
	return;
}
//输出每一行
void output_answer(bool answer,int k)
{
	for (int i = 0; i < num_of_func; ++i)
	{
		bool sign = k & (1 << (num_of_func - i - 1));
		printf(" %c  ", sign ? 'T' : 'F');
	}
	printf("  %c \n", answer ? 'T' : 'F');
	return;
}
//END-------------------------------------------------------------------------------------------------------------

//这部分进行预处理
//字符串前移函数
void mov_(int st)
{
	for (int i = st; i < len - 1; ++i)
	{
		s[i] = s[i + 1];
	}
	return;
}
//主字符串预处理函数
void pre_string()			//主预处理函数
{
	for (int i = 0; i < len - 1; ++i)
	{
		if (s[i] == '/'&&s[i + 1] == '\\')
		{
			s[i] = '&';
			mov_(i + 1);
			len--;
		}

		if (s[i] == '\\'&&s[i + 1] == '/')
		{
			s[i] = '|';
			mov_(i + 1);
			len--;
		}

		if (s[i] == '-'&&s[i + 1] == '>')
		{
			s[i] = '$';
			mov_(i + 1);
			len--;
		}
		if (s[i] == '<'&&s[i + 1] == '>')
		{
			s[i] = '#';
			mov_(i + 1);
			len--;
		}
	}
	s[len] = '\0';
	if (TEST_PRE_ANS)printf("pre_string answer is %s\n", s);
	return;

}
//END-------------------------------------------------------------------------------------------------------------

//这部分进行中缀向逆波兰表达式的转化
//判断是否为合法的原子命题
bool is_TF(char x)
{
	return(x == 'P' || x == 'Q' || x == 'R' || x == 'S' || x == 'K');
}
//判断是否为非括号运算符
bool is_oper(char x)
{
	return (x == '!' || x == '|' || x == '&' || x == '$' || x == '#');
	// 运算符优先级：前者小于后者为真
}
// 运算符优先级：前者小于后者为真
bool cmp_oper(char a, char b)
{
	int a_ = 1, b_ = 1;
	if (a == 'E' || b == 'E')return true;
	switch (a)
	{
	case '!':a_ = 4; break;
	case '&':a_ = 3; break;
	case '|':a_ = 2; break;
	case '$':a_ = 1; break;
	case '#':a_ = 0; break;
	};
	switch (b)
	{
	case '!':b_ = 4; break;
	case '&':b_ = 3; break;
	case '|':b_ = 2; break;
	case '$':b_ = 1; break;
	case '#':b_ = 0; break;
	};
	return a_ < b_;
}
//从堆栈转化为字符串
void str_rewrite()
{
	if (TEST_POLAND)printf("+++Now begin to clear the stack operand+++\n");
	int i = 0;
	while (!operand.empty())
	{
		if (operand.top() != '(' && operand.top() != ')')
		{
			if (TEST_POLAND)printf("write the character %c\n", operand.top());
			s[i] = operand.top();
			++i;
		}
		operand.pop();
	}
	s[i] = '\0';
	len = i;
	reverse(s, &s[len]);
	return;
}
//主转化函数
void poland()
{
	for (int i = 0; i < len; ++i)
	{
		if (TEST_POLAND&&i == 6 - 1)	
			system("pause");
		if (TEST_POLAND)printf("Now is the character %c\n", s[i]);
		if (is_TF(s[i]))
		{
			if (TEST_STACK)printf("operand stack push %c\n", s[i]);
			operand.push(s[i]);
			continue;
		}
		if (s[i] == '(')
		{
			if (TEST_STACK)printf("operate stack push %c\n", s[i]);
			operate.push(s[i]);
			continue;
		}
		if (s[i] == ')')
		{
			bool sign = 1;
			while (sign) {
				if (operate.top() == '(')											//这里原来是')'
					sign = 0;
				if (TEST_STACK)printf("operand stack push %c\n", operate.top());
				operand.push(operate.top());														//问题出在这一步
				if (TEST_STACK)printf("operate stack pop %c\n", operate.top());
				operate.pop();
			}
		}
		if (is_oper(s[i]))
		{
			if (operate.empty())
			{
				if (TEST_STACK)printf("operate stack push %c\n", s[i]);
				operate.push(s[i]);
				continue;
			}
			if (operate.top() == '(')
			{
				if (TEST_STACK)printf("operate stack push %c\n", s[i]);
				operate.push(s[i]);
				continue;
			}
			if ( cmp_oper(operate.top(), s[i]))
			{
				if (TEST_STACK)printf("operate stack push %c\n", s[i]);
				operate.push(s[i]);
				continue;
			}
			if (!cmp_oper(operate.top(), s[i]))
			{
				bool sign = 1;
				while (sign)
				{
					if (TEST_STACK)printf("operand stack push %c\n", operate.top());
					operand.push(operate.top());
					if (TEST_STACK)printf("operate stack pop--> %c\n", operate.top());
					operate.pop();
					if (operate.empty() || cmp_oper(operate.top(), s[i]) || operate.top() == '(')
					{
						sign = 0;
					}
				}
				if (TEST_STACK)printf("operate stack push %c\n", s[i]);
				operate.push(s[i]);
				continue;
			}
		}
	}
	while (operate.size())
	{
		if (TEST_STACK)printf("operand stack push %c\n", operate.top());
		operand.push(operate.top());
		if (TEST_STACK)printf("operate stack pop %c\n", operate.top());
		operate.pop();
	}
	str_rewrite();
	if (TEST_POLAND_ANS) printf("Poland answer string is %s\n", s);
	return;
}
//END------------------------------------------------------------------------------------------------------------

//这部分进行原子命题的统计与处理
//将字母数字化
int char_to_num(char x) {
	int temp = 0;
	switch (x) {
	case'P': temp = 0; break;
	case'Q': temp = 1; break;
	case'R': temp = 2; break;
	case'S': temp = 3; break;
	case'K': temp = 4; break;
	}
	return temp;
}
//数字字母化
char num_to_char(int x) {
	char temp;
	switch (x) {
	case 0: temp = 'P'; break;
	case 1: temp = 'Q'; break;
	case 2: temp = 'R'; break;
	case 3: temp = 'S'; break;
	case 4: temp = 'K'; break;
	}
	return temp;
}
//统计变量的个数
void TF_count()
{
	int flag[5] = { 0,0,0,0,0 };
	for (int i = 0; i < len; ++i)
	{
		if (is_TF(s[i]))
		{
			flag[char_to_num(s[i])] = 1;
		}
	}
	for (int i = 0; i < 5; ++i)
	{
		if (flag[i])
		{
			TF_char[num_of_func] = num_to_char(i);
			++num_of_func;
		}
	}
	if (TEST_COUNT)printf("Count finish with %d Atomic propositions\n", num_of_func);
	return;
}
//END------------------------------------------------------------------------------------------------------------

//这部分进行最终计算
//字母代换为值
bool get_value(char x,int k)//x是字母 ;k是计算次数
{
	for (int i = 0; i < num_of_func; ++i)
	{
		if (TF_char[i] == x) {
			return k & (1 << (num_of_func - i - 1));
		}
	}
}
//自定义运算：蕴涵
bool implication(bool a, bool b)
{
	if (a == 0 && b == 1) return false;
	else return true;
}
//主计算函数堆栈
stack<bool> calu_stack;
//主计算函数
bool calu(int k) 
{
	while (calu_stack.size()) calu_stack.pop();
	for (int i = 0; i < len; ++i)
	{
		if (is_TF(s[i]))
		{
			calu_stack.push(get_value(s[i], k));
			continue;
		}
		if (is_oper(s[i])) 
		{
			switch(s[i]) {
			case'&': {
				bool a, b;
				a = calu_stack.top();
				calu_stack.pop();
				b = calu_stack.top();
				calu_stack.pop();

				calu_stack.push(a&&b);
				break;
			}
			case'|': {
				bool a, b;
				a = calu_stack.top();
				calu_stack.pop();
				b = calu_stack.top();
				calu_stack.pop();

				calu_stack.push(a||b);
				break;
			}
			case'$': {
				bool a, b;
				a = calu_stack.top();
				calu_stack.pop();
				b = calu_stack.top();
				calu_stack.pop();

				calu_stack.push(implication(a,b));
				break;
			}
			case'!': {
				bool a;
				a = calu_stack.top();
				calu_stack.pop();

				calu_stack.push(!a);
				break;
			}
			case'#': {
				bool a, b;
				a = calu_stack.top();
				calu_stack.pop();
				b = calu_stack.top();
				calu_stack.pop();

				calu_stack.push(a == b);
				break;
			}
			}
		}
	}
	return calu_stack.top();
}
//END------------------------------------------------------------------------------------------------------------
int main()
{
	format();			//输出提示信息
	cin >> s;			//输入表达式						//不要忘了最后把这部分删掉
	len = strlen(s);
	int errorflag = 0;
	for (int i = 0; i < len; ++i)
	{
		if (s[i] == '(' || s[i] == ')') continue;
		if (is_TF(s[i]))
			errorflag++;
		else
			errorflag = 0;
		if (errorflag == 2)
			goto errorcase;	//判断是否为非法表达式
	}
	pre_string();		//预处理
	for (int i = 0; i < len; ++i)
	{
		if (
			(!is_TF(s[i])) &&
			(!is_oper(s[i])) &&
			(s[i] != '(') &&
			(s[i] != ')')
			) goto errorcase;//判断有无非法字符
	}
	poland();			//转化为逆波兰表达式
	TF_count();			//统计原子变量
	//最终计算与输出
	output_format();	//输出真值表的表头
	for (register int k = 0; k < (1 << num_of_func); ++k)
	{
		bool answer = calu(k);		//计算真值表的第k行
		output_answer(answer, k);	//输出真值表的第k行
	}
	//END
	system("pause");
	return 0;
	//错误处理部分
errorcase:
	printf("输入的表达式非法！");
	system("pause");
	return 0;
}