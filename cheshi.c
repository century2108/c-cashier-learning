#include <stdio.h>
#include <string.h>

#define GOODS_COUNT 3

int main(void)
{
    // 商品信息数组
    char name[GOODS_COUNT][20] = { "Cola", "Lollipop", "Noodles" };
    float price[GOODS_COUNT] = { 3.50f, 0.50f, 6.00f };
    int cart[GOODS_COUNT] = { 0 }; //购物车，记录每种商品购买数量

    char input[20];
    int i;
    int find_flag;
    float total = 0.0f;

    printf("===== 便利店收银系统 =====\n");
    printf("指令：\n");
    printf("  输入商品名：添加商品到购物车\n");
    printf("  list ：查看购物车\n");
    printf("  checkout ：结账并保存订单\n");
    printf("  exit ：退出程序\n");

    while (1)
    {
        printf("\n请输入指令：");
        scanf("%s", input);

        // 退出
        if (strcmp(input, "exit") == 0)
        {
            printf("程序结束\n");
            break;
        }
        // 查看购物车
        else if (strcmp(input, "list") == 0)
        {
            printf("\n-----购物车清单-----\n");
            total = 0;
            for (i = 0; i < GOODS_COUNT; i++)
            {
                if (cart[i] > 0)
                {
                    printf("%-10s 单价:%.2f 数量:%d 小计:%.2f\n",
                        name[i], price[i], cart[i], cart[i] * price[i]);
                    total += cart[i] * price[i];
                }
            }
            printf("====================\n");
            printf("当前合计：%.2f\n", total);
        }
        // 结账，写入文件
        else if (strcmp(input, "checkout") == 0)
        {
            FILE* fp = fopen("order.txt", "a");
            if (fp == NULL)
            {
                printf("订单文件打开失败！\n");
                continue;
            }
            total = 0;
            printf("\n=====结账小票=====\n");
            for (i = 0; i < GOODS_COUNT; i++)
            {
                if (cart[i] > 0)
                {
                    float sub = cart[i] * price[i];
                    printf("%s x%d  %.2f\n", name[i], cart[i], sub);
                    fprintf(fp, "%s x%d ", name[i], cart[i]);
                    total += sub;
                }
            }
            fprintf(fp, "Total=%.2f\n", total);
            printf("总价：%.2f\n", total);
            printf("结账成功，订单已保存到order.txt\n");
            fclose(fp);
            //清空购物车
            for (i = 0; i < GOODS_COUNT; i++)
            {
                cart[i] = 0;
            }
        }
        // 添加商品
        else
        {
            find_flag = 0;
            for (i = 0; i < GOODS_COUNT; i++)
            {
                if (strcmp(input, name[i]) == 0)
                {
                    cart[i]++;
                    printf("成功添加：%s，当前数量：%d\n", name[i], cart[i]);
                    find_flag = 1;
                    break;
                }
            }
            if (find_flag == 0)
            {
                printf("错误：找不到该商品！\n");
            }
        }
    }
    return 0;
}
