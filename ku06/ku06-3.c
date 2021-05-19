#include <stdio.h>
#include <string.h>
#include <time.h>

int main(void)
{
    struct tm tp;
    int duration = 0;
    int temp = 0;
    char buf[100] = { 0 };

    if (scanf("%d-%d-%d %d", &tp.tm_year, &tp.tm_mon, &tp.tm_mday, &duration) != 4)
        return 1;

    duration *= 2;
    tp.tm_year -= 1900;
    tp.tm_mon += 5;
    tp.tm_hour = 0;
    tp.tm_min = 0;
    tp.tm_sec = 0;
    tp.tm_isdst = -1;
    
    mktime(&tp);

    int add_year = 1;

    while (duration--)
    {
        temp = tp.tm_mday;
        tp.tm_mday += (tp.tm_wday == 0) * 1 + (tp.tm_wday == 6) * 2;
        mktime(&tp);

        strftime(buf, 100, "%Y-%m-%d", &tp);
        printf("%s\n", buf);

        tp.tm_mday = temp;
        if (add_year % 2) {
            tp.tm_mon -= 6;
            tp.tm_year++;
        } else {
            tp.tm_mon += 6;
        }
        mktime(&tp);
    }

    return 0;
}
