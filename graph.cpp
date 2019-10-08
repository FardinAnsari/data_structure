#include <iostream>
using namespace std;
class node{
public:
	int data;
	node* next;

	node(int n)
	{
		data=n;
		next=NULL;
	}
};

class queue{
public:
	node* front;
	node* rear;

	queue()
	{
		front=NULL;
		rear=NULL;
	}

	bool empty()
	{
		if(front==NULL)
			return 1;
		return 0;

	}
	void enque(int n)
	{
		node* nnode=new node(n);
		if (!rear)
		{
			front=nnode;
			rear=nnode;
			return;
		}
		rear->next=nnode;
		rear=nnode;
	}

	void deque()
	{
		if(!front)
			return;
		front=front->next;
		if(!front)
			rear=NULL;
	}

	int val()
	{
		return front->data;
	}


};


template<int num>
class digraph{
private:
	int vertex[num];
	bool adj[num][num];
public:

	void fill_graph()
	{
		for (int i = 0; i < num; ++i)
		{
			cin>>vertex[i];
		}
	}

	void make_graph()
	{
		fill_graph();
		for (int i = 0; i < num; ++i)
		{
			for (int j = i+1; j < num; ++j)
			{
				cout<<"Is "<<vertex[i]<<" and "<<vertex[j]<<" connected? 1 for yes, 0 for no.\n";
				cin>>adj[i][j];
				adj[j][i]=adj[i][j];
			}
		}
	}

	void predef()
	{
	    for(int i=1; i<=10; i++)
        {
            vertex[i-1]=i*10;
        }
	}

	void traverse(int v, bool vis[])
	{
		vis[v]=1;
		cout<<vertex[v]<<" ";
		for(int i=0; i<num; i++)
		{
			if(adj[v][i]==1)
				if(!vis[i])
					traverse(i,vis);
		}
	}

	void dfs()
	{
		bool visited[num];
		for (int i = 0; i < num; ++i)
			visited[i]=0;

		for(int i=0; i<num; i++)
			if(!visited[i])
				traverse(i,visited);
	}

	void bfs()
	{
		queue q;
		bool visited[num];
		for (int i = 0; i < num; ++i)
			visited[i]=0;

		for(int i=0; i<num; i++)
		{
			if(!visited[i])
			{
				q.enque(i);
				while(!q.empty())
				{
					int w=q.val();
					if(!visited[w])
					{
						visited[w]=1;
						cout<<vertex[w]<<" ";
						for(int k=0; k<num; k++)
						{
							if(adj[w][k]==1)
								q.enque(k);
						}
					}
					q.deque();
				}
			}
		}

	}

};

int main()
{
	digraph<5> g;
	g.make_graph();
	//g.dfs();
	g.bfs();
}

