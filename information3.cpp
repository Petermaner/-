/*
【题目0】：设信源可能输出的符号是26个字母，
且每个字母出现的概率为：a, b, c, d, e, f 均为0.1，其它是等概的，
试编写程序可以对任意字母序列（如presentation）进行固定模式的算术编码，并进行相应的译码。
*/

//灵感二，递归，返回的是low，因为区间长度可以求嘛
//灵感三，分组思想，每个组有各自的参数，用数组保存 （下标来区别，分类）

/*
注意：四种算术编码统一采用 8个字符一组，用空格或者回车作为间隔。
关于这个要求，夏娜老师的意思是输入的字符串超过8位时，以8个为一组进行编码，相邻两组之间的记忆性取消。
*/

#include<iostream>
#include<stdio.h>
#include<iomanip>
#include<cmath>
//#include<string>      //整体算法思想，关注分界线（0.6） 
using namespace std;    //三个全局变量 
int codeall[10][100] = { {0} };   //存储编码结果的数组 
float t[10], length[10];         // t是编码后码长，length是输入码长(abc ->3) 
int i = 0; //组别分类器i，矩阵来理解 (注意1、一共有i+1组 2、i也是一个全局变量，引用传递来修改)

//double Q=(pow(0.1,n)*pow(0.02,m)); //总的概率，就是区间长度！一切基于次式 
void bianma(int codeall[][100], float t[], float length[], int& i) {
	double low[10] = { 0.0 }, high[10] = { 1.0 };
	char x;
	cin >> x;
	int n[10] = { 0 }, m[10] = { 0 };
	do {	                //只计算low即可，因为high可以用low＋区间长度得到 
		if (x >= 'a' && x <= 'f') {
			n[i] += 1;
			low[i] += (int(x) - int('a')) * pow(0.1, n[i]) * pow(0.02, m[i]); //倍数乘区间长度 
		}

		if (x >= 'g' && x <= 'y') {
			m[i] += 1;
			low[i] += (pow(0.1, n[i]) * pow(0.02, m[i] - 1)) * 0.6 + (int(x) - int('f')) * (pow(0.1, n[i]) * pow(0.02, m[i]));
		}
		high[i] = low[i] + (pow(0.1, n[i]) * pow(0.02, m[i]));	//求high	 


		if (x == ' ') {   //有一个空格，增加一个组别，分组用
			i++;
		}
		x = getchar();
	} while (x != '\n');
	int count = 0;
	for (int j = 0; j <= i; j++) {
		count += n[j] + m[j];
	}
	cout << "原码长为:" << count << endl;  //n为分界线左个数，m为分界线右个数 

	for (int j = 0; j <= i; j++) {
		length[j] = n[j] + m[j];
	}

	cout << "选取区间为：" << endl;
	for (int j = 0; j <= i; j++) {
		cout << "[" << setprecision(10) << low[j] << "," << setprecision(10) << high[j] << ")" << "  ";
	}
	cout << endl; //setprecision(10)为c++、cout(默认6位)控制精度，double 

	double code[10];
	for (int j = 0; j <= i; j++) {
                code[j]=0.000001*low[j]+0.999999*high[j];
		//code[j]->high[j];
		t[j] = ceil(log(1 / (pow(0.1, n[j]) * pow(0.02, m[j]))) / log(2));   	//ceil向上取整，t为最少编码位数，香农
	}

	cout << "编码结果为:" << endl;
	for (int j = 0; j <= i; j++) {

		for (int k = 1; k <= t[j]; k++) {
			codeall[j][k - 1] = floor(code[j] * 2.0);              //floor向下取整 
			cout << codeall[j][k - 1];                        //十进制转二进制（乘2取整） 
			code[j] = code[j] * 2 - floor(code[j] * 2.0);
		}
		cout << " ";

	}
	int T = 0;
	for (int j = 0; j <= i; j++) {
		T += t[j];
	}
	cout << endl << "编码后码长为:" << T << endl;
}




void yima() {
	double result[10] = { 0.0 };
	cout << "译码初始化中......" << endl;
	for (int j = 0; j <= i; j++) {
		for (int k = 0; k < t[j]; k++) {
			result[j] += codeall[j][k] * pow(2, (-1) * (k + 1)); //二进制转十进制，加权求和 
		}

	}
	cout << "转换回十进制结果：" << endl;
	for (int j = 0; j <= i; j++) {
		cout << result[j] << "  ";
	}


	double low[10] = { 0.0 }, high[10] = { 1.0 };
	int n[10] = { 0 }, m[10] = { 0 }, l[10] = { 0 };
	float beishu[10] = { 1 };           //beishu是result所在位置与low分界线的 宽度  倍数（用来定位） 
	for (int j = 0; j <= i; j++) {
		low[j] = (pow(0.1, n[j]) * pow(0.02, m[j])) * 0.6;   //low是每个迭代里的0.6的分界线
	}

	cout <<endl<< "译码结果为：";               //l为计数器（以前的i） 
	for (int j = 0; j <= i; j++) {


		while (l[j] < length[j]) {                    //这里限制了译码位数，保证准确 

		//high=low+(pow(0.1,n)*pow(0.02,m));
			if (result[j] >= low[j]) {
				m[j]++;
				beishu[j] = ceil((result[j] - low[j]) / (pow(0.1, n[j]) * pow(0.02, m[j])));  //向上取整 
				//cout<<endl<<"倍数是："<<beishu<<" "<<char((beishu-1)+int('f'));
				cout << char((beishu[j] - 1) + int('f'));
				low[j] += (pow(0.1, n[j]) * pow(0.02, m[j])) * (beishu[j] - 1 + 0.6); //分界线右边，分界线需要向右调整，
															  //并且下一个分界线可以通过上一个 & beishu来调整 
				l[j]++;//编一个加一个，计数器 

			}
			if (result[j] < low[j]) {
				n[j]++;
				beishu[j] = floor((-1) * (result[j] - low[j]) / (pow(0.1, n[j]) * pow(0.02, m[j])));  //向下取整 
				//cout<<endl<<"倍数是啥："<<beishu<<" "<<char(int('f')-beishu);
				cout << char(int('f') - beishu[j]);
				low[j] -= (pow(0.1, n[j]) * pow(0.02, m[j])) * (beishu[j] + 0.4);  //分界线左边 
				l[j]++;

			}
		}

		cout << " ";

	}

}
int main() {
	cout << "---固定模式的算术编码---" << endl;
	cout << "请输入要编码的字符串(a to z):";
	i = 0;
	bianma(codeall, t, length, i); //编码函数，都是引用传递，修改全局变量 
	yima();                   //译码函数 
	return 0;
}
