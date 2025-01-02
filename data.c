#include "defines.h"
#include "file_io.h"
#include "user_io.h"
#include <stdio.h>
#include <string.h>

int timeLaterThan(time floor, time cur);
int timeEarlierThan(time ceil, time cur);

void filter(char *key)
{
    // TODO 先加载链表
    FILE *parcelData = openParcel("r");
    node *list = loadLinklist(parcelData);
    fclose(parcelData);
    
    char input[20] = {0};
    int matchCount = 0;
    int code = 0;
    // TODO 先判断要筛选哪个字段，然后strcasecmp或者单纯大小判断比较比较即可
    if (!strcasecmp(key, "from"))
    {
        code = 1;
    }
    else if (!strcasecmp(key, "to"))
    {
        code = 2;
    }
    else if (!strcasecmp(key, "ID"))
    {
        code = 3;
    }
    else if (!strcasecmp(key, "status"))
    {
        code = 4;
    }
    else if (!strcasecmp(key, "load_time"))
    {
        code = 5;
    }
    else if (!strcasecmp(key, "unload_time"))
    {
        code = 6;
    }

    switch (code)
    {
    case 1:

        printf("Criteria: ");
        scanf("%s", input);
        getchar();
        for (node *ptr = list; ptr != NULL; ptr = ptr->next)
        {
            if (!strcasecmp(ptr->data.from, input))
            {
                if (matchCount == 0)
                {
                    printf("Matched!\n");
                }
                outputParcel(&(ptr->data));
                matchCount++;
            }
        }
        break;

    case 2:
        printf("Criteria: ");
        scanf("%s", input);
        getchar();
        for (node *ptr = list; ptr != NULL; ptr = ptr->next)
        {
            if (!strcasecmp(ptr->data.to, input))
            {
                if (matchCount == 0)
                {
                    printf("Matched!\n");
                }
                outputParcel(&(ptr->data));
                matchCount++;
            }
        }
        break;

    case 3:
        printf("Criteria: ");
        scanf("%s", input);
        getchar();
        for (node *ptr = list; ptr != NULL; ptr = ptr->next)
        {
            if (!strcasecmp(ptr->data.ID, input))
            {
                if (matchCount == 0)
                {
                    printf("Matched!\n");
                }
                outputParcel(&(ptr->data));
                matchCount++;
            }
        }
        break;

    case 4:
        printf("Criteria: ");
        scanf("%s", input);
        getchar();
        int status = (int)input - 48; //* It‘s 0 or 1.
        for (node *ptr = list; ptr != NULL; ptr = ptr->next)
        {
            if (ptr->data.state == status)
            {
                if (matchCount == 0)
                {
                    printf("Matched!\n");
                }
                outputParcel(&(ptr->data));
                matchCount++;
            }
        }
        break;
    // TODO 为时间筛选设计单独的判断标准输入，以及评判条件，5和6基本相同，可以复制
    case 5:
        int mode = 0;
        printf("Select the filter mode, 1 for between, 2 for later, 3 for earlier\n");
        scanf("%d", &mode);
        getchar();

        switch (mode)
        {
        case 1:
            time floor;
            time ceil;
            printf("Earliest time: ");
            sacnf("%d %d %d %d %d %d", &floor.year, &floor.month, &floor.day, &floor.hour, &floor.minute, &floor.second);
            getchar();
            printf("Latest time: ");
            scanf("%d %d %d %d %d %d", &ceil.year, &ceil.month, &ceil.day, &ceil.hour, &ceil.minute, &ceil.second);
            getchar();

            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                if ((timeLaterThan(floor, ptr->data.load_time)) && (timeEarlierThan(ceil, ptr->data.load_time)))
                {
                    if (matchCount == 0)
                    {
                        printf("Matched!\n");
                    }
                    outputParcel(&(ptr->data));
                    matchCount++;
                }
            }

            break;

        case 2:
            time floor;
            printf("Earliest time: ");
            sacnf("%d %d %d %d %d %d", &floor.year, &floor.month, &floor.day, &floor.hour, &floor.minute, &floor.second);
            getchar();
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                if (timeLaterThan(floor, ptr->data.load_time))
                {
                    if (matchCount == 0)
                    {
                        printf("Matched!\n");
                    }
                    outputParcel(&(ptr->data));
                    matchCount++;
                }
            }

            break;

        case 3:
            time ceil;
            printf("Latest time: ");
            scanf("%d %d %d %d %d %d", &ceil.year, &ceil.month, &ceil.day, &ceil.hour, &ceil.minute, &ceil.second);
            getchar();

            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                if (timeEarlierThan(ceil, ptr->data.load_time))
                {
                    if (matchCount == 0)
                    {
                        printf("Matched!\n");
                    }
                    outputParcel(&(ptr->data));
                    matchCount++;
                }
            }

            break;

        default:
            break;
        }
        break;

    case 6:
        int mode = 0;
        printf("Select the filter mode, 1 for between, 2 for later, 3 for earlier\n");
        scanf("%d", &mode);
        getchar();

        switch (mode)
        {
        case 1:
            time floor;
            time ceil;
            printf("Earliest time: ");
            sacnf("%d %d %d %d %d %d", &floor.year, &floor.month, &floor.day, &floor.hour, &floor.minute, &floor.second);
            getchar();
            printf("Latest time: ");
            scanf("%d %d %d %d %d %d", &ceil.year, &ceil.month, &ceil.day, &ceil.hour, &ceil.minute, &ceil.second);
            getchar();

            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                if ((timeLaterThan(floor, ptr->data.unload_time)) && (timeEarlierThan(ceil, ptr->data.unload_time)))
                {
                    if (matchCount == 0)
                    {
                        printf("Matched!\n");
                    }
                    outputParcel(&(ptr->data));
                    matchCount++;
                }
            }

            break;

        case 2:
            time floor;
            printf("Earliest time: ");
            sacnf("%d %d %d %d %d %d", &floor.year, &floor.month, &floor.day, &floor.hour, &floor.minute, &floor.second);
            getchar();
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                if (timeLaterThan(floor, ptr->data.unload_time))
                {
                    if (matchCount == 0)
                    {
                        printf("Matched!\n");
                    }
                    outputParcel(&(ptr->data));
                    matchCount++;
                }
            }

            break;

        case 3:
            time ceil;
            printf("Latest time: ");
            scanf("%d %d %d %d %d %d", &ceil.year, &ceil.month, &ceil.day, &ceil.hour, &ceil.minute, &ceil.second);
            getchar();

            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                if (timeEarlierThan(ceil, ptr->data.unload_time))
                {
                    if (matchCount == 0)
                    {
                        printf("Matched!\n");
                    }
                    outputParcel(&(ptr->data));
                    matchCount++;
                }
            }

            break;

        default:
            break;
        }

    default:
        printf("Invalid key, check your input!\n");
        break;
    }

    // TODO 释放链表
    for (node *cur = list, *next = NULL; cur != NULL;)
    {
        next = cur->next;
        free(cur);
        cur = next;
    }
}

// TODO 完成这两个时间比较函数，当条件为真时返回值应该是正数
int timeLaterThan(time floor, time cur)
{
    if (cur.year > floor.year)
    {
        return 1;
    }
    else
    {
        if (cur.year < floor.year)
        {
            return 0;
        }
    }
    //* 现在 year 是相等的
    if (cur.month > floor.month)
    {
        return 1;
    }
    else
    {
        if (cur.month < floor.month)
        {
            return 0;
        }
    }
    //* 现在month是相等的
    if (cur.day > floor.day)
    {
        return 1;
    }
    else
    {
        if (cur.day < floor.day)
        {
            return 0;
        }
    }
    //* 现在day是相等的
    if (cur.hour > floor.hour)
    {
        return 1;
    }
    else
    {
        if (cur.hour < floor.hour)
        {
            return 0;
        }
    }
    //* 现在hour是相等的
    if (cur.minute > floor.minute)
    {
        return 1;
    }
    else
    {
        if (cur.minute < floor.minute)
        {
            return 0;
        }
    }
    //* 现在minute是相等的
    if (cur.second > floor.second)
    {
        return 1;
    }
    else
    {
        if (cur.second < floor.second)
        {
            return 0;
        }
    }
    //* 现在second是相等的

    return 1;
}

int timeEarlierThan(time ceil, time cur)
{
    if (cur.year < ceil.year)
    {
        return 1;
    }
    else
    {
        if (cur.year > ceil.year)
        {
            return 0;
        }
    }
    //* 现在 year 是相等的
    if (cur.month < ceil.month)
    {
        return 1;
    }
    else
    {
        if (cur.month > ceil.month)
        {
            return 0;
        }
    }
    //* 现在month是相等的
    if (cur.day < ceil.day)
    {
        return 1;
    }
    else
    {
        if (cur.day > ceil.day)
        {
            return 0;
        }
    }
    //* 现在day是相等的
    if (cur.hour < ceil.hour)
    {
        return 1;
    }
    else
    {
        if (cur.hour > ceil.hour)
        {
            return 0;
        }
    }
    //* 现在hour是相等的
    if (cur.minute < ceil.minute)
    {
        return 1;
    }
    else
    {
        if (cur.minute > ceil.minute)
        {
            return 0;
        }
    }
    //* 现在minute是相等的
    if (cur.second < ceil.second)
    {
        return 1;
    }
    else
    {
        if (cur.second > ceil.second)
        {
            return 0;
        }
    }
    //* 现在second是相等的

    return 1;
}