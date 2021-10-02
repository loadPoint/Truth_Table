//�������ߣ�	���α�
//ѧ�ţ�		2021010757
//������Ϊ1.5�汾 Ŀǰ�Ĺ����У�
//������ʽ����ֵ�����Դ�����Ƿ����ʽ������ʾ

//������־
//V1.5:����������ʶ������(P/\S)P֮��ķǷ����ʽ�����Ƕ������Ų�ƥ�仹��û�취
//V1.4:�޸���1.3�������Ŵ����������
//V1.3:�޸���1.2���bug���淶����һЩ���
#include<iostream>
#include<stdio.h>
#include<stack>

using namespace std;
// ��������
#define TEST_PRE_ANS	false
#define TEST_PRE		false
#define TEST_STACK		false
#define TEST_POLAND_ANS	false
#define TEST_POLAND		false
#define TEST_COUNT		false
#define TEST_CALU		false
//END

//�ⲿ���ǻ�����������������
char s[258];
int  len;
char TF_char[5];
int  num_of_func = 0;
//���ݽṹ
stack<char> operate;//�������ջ
stack<char> operand;//��������ջ
//END-------------------------------------------------------------------------------------------------------------

//�ⲿ��Ϊ��������I/O��ʽ
//ʹ��˵������
void format()
{
	printf("���淶��\n");
	printf("ʹ��P,Q,R,S,K���α�ʾ����ԭ������\n");
	printf("��ʹ�� '!',��ȡʹ��'/\\', ��ȡʹ��'\\/',�̺�ʹ��'->'\n");
	printf("˫�̺�Ҳ֧�֣���ʹ��'<>'\n");
	printf("ע�����з��Ŷ���Ӣ�ĵķ���,�������256���ַ�,���ܺ��пո�\n");
	printf("present by ���α� >_<\n");
	printf("\n\n��������ʽ:  ");
	return;
}
//����������
//�����ͷ
void output_format()
{
	for (int i = 0; i < num_of_func; ++i)
	{
		printf(" %c  ", TF_char[i]);
	}
	printf("ANSWER\n");
	return;
}
//���ÿһ��
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

//�ⲿ�ֽ���Ԥ����
//�ַ���ǰ�ƺ���
void mov_(int st)
{
	for (int i = st; i < len - 1; ++i)
	{
		s[i] = s[i + 1];
	}
	return;
}
//���ַ���Ԥ������
void pre_string()			//��Ԥ������
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

//�ⲿ�ֽ�����׺���沨�����ʽ��ת��
//�ж��Ƿ�Ϊ�Ϸ���ԭ������
bool is_TF(char x)
{
	return(x == 'P' || x == 'Q' || x == 'R' || x == 'S' || x == 'K');
}
//�ж��Ƿ�Ϊ�����������
bool is_oper(char x)
{
	return (x == '!' || x == '|' || x == '&' || x == '$' || x == '#');
	// ��������ȼ���ǰ��С�ں���Ϊ��
}
// ��������ȼ���ǰ��С�ں���Ϊ��
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
//�Ӷ�ջת��Ϊ�ַ���
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
//��ת������
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
				if (operate.top() == '(')											//����ԭ����')'
					sign = 0;
				if (TEST_STACK)printf("operand stack push %c\n", operate.top());
				operand.push(operate.top());														//���������һ��
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

//�ⲿ�ֽ���ԭ�������ͳ���봦��
//����ĸ���ֻ�
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
//������ĸ��
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
//ͳ�Ʊ����ĸ���
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

//�ⲿ�ֽ������ռ���
//��ĸ����Ϊֵ
bool get_value(char x,int k)//x����ĸ ;k�Ǽ������
{
	for (int i = 0; i < num_of_func; ++i)
	{
		if (TF_char[i] == x) {
			return k & (1 << (num_of_func - i - 1));
		}
	}
}
//�Զ������㣺�̺�
bool implication(bool a, bool b)
{
	if (a == 0 && b == 1) return false;
	else return true;
}
//�����㺯����ջ
stack<bool> calu_stack;
//�����㺯��
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
	format();			//�����ʾ��Ϣ
	cin >> s;			//������ʽ						//��Ҫ���������ⲿ��ɾ��
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
			goto errorcase;	//�ж��Ƿ�Ϊ�Ƿ����ʽ
	}
	pre_string();		//Ԥ����
	for (int i = 0; i < len; ++i)
	{
		if (
			(!is_TF(s[i])) &&
			(!is_oper(s[i])) &&
			(s[i] != '(') &&
			(s[i] != ')')
			) goto errorcase;//�ж����޷Ƿ��ַ�
	}
	poland();			//ת��Ϊ�沨�����ʽ
	TF_count();			//ͳ��ԭ�ӱ���
	//���ռ��������
	output_format();	//�����ֵ��ı�ͷ
	for (register int k = 0; k < (1 << num_of_func); ++k)
	{
		bool answer = calu(k);		//������ֵ��ĵ�k��
		output_answer(answer, k);	//�����ֵ��ĵ�k��
	}
	//END
	system("pause");
	return 0;
	//��������
errorcase:
	printf("����ı��ʽ�Ƿ���");
	system("pause");
	return 0;
}