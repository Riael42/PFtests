#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include "../includes/ft_printf.h"

int ft_printf(const char *format, ...);

typedef struct s_spec {
    char    format[64];
    char    type;
    long    args[3];   
    int     arg_count; 
} t_spec;

char *rand_str_3in1() {
    static char *pool[] = {"Hello", "42", "Spaghetti", " ", "", "WAS_HERE", "Bananas", "string", NULL};
    return pool[rand() % 9];
}

t_spec gen_random_spec() {
    char *types = "cspdiuxX";
    char *flags = "-0# +";
    t_spec spec;
    spec.arg_count = 0;
    spec.type = types[rand() % 8];
    
    // 1. Randomize Flags (up to 2 for legibility)
    char f_part[5] = "";
    if (rand() % 2) f_part[0] = flags[rand() % 5];
    if (rand() % 3 == 0) f_part[1] = flags[rand() % 5];

    // 2. Randomize Width (Max 25 for legibility)
    char width_part[10] = "";
    int r_width = rand() % 3;
    if (r_width == 1) {
        sprintf(width_part, "%d", rand() % 25);
    } else if (r_width == 2) {
        strcpy(width_part, "*");
        spec.args[spec.arg_count++] = (rand() % 35) - 10; // -10 to 25
    }

    // 3. Randomize Precision (Max 15)
    char prec_part[10] = "";
    int r_prec = rand() % 5;
    if (r_prec == 1) sprintf(prec_part, ".%d", rand() % 15);
    else if (r_prec == 2) {
        strcpy(prec_part, ".*");
        spec.args[spec.arg_count++] = (rand() % 20) - 5; // -5 to 15
    }
    else if (r_prec == 3) strcpy(prec_part, ".");
    else if (r_prec == 4) strcpy(prec_part, ".0");

    // 4. Assemble Format
    sprintf(spec.format, "%%%s%s%s%c", f_part, width_part, prec_part, spec.type);

    // 5. Generate Main Value (The Nasty Pool)
    long val = 0;
    int edge = (rand() % 6 == 0); // 16% chance for edge case

    if (spec.type == 's') val = (long)rand_str_3in1();
    else if (spec.type == 'p') {
        if (edge) val = (rand() % 2) ? 0 : -1;
        else val = (long)rand();
    } else if (spec.type == 'd' || spec.type == 'i') {
        if (edge) {
            long e[] = {0, INT_MAX, INT_MIN, -1, 1};
            val = e[rand() % 5];
        } else val = (int)rand() - (RAND_MAX / 2);
    } else if (spec.type == 'u' || spec.type == 'x' || spec.type == 'X') {
        if (edge) {
            unsigned int e[] = {0, UINT_MAX, 1};
            val = (long)e[rand() % 3];
        } else val = (long)(unsigned int)rand();
    } else val = (rand() % 95) + 32;

    spec.args[spec.arg_count++] = val;
    return spec;
}

int ft_printf(const char *format, ...);

int call_dynamic(int mine, const char *fmt, long *a, int count) {
    if (mine) {
        switch(count) {
            case 3: return ft_printf(fmt, a[0], a[1], a[2]);
            case 4: return ft_printf(fmt, a[0], a[1], a[2], a[3]);
            case 5: return ft_printf(fmt, a[0], a[1], a[2], a[3], a[4]);
            case 6: return ft_printf(fmt, a[0], a[1], a[2], a[3], a[4], a[5]);
            case 7: return ft_printf(fmt, a[0], a[1], a[2], a[3], a[4], a[5], a[6]);
            case 8: return ft_printf(fmt, a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
            case 9: return ft_printf(fmt, a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]);
            default: return ft_printf(fmt, a[0], a[1], a[2]);
        }
    } else {
        switch(count) {
            case 3: return printf(fmt, a[0], a[1], a[2]);
            case 4: return printf(fmt, a[0], a[1], a[2], a[3]);
            case 5: return printf(fmt, a[0], a[1], a[2], a[3], a[4]);
            case 6: return printf(fmt, a[0], a[1], a[2], a[3], a[4], a[5]);
            case 7: return printf(fmt, a[0], a[1], a[2], a[3], a[4], a[5], a[6]);
            case 8: return printf(fmt, a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
            case 9: return printf(fmt, a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]);
            default: return printf(fmt, a[0], a[1], a[2]);
        }
    }
}

void run_chaos_test(int iterations) {
    int i = 0;
    while (i < iterations || iterations == -1) {
        t_spec s[3] = {gen_random_spec(), gen_random_spec(), gen_random_spec()};
        char fmt[128];
        sprintf(fmt, "%s_%s_%s", s[0].format, s[1].format, s[2].format);

        long args[9];
        int count = 0;
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < s[j].arg_count; k++)
                args[count++] = s[j].args[k];

        printf("[Test %d] Format: [%s]\n", i, fmt);
        
        printf("Orig: ["); fflush(stdout);
        int o_ret = call_dynamic(0, fmt, args, count);
        printf("] (Ret: %d)\n", o_ret);

        printf("Mine: ["); fflush(stdout);
        int m_ret = call_dynamic(1, fmt, args, count);
        printf("] (Ret: %d)\n", m_ret);

        if (o_ret != m_ret) {
            printf("❌ FAILURE!\n");
            exit(1);
        }
        printf("✅ MATCH\n---------------------------------------\n");
        i++;
        usleep(5000); // 0.05s delay: fast but readable
    }
}