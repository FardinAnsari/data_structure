#include<iostream>
using namespace std;
struct node{
	int data;
	struct node* left;
	struct node* right;
};
struct node* create(int key)
{
	struct node *temp= new(struct node);
	if(temp==NULL)
	{
		cout<<"memory not allocated"<<endl;
	}
	else
	{
	temp->data=key;
	temp->left=NULL;
	temp->right=NULL;
	}
	return temp;
}

struct node* insert(struct node* node, int key) 
{ 
    if (node == NULL) return create(key); 
  
    if (key < node->data) 
        node->left  = insert(node->left, key); 
    else if (key > node->data) 
        node->right = insert(node->right, key);    
  
    return node; 
}
void display(struct node* root)
{
	struct node *current=root;
	if(current==NULL)
	{
		//cout<<"the tree is empty"<<endl;
		return;
	}
	else
	{
		display(current->left);
		cout<<current->data<<" ";
		display(current->right);
	}
}

int count_nodes(struct node* root,int count)
{
	if(root==NULL)
	{
		return count;
	}
	else
	{
		count++;
		count=count_nodes(root->left,count);
		count=count_nodes(root->right,count);
	}
	return count;
}

int maxDepth(struct node* node)  
{ 
   if (node==NULL)  
       return 0; 
   else 
   { 
       int lDepth = maxDepth(node->left); 
       int rDepth = maxDepth(node->right); 
  
       if (lDepth > rDepth)  
           return(lDepth+1); 
       else return(rDepth+1); 
   } 
}  
main()
{
	struct node *root=NULL;
	int choice=0;
	while(choice!=10)
	{
		cout<<endl<<"---------------------------------"<<endl;
      cout<<endl<<"Operations on trees"<<endl;
      cout<<endl<<"---------------------------------"<<endl;
      cout<<"1.insert"<<endl;
      cout<<"2.display"<<endl;
      cout<<"3.count nodes"<<endl;
      cout<<"4.height"<<endl;
      cout<<"10.exit"<<endl;
      cin>>choice;
      switch(choice)
      	{
      		case 1:
      			{
      				int key;
      				cout<<"enter the value to be inserted"<<endl;
      				cin>>key;
      				root=insert(root,key);
      				break;
					}
				case 2:
					{
						display(root);
						break;
					}
				case 3:
					cout<<"the no. of nodes are "<<count_nodes(root,0)<<endl;
					break;
				case 4:
					cout<<"height of the tree is "<<maxDepth(root);
				case 10:
					{
						break;		
					}
				default:
					cout<<"wrong choice try again"<<endl;
					break;
			}
	}
}

