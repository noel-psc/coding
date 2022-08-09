#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main(void)
{
    int num, guessing;
    _Bool flag = true, result;
    srand((unsigned int)time(NULL));
    num = rand() % 10;

    while (flag)
    {
        printf("猜猜我心里想的数字是几？\n");
        printf("我猜是：");
        scanf("%d", &guessing);
        if (guessing == num)
        {
            result = true;
            printf("猜对了！\n");
            printf("游戏结束！\n");
            goto FINISH;
        }
        else
        {
            if (guessing > num)
            {
                printf("猜大了！\n");
            }
            else if (guessing < num)
            {
                printf("猜小了！\n");
            }
        }
        // printf("%d\n", num);
    }
FINISH:
    system("pause");
    return 0;
}