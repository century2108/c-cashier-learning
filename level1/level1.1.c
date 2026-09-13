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

int i;
while(1)
{
printf("Enter product name:\n (tips1:you can enter 'exit' or 'quit' to quit）\n（tips2:you can enter 'prices' to view all products）\n(tips3:product names are Cola, Lollipop, Noodles\n)");//提示用户输入名称和如何关闭程序
scanf("%s",MC);

if(strcmp(MC,"exit")==0 || strcmp(MC,"quit")==0)
{
break;
}
if(strcmp(MC,"prices")==0)
{
for(i=0;i<3;i++)
{
printf("Product: %s, Code: %d, Price: %.2f\n", name[i], code[i], price[i]);
}
}

for(i=0;i<3;i++)                                                       
{
//if(code[i]==SZ)
if(strcmp(name[i],MC)==0)
{printf("code:%d\nprice:%.2f\n",code[i],price[i]);
break;
}
};
if(i == 3)
{printf("ERROR :code not found\n");


}
}

    return 0;
}