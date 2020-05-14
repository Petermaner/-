#include<iostream>
using namespace std;

typedef struct node{    //边结点结构体 
	int adjvex,data;
	struct node* nextadj;
}enode;
typedef struct tnode{   //头结点结构体 
	int verdata;
	enode* firstadj;	
}adjlink; 


const int MaxVertex=10;
int E=0; 
bool visited[MaxVertex];
class graph1{
	public:
		graph1();
		void createadj();// 建立邻接矩阵（无向图）
		void createadj2();//有向图 
		int firstadj(int v);//求顶点v的第一个邻接点
		int nextadj(int v,int w);//求顶点v的m邻接点后的邻接点
		
		void travel_dfs(); 
		int bianshu(int v);//求图中边或弧的数目
		bool mainpoint(int v);//判断无向连通图中的一个顶点是否为关节点
		bool istree();//判断一个有向图是不是一棵有向树	
		void visite(int v){cout<<vertex[v]<<"  ";}
		void numofGC(int &E_1,int &L_1){travel_dfs();E_1=E;L_1=L;E=0;L=0;}//E表示边数，L表示连通分量个数
      	int vnum(){return CurrentVertex;}
	 
	private:
		int vertex[MaxVertex];     //顶点表 
     	int edge[MaxVertex][MaxVertex];  //邻接矩阵
     	int CurrentVertex;       //当前顶点数
	 	void dfs(int v);//深度优先搜索遍历
	 	void bfs(int v);//广度优先搜索遍历

};

graph1::graph1(){    //构造函数 
	int i,j;
	for(i=0;i<MaxVertex;i++)
		vertex[i]=0;
	for(i=0;i<MaxVertex;i++)
		for(j=0;j<MaxVertex;j++)
		        edge[i][j]=0;
}


void graph1::createadj( ){   //建立邻接矩阵（无向图）
int i,j,k;
	cout<<"输入顶点数"<<endl;cin>>CurrentVertex;
	cout<<"输入顶点的值"<<endl;
	for(k=0;k<CurrentVertex;k++)
		cin>>vertex[k];
	cout<<"请输入：i j(i为-1时结束)"<<endl;
                cin>>i>>j;
	while(i!=-1){
	edge[i][j]=edge[j][i]=1;cin>>i>>j;
	}
}

void graph1::createadj2(){   //建立邻接矩阵（有向图）
	int i,j,k;
	cout<<"请输入顶点数"<<endl;cin>>CurrentVertex;
	cout<<"请输入各顶点的值"<<endl;
	for(k=0;k<CurrentVertex;k++)
		cin>>vertex[k];
	cout<<"请输入边：i j，i为-1时结束"<<endl;
                cin>>i>>j;
	while(i!=-1){	edge[i][j]=1;cin>>i>>j;}
}                 


int graph1::firstadj(int v){  //求第一个邻接点
      if(v!=-1){for(int col=0;col<CurrentVertex;col++)
              if(edge[v][col]>0) return col;}
      return -1;
}


int graph1::nextadj(elementtype v, elementtype m)  //求m后的邻接点
{	if(v!=-1&&m!=-1)
	{	for(int col=m+1;col<CurrentVertex;col++)
			if(edge[v][col]>0) return col;}
	return  -1;
}

void graph1::dfs(int v){	 //深度优先搜索遍历
	int w;
	visite(v);visited[v]=true;     //记录一个顶点是否被访问了
	w=firstadj(v);
	while(w!=-1){
	E++;
	if(visited[w]==false) dfs(w);
		w=nextadj(v,w);}
}

void graph1::travel_dfs()  //遍历全图的方法
{
     int i;
     for(i=0;i<CurrentVertex;i++)  
	 visited[i]=false;                            
     for (i=0; i<CurrentVertex; i++)  {if(visited[i]==false)  {	L++;dfs(i);}}
}
int graph1::bianshu(int v){
	int w;
    visited[v]=true;          //设置访问标志（访问结点的其它操作被省去）
    w=firstadj(v);
    while (w!=-1){
	E++;                    //此处意味着找到一条边，故累计到变量E中
    if(visited[w]==false)
    	dfs(w);
    w=nextadj(v,w);
   }
	return E/2;
}

bool graph1::mainpoint(int v)  //判断是否是关键结点
{
	int a,b,c,d;numofGC(a,b);
	for(int i=0;i<=CurrentVertex-1;i++)
	{
		if(edge[v][i]>0) edge[v][i]=-2;
		if(edge[i][v]>0) edge[i][v]=-2;
	}
	numofGC(c,d);
	for(int j=0;j<=CurrentVertex-1;j++)
	{
		if(edge[v][j]==-2) edge[v][j]=1;
		if(edge[j][v]==-2) edge[j][v]=1;
	}
	if(b+1==d) return false;
	else return true;
}




bool graph1::istree()  //判断此有向图是否是有向树
{int cou=0;int sum=0;
	for(int k=0;k<CurrentVertex;k++)
	{
		for(int k1=0;k1<CurrentVertex;k1++){cou+=edge[k1][k];}
		if(cou>1) return false;
		sum+=cou;
		cou=0;
	}
	if(sum==CurrentVertex-1) return true;
	else 
		return false;
}



class graph2{
	public:
		graph2();
		void createadj();//邻接表存储结构建立图 ,建立邻接表（无向图） 
		int firstadj(int v);
		int nextadj(int v,int w);
		void visite(int v);//打印 
		void dfs(int v);//深度优先搜索遍历
		void dfs2(int v);
		void travel_dfs();
		void bfs(int v);//广度优先搜索遍历
		void travel_bfs();
		int vnum(){return currentvertex;}//返回当前顶点数 
		
		void juzhen(); //邻接矩阵存储结构建立图 
		int bianshu(int v);//求图中边或弧的数目
		bool mainjoint(int v);//判断无向连通图中的一个顶点是否为关节点
		bool istree(int v);//判断一个有向图是不是一棵有向树
		int minbian(int v);//求顶点v到图中其余每个顶点的最短路径
		int numofGC();//无向图中连通分量的个数 
		
		//friend class queue;
	private:
		adjlink vertex[maxvertex];
		int currentvertex;
		bool visited[maxvertex]; 
}; 
graph2::graph2(){
	for(int i=0;i<maxvertex;i++){
		vertex[i].verdata=0;
		vertex[i].firstadj=NULL;
	}
} 
int graph2::firstadj(int v){
	enode* p;
	if(v!=-1){
		p=vertex[v].firstadj;
		if(p!=NULL)
			return p->adjvex;
	}
	return -1;
}
int graph2::nextadj(int v, int m)
{
	if(v!=-1)
	{ enode *p=vertex[v].firstadj;
	  while(p!=NULL&&p->adjvex!=m)
		  p=p->nextadj;
	  if(p!=NULL&&p->nextadj!=NULL)
		  return p->nextadj->adjvex;
	}
	return -1;
}
void graph2::createadj()
{	int i,j,k; enode *s;
	cout<<"请输入顶点个数：";
	cin>>currentvertex;
	cout<<"请输入顶点序列：";                   //输入顶点个数
	for(k=0;k<currentvertex;k++)
		cin>>vertex[k].verdata;        //输入顶点序列
    cout<<"请输入i和j的值：(输入i=-1停止)";
	cin>>i>>j;
	while(i!=-1)
	{	s= new enode; s->adjvex=j;
		s->nextadj=vertex[i].firstadj;
		vertex[i].firstadj=s;          //在顶点为i的邻接表中插入顶点为j的邻接点
		s= new enode; s->adjvex=i;
		s->nextadj=vertex[j].firstadj;
		vertex[j].firstadj=s;        //在顶点为j的邻接表中插入顶点为i的邻接点
        cin>>i>>j;
	}
}
void graph2::visite(int v){
	
	cout<<vertex[v].verdata<<" ";
} 
void  graph2::dfs(int v){
	int w;
	//visite(v);
	visited[v]=true;
	w=firstadj(v);
	while(w!=-1){
		if(!visited[w])
			dfs(w);
		w=nextadj(v,w);	
	}
	
}
void  graph2::dfs2(int v){
	int w;
	visite(v);
	visited[v]=true;
	w=firstadj(v);
	while(w!=-1){
		if(!visited[w])
			dfs(w);
		w=nextadj(v,w);	
	}
	
}
void graph2::travel_dfs(){
	for(int i=0;i<currentvertex;i++)
		visited[i]=false;
	for(int i=0;i<currentvertex;i++){
		if(!visited[i])
			dfs2(i); 
	}
}
void graph2::bfs(int v){
	int w;queue Q;int x;
	visite(v);
	visited[v]=true;
	Q.append(v);
	while(!Q.empty()){
		Q.get_top(x);
		v=x;
		Q.serve();
		w=firstadj(v);
		while(w!=-1){
			if(!visited[w]){
				visite(w);
				visited[w]=true;
				Q.append(w);
			}
			w=nextadj(v,w);
		}
	}
}
void graph2::travel_bfs()
{
	int i;
	for(i=0;i<currentvertex;i++)
		visited[i]=false;
	for(i=0;i<currentvertex;i++)
		if(!visited[i])
		      bfs(i);
}

int graph2::bianshu(int v){
	int E=0;
	int w;
    visited[v]=true;          //设置访问标志（访问结点的其它操作被省去）
    w=firstadj(v);
    while (w!=-1){
	E++;                    //此处意味着找到一条边，故累计到变量E中
    if(visited[w]==false)
    	dfs(w);
    w=nextadj(v,w);
   }
	return E/2;
}

int graph2::numofGC(){
	int i;  int k=0;                   // k用于连通分量的计数
    for (i=0; i<currentvertex; i++)
       visited[i]=false;             
    for (i=0; i<currentvertex; i++)
       if (visited[i]==false){ 
	   k++;  dfs(i);
	}         //用k来累计连通分量个数
   return k ;

}
/*
bool graph2::istree(int v,int k,int E/2){
	if(k==1&&E/2==(G.vnum()-1)
		return true;
	else 
		return false; 
}
*/
//bool mainjoint(int v){
	
//}

/*
1、分别以邻接矩阵和邻接表的存储结构建立图。
2、对图进行深度优先遍历。
3、求图中边（或弧）的数目。
4、判断无向连通图中的一个顶点是否为关节点。
5、判断一个有向图是不是一棵有向树。（任意一个顶点可能是根）

*/
 
int main(){    //主函数前半部分，测试邻接矩阵存储方式的各个任务class graph1
               //后半部分，测试邻接表存储的class graph2
	graph1 G1,G2;//G1为无向图，G2为有向图  
	int v1=1,v2=2;
	G1.createadj();
	cout<<endl<<"边数为："<<G1.bianshu(v1)<<endl<<"深度优先搜索遍历：";
	G1.travel_dfs();
	cout<<endl;
	cout<<"v2是关键结点吗？(1为是，0为否)"<<G1.mainpoint(v2) ;
	
	
	cout<<endl;
	cout<<endl;
	G2.createadj2(); 
	cout<<endl<<"深度优先搜索遍历：";
	G2.travel_dfs();
	cout<<endl;
	cout<<"是有向树吗？(1为是，0为否)"<<G2.istree();

	
}
