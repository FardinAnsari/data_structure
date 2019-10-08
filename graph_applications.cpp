#include <iostream>
using namespace std;

class node{
public:
	int data;
	node* next;

	node(int a)
	{
		data=a;
		next=NULL;
	}
};

class list{
public:
	node* head;

	list()
	{
		head=NULL;
	}

	void insert(int a)//inserts in beginning
	{
		node* t=new node(a);
		t->next=head;
		head=t;
	}

	void print()
	{
		node* t=head;
		while(t!=NULL)
		{
			cout<<t->data<<" ";
			t=t->next;
		}
		cout<<"\n";
	}
};

class stack{
public:
	node* top;

	stack()
	{
		top=NULL;
	}

	void push(int a)
	{
		node* t=new node(a);
		t->next=top;
		top=t;
	}

	int pop()
	{
		if(top!=NULL)
		{
			int a=top->data;
			top=top->next;
			return a;
		}
		else return -1;
	}

	int vtop()
	{
		if(top)
			return top->data;
		return -1;
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

class edge
{
public:
    int to_v;
    edge* next;

    edge(int a)
    {
        to_v=a;
        next=NULL;
    }
};

class vertex
{
public:
    int data;
    int noe;//number of edges
    edge* edges;

    vertex(int b)
    {
    	noe=0;
        data=b;
        edges=NULL;
    }
    vertex()
    {
        noe=0;
        edges=NULL;
    }
};

template<int num>
class graph{
public:
	vertex vertices[num];

	graph(){
		for(int i=1;i<=num;i++)
        {
            vertices[i].data=i;
        }
	}

	void add_edge(int a, int b)
    {
        if(vertices[a].edges==NULL)
        {
            vertices[a].edges=new edge(b);
            vertices[a].noe++;
        }
        else
        {
            edge* t=vertices[a].edges;
            while(t->next!=NULL)
            {
                if(t->to_v==b)
                    return;
                t=t->next;
            }
            t->next=new edge(b);
            vertices[a].noe++;
        }
    }

    void add_edge_undirected(int a,int b)
    {
        add_edge(a,b);
        add_edge(b,a);
    }

    bool edge_exist(int a, int b)
    {
    	if(vertices[a].edges==NULL)
        {
            return 0;
        }
        else
        {
        	edge* t=vertices[a].edges;
            while(t!=NULL)
            {
                if(t->to_v==b)
                    return 1;
                t=t->next;
            }
        }
        return 0;
    }

    void remove_edge(int a, int b)
    {
        if(vertices[a].edges->to_v==b)
        {
            vertices[a].edges=vertices[a].edges->next;
        }
        else
        {
            edge* t=vertices[a].edges;

            while(t->next->next!=NULL)
            {
                if(t->to_v==b)
                {
                    t->next=t->next->next;
                }
                t=t->next;
            }
        }
    }

    list topological_sort()
    {
    	list top_or;
    	bool visited[num];
    	for (int i = 0; i < num; ++i)
    	{
    		visited[i]=0;
    	}

    	for (int i = 0; i < num; ++i)
    	{
    		if(!visited[i])
    			rec_top_sort(i,visited,top_or);
    	}
    	return top_or;
    }

    void rec_top_sort(int i, bool* visited, list &top_or)
    {
    	visited[i]=1;
    	edge* temp=vertices[i].edges;
    	while(temp!=NULL)
    	{
    		int j=temp->to_v;
    		if(!visited[j])
    			rec_top_sort(j,visited,top_or);
    		temp=temp->next;
    	}
    	top_or.insert(i);
    }

    int max_edges_dag_ts()//O(v+e)+O(v) using topological sort
    {
    	int count=0;
    	int temp=num-1;
    	list ts=topological_sort();
    	node* t1=ts.head;
    	while(t1!=NULL)
    	{
    		count+=temp-vertices[num-temp-1].noe;
    		temp--;
    		t1=t1->next;
    	}
    	return count;
    }

    int max_edges_dag()//O(v)
    {
    	int maxx=(num*(num-1))/2;
    	int num_edges=0;
    	for(int i=0; i<num; i++)
            num_edges+=vertices[i].noe;
        return maxx-num_edges;

    }

    int path_exist_helper(int &count, int b, bool visited[], edge* e)
    {
    	if(e==NULL)
        {
    		return 0;
        }
    	edge* temp=e;
    	while(temp!=NULL)
    	{
    	    if(temp->to_v==b)
            {
                return 1;
            }
    		if(visited[temp->to_v]==0)
    		{
    			visited[temp->to_v]=1;
                if(path_exist_helper(++count, b, visited, vertices[temp->to_v].edges))
                {
                    //cout<<count<<"\n";
                    return 1;
                }
    		}
    		temp=temp->next;
    	}
    	return 0;
    }

    int path_exist(int a,int b)
    {
        int count=0;
    	if(edge_exist(a,b))
        {
           return 1;
        }
    	bool visited[num];
    	for (int i = 0; i < num; ++i)
    		visited[i]=0;
        if(path_exist_helper(count,b,visited,vertices[a].edges))
            return count;
        return 0;
    }

    int mother_vertex()
    {
    	int count=0;
    	for(int i=0; i<num; i++)
    	{
	    	count=0;
	    	for(int j=0; j<num; j++)
	    	{
	 	   		if(path_exist(i,j))
	 	   			count++;
	    	}
	    	if(count==num-1)
	    		return i;
    	}
    	return -1;
	}

	bool bipart()
	{
		bool color[num];
		bool visited[num];

		visited[0]=1;
		color[0]=1;

		if(bipart_helper(0,visited,color))
			return 1;
		return 0;
	}

	bool bipart_helper(int v, bool visited[], bool color[])
	{
		edge* temp=vertices[v].edges;
		while(temp!=NULL)
		{
			int u=temp->to_v;
			if(!visited[u])
			{
				visited[temp->to_v]=1;
				color[u]=!color[v];

				if(!bipart_helper(u,visited,color))
					return 0;
			}
			else if(color[u]==color[v])
				return 0;

			temp=temp->next;
		}
		return 1;
	}

	bool dg_cycle()
	{
	    for(int i=0; i<num; i++)
            if(path_exist(i,i))
                return 1;
        return 0;
	}

	udg_cycle_helper(int v,bool visited[],int p)//p is the prev node
	{
		visited[v]=1;
		edge* temp=vertices[v].edges;
		while(temp!=NULL)
		{
			if(!visited[temp->to_v])
			{
				if(udg_cycle_helper(temp->to_v, visited, v))
					return 1;
			}

			else if(temp->to_v!=p)
				return 1;
		}
		return 0;
	}

	udg_cycle()
	{
		bool visited[num];
		for (int i = 0; i < num; ++i)
		{
			visited[i]=0;
		}

		for(int i=0; i<num; i++)
		{
			if(!visited[i])
				if(udg_cycle_helper(i,visited,-1))
					return 1;
		}
		return 0;
	}

};

int main()
{
	graph<7> a;
	a.add_edge(5,2);
    a.add_edge(5,6);
    a.add_edge(0,2);
    a.add_edge(0,1);
    a.add_edge(1,3);
    //a.add_edge(1,4);
    //a.add_edge(1,2);
    a.add_edge(4,1);

    a.add_edge(6,4);
    a.add_edge(6,0);
	 list li=a.topological_sort();
	 li.print();
    graph<4> b;
    b.add_edge_undirected(0,1);
    b.add_edge_undirected(0,3);
    b.add_edge_undirected(1,2);
	 b.add_edge(2,3);
    cout<<b.bipart()<<endl;

  



}
