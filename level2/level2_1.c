#include <stdio.h>
#include <string.h>
#include <time.h>
int today_date = 1;
int serial_no = 0;
int admin_mode = 0;
char admin_password[100] = "admin123";
int main()
{
    char name[3][100] = {"Cola", "Lollipop", "Noodles"};
    int code[3] = {1, 2, 3};
    char code1[3][100] = {"1", "2", "3"}; // code1是code的字符串形式,后面用户既可输入名称也可输入编号查找相关信息
    float price[3] = {3.50, 0.50, 6.00};
    int count[3] = {0, 0, 0}; // count是每种商品的购买数量，初始为0

    char MC[20]; // MC表输入的名称

    int i;
    while (1)
    {
        if (admin_mode == 1)
        {
            printf("(tips1:可输入'setpassword+_+新密码'来修改密码)\n");
            printf("(tips2:可输入'back'返回用户模式)\n");
            printf("admin>");
        }
        else
        {
            printf(">");
            printf("Enter product name or code:\n (tips1:you can enter 'exit' or 'quit' to quit)\n(tips2:you can enter 'prices' to view all products)\n(tips3:product names are Cola, Lollipop, Noodles)\n"); // 提示用户输入名称或代码和如何关闭程序
        }

        scanf("%s", MC);
        if (strcmp(MC, "admin") == 0)
        {
            char input_password[100];
            printf("Password:\n");
            scanf("%s", input_password);
            if (strcmp(input_password, admin_password) == 0)

            {
                admin_mode = 1;
                printf("Admin mode.\n");
                continue;
            }

            else
            {
                printf("Error:wrong password.\n");
                continue;
            } // 判断是否进入管理员模式，是则继续，不是则提示用户输入名称或代码
        }

        if (MC[0] == 's' && MC[1] == 'e' && MC[2] == 't' && MC[3] == 'p' && MC[4] == 'a' && MC[5] == 's' && MC[6] == 's' && MC[7] == 'w' && MC[8] == 'o' && MC[9] == 'r' && MC[10] == 'd' && MC[11] == '_')
        {
            if (admin_mode == 1)
            {
                // MC+12：从下标12位置开始，就是新密码字符串
                strcpy(admin_password, MC + 12);
                printf("Password changed.\n");
                continue;
            }
            else
            {
                printf("ERROR: 你没有管理员权限\n");
            }
            continue;
        }

        if (strcmp(MC, "back") == 0)
        {
            if (admin_mode == 1)
            {
                admin_mode = 0;
                printf("Bye.\n");
            }
            else
            {
                printf("ERROR: 你没有管理员权限\n");
            }
            continue;
        }

        if (strcmp(MC, "exit") == 0 || strcmp(MC, "quit") == 0)
        {
            break;
        }
        if (strcmp(MC, "prices") == 0)
        {
            printf("%-15s  %-15s  %-15s\n", "name", "code", "price");
            printf("--------------------------------------------------\n"); // 不知道除了printf----还有没有更好的方法来打印表格，太慢了
            for (i = 0; i < 3; i++)
            {

                printf("%-15s  %-15d  %-15.2f\n", name[i], code[i], price[i]);
            }
            continue;
        }
        if (strcmp(MC, "print") == 0)
        {
            printf("Rceipt:\n");
            printf("%-15s  %-15s  %-15s   %-15s\n", "Item", "Pri.", "Qty", "Amount");
            printf("--------------------------------------------------\n");
            double Total = 0.00;
            for (int i = 0; i < 3; i++)
            {
                float item_sum = count[i] * price[i];
                printf("%-15s  %-15d  %-15.2f  %-15d  %-15.2f\n", name[i], code[i], price[i], count[i], item_sum);

                Total += item_sum;
            }
            printf("--------------------------------------------------\n");
            printf("Total: %.2f\n", Total);
            continue;
        }
        if (MC[0] == 's' && MC[1] == 'a' && MC[2] == 'l' && MC[3] == 'e' && MC[4] == 's')
        {
            int chaxun = 0;
            if (MC[5] == '\0')
            {
                chaxun = today_date;
            }
            else
            {
                sscanf(MC + 5, "%d", &chaxun);
            }
            FILE *fp_read = fopen("sales.txt", "r");
            if (fp_read == NULL)
            {
                printf("文件读取失败\n");
                continue;
            }
            char all[300];
            int read_date;
            int read_NO;
            int hh, mm, ss;
            char read_goods_counts[200];
            float read_Total;
            int found1 = 0; // 用于判断是否搜寻到相关订单
            double daily = 0;
            printf("Date;%d", chaxun);
            printf("%-15s  %-15s  %-15s   %-15s\n", "No.", "Time", "Items", "Amount");
            printf("-----------------------------------------------------------\n");
            printf("-----------------------------------------------------------\n");
            while (fgets(all, sizeof(all), fp_read) != NULL)
            {
                int read_number = sscanf(all, "Date:%d No:%d Time:%d:%d:%d %199[^T] Total=%f", &read_date, &read_NO, &hh, &mm, &ss, read_goods_counts, &read_Total);
                if (read_number == 7 && read_date == chaxun)
                {

                    printf("%-15d  %02d:%02d:%02d  %-15s   %-15.2f\n", read_NO, hh, mm, ss, read_goods_counts, read_Total);
                    daily += read_Total;
                    found1 = 1;
                }
            }
            printf("-----------------------------------------------------------\n");
            printf("Daily:%.2f\n", daily);
            if (found1 == 0)
            {
                printf("NO records for day %d.\n", chaxun);
            }
            fclose(fp_read);
            continue;
        }
        if (strcmp(MC, "newday") == 0)
        {
            today_date++;
            serial_no = 0;
            for (int i = 0; i < 3; i++)
            {
                count[i] = 0;
            }
            printf("New day started.Today's sales records cleared");
            continue;
        }
        else if (strcmp(MC, "checkout") == 0) // checkout：打印小票，然后清空当前订单
        {
            printf("Rceipt:\n");
            printf("%-15s  %-15s  %-15s   %-15s\n", "Item", "Pri.", "Qty", "Amount");
            printf("--------------------------------------------------\n");
            double Total = 0.00;
            for (int i = 0; i < 3; i++)
            {
                float item_sum = count[i] * price[i];
                printf("%-15s  %-15d  %-15.2f  %-15d  %-15.2f\n", name[i], code[i], price[i], count[i], item_sum);

                Total += item_sum;
            }
            printf("--------------------------------------------------\n");
            printf("Total: %.2f\n", Total);
            FILE *fp = fopen("sales.txt", "a");
            if (fp == NULL)
            {
                printf("文件打开失败\n");
            }
            else
            {
                time_t now = time(NULL);
                struct tm *t = localtime(&now);

                fprintf(fp, "Date:%d No:%d Time:%02d:%02d:%02d ",
                        today_date, serial_no + 1, t->tm_hour, t->tm_min, t->tm_sec);

                for (int i = 0; i < 3; i++)
                {
                    if (count[i] > 0)
                    {
                        fprintf(fp, "%s x%d ", name[i], count[i]);
                    }
                }
                fprintf(fp, "Total=%.2f\n", Total);
                fclose(fp);
                serial_no++;

                for (int i = 0; i < 3; i++) // 结账完成，清空购物记录
                {
                    count[i] = 0;
                }
                printf("结账完成\n");
                continue;
            }
        }

        int found = 0;    // found是一个标志变量，用于判断是否找到匹配的商品
        int delta;        // delta是用户输入的购买数量
        char *endptr;     // endptr是一个指针，用于指向字符串转换函数的结束位置
        if (MC[0] == '-') // 如果用户输入的第一个字符是负号，则表示减少购买数量
        {
            delta = -1;
            endptr = MC + 1;
        }
        else
        {
            delta = 1;
            endptr = MC;
        }
        for (i = 0; i < 3; i++)
        {

            if (strcmp(name[i], endptr) == 0 || strcmp(code1[i], endptr) == 0) // 前面输入name的endprt改为原来的MC也可以，因为MC和endptr指向同一个字符串，只是endptr可能会跳过负号
            {
                count[i] += delta; // 根据用户输入的正负号来增加或减少购买数量
                if (count[i] < 0)  // 如果购买数量小于0，则将其重置为0.
                {
                    count[i] = 0; // 即不可能购买负数的商品
                }

                printf("name:%s\ncode:%d\nprice:%.2f\ncount:%d\ntotal: %.2f\n", name[i], code[i], price[i], count[i], count[i] * price[i]);

                found = 1; // 将found标志变量设置为1，表示找到了匹配的商品
                break;
            }
        };
        if (found == 0)
        {
            printf("ERROR :code not found\n");
        }
    }
    return 0;
}
