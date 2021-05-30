#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

void DisplayMenu(char *items[],int mrp[]);
void TakeOrder(int n,int *itno,int *dish);
int AddOrder(int N,int n,int *itno,int *dish);
int RemoveOrder(int n,int *itno,int *dish,char *items[],int mrp[]);
void ShowBill(int n,int *itno,int *dish,char *items[],int mrp[]);

int main(void)
{
	char *items[]={"Idli vada","Khara bath","Kesari bath","Poori sagu","Plain dosa","Masala dosa",
"Onion dosa","Paper masala dosa","Rava idli","Mangalore bun","North Indian meals","South Indian meals","Fried rice"
,"Baby corn manchoorian","Noodles","Tomato Soup","Mixed vegetable soup","Curd rice","Shezwan fried rice",
"Roti curry"};
	int mrp[20]={40,30,30,40,35,45,40,55,40,20,200,180,100,120,90,60,60,50,120,70};
	DisplayMenu(items,mrp);
	bool flag=true;
	int times=1,N=0,n;
	int *itno;
	int *dish;
	int count;
	while(flag==true)
	{
		int choice;
		printf("Enter\n 1 to order\n 2 to remove items\n 0 to exit\n");
		scanf("%d",&choice);
		if((choice==1)&&(times==1))
		{
			printf("Enter the number of different items you want to order\n");
			scanf("%d",&n);
			itno=(int *)calloc(n,sizeof(int));
			dish=(int *)calloc(n,sizeof(int));
			if((itno==NULL)||(dish==NULL))
			{
				printf("Calloc failed.\n");
				exit(1);
			}
			count=n;
			TakeOrder(n,itno,dish);
			ShowBill(count,itno,dish,items,mrp);
			printf("\n\nAny more items you wish to add or delete?\n\n");
			times++;
		}
		else if(choice==1)
		{
			int new;
			printf("Enter the number of different items you want to order to your existing order\n");
			scanf("%d",&new);
			itno=(int *)realloc(itno,(new+n)*sizeof(int));
			dish=(int *)realloc(dish,(new+n)*sizeof(int));
			if((itno==NULL)||(dish==NULL))
			{
				printf("Realloc failed.\n");
				exit(1);
			}
			N=n+new;
			count=AddOrder(N,n,itno,dish);
			ShowBill(count,itno,dish,items,mrp);
			printf("\n\nany more items you wish to add or delete?\n\n");
		}
		else if((choice==2)&&(times>1))
		{
			count=RemoveOrder(n,itno,dish,items,mrp);
			ShowBill(count,itno,dish,items,mrp);
			printf("\n\nAny more items you wish to add or delete?\n\n");
		}
		else if((choice==2)&&(times==1))
			printf("You have tried to remove item from an empty cart\nPlease retry\n");
		else if((choice!=1) && (choice!=2) && (choice !=0))
			printf("Invalid choice\nPlease re-enter\n");	
		else
		{
			printf("You have entered 0, to exit\n");
			flag=false;
		}
	}
	ShowBill(count,itno,dish,items,mrp);
	free(itno);
	free(dish);
	return 0;
}

void DisplayMenu(char *items[],int mrp[])
{
	int i=0;
	printf("---------------MENU---------------\n");
	int sp=25,lsp,j,d;
	for(i=0;i<20;i++)
	{
		printf("%d.",i+1);
		printf("%s",items[i]);
		if(i+1>=10)
		d=2;
		else
		d=1;
		lsp=strlen(items[i])+d;
		for(j=0;j<(sp-lsp);j++)
			printf("-");
		printf("%d",mrp[i]);
		printf("\n");
	}
}

void TakeOrder(int n,int *itno,int *dish)
{
	int temp,j,d;
	for(int i=0;i<n;i++)
	{
		printf("Enter the item number on the menu\n");
		scanf("%d",&temp);
		if((temp<1)||(temp>20))
		{
			itno[i]=-1;
			printf("Invalid input\n");
			dish[i]=0;
		}
		else
		{	
			printf("Enter the number of plates\n");
			scanf("%d",&d);
			if(d<0)
			printf("Invalid input\n");
			else
			{
				itno[i]=temp;
				dish[i]=d;
				for(int j=0;j<i;j++)
				{
					if(itno[j]==temp)
					{
						itno[i]=-1;
						dish[j]=dish[j]+d;
						break;
					}
					else
					{
						itno[i]=temp;
						dish[i]=d;
					}
				}
			}
		}
	}
}

int AddOrder(int N,int n,int *itno,int *dish)
{
	int temp,j,d;
	for(int i=n;i<N;i++)
	{
		printf("Enter the item number on the menu\n");
		scanf("%d",&temp);
		if((temp<1)||(temp>20))
		{
			itno[i]=-1;
			printf("Invalid input\n");
		}
		else
		{
			printf("Enter the number of plates\n");
			scanf("%d",&d);
			if(d<0)
			printf("Invalid input\n");
			else
			{
				itno[i]=temp;
				dish[i]=d;
				for(int j=0;j<i;j++)
				{
					if(itno[j]==temp)
					{
						itno[i]=-1;
						dish[j]=dish[j]+d;
						break;
					}
					else
					{
						itno[i]=temp;
						dish[i]=d;
					}
				}
			}
		}
	}
	int count=N;
	return count;
}

int RemoveOrder(int n,int *itno,int *dish,char *items[],int mrp[])
{
	bool flag=true;
	while(flag==true)
	{
		int choice,pos;
		printf("Enter\n1 to remove an item completely\n2 To remove some plates from the cart\n0 to exit\n");
		scanf("%d",&choice);
		if(choice==1)
		{
			printf("Enter the Sl no. of item you want to completely remove\n");
			scanf("%d",&pos);
			if(pos>n)
			{
				printf("Invalid Sl no\nPlease re-enter\n");
				break;
			}
			for(int i=pos-1;i<n;i++)
			{
				itno[i]=itno[i+1];
				dish[i]=dish[i+1];
			}
			n=n-1;
			int count=n;
			ShowBill(count,itno,dish,items,mrp);
		}
		else if(choice==2)
		{
			int pos,plt;
			printf("Enter the Sl.no of item\n");
			scanf("%d",&pos);
			if(pos>n)
			{
				printf("Invalid Sl no\nPlease re-enter\n");
				break;
			}
			printf("Enter the number of plates to be removed\n");
			scanf("%d",&plt);
			if(dish[pos-1]>=plt)
			dish[pos-1]-=plt;
			else
			printf("You are trying to remove more than existing plates\n");
			int count=n;
			ShowBill(count,itno,dish,items,mrp);
		}
		else
			flag=false;
	}
	int count=n;
	return count;
}

void ShowBill(int n,int *itno,int *dish,char *items[],int mrp[])
{
	int sp=25,i;
	int total,gt=0,no,j,lsp,sl=1;
	printf("------------------WELCOME TO PES CANTEEN------------------\n");
	printf("-------------------------BILL-----------------------------\n");
	printf("Sl no.  ITEMS                    No    Price/plate   Total\n");
	printf("----------------------------------------------------------\n");
	printf("\n");
	for(i=0;i<n;i++)
	{
		no=itno[i];
		if((dish[i]==0)||(itno[i]==-1))
		continue;
		printf("%d.",sl);
		if(i<10)
		printf("      %s",items[no-1]);
		lsp=strlen(items[no-1]);
		for(j=0;j<(sp-lsp);j++)
		printf(" ");
		printf("%d",dish[i]);  
		printf("     %d",mrp[no-1]);
		total=dish[i]*mrp[no-1];
		gt+=total;
		printf("            %d",total);
		printf("\n");
		sl+=1;
	}
	printf("----------------------------------------------------------\n");
	int tax=gt*0.18;
	printf("GST--------------------------------------------%d RUPEES\n",tax);
	gt+=tax;
	printf("AMOUNT TO BE PAID------------------------------%d RUPEES\n",gt);
}
		 
