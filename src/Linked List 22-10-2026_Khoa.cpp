#include <bits/stdc++.h>
using namespace std;

struct node{
	int data;
	node* next;
};

node *makeNode(int data)
{
	node *newNode = new node;
	newNode->data = data;
	newNode->next= NULL;
	return newNode;
}

int size(node *head)
{
	int cnt = 0;
	
	while(head != NULL)
	{
		cnt++;
		head = head->next;
	}
	return cnt;	
}

void duyet(node *head)   // nay la truyen tham tri, khong phai tham chieu -> khong thay doi bien goc ngoai main
{
 	
 	while (head != NULL)
 	{
 		cout << head->data << " ";
 		head = head->next;
	}
}

void pushFront (node *& head, int x)
{
	node* newNode = makeNode(x);
	newNode->next = head;
	head = newNode;
}

void pushBack (node *& head, int x)
{
	if (head == NULL) 
	{
		pushFront(head, x);
		return;
	}
	
	node* newNode = makeNode(x);
	
	node* temp = head;
	
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newNode;
	
}

void insert (node *&head, int data , int vitri)
{
	int n = size(head);
	if (vitri < 1 || vitri > n + 1) 
	{
		cout << " Vi tri khong hop le"; 
		return;
	}
	
	if (vitri == 1) 
	{
		pushFront(head, data);
		return;
	}
	
	if (vitri == n + 1)
	{
		pushBack(head, data);
		return;
	}
	
	node* temp = head;
	node* newNode = makeNode(data);
	
	int cnt = 1;
	
	while(cnt != vitri - 1)
	{
		temp = temp->next;
		cnt++;
	} 
	
	newNode->next = temp->next;
	temp->next = newNode;
}

void delFront(node *&head)
{
	if (head == NULL) return;
	
	node* temp = head;
	head = head->next;
	
	delete temp;
}

void delBack(node*& head)
{
	if (head == NULL) return; // TH khong co node nao;
	if (size(head) == 1) // TH chi co 1 node khong tro temp->next->next duoc;
	{
		delete head;   // xoa head hoi heap truoc;
		head = NULL;	// vo hieu hoa con tro;
		return;
	}
	
	node* temp = head;
	while (temp->next->next != NULL)
	{
		temp = temp->next;
	}
	
	delete temp->next;
	temp->next = NULL;
}

void delPos(node *&head , int vitri)
{
	int n = size(head);
	if (vitri < 1 || vitri > n) 
	{
		cout << " Vi tri khong hop le"; 
		return;
	}
	
	if (vitri == 1) 
	{
		delFront(head);
		return;
	}
	
	if (vitri == n)
	{
		delBack(head);
		return;
	}
	
	node* temp = head;
	
	int cnt = 1;
	
	while(cnt < vitri - 1)
	{
		temp = temp->next;
		cnt++;
	}
	
	node* temp2 = temp->next;
	temp->next = temp->next->next;
	delete temp2;
}
int main()
{
	node* head = NULL;
	 pushFront(head,3);
	 pushBack(head,4);
	 pushBack(head,2); 
	 pushBack(head,1);
	 pushFront(head,5);
	 insert(head,10,2);
	 delPos(head,5); 
	 duyet(head);
	
	
	
}
