
#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include<windows.h>

using namespace std;

struct Binary {
	Binary(int c, int i, string v = "_") {
		type = c;
		index = i;
		value = v;
	}
	int type = 0;
	int index = 0;
	string value = "_";
}; // 二元集

class Settie_lex_analyzer {
public:
	void init(); // 初始化 
	void input(); // 输入 
	Binary Scan(); // 逐个扫描字符并返回其对应的二元集 
	void cycle(); // 循环读取整个输入 
	void show_table(); // 展示 
};



string in_str;				//输入符号串
int index;					//当前输入符号读入字符的位置
char character;				//全局变量字符，存放最新读入的字符
string token;				//字符数组，存放已读入的字符序列
map<string, int> Symbol;	//标识符集
map<string, int> Digit;		//常数集
map<string, int> String;		//字符串集
map<string, int>::iterator ite; // 迭代器
const int len = 100;
string Reserve[3 * len];

void getChar(); // 读取字符
void get_no_blank(); // 跳过空白
void concat(); // 连接字符
void retract(); // 回退字符
bool is_letter(); // 判断字母
bool is_digit(); // 判断数字
bool is_string(); // 判断字符串
bool is_dotOnce(); // 判断单点
int reserve(); // 匹配保留字
string symbol(); // 匹配已有的符号表
string constant(); // 匹配已有的常数表
string _string(); // 匹配已有的字符串
Binary error(); // 报错

void Settie_lex_analyzer::init()
{
	// 保留字

	// 关键字
	Reserve[4] = "set";
	Reserve[5] = "func";
	Reserve[6] = "with";
	Reserve[7] = "assign";
	Reserve[8] = "unfold";
	Reserve[9] = "this";
	Reserve[10] = "is";

	// 界符
	Reserve[11] = "=";
	Reserve[12] = ":";
	Reserve[13] = ".";
	Reserve[14] = "(";
	Reserve[15] = ")";
	Reserve[16] = "{";
	Reserve[17] = "}";
	Reserve[18] = "=>";
	Reserve[19] = ";";
	Reserve[20] = "-";

	// 运算符
	Reserve[21] = "->";
	Reserve[22] = "|";
	Reserve[23] = "&";
	Reserve[24] = ".";


	//标记

	Reserve[28] = "BINDING";
	Reserve[29] = "COLON";
	Reserve[30] = "DOT";
	Reserve[31] = "OB";
	Reserve[32] = "CB";
	Reserve[33] = "LB";
	Reserve[34] = "RB";
	Reserve[35] = "MATCH";
	Reserve[36] = "SE";
	Reserve[37] = "SP";
	Reserve[38] = "FS";
	Reserve[39] = "OR";
	Reserve[40] = "AND";
	Reserve[41] = "POINT";

	Symbol.clear();		//标识符集初始化
	Digit.clear();		//常数集初始化
	index = 0;
	character = ' ';
	token = "";
}



void getChar() {
	character = in_str[index++];
}


void get_no_blank()
{

	while (character == ' ') {
		getChar();
	}
}


void concat() {
	token = token + character;
}


void retract()
{
	character = ' ';
	index--;
}


bool is_letter()
{
	if ((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z'))
		return true;
	return false;
}


bool is_digit()
{
	if (character >= '0' && character <= '9')
		return true;

	return false;
}

bool is_string()
{
	if (character == '"')
		return true;
	return false;
}

int dot_Sum = 0;
bool is_dotOnce()
{
	if (character == '.')
		dot_Sum++;
	if (dot_Sum == 1 || dot_Sum == 0)
		return true;
	else
		return false;
}

int reserve()
{
	for (int i = 0; i < 40; i++)
		if (Reserve[i] == token)
			return i;
	return -1;
}

string symbol()
{
	ite = Symbol.find(token); // 寻找符号

	if (ite != Symbol.end()) {
		return ite->first;  // 找到，返回其值
	}
	else {
		Symbol[token] = Symbol.size();
		return token;  // 没找到，将其写入符号表
	}
}

string constant()
{
	ite = Digit.find(token);

	if (ite != Digit.end()) {
		return ite->first;
	}
	else {
		Digit[token] = Digit.size();
		return token;
	}
}

string  _string()
{
	ite = String.find(token);

	if (ite != String.end()) {
		return ite->first;
	}
	else {
		String[token] = String.size();
		return token;
	}
}

Binary error()
{
	cout << token << "错误！" << endl;
	return Binary(0, 0);

}


Binary Settie_lex_analyzer::Scan()
{
	token = "";
	getChar();
	get_no_blank();
	string val;
	int num = -1;
	dot_Sum = 0;

	switch (character) {
	case'a':
	case'b':
	case'c':
	case'd':
	case'e':
	case'f':
	case'g':
	case'h':
	case'i':
	case'j':
	case'k':
	case'l':
	case'm':
	case'n':
	case'o':
	case'p':
	case'q':
	case'r':
	case's':
	case't':
	case'u':
	case'v':
	case'w':
	case'x':
	case'y':
	case'z':
	case'A':
	case'B':
	case'C':
	case'D':
	case'E':
	case'F':
	case'G':
	case'H':
	case'I':
	case'J':
	case'K':
	case'L':
	case'M':
	case'N':
	case'O':
	case'P':
	case'Q':
	case'R':
	case'S':
	case'T':
	case'U':
	case'V':
	case'W':
	case'X':
	case'Y':
	case'Z':
		while (is_letter() || is_digit() || character == '_') { //为字母 数字 下划线
			concat();		//追加到token末尾
			getChar();		//读取下一个字符
		}
		retract();			//回退一个字符
		num = reserve();	//判断是否为保留字
		if (num != -1) {
			return Binary(num, 1);
		}
		else {
			val = symbol();	// 查看符号表
			return Binary(1, Symbol[val], val);
		}
		break;


	case'0':
		concat();
		getChar();
		if (character == 'x' || character == 'X')	//十六进制
		{
			concat();		//追加到token末尾
			getChar();		//读取下一个字符
			while (is_letter() || is_digit()) { //为字母 数字 
				concat();		//追加到token末尾
				getChar();		//读取下一个字符
			}
			retract();			//回退一个字符
			val = constant();
			return Binary(2, Digit[val], val);
		}

		else if (is_dotOnce() || is_digit())
		{
			concat();		//追加到token末尾
			getChar();
			while (is_digit() && is_dotOnce()) {	//为数字
				concat();
				getChar();
			}
			retract();
			val = constant();	//查看常数表
			return Binary(2, Digit[val], val);
		}
		else
			retract();
		break;

	case'1':
	case'2':
	case'3':
	case'4':
	case'5':
	case'6':
	case'7':
	case'8':
	case'9':
		concat();		//追加到token末尾
		getChar();
		while (is_digit() || character == '.' && is_dotOnce() || is_letter())
		{
			if (character == 'e' || character == 'E') {
				concat();
				getChar();
				if (character == '-' || is_digit()) {
					concat();
					getChar();
					continue;
				}
			}
			concat();
			getChar();
		}
		retract();
		val = constant();	//查看常数表
		return Binary(2, Digit[val], val);

		break;


	case'=':
		getChar();
		if (character == '>')
			return Binary(35, 0);	
		else {
			retract();
			return Binary(28, 0);	
		}
		break;

	case'-':
		getChar();
		if (character == '>')
			return Binary(38, 0);	
		else {
			retract();
			return Binary(37, 0);	
		}
		break;

	case'{':
		return Binary(33, 0);
		break;

	case'}':
		return Binary(34, 0);
		break;
	case'(':
		return Binary(31, 0);
		break;

	case')':
		return Binary(32, 0);
		break;

	case'|':
		return Binary(39, 0);
		break;

	case',':
		return Binary(30, 0);
		break;

	case';':
		return Binary(36, 0);
		break;

	case'.':
		return Binary(41, 0);
		break;

	case':':
		return Binary(29, 0);
		break;

	case'"':
		getChar();
		while (character != '"') { // 字符串（“”）
			concat();
			getChar();

		}
		val = _string();
		return Binary(3, String[val], val);
		break;


	default:
		return error();
	}
}


void Settie_lex_analyzer::show_table()
{

	cout << "==================" << "保留字" << "==================" << endl;
	cout << "保留字符\t类别编码" << endl;
	for (int i = 0; i < 25; i++) {
		if (Reserve[i] != "") {
			if (Reserve[i].size() >= 8)
				cout << Reserve[i] << "\t" << i << endl;
			else
				cout << Reserve[i] << "\t\t" << i << endl;
		}
	}

	cout << "\n==================" << "标识符" << "==================" << endl;
	cout << "标识符\t\t类别编码\t表中位置" << endl;
	for (ite = Symbol.begin(); ite != Symbol.end(); ite++) {
		if (ite->first.size() >= 8)
			cout << ite->first << "\t1\t\t" << ite->second << endl;
		else
			cout << ite->first << "\t\t1\t\t" << ite->second << endl;
	}

	cout << "\n==================" << "常数表" << "==================" << endl;
	cout << "常量值\t\t类别编码\t表中位置" << endl;
	for (ite = Digit.begin(); ite != Digit.end(); ite++) {
		cout << ite->first << "\t\t2\t\t" << ite->second << endl;
	}

	cout << "\n=================" << "字符串表" << "==================" << endl;
	cout << "字符串值\t类别编码\t表中位置" << endl;
	for (ite = String.begin(); ite != String.end(); ite++) {
		cout << ite->first << "\t\t3\t\t" << ite->second << endl;
	}

}

void Settie_lex_analyzer::input() {
	
	string in;
	while (cin >> in && in != "@") {
		in_str = in_str + " " + in;
	}
}


void  Settie_lex_analyzer::cycle() {
	Binary word(0, 0, "_");

	while (index < in_str.size())
	{
		word = Scan();

		if (word.type != 0)
		{
		
			if (word.type == 1) {
				cout << "(" << "ID" << "," << "\"" << word.value << "\"" << ")" << endl;
				continue;
			}
			if (word.type == 2) {
				cout << "(" << "NUB" << "," << word.value << ")" << endl;
				continue;
			}
			if (word.type == 3) {
				cout << "(" << "STRING" << "," << "\"" << word.value << "\"" << ")" << endl;
				continue;
			}
			cout << "(" << Reserve[word.type] << "," << word.value << ")" << endl;
			
		}
		
	}

}


int main()
{
	cout << "输入待词法分析的源程序代码：以Begin 开头，并输入@代表结束\n" << endl;
	//初始化
	Settie_lex_analyzer a;
	a.init();
	a.input();
	cout << "\n------------------------识别结果------------------------" << endl;
	a.Scan();
	a.cycle();
	cout << "\n------------------------词汇表展示------------------------\n" << endl;
	a.show_table();
	return 0;

}



