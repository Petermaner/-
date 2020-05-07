#include<iostream>
#include<cmath>
#include<cstdlib>
using namespace std;
//enum error_code1 {success,overflow,underflow,rangeerror};
typedef char elementtype;
typedef struct binode{
	elementtype data;
	struct binode* lchild,*rchild;
}bnode;
/*
class stack {
public:
	stack();
	bool empty();
	bool full();
	bool get_top(int &x);
	bool push(int x);
	bool pop();
private:
	int count,maxlen;
	int data[100];      //顺序栈的问题：只能确定的栈大小
};
stack::stack(){count=0;}  //初始化
bool stack::empty() {   //判断空
	if (count == 0) 
		return true;
	return false;
}
bool stack::full() {   //判断满
	if (count == maxlen)
		return true;
	return false;
}
bool stack::get_top(int &x) {  //取栈顶
	if (empty())
		return false;
	x = data[count - 1];
	return true;
}
bool stack::push(int x){  //入栈
	if (full())
		return false;
	data[count] = x;
	count++;
	return true;
}
bool stack::pop() {   //出栈
	if (empty()) 
		return false;
	count--;
	return true;
}
*/
class bitree{    //写完了之后发现，直接返回int的算法才是最直观，最简洁的！
	public:
		bitree();
		//void preorder(){preorder(root);}//这几个放公有，是为了直接遍历整个root为根的二叉树
		//void inorder(){inorder(root);}  //而私有的那几个，是想遍历那个结点都可以，有一种拆分的感觉
		//void postorder(){postorder(root);}
		//void createbitree(){createbitree(root);}
		int high(bnode*T);        //T为根的二叉树的高度,算法1
		void high2(bnode*T,int &h);//T为根的二叉树的高度,算法2
		//void num1(bnode*T);       //T为根的二叉树的总结点数，算法1
		//void num2(bnode*T,int &k);//算法2
		int num3(bnode*T);        //算法3
		int leaf(bnode*T);        //二叉树叶子结点数，算法1
		//void leaf(bnode*T,int &k);//二叉树叶子结点数，算法2
		void dutwo(bnode*T);//中序遍历度为2的结点
		//void print1(bonde*T);//中序输出二叉树各结点的值及其层次数。
		void copy(bnode*T,bnode*&T1);//复制一棵二叉树
		void exchange(bnode*T);//交换二叉树中每个结点的左右孩子指针的值。
		void print2(bnode*T);//设计一个非递归算法以输出二叉树t中先序序列中最后一个结点的值。
		void createbitree(bnode* &T);//输入广义表建立二叉树
		void inorder2(binode *T,int n);//增加输出：层次
		void visit(bnode*T);
		void preorder(bnode*T);
		void inorder(bnode*T);
		void postorder(bnode*T);
		void super(bnode*&T);
	private:
		bnode* root; 
		
		
};
bitree::bitree(){
	root=NULL;
}
void bitree::super(bnode*&T){
	T=root;
}
void bitree::visit(bnode*T){
	cout<<T->data;
}
void bitree::preorder(bnode*T){
	if(T!=NULL){
		visit(T);
		preorder(T->lchild);
		preorder(T->rchild);
	}
}
void bitree::inorder(bnode*T){
	if(T!=NULL){
		inorder(T->lchild);
		visit(T);
		inorder(T->rchild);
	}
}

void bitree::inorder2(bnode* T,int n) //细品，有点东西
{
	//改造中序遍历算法即可  
	if(T!=NULL)
	{
		inorder2(T->lchild,n + 1);
		cout<<"节点:"<<T->data<<"  该节点层次："<<n<<endl;;
		inorder2(T->rchild,n + 1);
	} 
 } 

void bitree::postorder(bnode*T){
	if(T!=NULL){
		postorder(T->lchild);
		postorder(T->rchild);
		visit(T);
	}
}
void bitree::createbitree(bnode *&T){  //这个感觉不是重点，后面再细品
  char ch;  
  cin>>ch;  
  if(ch=='#') T=NULL;
  else { T=new bnode;
            T->data=ch;
            createbitree(T->lchild);
            createbitree(T->rchild);
           }
}
   
int bitree::high(bnode *T){
	if(T==NULL)return 0;
	else if(high(T->lchild)>high(T->rchild))
		return high(T->lchild)+1;
	else return high(T->rchild)+1;
}



void bitree::high2(bnode*T,int &h){
	int h1,h2;
	if(T==NULL)h=0;
	else{
		high2(T->lchild,h1);
		high2(T->rchild,h2);
		h=max(h1,h2)+1;
	}
}
int bitree::num3(bnode*T){
	if(T==NULL)return 0;
	else
		return num3(T->lchild)+num3(T->rchild)+1;
}
int bitree::leaf(bnode*T){
	if(T==NULL)return 0;
	if(T->lchild==NULL&&T->rchild==NULL)return 1;
	else
		return leaf(T->lchild)+leaf(T->rchild);
}
void bitree::dutwo(bnode*T){
	if(T!=NULL){
		dutwo(T->lchild);
		if(T->lchild!=NULL&&T->rchild!=NULL){
			cout<<T->data;
		}
		dutwo(T->rchild);
	}
}
/*   算法已用inorder2实现（改造inorder1）
void bitree::print1(bonde*T){
	int n;

}
*/
void bitree::print2(bnode*T){  //细品，很有意思的
	bnode* p=T;                //设计一个非递归算法以输出二叉树t中先序序列中最后一个结点的值。
	while(p->lchild!=NULL||p->rchild!=NULL){
		if(p->rchild==NULL)p=p->lchild;
		else
			p=p->rchild;
	}
	cout<<p->data;
}
void bitree::copy(bnode*T,bnode*&T1){  //复制一棵二叉树
	if(T==NULL){
		T1=NULL;
		return;
	}
	else{
		T1=new bnode;
		T1->data=T->data;
		copy(T->lchild,T1->lchild);
		copy(T->rchild,T1->rchild);

	}
}

void bitree::exchange(bnode*T){       //交换二叉树中每个结点的左右孩子指针的值。
	                                  //此算法根据二叉树先序遍历算法改造而来
    if(T!=NULL){
        if(T->lchild!=NULL&&T->rchild!=NULL){
            swap(T->lchild,T->rchild);
        }
        else if(T->lchild!=NULL&&T->rchild==NULL){
        	T->rchild=T->lchild;
			T->lchild=NULL;
        }
        else if(T->lchild==NULL&&T->rchild!=NULL){
            T->lchild=T->rchild;
            T->rchild=NULL;
        }
        else{
            ;
        }
        exchange(T->lchild);
        exchange(T->rchild);
    }
}

int main(){
	bitree A,A1;
	int n=1,h;
	bnode*T=new bnode;
	bnode*T1=new bnode;
	A1.super(T1);
	//输入为：A B D # G # # # C E # #  F # # （先序） 
	A.createbitree(T);cout<<endl;
	cout<<"先序遍历：";A.preorder(T);cout<<endl;
	cout<<"中序遍历：";A.inorder(T);cout<<endl;
	cout<<"后序遍历：";A.postorder(T);cout<<endl;
	cout<<"二叉树的高度：";cout<<A.high(T)<<endl;
	cout<<"二叉树叶子结点数：";cout<<A.leaf(T)<<endl;
	cout<<"中序输出二叉各结点的值+层次："<<endl;A.inorder2(T,n);cout<<endl;
	cout<<"复制二叉树：";A.copy(T,T1);A1.preorder(T1);cout<<endl;
	cout<<"交换左右孩子的值：";A.exchange(T);A.preorder(T);cout<<endl;
	return 0;
}
