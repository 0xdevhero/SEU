#include<iostream>

using namespace std;

struct node
{
    int data;
    node *next;
    node *prev;
} *head,*tail;

int sizeOfList=1;

void insert()
{
    int Position;
    cout<<"Input the Position:";
    cin>>Position;
    if(Position<=sizeOfList)
    {
        if(tail == NULL)
        {
            if(Position!=1)
            {
                cout<<"Wrong input, the list is empty. Try again";
                insert();
            }
            else
            {
                head = new node;
                head->next=NULL;
                head->prev=NULL;
                tail = head;
                cout<<"Input the value:";
                cin>>head->data;
                sizeOfList++;
            }
        }
        else if(Position==sizeOfList)
        {
            node *temp = new node();
            cout<<"Input the value:";
            cin>>temp->data;
            temp->next=NULL;
            temp->prev = tail;
            tail->next = temp;
            tail = temp;
            sizeOfList++;
        }
        else
        {
            node *temp= new node();
            cout<<"Input the value:";
            cin>>temp->data;
            node *cur =head;
            for(int i =1;i<Position-1;i++)
            {
                cur= cur->next;
            }
            temp->next= cur->next;
            temp->prev= cur;
            cur->next->prev=temp;
            cur->next= temp;
            sizeOfList++;
        }
    }
    else
    {
        cout<<"Invalid Position, try again!\n";
        insert();
    }


}


int search()
{
    if(tail ==NULL)
    {
        cout<<"The list is empty.\n";
        return 0;
    }
    cout<<"Insert the key value you would like to find:";
    int key;
    cin>>key;
    node *cur = head;
    int index=1;
    while(cur!=NULL)
    {
        if(key==cur->data)
        {
            cout<<"Found\n"
                <<"The value is at index "<<index<<'\n';
            return 0;
        }
        else
            index++;
        cur= cur->next;
    }
    cout<<"Not Found";
}


int remove()
{
    if(tail==NULL)
    {
        cout<<"The list is empty.\n";
        return 0;
    }

    cout<<"Insert the key value you would like to remove:";
    int key;
    cin>>key;
    bool loopBreaker = true;
    node *cur = head;
    if(cur->data !=key)
    {
        while(cur!=NULL)
        {
            if(key==cur->next->data)
                loopBreaker = false;
            if(!loopBreaker)
                break;
            cur=cur->next;
        }
        if(cur->next==tail)
        {
            tail=tail->prev;
            tail->next = NULL;
        }
        else
        {
            cur->next->next->prev = cur;
            cur->next= cur->next->next;
        }
    }
    else if(cur->data ==key)
    {
        head = head->next;
        head->prev = NULL;
    }
    else
    {
        cout<<"The value is not present in the list."
            <<"Try again";
        remove();
    }

}


int mid()
{
    if(tail==NULL)
    {
        cout<<"The list is empty.\n";
        return 0;
    }
    node *cur = head;
    for(int i =1;i<sizeOfList/2;i++)
    {
        cur= cur->next;
    }
    cout<<"Middle node is at index "<<sizeOfList/2<<'\n'
        <<"Middle node value: "<<cur->data<<"\n";
}


int display()
{
    if(tail == NULL)
    {
        cout<<"The list is empty.\n";
        return 0;
    }

    node *cur = head;
    while(cur!=NULL)
    {
        cout<<cur->data<<" ";
        cur = cur->next;
    }
    cout<<'\n';
}


int main()
{
    head = NULL;
    tail = NULL;
    while(2)
    {
        cout<<"\nPress 1 to insert value at a Position.\n"
            <<"Press 2 to search a key value in the list.\n"
            <<"Press 3 to remove a key value in the list.\n"
            <<"Press 4 to find the mid value of the linked list.\n"
            <<"Press 5 to display the whole linked list.\n"
            <<"Press 6 to end the program.\n";
        int Decision;
        cin>>Decision;
        if(Decision ==6)
            break;
        else if (Decision ==1)
            insert();
        else if (Decision ==2)
            search();
        else if (Decision ==3)
            remove();
        else if (Decision ==4)
            mid();
        else
            display();
    }
    return 0;
}
