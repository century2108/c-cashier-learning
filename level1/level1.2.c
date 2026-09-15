#include <stdio.h>
#include <string.h>
int main()
{
char name[3][100]={"Cola","Lollipop","Noodles"};
int code[3]={1,2,3};
char code1[3][100]={"1","2","3"};//code1是code的字符串形式,后面用户既可输入名称也可输入编号查找相关信息
float price[3] ={3.50,0.50,6.00};
int count[3]={0,0,0};//count是每种商品的购买数量，初始为0

char MC[20];//MC表输入的名称


int i;
while(1)
{
printf("Enter product name or code:\n (tips1:you can enter 'exit' or 'quit' to quit)\n(tips2:you can enter 'prices' to view all products)\n(tips3:product names are Cola, Lollipop, Noodles)\n");//提示用户输入名称或代码和如何关闭程序
scanf("%s",MC);

if(strcmp(MC,"exit")==0 || strcmp(MC,"quit")==0)
{
break;
}
if(strcmp(MC,"prices")==0)
{printf("%-15s  %-15s  %-15s\n","name","code","price");
    printf("--------------------------------------------------\n");//不知道除了printf----还有没有更好的方法来打印表格，太慢了
for(i=0;i<3;i++)
{
    
printf("%-15s  %-15d  %-15.2f\n", name[i], code[i], price[i]);
  
}
continue;
}
if(strcmp(MC,"print")==0)
{printf("Rceipt:\n");
    printf("%-15s  %-15s  %-15s   %-15s\n","Item","Pri.","Qty","Amount");
    printf("--------------------------------------------------\n");
    double Total=0.00;
    for(int i=0;i<3;i++)
    {
       float item_sum= count[i]*price[i];
    printf("%-15s  %-15d  %-15.2f  %-15d  %-15.2f\n", name[i], code[i], price[i], count[i], item_sum);
    

    Total+=item_sum;
    }
    printf("--------------------------------------------------\n");
    printf("Total: %.2f\n", Total);
continue;
}
else if (strcmp(MC, "checkout") == 0)// checkout：打印小票，然后清空当前订单
{
    printf("Rceipt:\n");
    printf("%-15s  %-15s  %-15s   %-15s\n", "Item", "Pri.", "Qty", "Amount");
    printf("--------------------------------------------------\n");
    double Total = 0.00;
    for (int i = 0;i < 3;i++)
    {
        float item_sum = count[i] * price[i];
        printf("%-15s  %-15d  %-15.2f  %-15d  %-15.2f\n", name[i], code[i], price[i], count[i], item_sum);


        Total += item_sum;
    }
    printf("--------------------------------------------------\n");
    printf("Total: %.2f\n", Total);
    
    for (int i = 0; i < 3; i++)// 结账完成，清空购物记录
    {
        count[i] = 0;
    }
    printf("结账完成\n");
    continue;
}

int found=0;//found是一个标志变量，用于判断是否找到匹配的商品
int delta;//delta是用户输入的购买数量
char*endptr;//endptr是一个指针，用于指向字符串转换函数的结束位置
if(MC[0]== '-')//如果用户输入的第一个字符是负号，则表示减少购买数量
{delta=-1;
endptr=MC+1;
}
else
{
delta=1;
endptr=MC;
}
for(i=0;i<3;i++)                                                       
{


if(strcmp(name[i],endptr)==0 || strcmp(code1[i],endptr)==0)//前面输入name的endprt改为原来的MC也可以，因为MC和endptr指向同一个字符串，只是endptr可能会跳过负号
{count[i]+=delta;//根据用户输入的正负号来增加或减少购买数量
if(count[i]<0)//如果购买数量小于0，则将其重置为0.
{
count[i]=0;//即不可能购买负数的商品
}
    
    printf("name:%s\ncode:%d\nprice:%.2f\ncount:%d\ntotal: %.2f\n", name[i], code[i], price[i], count[i], count[i] * price[i]);

    found = 1;//将found标志变量设置为1，表示找到了匹配的商品
break;
}
};
if(found == 0)
{printf("ERROR :code not found\n");


}
}

    return 0;
}