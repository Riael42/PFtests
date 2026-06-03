#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include "../includes/ft_printf.h"

int ft_printf(const char *format, ...);

typedef union u_val {
    long            l;
    char            *s;
    char            c;
    void            *p;
    unsigned int    ui;
} t_val;

int ft_printf(const char *format, ...);

char *rand_str() {
    static char *pool[] = {"Hello", "42", "Spaghetti", " ", "", "NICHOLAS WAS HERE", \
		"an apple a day keeps", " away", "Bananas", "Doctors", "LOREM IPSUM SOMETHING SOMETHING", "Yes I am being very original how could you tell" "" "string"};
    return pool[rand() % 12];
}

int ft_printf(const char *format, ...);

// This helper calls the real printf with the correct argument types
int call_orig(char *format, char type, t_val val) {
    if (type == 's') return printf(format, val.s);
    if (type == 'c') return printf(format, val.c);
    if (type == 'p') return printf(format, val.p);
    if (type == 'u' || type == 'x' || type == 'X') return printf(format, val.ui);
    if (type == '%') return printf(format);
    return printf(format, (int)val.l);
}

int ft_printf(const char *format, ...);

// This helper calls your ft_printf with the correct argument types
int call_mine(char *format, char type, t_val val) {
    if (type == 's') return ft_printf(format, val.s);
    if (type == 'c') return ft_printf(format, val.c);
    if (type == 'p') return ft_printf(format, val.p);
    if (type == 'u' || type == 'x' || type == 'X') return ft_printf(format, val.ui);
    if (type == '%') return ft_printf(format);
    return ft_printf(format, (int)val.l);
}

int ft_printf(const char *format, ...);

int contains(const char *str, char c) {
    while (*str) {
        if (*str == c) return 1;
        str++;
    }
    return 0;
}

int ft_printf(const char *format, ...);

void simple_chaos_test(int iterations) {
    char *types = "cspdiuxX%";
    char *flags = "-0# +";
    int i = 0;

    while (i < iterations || iterations == -1) {
        t_val val;
        char type = types[rand() % 9];
        
        // --- MULTIPLE FLAGS GENERATION ---
        char active_flags[10] = {0};
        int flag_idx = 0;

        // Randomly decide to add flags (up to all 5)
        for (int f = 0; f < 5; f++) {
            if (rand() % 2) {
                char candidate = flags[f];

                // --- RESTRICTIONS & SAFEDARDS ---
                // 1. No flag allowed for %% 
                if (type == '%') continue;

                // 2. '#' is only valid for o, x, X, a, A, e, E, f, F, g, G (in our list: x, X)
                if (candidate == '#' && type != 'x' && type != 'X') continue;

                // 3. '+' and ' ' are only for signed conversions (d, i)
                if ((candidate == '+' || candidate == ' ') && type != 'd' && type != 'i') continue;

                // 4. Mutually exclusive: If we already have '+', skip ' '
                if (candidate == ' ' && contains(active_flags, '+')) continue;
                if (candidate == '+' && contains(active_flags, ' ')) continue;

                // 5. Mutually exclusive: If we already have '-', skip '0'
                if (candidate == '0' && contains(active_flags, '-')) continue;
                if (candidate == '-' && contains(active_flags, '0')) continue;

                // If it passes all checks, add it separated by an underscore
                if (flag_idx > 0) {
                    active_flags[flag_idx++] = '_';
                }
                active_flags[flag_idx++] = candidate;
            }
        }
        active_flags[flag_idx] = '\0';
        // ---------------------------------

        char format[100];
        // Build the format string using the stacked flags
        sprintf(format, "%%%s%s%s%c", 
            active_flags,
            (rand() % 2) ? "10" : "",
            (rand() % 2) ? ".5" : "",
            type);

        // Generate matching random value
        if (type == 's') val.s = rand_str();
        else if (type == 'c') val.c = (rand() % 95) + 32;
        else if (type == 'p') val.p = (void *)(long)rand();
        else if (type == 'u' || type == 'x' || type == 'X') val.ui = (unsigned int)rand();
        else val.l = (int)rand() - (RAND_MAX / 2);

        printf("[Test %d] Format: [%s] ", i, format);
        
        int o_ret, m_ret;
        
        // Print "Orig"
        fflush(stdout);
        o_ret = call_orig(format, type, val);
        
        printf(" | ");
        
        // Print "Mine"
        fflush(stdout);
        m_ret = call_mine(format, type, val);

        if (o_ret != m_ret) {
            printf("\n❌ FAILURE!\nFormat: %s\nOrig Ret: %d | Mine Ret: %d\n", format, o_ret, m_ret);
            exit(1);
        }
        printf(" ✅\n");
        i++;
        usleep(2000);
    }
}