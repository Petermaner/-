 #include<iostream>
using namespace std; 
void shell_sort(int array[],int n)//希尔排序
{
	int d=n/2;int j;
	while(d>0)
	{
		for(int i=d;i<n;i++)
		{
			int temp=array[i];j=i-d;
			while(j>=0&&array[j]>temp)
			{
				array[j+d]=array[j];
				j=j-d;
			}
			array[j+d]=temp;
		}
		d=d/2;
	}
}

void test(int array[],int s,int t,int &cutpoint)
{
	int x,i,j;
	x=array[s];
	i=s;j=t;
	while(i!=j)
	{
		while(i<j&&array[j]%3==2) {j--;}
		if(i<j)  {array[i]=array[j];i++;}
		while(i<j&&array[i]%3!=2) {i++;}
		if(i<j) {array[j]=array[i];j--;}
	}
	array[i]=x;cutpoint=i;
	if(array[i]%3==2) j=i-1;
	else j=i;
	i=s;
	while(i!=j)
	{
		while(i<j&&array[j]%3!=0) {j--;}
		if(i<j)  {array[i]=array[j];i++;}
		while(i<j&&array[i]%3==0) {i++;}
		if(i<j) {array[j]=array[i];j--;}
	}
	array[i]=x;cutpoint=i;
}


void sift(int array[],int k,int m)//堆排序
{
	int x;int i,j;
	i=k;	j=2*i;
	x=array[k-1];bool finished=false;
	while(j<=m&&finished==false)
	{
		if(j<m&&array[j-1]<array[j]) j++;
		if(x>=array[j-1]) finished=true;
		else 
		{
			array[i-1]=array[j-1];
			i=j;j=2*i;
		}
	}
	array[i-1]=x;
}

void heap_sort(int array[],int n)//堆排序
{
	for(int i=n/2;i>=1;i--) 
		{sift(array,i,n);}
	for(int i0=n;i0>=2;i0--)
	{
		int temp=array[i0-1];
		array[i0-1]=array[0];
		array[0]=temp;
		sift(array,1,i0-1);
	}
}


int main(){
	int crray[30]={180,203,32,46,25,76,17,58,99,100,11,102,13,54,75,6,27,18,19,29,2,82};
	shell_sort(crray,25);
	for(int i=0;i<=24;i++){
		cout<<crray[i]<<" ";
	}
	cout<<endl;
	
	int array[30]={106,213,325,446,579,654,721,870,917,510,21,632,73,14,815,316,412,18,619,720,21,808,923,25,26};
	heap_sort(array,25);
	for(int i=0;i<=24;i++)
		cout<<array[i]<<" ";
		
	cout<<endl;	
	int brray[10]={3,6,9,12,7,10,13,8,11,14};int x;	
	test(brray,0,9,x);
	for(int i=0;i<=9;i++)
		cout<<brray[i]<<" ";

	
	cout<<endl;

	return 0;
}
