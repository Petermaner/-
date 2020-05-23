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
int codeall2[100]={0};
float t,length,t2,length2;         // t是编码后码长，length是输入码长(abc ->3) 

//double Q=(pow(0.1,n)*pow(0.02,m)); //总的概率，就是区间长度！一切基于次式 
void bianma(int codeall[],float &t,float &length,int codeall2[],float &t2,float &length2){
	double low=0.0,high=1.0;
	char x;
	cin>>x;
	int n=0,m=0;
	
	int n2=0,m2=0;
	double low2=0.0,high2=1.0;	

//------------最外层do while循环----------------// 
	
	do{	                //只计算low即可，因为high可以用low＋区间长度得到  //1
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
	    

//-------------空格后的原码重新do while-----------// 
if(x==' ') {
	char x2;
	cin>>x2;
	
	do{	                //只计算low即可，因为high可以用low＋区间长度得到 
		if(x2>='a'&&x2<='f'){
			n2++;
			low2+=(int(x2)-int('a'))*pow(0.1,n2)*pow(0.02,m2); //倍数乘区间长度 
		}

		if(x2>='g'&&x2<='y'){
			m2+=1;
			low2+=(pow(0.1,n2)*pow(0.02,m2-1))*0.6+(int(x2)-int('f'))*(pow(0.1,n2)*pow(0.02,m2));
		}
		high2=low2+(pow(0.1,n2)*pow(0.02,m2));	//求high	 
	    
		x2=getchar();
		  } while(x2!='\n');
}
	/*	
		if(n+m==8){
			n=m=0;
			}
	*/ 
	
	
	
}while(x!='\n'); //1
//-------------最外层while结束-------------// 
	   
	cout<<"原码长为:"<<n+m+n2+m2<<"="<<n<<"+"<<m<<"+"<<n2<<"+"<<m2<<endl;  //n为分界线左个数，m为分界线右个数 
	
	length=n+m;
	length2=n2+m2;

//-------------两个区间的计算----------------//	
	cout<<"选取区间1为："<<setprecision(10)<<low<<" "<<setprecision(10)<<high<<endl;
	cout<<"选取区间2为："<<setprecision(10)<<low2<<" "<<setprecision(10)<<high2<<endl;
	double code=low*0.000001+high*0.999999;        //setprecision(10)为c++、cout(默认6位)控制精度，double
	double code2=low2*0.000001+high2*0.999999; 
	t=ceil(log(1/(pow(0.1,n)*pow(0.02,m)))/log(2));//ceil向上取整，t为最少编码位数，香农定理公式 
	t2=ceil(log(1/(pow(0.1,n2)*pow(0.02,m2)))/log(2));
	cout<<"编码结果为:";
	for(int i=1;i<=t;i++){
		codeall[i-1]=floor(code*2.0);              //floor向下取整 
		cout<<codeall[i-1];                        //十进制转二进制（乘2取整） 
		code=code*2-floor(code*2.0);
	}
	cout<<" "; 
	for(int i=1;i<=t2;i++){
		codeall2[i-1]=floor(code2*2.0);              //floor向下取整 
		cout<<codeall2[i-1];                        //十进制转二进制（乘2取整） 
		code2=code2*2-floor(code2*2.0);
	}
	cout<<endl<<"编码后码长为:"<<t+t2<<endl; 
}

void yima(){
	double result=0.0,result2=0.0;
	cout<<"译码初始化中......"<<endl;
	for(int i=0;i<t;i++){
		result+=codeall[i]*pow(2,(-1)*(i+1)); //二进制转十进制，加权求和 
	} 
	
	for(int i=0;i<t2;i++){
		result2+=codeall2[i]*pow(2,(-1)*(i+1)); //二进制转十进制，加权求和 
	}
	
	cout<<"转换回十进制结果："<<result<<" "<<result2<<endl;
	
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
		    i++;

		}	
	}
	
	
	cout<<" ";
	double low2=0.0,high2=1.0;
	int n2=0,m2=0,beishu2=1;
	i=0;
	low2=(pow(0.1,n2)*pow(0.02,m2))*0.6; 
	while(i<length2){                    //这里限制了译码位数，保证准确 
		
		//high=low+(pow(0.1,n)*pow(0.02,m));
		if(result2>=low2){
			m2++; 
			float beishu2=ceil((result2-low2)/(pow(0.1,n2)*pow(0.02,m2)));  //向上取整 
			//cout<<endl<<"倍数是："<<beishu<<" "<<char((beishu-1)+int('f'));
			cout<<char((beishu2-1)+int('f'));
			low2+=(pow(0.1,n2)*pow(0.02,m2))*(beishu2-1+0.6); //分界线右边，分界线需要向右调整，
			                                              //并且下一个分界线可以通过上一个 & beishu来调整 
		    i++;//编一个加一个，计数器 
			
		}	
	    if(result2<low2){
    		n2++;
			float beishu2=floor( (-1)*(result2-low2)/(pow(0.1,n2)*pow(0.02,m2))  );  //向下取整 
    		//cout<<endl<<"倍数是啥："<<beishu<<" "<<char(int('f')-beishu);
    		cout<<char(int('f')-beishu2);
    	 	low2-=(pow(0.1,n2)*pow(0.02,m2))*(beishu2+0.4);  //分界线左边 
		    i++;

		}	
	}
	
	
}


int main(){
	cout<<"---固定模式的算术编码---"<<endl; 
	cout<<"请输入要编码的字符串(a to z):"; 
	bianma(codeall,t,length,codeall2,t2,length2); //编码函数，都是引用传递，修改全局变量 
	yima();                 //译码函数 
	return 0;
}
