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
	float coef;  //系数
	int exp;    //指数
	struct Node *next;
}LinkList;

void ListInitiate(LinkList**head)  //链表初始化
{
	*head=(LinkList*)malloc(sizeof(LinkList));
	(*head)->next=NULL;
}

void ListInsert(LinkList *head,count L)  //链表插入操作
{
	LinkList *p,*q;
	p=head;
	while(p->next!=NULL)    //从系数由小到大排序的角度寻找插入结点
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

int Print(LinkList *head)    //输出
{
	LinkList *p;
	p=head->next;
	if(p==NULL)     //多项式为0时直接输出
	{
		printf("0\n");
		exit(0);
	}
	while(p->coef==1&&p->exp)  //指数不为零时系数为1时的输出
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

void Add(LinkList *a,LinkList *b,LinkList *c)  //多项式a b相加等于多项式c
{
	LinkList *p,*q,*s,*k;
	s=c;
	p=a->next;
    while(p!=NULL) //先将a存入c中  
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
    while(p!=NULL)   //将b存入c中
	{
		while((c->next!=NULL)&&(p->exp>(c->next->exp))) //寻找插入结点
		{
			c=c->next;
		}
		if(c->next==NULL)   //从最后插入
		{
		   q=(LinkList*)malloc(sizeof(LinkList));
           q->coef=p->coef;
		   q->exp=p->exp;
		   q->next=c->next;
		   c->next=q;
		}
		else if(p->exp==c->next->exp)  //指数相等时系数相加
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
		else if(p->exp>c->exp&&c->next!=NULL)  //普通插入
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
			
		
void main()    //主函数
{
		LinkList *a,*b,*c;
		count L;
		int i,j;
		ListInitiate(&a);
		ListInitiate(&b);
		ListInitiate(&c);
		printf("请输入a的项数：");
		scanf("%d",&j);
		for(i=0;i<j;i++)
		{
			printf("输入a的第%d项系数：",i+1);
			scanf("%g",&L.coef);
            printf("输入a的第%d项指数：",i+1);
			scanf("%d",&L.exp);
			ListInsert(a,L);
		}
	    printf("请输入b的项数：");
		scanf("%d",&j);
		for(i=0;i<j;i++)
		{
			printf("输入b的第%d项系数：",i+1);
			scanf("%g",&L.coef);
            printf("输入b的第%d项指数：",i+1);
			scanf("%d",&L.exp);
			ListInsert(b,L);
		}
		Add(a,b,c);
		printf("输入的多项式a为:\n");
		Print(a);printf("\n");
     	printf("输入的多项式b为:\n");
		Print(b);printf("\n");
		printf("输入的多项式a+b=c为:\n");
		Print(c);printf("\n");
}






