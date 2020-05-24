/*
【题目2】：设信源可能输出的符号是a, b, c 三个字母，构成一个二阶Markov信源，
且各阶条件概率如下，试编写程序可以对任意字母序列（如abbcabcb）.
进行基于上下文的自适应算术编码，并进行相应的译码。
零阶条件概率：
    p(a)=1/3;	p(b)=1/3;	p(c)=1/3;
一阶条件概率：
	p(a/a)=1/2;	p(b/a )=1/4;	p(c/a)=1/4;    //横着来看，下面数组也是横着写的
	p(a/b)=1/4;	p(b/b)=1/2;	p(c/b)=1/4;
	p(a/c)=1/4;	p(b/c)=1/4;	p(c/c)=1/2;
二阶条件概率：
	p(a/aa)=3/5;	p(b/aa)=1/5;	p(c/aa)=1/5;
	p(a/ab)=1/4;	p(b/ab)=1/4;	p(c/ab)=1/2;
	p(a/ac)=1/4;	p(b/ac)=1/4;	p(c/a2)=1/2;
	p(a/ba)=1/2;	p(b/ba)=1/4;	p(c/ba)=1/4;
	p(a/bb)=1/5;	p(b/bb)=3/5;	p(c/bb)=1/5;
	p(a/bc)=1/4;	p(b/bc)=1/4;	p(c/bc)=1/2;		
	p(a/ca)=1/2;	p(b/ca)=1/4;	p(c/ca)=1/4;
	p(a/cb)=1/2;	p(b/cb)=1/4;	p(c/cb)=1/4;
	p(a/cc)=1/5;	p(b/cc)=1/5;	p(c/cc)=3/5;

*/

//灵感三，分组思想，每个组有各自的参数，用数组保存 （下标来区别，分类）

/*
注意：四种算术编码统一采用 8个字符一组，用空格或者回车作为间隔。
关于这个要求，夏娜老师的意思是输入的字符串超过8位时，以8个为一组进行编码，相邻两组之间的记忆性取消。

【warning】此代码没有考虑这一点！
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include<iomanip>
#include <math.h>
using namespace std;


char str[1000];											
char codeall[1000];									
char letter[3] = { 'a','b','c' };															
int len, k1, k2, k3, t, se_len;  //len是输入的字符串长，k123是标识符，t是香农公式结果，se_len和t一样
long double low, high, pro, code, start;//pro是概率，也是区间长度，code是区间中选取位置，start计数器
long double pro1 = 0.333333;									
long double pro2[3][3] = 
{ 0.5,0.25,0.25,
0.25,0.5,0.25,
0.25,0.25,0.5 };	
long double pro22[3][4] = 
{ 0.0,0.5,0.75,
1.0,0.0,0.25,
0.75,1.0,0.0,
0.25,0.5,1.0 };		
long double pro3[3][3][3] = 
{ 0.6,0.2,0.2,
0.25,0.25,0.5,
0.25,0.25,0.5,

0.5,0.25,0.25,
0.2,0.6,0.2,
0.25,0.25,0.5,

0.5,0.25,0.25,
0.5,0.25,0.25,
0.2,0.2,0.6 };			
long double pro33[3][3][4] = 
{ 0.0,0.6,0.8,
1.0,0.0,0.25,
0.5,1.0,0.0,

0.25,0.5,1.0,
0.0,0.5,0.75,
1.0,0.0,0.2,

0.8,1.0,0.0,
0.25,0.5,1.0,
0.0,0.5,0.75,

1.0,0.0,0.5,
0.75,1.0,0.0,
0.2,0.4,1.0 };	

void dingwei1(int a) {				//定位函数
	if (str[a] == 'a' ) {
		k1 = 0;
	}
	if (str[a] == 'b' ) {
		k1 = 1;
	}
	if (str[a] == 'c' ) {
		k1 = 2;
	}
}
void dingwei2(int a) {			//定位函数
	if (a != 0) {
		a = a - 1;
		if (str[a] == 'a') {
			k2 = 0;
		}
		if (str[a] == 'b') {
			k2 = 1;
		}
		if (str[a] == 'c') {
			k2 = 2;
		}
	}

}
void dingwei3(int a) {				//定位函数
	if (a != 0 && a != 1) {
		a = a - 2;
		if (str[a] == 'a') {
			k3 = 0;
		}
		if (str[a] == 'b') {
			k3 = 1;
		}
		if (str[a] == 'c') {
			k3 = 2;
		}
	}
}
bool shuru() {					
	int i = 0;
	cout << "请输入要编码的字符串(a to c)：";
	cin >> str;						//输入要编码的字符串
	while (str[i] != 0) {								
		len++;
		i++;
	}
	cout << "字符串长度为 :" << len << endl;
	for (i = 0; i < len; i++) {			  //判断输入是否合理
		if (str[i] >= 'a' && str[i] <= 'c' ) {

		}
		else {
			cout << "格式错误" << endl;
			exit(1);
			return false;
		}
	}
	i = 0;

	cout << endl;
	return true;
}


void bianma() {
	cout << "----编码开始标识符----" << endl;
	pro = 1;
	for (int i = 0; i < len; i++) {				
		dingwei1(i);
		dingwei2(i);
		dingwei3(i);
		if (i == 0) {
			low = low + k1 * pro1;
			pro = pro * pro1;
			high = low + pro;
		}
		else if (i == 1) 
		{
			low = low + pro * pro22[k2][k1];
			pro = pro * pro2[k2][k1];
			high = low + pro;
		}
		else 
		{
			low = low + pro * pro33[k3][k2][k1];
			pro = pro * pro3[k3][k2][k1];
			high = low + pro;
		}
	}

	t = ceil((log10(1 / pro)) / 0.301);			//香农公式定理
	cout << "最小编码数为(香农)：:" << "	" << t << endl;
	cout << "选取的区间为： " << "[" << setprecision(10) << low << "," << setprecision(10) << high << ")" << endl;
	code = 0.001 * low+0.999*high;		//code为选取位置 	
	cout << "选取的位置为 :" << setprecision(10) << code << endl;
	cout << "编码结果为： :";
	for (int i = 0; i < t; i++) {				//转为二进制
		code = code * 2;
		codeall[i] = (char)((int)code + 48);	//转为字符数组
		if (code >= 1)
			code = code - (int)code;
	}
	cout << codeall << endl;
}

void yima() {
	cout << endl<<"----译码开始标志----" << endl;
	int i = 0 ,j=0;
	start = 0;
	code = 0;
	se_len = 0;
	pro = 1;low = 0;high = 0;
	//	high = low+scale[j+1]*pro;
	//	low = low+pro*scale[j];
	while (codeall[i] != 0) {			//读取二进制的长度，就是编码后长度										
		se_len++;
		i++;
	}
	//cout << "字符串长度为： :" << se_len << endl;
	for (i = 0; i < se_len; i++) {							//转为十进制
		code = code + ((int)(codeall[i]) - 48) * pow(2, (-(i + 1)));
	}
	cout << "转换回十进制的值为 :" << setprecision(10) << code << endl;
	for (i = 0; i < len; i++) {		 //对应区间译码
		if (i == 0) {
			if (code >= 0 && code < pro1) {
				cout << letter[0];
				low = 0;
				high = pro1;
				pro = high - low;
				k1 = 0;
			}
			else if (code >= pro1 && code < pro1 * 2) {
				cout << letter[1] << endl;
				low = pro1;
				high = pro1 * 2;
				pro = high - low;
				k1 = 1;
			}
			else {
				cout << letter[2];
				low = pro1 * 2;
				high = 1;
				pro = high - low;
				k1 = 2;
			}
			start = low;
		}
		else if (i == 1) {
			for (int j = 0; j < 3; j++) {
				high = start + pro22[k1][j + 1] * pro;
				low = start + pro * pro22[k1][j];
				if (code >= low && code < high) {
					cout << letter[j];
					pro = high - low;
					start = low;
					k2 = j;
					break;
				}
			}
		}
		else {
			for (int j = 0; j < 3; j++) {
				high = start + pro33[k1][k2][j + 1] * pro;
				low = start + pro * pro33[k1][k2][j];
				if (code >= low && code < high) {
					cout << letter[j];
					pro = high - low;
					start = low;
					k1 = k2;
					k2 = j;
					break;
				}
			}
		}
	}
	cout << endl;
}

int main() {
	shuru();
	bianma();
	yima();
	return 0;
}
