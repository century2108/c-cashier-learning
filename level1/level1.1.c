#include <stdio.h>
#include <string.h>
int main()
{
char name[3][100]={"Cola","Lollipop","Noodles"};
int code[3]={1,2,3};
float price[3] ={3.50,0.50,6.00};

char MC[20];//MC表输入的名称
//int SZ=0;//SZ代表输入的数字
//scanf("%d",&SZ)
scanf("%s",MC);
int i;

for(i=0;i<3;i++)                                                       
{
//if(code[i]==SZ)
if(strcmp(name[i],MC)==0)
{printf("ok");
break;
}
};
if(i == 3)
{printf("ERROR :code not found\n");


}

    return 0;
}