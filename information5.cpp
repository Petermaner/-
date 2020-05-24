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
[waring:这次是考虑了这一点的！]
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include<iomanip>
#include <math.h>
using namespace std;

int z = 0;//像上一题的i，分组专用  （保留）

char str[10][1000];
//char codeall[10][1000];
long double codeall[10][1000];
char letter[3] = { 'a','b','c' };
int len[10] = { 0 }, k1[5] = { 0 }, k2[5] = { 0 }, k3[5] = { 0 }, t[5]; //se_len[10];  //len是输入的字符串长，k123是标识符，t是香农公式结果，se_len和t一样
long double result[4],low[5], high[5], pro[5], code[5], start[5];//pro是概率，也是区间长度，code是区间中选取位置，start计数器
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
long double pro3[3][3][3] = //下标
{ 0.6,0.2,0.2,              //00-0  00-1  00-2
0.25,0.25,0.5,              //01
0.25,0.25,0.5,              //02
0.5,0.25,0.25,              //10
0.2,0.6,0.2,                //11
0.25,0.25,0.5,              //12
0.5,0.25,0.25,              //20
0.5,0.25,0.25,              //21
0.2,0.2,0.6 };	    	    //22          22-2
long double pro33[3][3][4] =  //举例：abbc,选到c的时候，low[k]值的改动，需要0.8=0.2+0.6
						  //构造方法：pro3的第1列，都给pro33的第二列；pro3的第1和2列和，赋给pro33的第三列；首尾赋0，1
						  //0.0是因为又选到了a， 选到b就是前面一个a的值，选到c就是前面a和b的和
{ 0.0,0.6,0.8,1.0,    //下标  00-0  00-1  00-2  00-3
0.0,0.25,0.5,1.0,           //01
0.0,0.25,0.5,1.0,           //02
0.0,0.5,0.75,1.0,           //10
0.0,0.2,0.8,1.0,            //11
0.0,0.25,0.5,1.0,           //12
0.0,0.5,0.75,1.0,           //20
0.0,0.5,0.75,1.0,           //21
0.0,0.2,0.4,1.0 };	    //22                22-3

void dingwei1(int a, int k) {				//定位函数
	if (str[k][a] == 'a') {
		k1[k] = 0;
	}
	if (str[k][a] == 'b') {
		k1[k] = 1;
	}
	if (str[k][a] == 'c') {
		k1[k] = 2;
	}
}
void dingwei2(int a, int k) {			//定位函数
	if (a != 0) {
		a = a - 1;
		if (str[k][a] == 'a') {
			k2[k] = 0;
		}
		if (str[k][a] == 'b') {
			k2[k] = 1;
		}
		if (str[k][a] == 'c') {
			k2[k] = 2;
		}
	}

}
void dingwei3(int a, int k) {				//定位函数
	if (a != 0 && a != 1) {
		a = a - 2;
		if (str[k][a] == 'a') {
			k3[k] = 0;
		}
		if (str[k][a] == 'b') {
			k3[k] = 1;
		}
		if (str[k][a] == 'c') {
			k3[k] = 2;
		}
	}
}
bool shuru(int& z) {
	int i = 0;
	cout << "请输入要编码的字符串(a to c)：";
	/*
		cin >> str[k];						//输入要编码的字符串
		while (str[k][i] != 0) {
			len[k]++;
			if (str[k][i] == ' ') {
				len[k]--;
				k++;
			}
			i++;
			cin>>str[k];
		}
	*/

	char x;
	cin >> x;
	while (x != '\n') {   //这里三个k要保留
		str[z][i] = x;
		i++;
		len[z]++;
		
		x = getchar();
		if (x == ' ') {
			z++;
			x = getchar();
			i=0;
		}

	}
	cout << "z的值为(组数)：" << z << endl;
	cout<<"请确认输入的字符串为：（验证用）" ;
	for (int k = 0; k <= z; k++) {
		for (int q = 0; q <= i; q++) {
			cout << str[k][q] ;
		}
		cout << "  ";
		
	}
	/* 测试时使用 
		for(int k=0;k<=k;k++){
		  for(int q=0;q<=i;q++){
				cout<<"看到我了吗？"<<str[k][q]<<" ";
			}

	*/
	int count = 0;
	for (int k = 0; k <= z; k++) {
		count += len[k];
	}
	cout<<endl<< "字符串长度为 :" << count << endl;

/*
	for (int k = 0; k <= z; k++) {
		for (i = 0; i < len[k]; i++) {			  //判断输入是否合理
			if (str[k][i] >= 'a' && str[k][i] <= 'c' || str[k][i] == ' ') {

			}
			else {
				cout << "格式错误" << endl;
				exit(1);
				return false;
			}
		}

	}
*/
	i = 0;
	cout << endl;
	return true;
}


void bianma() {
	cout << "----编码开始标识符----" << endl;
	for (int k = 0; k <= z; k++) {
		pro[k] = 1;
		for (int i = 0; i < len[k]; i++) {
			dingwei1(i, k);
			dingwei2(i, k);
			dingwei3(i, k);
			if (i == 0) {
				low[k] = low[k] + k1[k] * pro1;
				pro[k] = pro[k] * pro1;
				high[k] = low[k] + pro[k];
			}
			else if (i == 1)
			{
				low[k] = low[k] + pro[k] * pro22[k2[k]][k1[k]];
				pro[k] = pro[k] * pro2[k2[k]][k1[k]];
				high[k] = low[k] + pro[k];
			}
			else
			{
				low[k] = low[k] + pro[k] * pro33[k3[k]][k2[k]][k1[k]];
				pro[k] = pro[k] * pro3[k3[k]][k2[k]][k1[k]];
				high[k] = low[k] + pro[k];
			}
		}


	}

	cout << "最小编码数为(香农)：:";
	for (int k = 0; k <= z; k++) {
		t[k] = ceil((log10(1 / pro[k])) / 0.301);			//香农公式定理
		cout << t[k] << " ";
	}


	cout << endl << "选取的区间为： ";
	for (int k = 0; k <= z; k++) {
		cout << "[" << setprecision(10) << low[k] << "," << setprecision(10) << high[k] << ")" << " ";
		code[k] = 0.001 * low[k] + 0.999 * high[k];		//code为选取位置
	}

	cout << endl << "选取的位置为 :";
	for (int k = 0; k <= z; k++) {
		cout << setprecision(10) << code[k] << "  ";

	}
	cout << endl << "编码结果为： :";        //这里出了问题1
/*
	for (int k = 0; k <= z; k++) {
		for (int i = 0; i < t[k]; i++) {				//转为二进制
			code[k] = code[k] * 2;
			codeall[k][i] = (char)((int)code[k] + 48);	//转为字符数组
			if (code[k] >= 1)
				code[k] = code[k] - (int)code[k];
		}
		cout << codeall[k] << " ";
	}

*/

	for (int k = 0; k <= z; k++) {
		for (int i = 0; i < t[k]; i++) {				//转为二进制
			codeall[k][i] = floor(code[k] * 2.0);	//转为字符数组
			cout << codeall[k][i];
			code[k] = code[k] * 2 - floor(code[k] * 2.0);
		}
		cout << " ";

	}

}

void yima() {
	cout << endl << endl << "----译码开始标志----" << endl;
	int i = 0, j = 0;
	start[5] = { 0 };
	code[5] = { 0 };
	//se_len[5] = { 0 };
	//result[5] = { 0.0 };
	pro[5] = { 1 }; low[5] = { 0 }; high[5] = { 0 };
	//	high[k] = low[k]+scale[j+1]*pro;
	//	low[k] = low[k]+pro*scale[j];
/*
	for (int k = 0; k <= z; k++) {
		while (codeall[k][i] != '\0') {			//读取二进制的长度，就是编码后长度										
			se_len[k]++;
			i++;
		}

	}
*/
	cout << "转换回十进制的值为 :";            //这里出了问题2，可能是问题1导致
	//cout << "字符串长度为： :" << se_len << endl;
	
/*
	for (int k = 0; k <= z; k++) {
		for (i = 0; i < se_len[k]; i++) {							//转为十进制
			code[k] = code[k] +((int)(codeall[k][i]) - 48) * pow(2, (-(i + 1)));
		}
		cout << setprecision(10) << code[k] << "  ";
	}
*/
	//code是位置，编码结果存在codeall里面
	for (int k = 0; k <= z; k++) {
		for (i = 0; i < t[k]; i++) {							//转为十进制
			result[k] += codeall[k][i]*pow(2,(-1)*(i+1));
		}
		cout << setprecision(10) << result[k] << "  ";
	}




	cout << endl << "译码结果为：";
	for (int k = 0; k <= z; k++) {
		for (i = 0; i < len[k]; i++) {		 //对应区间译码  //第一个直接if判断找出a,b,c
			if (i == 0) {
				if (result[k] >= 0 && result[k] < pro1) {
					cout << letter[0];
					low[k] = 0;
					high[k] = pro1;
					pro[k] = high[k] - low[k];
					k1[k] = 0;
				}
				else if (result[k] >= pro1 && result[k] < pro1 * 2) {
					cout << letter[1] << endl;
					low[k] = pro1;
					high[k] = pro1 * 2;
					pro[k] = high[k] - low[k];
					k1[k] = 1;
				}
				else {
					cout << letter[2];
					low[k] = pro1 * 2;
					high[k] = 1;
					pro[k] = high[k] - low[k];
					k1[k] = 2;
				}
				start[k] = low[k];
			}
			else if (i == 1) {      //这里因为概率不确定，这里选择穷举遍历（暴力匹配）来找
				for (int j = 0; j < 3; j++) {
					high[k] = start[k] + pro22[k1[k]][j + 1] * pro[k];
					low[k] = start[k] + pro[k] * pro22[k1[k]][j];
					if (result[k] >= low[k] && result[k] < high[k]) {
						cout << letter[j];
						pro[k] = high[k] - low[k];
						start[k] = low[k];
						k2[k] = j;
						break;
					}
				}
			}
			else {                 //位数多了，基本都是在走这一步，算法原理同上
				for (int j = 0; j < 3; j++) {
					high[k] = start[k] + pro33[k1[k]][k2[k]][j + 1] * pro[k];
					low[k] = start[k] + pro[k] * pro33[k1[k]][k2[k]][j];
					if (result[k] >= low[k] && result[k] < high[k]) {
						cout << letter[j];
						pro[k] = high[k] - low[k];
						start[k] = low[k];
						k1[k] = k2[k];
						k2[k] = j;
						break;
					}
				}
			}
		}
		cout << "  ";

	}

}

int main() {
	shuru(z);//z要保留，引用传递，修改全局变量
	bianma();
	yima();
	return 0;
}
