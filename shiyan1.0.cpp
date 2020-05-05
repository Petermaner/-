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
		int length()const;
		error_code1 get_element(const int i,elementtype &x)const;
		//node * locate(const elementtype x)const;
		error_code1 insert(const int i,const elementtype x);//在i前面插入一个结点。
        void insert1(elementtype x);//已经递增有序了，插入一个x，仍递增有序
		error_code1 delete_element(const int i);
		node * get_head(){return head;}//返回的是head指针
        void creat1();//头插法创建单链表
        void creat2();//尾插法创建单链表
        void creat3();//创建递增有序的单链表。
        //void separate(list& L1,list& L2);//将单链表Ｌ中的奇数项和偶数项结点分解开，并分别连成一个单链表
        //bool ziji(list A,list B);//用递增有序的链表A、B表示两个集合，判断B是否是A的子集。
        //void bingji(list A,list B,list& C);//用递增有序的链表A、B表示两个集合，设计算法求它们的并集。
        //bool evennumber(list A);//设计算法判断单循环链表是否每个结点的值都是偶数。
        //bool symmetry(list A);//判断一个双循环链表是否是对称的。（可选做）
    private:
		int count;
		node * head;
};
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
error_code1 list::get_element(const int i,elementtype &x)const{
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
error_code1 list::insert(const int i,const elementtype x){
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

void list::insert1(elementtype x){
    node*p=head;
    while(p->next!=NULL&&p->next->data<x){
        p=p->next;
    }
    if(p->next==NULL||p->next->data>x){
        node*u=new node;
        u->data=x;
        u->next=p->next;
        p->next=u;
        count++;
    }
}
error_code1 list::delete_element(const int i){
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

void list::creat3(){             //创建递增有序的单链表。
    int x;
    cout<<"运行成功！"<<endl;
    cin>>x;
    while(x!=12345){
        insert1(x);
        cin>>x;
    }
 }

int main(){
     list L;
     L.creat3();
     int a[5];
     for(int i=1;i<=5;i++){
         L.get_element(i,a[i-1]);
         cout<<a[i-1]<<" ";
     }
     return 0;
 }
```
//运行结果说明已经可用。
