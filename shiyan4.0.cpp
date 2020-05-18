#include<iostream>
using namespace std; 

enum error_code{underflow,overflow,rangeerror,success};
typedef int elementtype;
const int maxlen=50;
int i,j;

class list{
public:
    list();
    int  length()const;
    error_code create();
    void search(elementtype x);
    error_code  get_element(const int i, elementtype &x)const;
    int  locate(const elementtype x) const;
    error_code  insert(const int i, const elementtype x);
    error_code  delete_element(const int i);
	
 private:
    elementtype  data[maxlen];
    int  count;
};


list::list(){
	count = 0;
	}
   
int  list::length() const{ 
	return count;
	}

 error_code   list::insert(const int i,const elementtype x){
    if (count==maxlen) 
          return overflow;
    if (i<1||i>length()+1) 
          return rangeerror;
   for(j=count;j>=i;j--)  
        data[j] = data[j -1 ];
   data[i - 1] = x;                     
    count ++;
    return success;
  } 


 error_code list::create(){
	 elementtype x;
	 cin>>x;
	 while (x!=12345)
	 {
		 if(count<maxlen)
		 {
			 insert(count+1,x);
			 cin>>x;
		 }
		 else return overflow;
	 }
	 return success;
 }

void list::search(elementtype x){
	 int mid,low=0,high=count-1;
	 while(low<=high)
	 {
		 mid=(low+high)/2;
		 cout<<mid<<" ";
		 if(x<data[mid]) high=mid-1;
		 else if(x>data[mid]) low=mid+1;
		 else {
		 cout<<mid<<" "<<"找到："<<x<<endl;
		 return;
		 }
	 }
	 cout<<x<<":"<<"没找到"<<endl;
	 return;
}
	
int main(){
	list a;
	//第一组数据：1 2 3 4 6 7 8 9 10 11 12 13 17 18 19 20 24 25 26 30 35 40 45 50 100 （12345） 
	//第二组数据：2 4 6 8 9  12 58 68 71 85 65 325  4522 4544 45646 45462 465465 （12345） 
	a.create();
	int x;cin>>x;
	while(x!=12345)
	{
		a.search(x);
		cin>>x;
	//第一组要找的数：2 8 20 30 50 5 15 33 110 12345
	//第二组要找的数：1 3 4 5 6 8 12 22  325  4544 12345  
	}
	return 0;
}

 
