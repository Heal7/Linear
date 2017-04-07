#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct
{
	float coef;
	int exp;
}count;
typedef struct Node
{
	float coef;  //ϵ��
	int exp;    //ָ��
	struct Node *next;
}LinkList;

void ListInitiate(LinkList**head)  //�����ʼ��
{
	*head=(LinkList*)malloc(sizeof(LinkList));
	(*head)->next=NULL;
}

void ListInsert(LinkList *head,count L)  //����������
{
	LinkList *p,*q;
	p=head;
	while(p->next!=NULL)    //��ϵ����С��������ĽǶ�Ѱ�Ҳ�����
	{
		if(p->next->exp>L.exp)  break;
		p=p->next;
	}
    q=(LinkList*)malloc(sizeof(LinkList));
	q->coef=L.coef;
	q->exp=L.exp;
	q->next=p->next;
	p->next=q;
}

int Print(LinkList *head)    //���
{
	LinkList *p;
	p=head->next;
	if(p==NULL)     //����ʽΪ0ʱֱ�����
	{
		printf("0\n");
		exit(0);
	}
	while(p->coef==1&&p->exp)  //ָ����Ϊ��ʱϵ��Ϊ1ʱ�����
	{
		printf("X^%d",p->exp);
		p=p->next;
		if(p==NULL) return 0;
		else printf("+");
	}
	while(p->next)
	{
		printf("%gx^%d",p->coef,p->exp);
		p=p->next;
		if(p->coef>0) printf("+");
	}
		printf("%gx^%d",p->coef,p->exp);
		return 1;
}

void Add(LinkList *a,LinkList *b,LinkList *c)  //����ʽa b��ӵ��ڶ���ʽc
{
	LinkList *p,*q,*s,*k;
	s=c;
	p=a->next;
    while(p!=NULL) //�Ƚ�a����c��  
	{
	    q=(LinkList*)malloc(sizeof(LinkList));
		q->coef=p->coef;
		q->exp=p->exp;
		q->next=NULL;
		c->next=q;
		c=c->next;
		p=p->next;
	}
	c=s;
	p=b->next;
    while(p!=NULL)   //��b����c��
	{
		while((c->next!=NULL)&&(p->exp>(c->next->exp))) //Ѱ�Ҳ�����
		{
			c=c->next;
		}
		if(c->next==NULL)   //��������
		{
		   q=(LinkList*)malloc(sizeof(LinkList));
           q->coef=p->coef;
		   q->exp=p->exp;
		   q->next=c->next;
		   c->next=q;
		}
		else if(p->exp==c->next->exp)  //ָ�����ʱϵ�����
		{
		    s=c;
			c=c->next;
			c->coef=c->coef+p->coef;
			if(c->coef==0)
			{
				k=c;
				c=s;
				c->next=c->next->next;
				free(k);
			}
		}
		else if(p->exp>c->exp&&c->next!=NULL)  //��ͨ����
		{
            q=(LinkList*)malloc(sizeof(LinkList));
            q->coef=p->coef;
		    q->exp=p->exp;
		    q->next=c->next;
		    c->next=q;
		}
	    p=p->next;
	}
}
			
		
void main()    //������
{
		LinkList *a,*b,*c;
		count L;
		int i,j;
		ListInitiate(&a);
		ListInitiate(&b);
		ListInitiate(&c);
		printf("������a��������");
		scanf("%d",&j);
		for(i=0;i<j;i++)
		{
			printf("����a�ĵ�%d��ϵ����",i+1);
			scanf("%g",&L.coef);
            printf("����a�ĵ�%d��ָ����",i+1);
			scanf("%d",&L.exp);
			ListInsert(a,L);
		}
	    printf("������b��������");
		scanf("%d",&j);
		for(i=0;i<j;i++)
		{
			printf("����b�ĵ�%d��ϵ����",i+1);
			scanf("%g",&L.coef);
            printf("����b�ĵ�%d��ָ����",i+1);
			scanf("%d",&L.exp);
			ListInsert(b,L);
		}
		Add(a,b,c);
		printf("����Ķ���ʽaΪ:\n");
		Print(a);printf("\n");
     	printf("����Ķ���ʽbΪ:\n");
		Print(b);printf("\n");
		printf("����Ķ���ʽa+b=cΪ:\n");
		Print(c);printf("\n");
}






