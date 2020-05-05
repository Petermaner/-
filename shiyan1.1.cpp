```cpp
#include<iostream>
using namespace std;
typedef int elementtype;
enum error_code1{success,overflow,underflow,rangeerror};
typedef struct LinkNode{
    elementtype data;
    struct LinkNode* next;
}node;
class list{
	public:
		list();
		//~list(); 
		int length()const;
		void print();
		error_code1 get_element(const int i,elementtype &x)const;
		//node * locate(const elementtype x)const;
		error_code1 insert(const int i,const elementtype x);//在i前面插入一个结点。
        void insert1(elementtype x);//已经递增有序了，插入一个x，仍递增有序
		error_code1 delete_element(const int i);
		node * get_head(){return head;}//返回的是head指针
        void creat1();             //头插法创建单链表
        void creat2();             //尾插法创建单链表
        void creat3();             //创建递增有序的单链表。
        void creat4();             //创建单循环列表 。 
        void separate(list& L1,list& L2);//将单链表Ｌ中的奇数项和偶数项结点分解开，并分别连成一个单链表
        bool ziji(list A,list B);//用递增有序的链表A、B表示两个集合，判断B是否是A的子集。
        void bingji(list A,list B,list& C);//用递增有序的链表A、B表示两个集合，设计算法求它们的并集。
        void jiaoji(list A,list B,list& C);//用递增有序的链表A、B表示两个集合，设计算法求它们的交集。
        //bool symmetry(list A);//判断一个双循环链表是否是对称的。（可选做）
    private:
		int count;
		node * head;
};
class list2:public list{   //list2 公有继承
	public:                  //新增公有函数成员
		list2();
		void creat4();         //尾插法创建带尾指针的循环单链表 
		bool evennumber();     //设计算法判断单循环链表是否每个结点的值都是偶数。
	private:                 //新增私有数据成员
		int count;
		node* head,*rear;
};
list2::list2(){
	head=new node;
	head->next=head;
	count=0;
}

void list2::creat4(){         //尾插法创建循环单链表
    rear=head;
    int x;
    cout<<"输入int型整数（输入12345可以结束）:";
    cin>>x;
    while(x!=12345){
        node*u=new node;
        u->data=x;
        u->next=head;
        rear->next=u;
        rear=u;
        count++;
        cin>>x;
    }
}

bool list2::evennumber(){            //设计算法判断单循环链表是否每个结点的值都是偶数。
	node*p=head->next;                
	while(p!=rear){
		if(p->data%2!=0)return false;
		p=p->next;
	}
	return true;	 
}

list::list(){
    head=new node;
    head->next=NULL;
    count=0;
}

int list::length()const{
    node*p =head->next;
    int n=0;
    while(p!=NULL){
        n++;
        p=p->next;
    }
    return n;
}

error_code1 list::get_element(const int i,elementtype &x)const{ //取元素操作，引用传递
    node*p=head->next;
    int n=1;
    
    while(p!=NULL&&i!=n){
        p=p->next;
        n++;
    }
    if(i<1||i>count)return rangeerror;
    x=p->data;
    return success;
}
//node * locate(const elementtype x)const{
//}

error_code1 list::insert(const int i,const elementtype x){   //指定序号i前面，插入操作
    node*p=head;
    int n=0;
    while(p->next!=NULL&&n!=i-1){   //p(会让n多1)或者p->next都一样，只要在涉及我想定位到操作结点的前一位，让p=head，n=0就行
        p=p->next;
        n++;
    }
    if(i<1||i>count+1)return rangeerror;
    node* u=new node;
    u->data=x;
    u->next=p->next;
    p->next=u;
    count++;
    return success;
}

void list::insert1(elementtype x){              //母题：已经递增有序的单链表，加入x使之仍然保持有序
    node*p=head;
    while(p->next!=NULL&&p->next->data<x){
        p=p->next;
    }
    if(p->next==NULL||p->next->data>=x){
        node*u=new node;
        u->data=x;
        u->next=p->next;
        p->next=u;
        count++;
    }
}

error_code1 list::delete_element(const int i){  //删除指定序号的结点
    node* p=head;
    node* u=new node;
    int n=0;
    while(p!=NULL&&n!=i-1){
        p=p->next;
        n++;
    }
    if(i<1||i>count)return rangeerror;
    u=p->next;
    p->next=u->next;
    delete u;
    count--;
    return success;
}

void list::creat1(){          //头插法创建单链表
    node*p=head;
    int x;
    cout<<"输入int型整数（输入12345可以结束）:";
    cin>>x;
    while(x!=12345){
        node*u=new node;
        u->data=x;
        u->next=p->next;
        p->next=u;
        count++;
        cin>>x;
    }
}

void list::creat2(){         //尾插法创建单链表
    node*rear =head;
     int x;
    cout<<"输入int型整数（输入12345可以结束）:";
    cin>>x;
    while(x!=12345){
        node*u=new node;
        u->data=x;
        u->next=NULL;
        rear->next=u;
        rear=u;
        count++;
        cin>>x;
    }
}

void list::creat3(){         //创建递增有序的单链表。
    int x;
    cin>>x;
    while(x!=12345){
        insert1(x);
        cin>>x;
    }
}

void list::separate(list& L1,list& L2){ //将单链表Ｌ中的奇数项和偶数项结点分解开，并分别连成一个单链表[本质就是尾插法构建单链表]
	node*u;
	node*p=head->next;
	node*a1=L1.get_head();
	node*a2=L2.get_head();
	for(int i=0;p!=NULL;i++,p=p->next){
		u=new node;
		u->data=p->data;
		if(i%2==0){
			a1->next=u;
			a1=a1->next;
		}
		else{
			a2->next=u;
			a2=a2->next;
		}
		a1->next=NULL;
		a2->next=NULL;
	}

}

bool list::ziji(list A,list B){  //用递增有序的链表A、B表示两个集合，判断B是否是A的子集。
	node*p1,*p2;
	p1=A.get_head()->next;
	p2=B.get_head()->next;
	while(p2!=NULL){
		while(p1!=NULL&&p1->data!=p2->data){
			p1=p1->next;
		}
		if(p1==NULL)return false;
		p2=p2->next;
	}
	return true;
} //写法1：这种写法没利用到两个链表递增 ，但是使用面广 
/*不论在在while(condition){statement;},do{statement;}while(condition),还是for(;;)循环中,都可以
使用return跳出循环. 当跳出循环的时候还可以使用break语句.但是这二者是有区别的.例如:当我们有一个双层循环操作,
我们在循环的时候使用return 语句的时候,可以直接跳出这双层循环.但是我们使用的是break语句的时候,只能跳出一层循环.
所以我们要清楚这两点,避免潜在的bug*/
/*

bool list::ziji(list A,list B){
	int a=0,b=0,x,y;
	while(a<A.length()&&b<B.length()){
		A.get_element(a+1,x);
		B.get_element(b+1,y);
		if(x==y){
			a++;b++;
		}
		else if(y>x){
			a++;
		}
		else
			return false;
	}
	if(b>=B.length())
		return true;
	return false;
}//写法2：这种写法利用到了递增性质。
*/

/*
bool list::ziji(list A,list B){
	node* a,*b;
	a=A.get_head()->next;
	b=B.get_head()->next;
	while(a!=NULL&&b!=NULL){
		if(a->data<b->data)a=a->next;
		else if(a->data>b->data)return false;
		else{
			a=a->next;
			b=b->next;	
		}
	}
	return true;
} //写法3：用到了性质，而且简化了判断 
*/
void list::jiaoji(list A,list B,list& C){  //用递增有序的链表A、B表示两个集合，设计算法求它们的交集。  
	node* a,*b,*c;
	a=A.get_head()->next;
	b=B.get_head()->next;
	c=C.get_head();
	while(a!=NULL&&b!=NULL){
		if(a->data<b->data)a=a->next;
		else if(a->data>b->data)b=b->next;
		else{
			node*u=new node;
			u->data=a->data;
			u->next==NULL;  //注意新建结点的时候，什么都还没有配置，要配置好 
			c->next=u;
			c=u;
			a=a->next;
			b=b->next;
		}
	}
}

void list::bingji(list A,list B,list& C){  //求并集
	node*a1,*a2,*a3;
	a1=A.get_head()->next;
	a2=B.get_head()->next;
	a3=C.get_head();
	while(a1!=NULL&&a2!=NULL){
		if(a1->data<a2->data){
			node*u =new node;
			u->data=a1->data;
			u->next=NULL;
			a3->next=u;
			a3=u;
			a1=a1->next;
		}
		else if(a1->data>a2->data){
			node*s =new node;
			s->data=a2->data;
			s->next=NULL;
			a3->next=s;
			a3=s;
			a2=a2->next;
		}
		else{
			node*t =new node;
			t->data=a2->data;
			t->next=NULL;
			a3->next=t;
			a3=t;
			a1=a1->next;
			a2=a2->next;
		}
	} 
}
void list::print(){       //通用打印算法，提高可视化
	node*p=head->next;
	while(p!=NULL){
		cout<<p->data<<" ";
		p=p->next;
	}
	cout<<endl; 
}

/*
list::~list(){            //析构函数
	node*p =head;
	while(p->next!=NULL){
		node*u =p->next;
		p->next=u->next;
	}
}
*/
/*
测试
1、对任意输入的一组数据，建立一个递增有序的单链表。
2、将单链表Ｌ中的奇数项和偶数项结点分解开，并分别连成一个单链表。
3、用递增有序的链表A、B表示两个集合，判断B是否是A的子集。
4、用递增有序的链表A、B表示两个集合，设计算法求它们的并集。
5、设计算法判断单循环链表是否每个结点的值都是偶数。
6、判断一个双循环链表是否是对称的。（可选做）
测试集：
1、2 3 2 3 5 5 1 --> 1 2 2 3 3 5 5
2、1 2 2 3 3 5 5 --> 奇:1 2 3 5  偶:2 3 5
3、A:1 2 3 5 B:2 3 5 --> 0(FALSE)
4、A:1 2 3 5 B:2 3 5 --> 1 2 3 5
5、2 4 6 8 10 -->1(TRUE)
*/

int main(){
	list L1,L2,L3,Lb;
	int a[5],b[3],c[2]; 
	cout<<"测试1：请输入一组数据（输入12345以结束）："<<endl;
	L1.creat3();
	cout<<"运行结果："; 
	L1.print();
	cout<<"测试2："<<endl<<"奇数结点为：";
	L1.separate(L2,L3);
	L2.print();
	cout<<"偶数结点为：";
	L3.print();
	cout<<"测试3：以奇数结点链表和偶数结点链表为例"<<endl<<"结果为："; 
	cout<<L1.ziji(L2,L3)<<endl;	 
	cout<<"测试4：以奇数结点链表和偶数结点链表为例"<<endl<<"结果为：";
	L1.bingji(L2,L3,Lb);
	Lb.print(); 
	cout<<"测试5：";
	list2 L4;
	L4.creat4();
	L4.print();
	cout<<"结果为："<<L4.evennumber()<<endl;
 }
```cpp
