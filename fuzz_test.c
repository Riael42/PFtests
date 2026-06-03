#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

// Your printf prototype
int ft_printf(const char *format, ...);

void run_fuzz_test(int count)
{
    char *types = "diuxXp"; // We'll stick to numbers for the math chaos
    char *flags = "-0# +";
    int i = 0;

    while (i < count || count == -1)
    {
        char format[100];
        int width = rand() % 30;
        int precision = rand() % 30;
        char type = types[rand() % 6];
        char flag = flags[rand() % 5];
        
        // Randomly decide which flags to include
        int use_prec = rand() % 2;
        int use_width = rand() % 2;
        int use_flag = rand() % 2;

        // Build the format string procedurally
        sprintf(format, "%%");
        if (use_flag) strncat(format, &flag, 1);
        if (use_width) sprintf(format + strlen(format), "%d", width);
        if (use_prec) sprintf(format + strlen(format), ".%d", precision);
        strncat(format, &type, 1);

        // Generate a random value
        long val;
        if (type == 'p') val = (long)&i + (rand() % 1000);
        else if (rand() % 5 == 0) val = 0;
        else if (rand() % 5 == 1) val = INT_MIN;
        else if (rand() % 5 == 2) val = INT_MAX;
        else val = (rand() % 20000) - 10000;

        // EXECUTE AND COMPARE
        int orig_ret, mine_ret;
        
        // We use a buffer or visually compare. Visual is easier to debug:
        printf("\n[Test %d] Format: [%s] Value: %ld\n", i, format, val);
        
        printf("Orig: [");
        fflush(stdout);
        orig_ret = printf(format, val);
        printf("]\n");

        printf("Mine: [");
        fflush(stdout);
        mine_ret = ft_printf(format, val);
        printf("]\n");
        fflush(stdout);

        if (orig_ret != mine_ret)
        {
            printf("\n❌ ERROR DISCOVERED!\n");
            printf("Format: %s\nValue: %ld\n", format, val);
            printf("Orig Ret: %d | Mine Ret: %d\n", orig_ret, mine_ret);
            exit(1); // Stop immediately on failure
        }
        
        printf("✅ Match! (%d)\n", orig_ret);
        i++;
        usleep(10000); // Small delay so you can actually see it running
    }
}
