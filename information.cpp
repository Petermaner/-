/*
【题目0】：设信源可能输出的符号是26个字母，
且每个字母出现的概率为：a, b, c, d, e, f 均为0.1，其它是等概的，
试编写程序可以对任意字母序列（如presentation）进行固定模式的算术编码，并进行相应的译码。
*/

//灵感二，递归，返回的是low，因为区间长度可以求嘛

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
int codeall[100]={0};   //存储编码结果的数组 
float t,length;         // t是编码后码长，length是输入码长(abc ->3) 

//double Q=(pow(0.1,n)*pow(0.02,m)); //总的概率，就是区间长度！一切基于次式 
void bianma(int codeall[],float &t,float &length){
	double low=0.0,high=1.0;
	char x;
	cin>>x;
	int n=0,m=0;
	do{	                //只计算low即可，因为high可以用low＋区间长度得到 
		if(x>='a'&&x<='f'){
			n++;
			low+=(int(x)-int('a'))*pow(0.1,n)*pow(0.02,m); //倍数乘区间长度 
		}

		if(x>='g'&&x<='y'){
			m+=1;
			low+=(pow(0.1,n)*pow(0.02,m-1))*0.6+(int(x)-int('f'))*(pow(0.1,n)*pow(0.02,m));
		}
		high=low+(pow(0.1,n)*pow(0.02,m));	//求high	 
	    
		x=getchar();
	    //if(x==' ')
		//	goto ;
	/*	
		if(n+m==8){
			n=m=0;
			}
	*/ 
	}while(x!='\n');    
	cout<<"原码长为:"<<n+m<<"="<<n<<"+"<<m<<endl;  //n为分界线左个数，m为分界线右个数 
	length=n+m;
	cout<<"选取区间为："<<setprecision(10)<<low<<" "<<setprecision(10)<<high<<endl;
	double code=low*0.000001+high*0.999999;        //setprecision(10)为c++、cout(默认6位)控制精度，double 
	t=ceil(log(1/(pow(0.1,n)*pow(0.02,m)))/log(2));//ceil向上取整，t为最少编码位数，香农 
	cout<<"编码结果为:";
	for(int i=1;i<=t;i++){
		codeall[i-1]=floor(code*2.0);              //floor向下取整 
		cout<<codeall[i-1];                        //十进制转二进制（乘2取整） 
		code=code*2-floor(code*2.0);
	}
	cout<<endl<<"编码后码长为:"<<t<<endl; 
}
void yima(){
	double result=0.0;
	cout<<"译码初始化中......"<<endl;
	for(int i=0;i<t;i++){
		result+=codeall[i]*pow(2,(-1)*(i+1)); //二进制转十进制，加权求和 
	} 
	cout<<"转换回十进制结果："<<result<<endl;
	
	double low=0.0,high=1.0;
	int n=0,m=0,i=0,beishu=1;           //beishu是result所在位置与low分界线的 宽度  倍数（用来定位） 
	low=(pow(0.1,n)*pow(0.02,m))*0.6;   //low是每个迭代里的0.6的分界线
	cout<<"译码结果为："; 
	while(i<length){                    //这里限制了译码位数，保证准确 
		
		//high=low+(pow(0.1,n)*pow(0.02,m));
		if(result>=low){
			m++; 
			float beishu=ceil((result-low)/(pow(0.1,n)*pow(0.02,m)));  //向上取整 
			//cout<<endl<<"倍数是："<<beishu<<" "<<char((beishu-1)+int('f'));
			cout<<char((beishu-1)+int('f'));
			low+=(pow(0.1,n)*pow(0.02,m))*(beishu-1+0.6); //分界线右边，分界线需要向右调整，
			                                              //并且下一个分界线可以通过上一个 & beishu来调整 
		    i++;//编一个加一个，计数器 
			
		}	
	    if(result<low){
    		n++;
			float beishu=floor( (-1)*(result-low)/(pow(0.1,n)*pow(0.02,m))  );  //向下取整 
    		//cout<<endl<<"倍数是啥："<<beishu<<" "<<char(int('f')-beishu);
    		cout<<char(int('f')-beishu);
    	 	low-=(pow(0.1,n)*pow(0.02,m))*(beishu+0.4);  //分界线左边 
		    i++;  //i计数器，看译码出来多少位了。不要译多。

		}	
	}
}
int main(){
	cout<<"---固定模式的算术编码---"<<endl; 
	cout<<"请输入要编码的字符串(a to z):"; 
	bianma(codeall,t,length); //编码函数，都是引用传递，修改全局变量 
	yima();                   //译码函数 
	return 0;
}
