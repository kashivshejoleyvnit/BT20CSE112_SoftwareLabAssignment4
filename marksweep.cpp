// A simple representation of graph using STL
#include "heap_manager.h"
using namespace std;

extern vector<vector<int>> free_list;
extern vector<vector<int>> filled_list;
int free_space;
int filled_space;
int merged_space;
int freed_space;
class node
{
	static int id;
	public:
	int address;
	int value;
	int index;
	int markbit;
	node(int v):value{v}{
		index = id;
		id = id+1;
		address = allocate(sizeof(int));
		markbit = 0;
	}
	node(){}
	static int V(){
		return id;
	}
};
int node::id =0;
void print_garbage(vector<node>& garbage){
	cout<<"Garbage nodes are as follows :"<<endl;
	for(auto x : garbage)
	{
		cout<<"Index : "<<x.index<<" Value : "<<x.value<<endl;
	}
}
void mark(vector<node> adj[], node u, node& v){
	adj[u.index].push_back(v);
	if(u.markbit==1)
    {
        v.markbit = 1;
    }
}
int fu(int i)
{
	if(i<3)
	{
		return i+1;
	}
	else if(i==3)
	{
		return i+2;
	}
	else
	{
		return i+3;
	}
}
// A utility function to print the adjacency list
//for heap-managementschema
void printGraph(vector<node> adj[], int V)
{
	cout<<"Adjacency List"<<endl;
	for (int i=0; i <V;++i) {
		cout<<fu(i)<<"->";
		for (auto x : adj[i])
			cout << " " << x.value;
		cout<<endl;
	}
}
class root
{
	node* next;
	public:
	root(node* n){
		next = n;
	}
	void set_next(node* n){
		next = n;
		next->markbit = 1;
	}
	node* get_next(){
		return next;
	}
	~root(){}
};
void printAdjacencyMatrix(vector<node> adj[],int V)
{
	int a[V][V];
	for(int i=0;i<V;i++)
		for(int j=0;j<V;j++)
			a[i][j]=0;
	cout<<"Adjacency Matrix is as follows"<<endl;
	cout<<"     ";
	for(int i=0;i<V;i++)
		cout<<fu(i)<<" ";
	cout<<endl;
	for(int i=0;i<V;i++)
	{
		for(auto x : adj[i])
		{
			a[i][x.index] = 1;
		}
	}
	for(int i=0;i<V;i++)
	{
		cout<<fu(i)<<" -> ";
		for(int j=0;j<V;j++)
			cout<<a[i][j]<<" ";
		cout<<endl;
	}

}
void sweep(node& x,vector<node> adj[],int V,vector<node>& garbage){
	if(x.markbit==0)
	{
		garbage.push_back(x);
		adj[x.index].clear();
		deallocate(x.address);
		x.address = -1;
	}
}
// Driver code
int main()
{
	cout<<"**************Program to implement Mark-Sweep Garbage Collection Implementation********************"<<endl;
	init();

	node x1(1),x2(2),x3(3),x5(5),x7(7),x8(8),x9(9),x10(10);
	const int V = node::V();
	root root1(&x5),root2(&x1);

	x5.markbit = 1;
	x1.markbit = 1;
	vector<node> adj[V];
	mark(adj, x5,x1);
	mark(adj, x7,x1);
	mark(adj,x7,x8);
	mark(adj,x1,x2);
	mark(adj, x1,x9);
	mark(adj, x8,x9);
	mark(adj, x1,x10);
	mark(adj, x3,x8);
	mark(adj,x3,x10);
	cout<<"root1->"<<root1.get_next()->value<<endl;
	cout<<"root2->"<<root2.get_next()->value<<endl;
	printGraph(adj, V);
	printAdjacencyMatrix(adj,V);

	cout<<"free list : ";
	display(free_list);
	cout<<endl;
	cout<<"filled list : ";
	display(filled_list);
	cout<<endl;
	cout<<"Free Space Available = "<<free_space<<endl;
	cout<<"Filled Space Available = "<<filled_space<<endl;
	cout<<"Freed Space = "<<freed_space<<endl;
	cout<<"Merged Space = "<<merged_space<<endl;
	vector<node> garbage;
	sweep(x1,adj,V,garbage);
	sweep(x2,adj,V,garbage);
	sweep(x3,adj,V,garbage);
	sweep(x5,adj,V,garbage);
	sweep(x7,adj,V,garbage);
	sweep(x8,adj,V,garbage);
	sweep(x9,adj,V,garbage);
	sweep(x10,adj,V,garbage);

	cout<<"root1->"<<root1.get_next()->value<<endl;
	cout<<"root2->"<<root2.get_next()->value<<endl;
	printGraph(adj, V);
	printAdjacencyMatrix(adj,V);
	cout<<"free list : ";
	display(free_list);
	cout<<endl;
	cout<<"filled list : ";
	display(filled_list);
	cout<<endl;

	print_garbage(garbage);
	cout<<"Free Space Available = "<<free_space<<endl;
	cout<<"Filled Space Available = "<<filled_space<<endl;
	cout<<"Freed Space = "<<freed_space<<endl;
	cout<<"Merged Space = "<<merged_space<<endl;
	return 0;
}