#include<stdio.h>
#include<stdlib.h>
#define SIZE 11

struct Node{
    int data;
    struct Node* next;

    Node(int n)
    {
        data=n;
        next=NULL;
    }
};

typedef struct Node node;

struct Set{
    node** table;
};

typedef struct Set set;

set create()
{
    set t;
    t.table=(node**)malloc(SIZE*sizeof(node*));
    for(int i=0; i<SIZE; i++)
        t.table[i]=NULL;
    return t;
}


int hashed(int n)
{
    return n%SIZE;
}

int is_element_of(set s1, int x)
{
    int h=hashed(x);
    node* current = s1.table[h];
    while (current != NULL)
    {
        if (current->data == x)
            return 1;
        current = current->next;
    }
    return 0;
}

int is_empty(set s1)
{
    for(int i=0; i<SIZE; i++)
        if(s1.table[i]!=NULL)
            return 0;
    return 1;
}

void add(set t, int x)
{
    if(!(is_element_of(t,x)))            //only insert the element if the element doesn't already exist in the set
    {
        int h=hashed(x);
        node* temp = new node(x);
        if(t.table[h]==NULL){                 //special condition if the set is empty
            t.table[h] = temp;
        }
        else{
            node* p = t.table[h];
            while(p->next != NULL){
                p = p->next;
            }
            p->next = temp;
        }
    }
    /*else
    {
        printf("element already exists.\n");
    }*/
}

int size(set t)
{
    int x=0;
    for(int i=0; i<SIZE; i++)
    {
        if(t.table[i]!=NULL)
        {
            node* temp=t.table[i];
            while(temp!=NULL)
            {
                x++;
                temp=temp->next;
            }
        }
    }
    return x;
}

void enumerate(set t)
{
    printf("\n\n");
    if(is_empty(t))//error if the list is empty
        printf("List is empty.\n");
    else
    {
        for(int i=0; i<SIZE; i++)
    {
        if(t.table[i]!=NULL)
        {
            node* temp=t.table[i];
            while(temp!=NULL)
            {
                printf("%d ", temp->data);
                temp=temp->next;
            }
        }
    }
    printf("\n\n");
    }
}

set build(int t[], int s)//s=size
{
    set s1=create();
    for(int i=0; i<s; i++)
    {
        add(s1, t[i]);
    }
    return s1;
}

void Remove(set t, int s)
{
    if(is_empty(t))   //error if the list is already empty
    {
        printf("Set is empty");
        return;
    }
    else if(is_element_of(t,s)) //only can remove the element if the element already exists
    {
        int h=hashed(s);
        if((t.table[h])->data==s)
            t.table[h]=t.table[h]->next;
        else
        {
            node* head=t.table[h];
            while(head->next->data!=s)
                head=head->next;
            head->next=head->next->next;
        }
    }
    else
        printf("Element does not exist");
}

set Union(set h1, set h2)
{
    set h3=create();
    for(int i=0; i<SIZE; i++)
    {
        if(h1.table[i]!=NULL)
        {
            node* temp=h1.table[i];
            while(temp!=NULL)
            {
                add(h3,temp->data);
                temp=temp->next;
            }
        }
        if(h2.table[i]!=NULL)
        {
            node* temp=h2.table[i];
            while(temp!=NULL)
            {
                add(h3,temp->data);
                temp=temp->next;
            }
        }
    }
    return h3;
}

set intersection(set h1, set h2)
{
    set h3=create();
    for(int i=0; i<SIZE; i++)
    {
        if(h1.table[i]!=NULL)
        {
            node* temp=h1.table[i];
            while(temp!=NULL)
            {
                if(is_element_of(h2, temp->data))
                    add(h3,temp->data);
                temp=temp->next;
            }
        }
    }
    return h3;
}

set difference(set h1, set h2)
{
    set in=intersection(h1,h2);//a new list that  3
    set r=create();
    for(int i=0; i<SIZE; i++)
    {
        if(h1.table[i]!=NULL)
        {
            node* t1=h1.table[i];
            while(t1!=NULL)
            {
                if(!(is_element_of(in, t1->data)))
                    add(r, t1->data);
                t1=t1->next;
            }
        }
    }
    return r;
}


//returns 1 if t1 is a subset of t2..
    int subset(set h1, set h2)
    {
        for(int i=0; i<SIZE; i++)
        {
            if(h1.table[i]!=NULL)
            {
                node* t1=h1.table[i];
                while(t1!=NULL)
                {
                    if(!(is_element_of(h2, t1->data)))
                        return 0;
                    t1=t1->next;
                }
            }
        }
        return 1;
    }



int main(){
    set s1=create();
    add(s1,5);
    add(s1,1);
    add(s1,18);
    add(s1,12);

    set s2=create();
    add(s2,5);
    add(s2,1);
    add(s2,8);
    add(s2,10);
    add(s2,10);
    add(s2,4);
    add(s2,18);

    printf("Set1: ");
    enumerate(s1);
    printf("Set2: ");
    enumerate(s2);


    set s3=Union(s1,s2);
    printf("Size of Set3: %d", size(s3));
    printf("\n\nSet3(Union of Set1 and Set2): ");
    enumerate(s3);
    printf("Intersection of Set1 and Set2");
    enumerate(intersection(s1,s2));
    printf("Difference (s2-s1): ");
    enumerate(difference(s2,s1));
    printf("Is s1 subset of s2? ");
    if(subset(s1,s2))
    {
    	printf("yes!");
	}
	else
	{
		printf("no!");
	}


}
