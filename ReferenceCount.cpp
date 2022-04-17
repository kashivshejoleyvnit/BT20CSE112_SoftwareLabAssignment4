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
	int ref;
	node(int v):value{v}{
		index = id;
		id = id+1;
		address = allocate(sizeof(int));
		ref = 0;
	}
	node(){}
	static int V(){
		return id;
	}
};
int node::id =0;
// A utility function to add a node connection in
// heap management schema
void addEdge(vector<node> adj[], node u, node& v)
{
	adj[u.index].push_back(v);
	v.ref = u.ref+v.ref+1;
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
// representation of heap_management schema
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
		n->ref = n->ref+1;
	}
	void set_next(node* n){
		next->ref--;
		next = n;
		next->ref++;
	}
	node* get_next(){
		return next;
	}
	~root(){
		next->ref--;
	}
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
void check_ref(node& x,vector<node> adj[],int V,vector<node>& garbage);
void deleteedge(const node& x1,vector<node> adj[],int V,vector<node>& garbage)
{
	for(int i=0;i<adj[x1.index].size();i++)
	{
		adj[x1.index][i].ref--;
		if(adj[x1.index][i].ref == 0)
		{
			check_ref(adj[x1.index][i],adj,V,garbage);
		}
	}
	adj[x1.index].clear();
	for(int i=0;i<V;i++)
	{
		for(int j=0;j<adj[i].size();j++)
		{
			if(adj[i][j].index == x1.index)
			{
				adj[i][j].ref--;
				adj[i].erase(adj[i].begin()+j);
				cout<<"For value "<<x1.index<<" "<<adj[i][j].index<<endl;
			}
		}
	}
}
void check_ref(node& x,vector<node> adj[],int V,vector<node>& garbage){
	if(x.ref==0)
	{
		garbage.push_back(x);
		deleteedge(x,adj,V,garbage);
		deallocate(x.address);
		x.address = -1;
	}
}
void print_garbage(vector<node>& garbage){
	cout<<"Garbage nodes are as follows :"<<endl;
	for(auto x : garbage)
	{
		cout<<"Index : "<<x.index<<" Value : "<<x.value<<endl;
	}
}
// Driver code
int main()
{
	cout<<"***************Program to implement Reference Count heap management implementaion************"<<endl;
	init();

	node x1(1),x2(2),x3(3),x5(5),x7(7),x8(8),x9(9),x10(10);
	const int V = node::V();
	root root1(&x5),root2(&x1);

	vector<node> adj[V];
	addEdge(adj, x5,x1);
	addEdge(adj, x7,x1);
	addEdge(adj,x7,x8);
	addEdge(adj,x1,x2);
	addEdge(adj, x1,x9);
	addEdge(adj, x8,x9);
	addEdge(adj, x1,x10);
	addEdge(adj, x3,x8);
	addEdge(adj,x3,x10);
	cout<<"root1->"<<root1.get_next()->value<<endl;
	cout<<"root2->"<<root2.get_next()->value<<endl;
	printGraph(adj, V);
	printAdjacencyMatrix(adj,V);
	cout<<"Free Space Available = "<<free_space<<endl;
	cout<<"Filled Space Available = "<<filled_space<<endl;
	cout<<"Freed Space = "<<freed_space<<endl;
	cout<<"Merged Space = "<<merged_space<<endl;
	vector<node> garbage;
	display(free_list);
	cout<<endl;
	display(filled_list);
	cout<<endl;

	check_ref(x1,adj,V,garbage);
	check_ref(x2,adj,V,garbage);
	check_ref(x3,adj,V,garbage);
	check_ref(x5,adj,V,garbage);
	check_ref(x7,adj,V,garbage);
	check_ref(x8,adj,V,garbage);
	check_ref(x9,adj,V,garbage);
	check_ref(x10,adj,V,garbage);

	cout<<"root1->"<<root1.get_next()->value<<endl;
	cout<<"root2->"<<root2.get_next()->value<<endl;
	printGraph(adj, V);
	printAdjacencyMatrix(adj,V);
	display(free_list);
	cout<<endl;
	display(filled_list);
	cout<<endl;

	print_garbage(garbage);

	cout<<"Free Space Available = "<<free_space<<endl;
	cout<<"Filled Space Available = "<<filled_space<<endl;
	cout<<"Freed Space = "<<freed_space<<endl;
	cout<<"Merged Space = "<<merged_space<<endl;
	return 0;
}