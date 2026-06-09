/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riael <gpascu@student.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 16:56:45 by riael             #+#    #+#             */
/*   Updated: 2026/06/03 16:09:01 by riael            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/ft_printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

void	ft_c_test(void);
void	ft_s_test(void);
void	ft_p_test(void);
void	ft_d_test(void);
void	ft_i_test(void);
void	ft_u_test(void);
void 	ft_x_test(void);
void 	ft_X_test(void);
void	ft_percent_test(void);
void 	test_final(void);
void    sometest(void);
void    speedtest(void);
void    weirdtest(void);
void    run_fuzz_test(int count);
int     ft_printf(const char *format, ...);
void    errortest(void);
void    test_d(char *test_name, char *format, int val);
void    test_i(char *test_name, char *format, int val);
void    run_chaos_test(int iterations);
void    simple_chaos_test(int iterations);
void    test_pct(char *test_name, char *format);


int	main(int argc, char **argv)
{
	int	i;

	if (argc != 2)
	{
		ft_printf("|Proper usage:                |\n");
		ft_printf("|test.out followed by a number|\n");
		ft_printf("|Possible values:             |\n");
		ft_printf("|1: Testing the %%c flag       |\n");
		ft_printf("|2: Testing the %%s flag       |\n");
		ft_printf("|3: Testing the %%p flag       |\n");
		ft_printf("|4: Testing the %%d flag       |\n");
		ft_printf("|5: Testing the %%i flag       |\n");
		ft_printf("|6: Testing the %%u flag       |\n");
		ft_printf("|7: Testing the %%x flag       |\n");
		ft_printf("|8: Testing the %%X flag       |\n");
		ft_printf("|9: Testing the %%%% flag       |\n");
		ft_printf("|10: -0# +cspdiuxX% random    |\n");
		ft_printf("|11: diuxXp-0# + random 2     |\n");
        ft_printf("|12: cspdiuxX-0# + 3-in-1     |\n");
        ft_printf("|13: sometest                 |\n");
		ft_printf("|14: speedtest                |\n");
        ft_printf("|15: weirdtest                |\n");
		return (0);
	}
	i = atoi(argv[1]);
	if (i == 1)
		ft_c_test();
	if (i == 2)
		ft_s_test();
	if (i == 3)
		ft_p_test();
	if (i == 4)
		ft_d_test();
	if (i == 5)
		ft_i_test();
	if (i == 6)
		ft_u_test();
	if (i == 7)
		ft_x_test();
	if (i == 8)
		ft_X_test();
	if (i == 9)
		ft_percent_test();
	if (i == 10)
		{
            srand(time(NULL));
            simple_chaos_test(argc > 2 ? atoi(argv[2]) : -1);
        }
    if (i == 11)
	{
            srand(time(NULL));
        int tests = -1; // Default to infinite
        if (argc > 2)
            tests = atoi(argv[2]);
    
    run_fuzz_test(tests);
    }
    if (i == 12)
	{
        srand(time(NULL));
        run_chaos_test(argc > 2 ? atoi(argv[2]) : -1);
    }
    if (i == 13)
		sometest();
    if (i == 14)
		speedtest();
	if (i == 15)
        weirdtest();
    if (i == 16)
        errortest();
	return (0);
}

void    errortest(void)
{
    int orig, mine;

    void    *p1 = (void *)0x7fff5fbff708;

        test_i("Zero Pad with Plus", "%010+i", 42); // Should be +000000042
        test_d("Zero Pad with Plus", "%010+d", 42);
            // Precision (Small)
        orig = printf("Orig: [%.5p]\n", p1);
        mine = ft_printf("Mine: [%.5p]\n", p1);
        printf("Return: orig %d | mine %d\n\n", orig, mine);

        // Precision (Large - Padding zeros after 0x)
        orig = printf("Orig: [%.20p]\n", p1);
        mine = ft_printf("Mine: [%.20p]\n", p1);
        printf("Return: orig %d | mine %d\n\n", orig, mine);

        // Width and Precision Combined
        orig = printf("Orig: [%25.20p]\n", p1);
        mine = ft_printf("Mine: [%25.20p]\n", p1);
        printf("Return: orig %d | mine %d\n\n", orig, mine);

            // Precision (Small)
        orig = printf("Orig: [%.5p]\n", p1);
        mine = ft_printf("Mine: [%.5p]\n", p1);
        printf("Return: orig %d | mine %d\n\n", orig, mine);

        // Precision (Large - Padding zeros after 0x)
        orig = printf("Orig: [%.20p]\n", p1);
        mine = ft_printf("Mine: [%.20p]\n", p1);
        printf("Return: orig %d | mine %d\n\n", orig, mine);

        // Width and Precision Combined
        orig = printf("Orig: [%25.20p]\n", p1);
        mine = ft_printf("Mine: [%25.20p]\n", p1);
        printf("Return: orig %d | mine %d\n\n", orig, mine);

        // Left Align + Width + Precision
        orig = printf("Orig: [%-25.20p]\n", p1);
        mine = ft_printf("Mine: [%-25.20p]\n", p1);
        printf("Return: orig %d | mine %d\n\n", orig, mine);
        
        	// Pointer with zero padding flag (usually ignored/undefined for %p)
        orig = printf("Orig: [%020p]\n", p1);
        mine = ft_printf("Mine: [%020p]\n", p1);
        printf("Return: orig %d | mine %d\n\n", orig, mine);

          // 6. WIDTH + ZERO + MULTIPLE
        test_pct("The Weirdo", "%010%%%-10%"); // [000000000%%         ]

}

void test_pct(char *test_name, char *format)
{
    int orig, mine;
    printf("--- %s ---\nFormat: [%s]\n", test_name, format);
    
    printf("Orig: [");
    fflush(stdout);
    orig = printf(format);
    printf("]\n");

    printf("Mine: [");
    fflush(stdout);
    mine = ft_printf(format);
    printf("]\n");
    fflush(stdout);

    printf("Return: orig %d | mine %d\n", orig, mine);
    if (orig != mine)
        printf(">> ERROR: Return values don't match! <<\n");
    printf("\n");
}

void ft_percent_test(void)
{
    // 1. THE BASICS
    test_pct("Simple Percent", "%%");
    test_pct("Double Percent", "%%%%");
    test_pct("Percent with text", "100%% sure");

    // 2. WIDTH (The "Hidden" challenge)
    test_pct("Width Right", "%5%");   // [    %]
    test_pct("Width Left", "%-5%");  // [%    ]
    
    // 3. ZERO PADDING
    test_pct("Zero Padded", "%05%"); // [0000%]

    // 4. THE "SPAGHETTI" COMBO
    printf("--- Multiple Types with Percent ---\n");
    int o = printf("Orig: [%d%%] [%s%%] [%c%%]\n", 42, "Success", '!');
    int m = ft_printf("Mine: [%d%%] [%s%%] [%c%%]\n", 42, "Success", '!');
    printf("Return: orig %d | mine %d\n\n", o, m);

    // 5. THE CRAZY ONE
    // This tests if your parser gets confused by multiple % in a row
    test_pct("Percent Overload", "%%%%%%%%%%"); 
	
	// 7. THE "SPAGHETTI" COMBO
	printf("--- Multiple Types with Percent ---\n");
	o = printf("Orig: [%d%%] [%s%%] [%c%%]\n", 42, "Success", '!');
	m = ft_printf("Mine: [%d%%] [%s%%] [%c%%]\n", 42, "Success", '!');
	printf("Return: orig %d | mine %d\n\n", o, m);

}

void test_X(char *test_name, char *format, unsigned int val)
{
    int orig, mine;
    // Note: Printing val as %u and %X in the header for clarity
    printf("--- %s ---\nFormat: [%s] | Value: %u\n", test_name, format, val);
    
    printf("Orig: [");
    fflush(stdout);
    orig = printf(format, val);
    printf("]\n");

    printf("Mine: [");
    fflush(stdout);
    mine = ft_printf(format, val);
    printf("]\n");
    fflush(stdout);

    printf("Return: orig %d | mine %d\n", orig, mine);
    if (orig != mine)
        printf(">> ERROR: Return values don't match! <<\n");
    printf("\n");
}

void ft_X_test(void)
{
    // === SECTION 1: THE FOUNDATION ===
    test_X("Zero", "%X", 0);
    test_X("Single Digit", "%X", 10);
    test_X("Max Unsigned", "%X", UINT_MAX);
    test_X("Overflow logic", "%X", UINT_MAX + 1);

    // === SECTION 2: THE HASH (#) DYNAMICS ===
    test_X("Hash Non-Zero", "%#X", 255);
    test_X("Hash Zero", "%#X", 0); // SHOULD NOT print 0X
    test_X("Hash Width", "%#15X", 123456);
    test_X("Hash Left Align", "%-#15X", 123456);

    // === SECTION 3: THE PRECISION GAUNTLET ===
    test_X("Prec 0 on 0", "%.0X", 0);
    test_X("Prec 1 on 0", "%.1X", 0);
    test_X("Prec 5 on 255", "%.5X", 255);
    test_X("Prec > Width", "%5.10X", 255);
    test_X("Width > Prec", "%10.5X", 255);

    // === SECTION 4: THE ZERO-FLAG TRAPS ===
    // If precision is present, 0 flag is ignored
    test_X("Zero flag + Prec", "%010.5X", 42); 
    test_X("Zero flag no Prec", "%010X", 42);
    test_X("Hash + Zero flag", "%#010X", 42); // Should be 0X0000002A
    test_X("Hash + Zero flag + Prec", "%#010.5X", 42); // 0 flag IGNORED

    // === SECTION 5: LEFT ALIGNMENT STRESS ===
    test_X("Left Align Prec", "%-10.5X", 42);
    test_X("Left Align Hash Prec", "%-#15.10X", 1000);
    test_X("Left Align Max Width", "%-50X", 1);

    // === SECTION 6: ILLEGAL/WEIRD COMBOS ===
    test_X("Space on X", "% X", 42);
    test_X("Plus on X", "%+X", 42);
    test_X("Space + Hash", "% #X", 42);
    test_X("Plus + Hash", "%+#X", 42);

    // === SECTION 7: THE "BORING" PERMUTATIONS (The Wall) ===
    test_X("Perm 1", "%1.1X", 1);
    test_X("Perm 2", "%1.2X", 1);
    test_X("Perm 3", "%2.1X", 1);
    test_X("Perm 4", "%05.3X", 123);
    test_X("Perm 5", "%-05.3X", 123);
    test_X("Perm 6", "%#15.10X", 0);
    test_X("Perm 7", "%#.5X", 42);
    test_X("Perm 8", "%#1.1X", 1);
    test_X("Perm 9", "%#1.1X", 0);
    test_X("Perm 10", "%5.0X", 0);
    test_X("Perm 11", "%5.X", 0);
    test_X("Perm 12", "%#5.0X", 42);
    test_X("Perm 13", "%-10.10X", 42);
    test_X("Perm 14", "%010.0X", 0);
    test_X("Perm 15", "%010.1X", 0);
    test_X("Perm 16", "%-10.0X", 0);
    test_X("Perm 17", "%#.X", 0);
    test_X("Perm 18", "%#.X", 42);
    test_X("Perm 19", "%10.5X", UINT_MAX);
    test_X("Perm 20", "%#10.5X", UINT_MAX);

    // === SECTION 8: MULTIPLE CONVERSIONS ===
    printf("--- Multiple Conversions ---\n");
    ft_printf("Hex Mix: [%#X] [%010X] [%.5X] [%-15.10X]\n", 255, 255, 255, 255);
    ft_printf("Consecutive: %X%X%X%X%X\n", 10, 11, 12, 13, 14);
    ft_printf("Zero Sandwich: %X %X %X\n", 42, 0, 42);

	// === SECTION 9: THE "CONFLICT" ZONE ===
    // If '0' and '.' (precision) are both present, '0' is IGNORED.
    test_X("Conflicting 0 and Precision", "%010.5X", 255);   // [     000FF]
    test_X("Conflicting - and 0", "%-010X", 255);           // [FF        ] (- overrides 0)

    // === SECTION 10: THE "ZERO-VALUE" LABYRINTH ===
    // These test the interaction between #, 0, width, and precision on a value of 0.
    test_X("Zero: %#.X", "%#.X", 0);             // [] (Empty)
    test_X("Zero: %#.0X", "%#.0X", 0);           // [] (Empty)
    test_X("Zero: %5.0X", "%5.0X", 0);           // [     ] (5 spaces)
    test_X("Zero: %#5.0X", "%#5.0X", 0);         // [     ] (Still 5 spaces, # is ignored)
    test_X("Zero: %05X", "%05X", 0);             // [00000]
    test_X("Zero: %#05X", "%#05X", 0);           // [00000] (No 0X because value is 0)

    // === SECTION 11: THE "EXTREME PREFIX" PLACEMENT ===
    test_X("Hash + Big Prec", "%#.20X", 1234);   // 0X000000000000000004D2
    test_X("Hash + Width + Prec", "%#15.10X", 1); // [     0X0000000001]

    // === SECTION 12: THE "ILLEGAL" FLAG DANCE ===
    // Standard printf ignores + and space for %X, but let's see if your engine survives.
    test_X("Illegal Plus", "%+X", 42);           // [2A]
    test_X("Illegal Space", "% X", 42);          // [2A]
    test_X("Illegal Plus + Hash", "%+#X", 42);   // [0X2A]
    test_X("Illegal Space + Hash", "% #X", 42);  // [0X2A]

    // === SECTION 13: THE "MAX & WRAP" EXTREMES ===
    test_X("UINT_MAX with Hash", "%#X", UINT_MAX);
    test_X("UINT_MAX Left Align Hash", "%-#20X", UINT_MAX);
    test_X("One over UINT_MAX", "%X", (unsigned int)4294967296); // Should wrap to 0

    // === SECTION 14: THE "LONG STRING" SPAM ===
    printf("--- Concat Stress ---\n");
    ft_printf("CRAZY: %X %010X %#.5X %-15.10X %#X %#.0X %X\n", 
               1, 2, 3, 4, 0, 0, UINT_MAX);
}

void test_x(char *test_name, char *format, unsigned int val)
{
    int orig, mine;
    printf("--- %s ---\nFormat: [%s] | Value: %u (0x%x)\n", test_name, format, val, val);
    
    printf("Orig: [");
    fflush(stdout);
    orig = printf(format, val);
    printf("]\n");

    printf("Mine: [");
    fflush(stdout);
    mine = ft_printf(format, val);
    printf("]\n");
    fflush(stdout);

    printf("Return: orig %d | mine %d\n", orig, mine);
    if (orig != mine)
        printf(">> ERROR: Return values don't match! <<\n");
    printf("\n");
}

void ft_x_test(void)
{
    // 1. THE BASICS
    test_x("Zero", "%x", 0);
    test_x("Max", "%x", UINT_MAX);
    test_x("A classic", "%x", 255);

    // 2. THE HASH FLAG (#) - The "0x" logic
    test_x("Hash on non-zero", "%#x", 42);      // 0x2a
    test_x("Hash on ZERO", "%#x", 0);          // 0 (NOT 0x0) -> IMPORTANT!
    test_x("Hash with Width", "%#10x", 42);    // [      0x2a]
    test_x("Hash with Left Align", "%-#10x", 42); // [0x2a      ]

    // 3. THE "HASH-ZERO" TRAP (Order of 0x)
    test_x("Hash + Zero Pad", "%#010x", 42);   // 0x0000002a (0x comes BEFORE zeros)
    test_x("Hash + Zero Pad on 0", "%#010x", 0); // [0000000000] (No 0x!)

    // 4. THE PRECISION OVERLAP
    test_x("Precision > Digits", "%.10x", 42);
    test_x("Hash + Precision", "%#.10x", 42);  // 0x000000002a
    test_x("Width > Precision > Digits", "%15.10x", 42); 
    test_x("Left Align + Hash + Prec", "%-#15.10x", 42);

    // 5. THE "0 VALUE" EDGE CASES (The most failed tests)
    test_x("Zero value, Prec 0", "%.0x", 0);        // EMPTY
    test_x("Zero value, Prec 0, Hash", "%#.0x", 0); // EMPTY
    test_x("Zero value, Prec 0, Width", "%5.0x", 0); // [     ] (5 spaces)
    test_x("Zero value, Prec 1", "%.1x", 0);        // 0

    // 6. THE "ILLEGAL" FLAGS (Signed flags on Unsigned Hex)
    // Standard printf usually ignores '+' and ' ' for %x.
    test_x("Plus Flag on Hex", "%+x", 42);   
    test_x("Space Flag on Hex", "% x", 42);
    test_x("Plus + Hash", "%+#x", 42);

    // 7. WEIRD COMBOS
    test_x("Multiple hashes?", "%##x", 42); // Should treat as one #
    test_x("Precision with zero", "%.x", 0); // Same as %.0x (empty)

    // 8. THE BIG ONE
    test_x("The Kitchen Sink", "%-#20.15x", UINT_MAX);

	ft_printf("Mixed Hex: %#x %#x %#x\n", 0, 42, UINT_MAX);
	ft_printf("Mixed Hex: %#x%#x%#x\n", 0, 42, UINT_MAX);
}

void test_u(char *test_name, char *format, unsigned int val);
void ft_u_test(void)
{
    // 1. THE LIMITS
    test_u("Zero", "%u", 0);
    test_u("Simple", "%u", 42);
    test_u("Max Unsigned Int", "%u", UINT_MAX); // 4294967295
    test_u("Over Max (Wrap)", "%u", UINT_MAX + 1); // Should print 0

    // 2. THE PRECISION "NOTHINGNESS"
    test_u("Precision 0 on 0", "%.0u", 0);       // EMPTY
    test_u("Precision 0 on 0 with Width", "%5.0u", 0); // 5 Spaces
    test_u("Precision 1 on 0", "%.1u", 0);       // "0"
    test_u("Huge Precision", "%.50u", 4294967295);

    // 3. THE WIDTH & ZERO PAD COMBO
    test_u("Width 10", "%10u", 123);
    test_u("Zero Pad 10", "%010u", 123);
    test_u("Zero Pad on Max", "%015u", UINT_MAX);
    test_u("Zero Pad with Precision", "%010.5u", 123); // Precision overrides '0' flag! (Spaces)

    // 4. LEFT ALIGNMENT
    test_u("Left Align", "%-10u", 123);
    test_u("Left Align Huge", "%-20u", UINT_MAX);
    test_u("Left Align + Precision", "%-10.5u", 123); // [00123     ]

    // 5. THE "UNDEFINED" ZONE (Standard flags on Unsigned)
    // Standard printf usually ignores '+' and ' ' for %u, 
    // but how does your engine handle them?
    test_u("Plus Flag (Illegal?)", "%+u", 42); 
    test_u("Space Flag (Illegal?)", "% u", 42);

    // 6. RAPID FIRE MULTIPLES
    printf("--- Multiple Unsigned ---\n");
    int o = printf("Orig: [%u] [%10u] [%.5u] [%-10.2u]\n", 0, 42, 123, UINT_MAX);
    int m = ft_printf("Mine: [%u] [%10u] [%.5u] [%-10.2u]\n", 0, 42, 123, UINT_MAX);
    printf("Return: orig %d | mine %d\n\n", o, m);

    // 7. THE "CRAZY" TEST (Spamming)
    printf("--- The Spam Test ---\n");
    ft_printf("Spam: %u%u%u%u%u%u%u%u\n", 1, 2, 3, 4, 5, 6, 7, UINT_MAX);
    
    // 8. LARGE WIDTH + LARGE PRECISION
    test_u("The Mega Test", "%100.75u", 123456789);
}

void test_u(char *test_name, char *format, unsigned int val)
{
    int orig, mine;

    printf("--- %s ---\n", test_name);
    printf("Format: [%s] | Value: %u\n", format, val);
    
    printf("Orig: [");
    fflush(stdout); // <--- FORCE PRINT
    orig = printf(format, val);
    printf("]\n");

    printf("Mine: [");
    fflush(stdout); // <--- FORCE PRINT
    mine = ft_printf(format, val);
    printf("]\n");
    fflush(stdout); // <--- FORCE PRINT

    printf("Return: orig %d | mine %d\n", orig, mine);
    if (orig != mine)
        printf(">> ERROR: Return values don't match! <<\n");
    printf("\n");
}

void test_d(char *test_name, char *format, int val)
{
    int orig, mine;

    printf("--- %s ---\n", test_name);
    printf("Format: %s | Value: %d\n", format, val);
    
    printf("Orig: [");
    orig = printf(format, val);
    printf("]\n");

    ft_printf("Mine: [");
    mine = ft_printf(format, val);
    ft_printf("]\n");

    printf("Return: orig %d | mine %d\n", orig, mine);
    if (orig != mine)
        printf(">> ERROR: Return values don't match! <<\n");
    printf("\n");
}

void test_i(char *test_name, char *format, int val)
{
    int orig, mine;

    printf("--- %s ---\n", test_name);
    printf("Format: %s | Value: %d\n", format, val);
    
    printf("Orig: [");
    orig = printf(format, val);
    printf("]\n");

    ft_printf("Mine: [");
    mine = ft_printf(format, val);
    ft_printf("]\n");

    printf("Return: orig %d | mine %d\n", orig, mine);
    if (orig != mine)
        printf(">> ERROR: Return values don't match! <<\n");
    printf("\n");
}

void	ft_i_test()
{
	 // 1. BASIC & LIMITS
    test_i("Simple Zero", "%i", 0);
    test_i("Simple Positive", "%i", 42);
    test_i("Simple Negative", "%i", -42);
    test_i("INT_MAX", "%i", INT_MAX);
    test_i("INT_MIN", "%i", INT_MIN);

    // 2. FLAGS (+ and Space)
    test_i("Plus Flag Pos", "%+i", 42);
    test_i("Plus Flag Neg", "%+i", -42);
    test_i("Space Flag Pos", "% i", 42);
    test_i("Space Flag Neg", "% i", -42);
    test_i("Plus Flag Zero", "%+i", 0);

    // 3. WIDTH
    test_i("Width Right", "%10i", 42);
    test_i("Width Left", "%-10i", 42);
    test_i("Width Right Neg", "%10i", -42);
    test_i("Width Left Neg", "%-10i", -42);

    // 4. PRECISION (The "0" logic)
    test_i("Precision 5 on 42", "%.5i", 42);
    test_i("Precision 5 on -42", "%.5i", -42);
    test_i("Precision 0 on 0", "%.0i", 0); // Should print NOTHING
    test_i("Precision 1 on 0", "%.1i", 0); // Should print 0
    test_i("Width 5 Precision 0 on 0", "%5.0i", 0); // Should print 5 spaces

    // 5. ZERO PADDING
    test_i("Zero Pad", "%010i", 42);
    test_i("Zero Pad Neg", "%010i", -42); // Should be -000000042
    test_d("Zero Pad with Plus", "%+010d", 42);


    // 6. WIDTH & PRECISION COMBINED
    test_i("Width 10 Prec 5", "%10.5i", 42);
    test_i("Width 10 Prec 5 Neg", "%10.5i", -42);
    test_i("Width 10 Prec 5 Plus", "%+10.5i", 42);
    test_i("Left Align Width 10 Prec 5", "%-10.5i", 42);

    // 7. SURROUNDING TEXT & MULTIPLES
    printf("--- Multiple Values ---\n");
    int o = printf("Orig: [Text %i more text %10i and %+i]\n", 1, 500, -20);
    int m = ft_printf("Mine: [Text %i more text %10i and %+i]\n", 1, 500, -20);
    printf("Return: orig %d | mine %d\n\n", o, m);

    printf("--- Mixed Flags Stress ---\n");
    test_i("The Everything Bagel", "%+-15.10i", 42);
    test_i("Zero Flag ignored by Prec", "%010.5i", 42); // Precision overrides '0' flag
    
    // 8. WILDCARDS
    printf("--- Wildcards ---\n");
    o = printf("Orig: [%*.*i]\n", 10, 5, 42);
    m = ft_printf("Mine: [%*.*i]\n", 10, 5, 42);
    printf("Return: orig %d | mine %d\n", o, m);

	test_i("Precision > Width", "%5.10i", 42);     // Should be 10 digits
	test_i("Width > Precision", "%10.5i", 42);     // Should be 5 spaces, 5 digits
	test_i("Zero value, Zero Prec", "%.0i", 0);    // Should be EMPTY
	test_i("Zero value, Prec 1", "%.1i", 0);       // Should be "0"
	test_i("Minus flag with Zero", "%010i", -42);  // Should be -000000042
	test_i("Plus flag with Zero", "%+010i", 42);   // Should be +000000042
	test_i("Space flag with Zero", "% 010i", 42);  // Should be  000000042
	test_i("Left Align + Prec", "%-10.5i", 42);    // [00042     ]
	test_i("Left Align + Sign", "%-+10i", 42);     // [+42       ]
	test_i("Left Align INT_MIN", "%-15i", -2147483648);
	test_i("Big Width", "%50i", 42);
	test_i("Big Precision", "%.50i", 42);
	test_i("Zero Flag ignored by Prec", "%010.5i", 42); // Logic: '0' flag is ignored if '.' is present
}

void	ft_d_test()
{
	 // 1. BASIC & LIMITS
    test_d("Simple Zero", "%d", 0);
    test_d("Simple Positive", "%d", 42);
    test_d("Simple Negative", "%d", -42);
    test_d("INT_MAX", "%d", INT_MAX);
    test_d("INT_MIN", "%d", INT_MIN);

    // 2. FLAGS (+ and Space)
    test_d("Plus Flag Pos", "%+d", 42);
    test_d("Plus Flag Neg", "%+d", -42);
    test_d("Space Flag Pos", "% d", 42);
    test_d("Space Flag Neg", "% d", -42);
    test_d("Plus Flag Zero", "%+d", 0);

    // 3. WIDTH
    test_d("Width Right", "%10d", 42);
    test_d("Width Left", "%-10d", 42);
    test_d("Width Right Neg", "%10d", -42);
    test_d("Width Left Neg", "%-10d", -42);

    // 4. PRECISION (The "0" logic)
    test_d("Precision 5 on 42", "%.5d", 42);
    test_d("Precision 5 on -42", "%.5d", -42);
    test_d("Precision 0 on 0", "%.0d", 0); // Should print NOTHING
    test_d("Precision 1 on 0", "%.1d", 0); // Should print 0
    test_d("Width 5 Precision 0 on 0", "%5.0d", 0); // Should print 5 spaces

    // 5. ZERO PADDING
    test_d("Zero Pad", "%010d", 42);
    test_d("Zero Pad Neg", "%010d", -42); // Should be -000000042
    test_d("Zero Pad with Plus", "%+010d", 42); // Should be +000000042

    // 6. WIDTH & PRECISION COMBINED
    test_d("Width 10 Prec 5", "%10.5d", 42);
    test_d("Width 10 Prec 5 Neg", "%10.5d", -42);
    test_d("Width 10 Prec 5 Plus", "%+10.5d", 42);
    test_d("Left Align Width 10 Prec 5", "%-10.5d", 42);

    // 7. SURROUNDING TEXT & MULTIPLES
    printf("--- Multiple Values ---\n");
    int o = printf("Orig: [Text %d more text %10d and %+d]\n", 1, 500, -20);
    int m = ft_printf("Mine: [Text %d more text %10d and %+d]\n", 1, 500, -20);
    printf("Return: orig %d | mine %d\n\n", o, m);

    printf("--- Mixed Flags Stress ---\n");
    test_d("The Everything Bagel", "%+-15.10d", 42);
    test_d("Zero Flag ignored by Prec", "%010.5d", 42); // Precision overrides '0' flag
    
    // 8. WILDCARDS
    printf("--- Wildcards ---\n");
    o = printf("Orig: [%*.*d]\n", 10, 5, 42);
    m = ft_printf("Mine: [%*.*d]\n", 10, 5, 42);
    printf("Return: orig %d | mine %d\n", o, m);

	test_d("Precision > Width", "%5.10d", 42);     // Should be 10 digits
	test_d("Width > Precision", "%10.5d", 42);     // Should be 5 spaces, 5 digits
	test_d("Zero value, Zero Prec", "%.0d", 0);    // Should be EMPTY
	test_d("Zero value, Prec 1", "%.1d", 0);       // Should be "0"
	test_d("Minus flag with Zero", "%010d", -42);  // Should be -000000042
	test_d("Plus flag with Zero", "%+010d", 42);   // Should be +000000042
	test_d("Space flag with Zero", "% 010d", 42);  // Should be  000000042
	test_d("Left Align + Prec", "%-10.5d", 42);    // [00042     ]
	test_d("Left Align + Sign", "%-+10d", 42);     // [+42       ]
	test_d("Left Align INT_MIN", "%-15d", -2147483648);
	ft_printf("Multi: [%d] [%10d] [%.5d] [%-10.5d]\n", 1, 2, 3, 4);
	ft_printf("No Space: %d%d%d%d\n", 10, 20, 30, 40);
	ft_printf("Text in between: Value 1 is %d and Value 2 is %+d\n", 500, -500);
	test_d("Big Width", "%50d", 42);
	test_d("Big Precision", "%.50d", 42);
	test_d("Zero Flag ignored by Prec", "%010.5d", 42); // Logic: '0' flag is ignored if '.' is present
}

void	ft_p_test()
{
int 	mine, orig;
char	*str = "Hello";
int		n = 42;
void	*ptr = &n;

// Basic address
mine = ft_printf("mine: %p\n", ptr);
orig =    printf("orig: %p\n", ptr);
printf("res: m:%d o:%d\n\n", mine, orig);

// NULL pointer (The most common crash site)
mine = ft_printf("mine: %p\n", NULL);
orig =    printf("orig: %p\n", NULL);
printf("res: m:%d o:%d\n\n", mine, orig);

// Address of a string literal
mine = ft_printf("mine: %p\n", str);
orig =    printf("orig: %p\n", str);
printf("res: m:%d o:%d\n\n", mine, orig);

int array[] = {1, 2, 3};
void *p_arr = array;

// Testing incremented pointer
mine = ft_printf("mine: %p\n", p_arr + 1);
orig =    printf("orig: %p\n", p_arr + 1);
printf("res: m:%d o:%d\n\n", mine, orig);

// Address of the pointer itself (Double pointer logic)
mine = ft_printf("mine: %p\n", &ptr);
orig =    printf("orig: %p\n", &ptr);
printf("res: m:%d o:%d\n\n", mine, orig);

// Long long max as a pointer (Stress testing hex length)
mine = ft_printf("mine: %p\n", (void *)-1);
orig =    printf("orig: %p\n", (void *)-1);
printf("res: m:%d o:%d\n\n", mine, orig);

// Multiple pointers in one go
mine = ft_printf("mine: %p %p %p\n", &n, &str, ptr);
orig =    printf("orig: %p %p %p\n", &n, &str, ptr);
printf("res: m:%d o:%d\n\n", mine, orig);

// Pointers sandwiched between text
mine = ft_printf("mine: Start%pMid%pEnd\n", &n, &n);
orig =    printf("orig: Start%pMid%pEnd\n", &n, &n);
printf("res: m:%d o:%d\n\n", mine, orig);

// Pointers with confusing characters
mine = ft_printf("mine: %p%%%p\n", &n, &n);
orig =    printf("orig: %p%%%p\n", &n, &n);
printf("res: m:%d o:%d\n\n", mine, orig);

// The Ultimate Mix
mine = ft_printf("mine: %c | %s | %p | %c | %s\n", 'A', "Banana", &n, 'Z', "End");
orig =    printf("orig: %c | %s | %p | %c | %s\n", 'A', "Banana", &n, 'Z', "End");
printf("res: m:%d o:%d\n\n", mine, orig);

// Empty strings and NULL strings with pointers
mine = ft_printf("mine: %s %p %s\n", "", &n, (char *)NULL);
orig =    printf("orig: %s %p %s\n", "", &n, (char *)NULL);
printf("res: m:%d o:%d\n\n", mine, orig);

// Pointer arithmetic inside the call
char *hop = "abcdef";
mine = ft_printf("mine: %p %c %p %c\n", hop, *hop, hop + 3, *(hop + 3));
orig =    printf("orig: %p %c %p %c\n", hop, *hop, hop + 3, *(hop + 3));
printf("res: m:%d o:%d\n\n", mine, orig);

	void	*p1 = (void *)0x7fff5fbff708;
	void	*p2 = NULL;
	void	*p3 = (void *)ULONG_MAX;
	int		a = 42;

	// Basic Address
	orig = printf("Orig: [%p]\n", p1);
	mine = ft_printf("Mine: [%p]\n", p1);
	printf("Return: orig %d | mine %d\n\n", orig, mine);

	// Null Pointer
	orig = printf("Orig: [%p]\n", p2);
	mine = ft_printf("Mine: [%p]\n", p2);
	printf("Return: orig %d | mine %d\n\n", orig, mine);

	// Max Address
	orig = printf("Orig: [%p]\n", p3);
	mine = ft_printf("Mine: [%p]\n", p3);
	printf("Return: orig %d | mine %d\n\n", orig, mine);

	// Field Width (Right Aligned)
	orig = printf("Orig: [%20p]\n", p1);
	mine = ft_printf("Mine: [%20p]\n", p1);
	printf("Return: orig %d | mine %d\n\n", orig, mine);

	// Field Width (Left Aligned)
	orig = printf("Orig: [%-20p]\n", p1);
	mine = ft_printf("Mine: [%-20p]\n", p1);
	printf("Return: orig %d | mine %d\n\n", orig, mine);

	// Left Align + Width + Precision
	orig = printf("Orig: [%-25.20p]\n", p1);
	mine = ft_printf("Mine: [%-25.20p]\n", p1);
	printf("Return: orig %d | mine %d\n\n", orig, mine);

	// Null with Precision 0 (Some systems print nothing or just 0x)
	orig = printf("Orig: [%.p]\n", p2);
	mine = ft_printf("Mine: [%.p]\n", p2);
	printf("Return: orig %d | mine %d\n\n", orig, mine);

	// Mixed with text and other flags
	orig = printf("Orig: [Address: %15p, Val: %d]\n", &a, a);
	mine = ft_printf("Mine: [Address: %15p, Val: %d]\n", &a, a);
	printf("Return: orig %d | mine %d\n\n", orig, mine);

	// Multiple pointers
	orig = printf("Orig: [%p] [%p] [%p]\n", p1, p2, p3);
	mine = ft_printf("Mine: [%p] [%p] [%p]\n", p1, p2, p3);
	printf("Return: orig %d | mine %d\n\n", orig, mine);

	// Pointer with zero padding flag (usually ignored/undefined for %p)
	orig = printf("Orig: [%020p]\n", p1);
	mine = ft_printf("Mine: [%020p]\n", p1);
	printf("Return: orig %d | mine %d\n\n", orig, mine);

}

void	ft_s_test()
{
    int mine;
    int orig;

    // --- Basic String Tests ---

	printf("# mixed test\n");
	mine = ft_printf("Hello %#s\n", "yo");
	printf("value: %d\n", mine);
    
    printf("Test 1: Simple string\n");
    mine = ft_printf("Hello %s\n", "world");
    orig = printf("Hello %s\n", "world");
    printf("Return: mine %d | orig %d\n\n", mine, orig);

    printf("Test 2: Empty string\n");
    mine = ft_printf("Empty: %s\n", "");
    orig = printf("Empty: %s\n", "");
    printf("Return: mine %d | orig %d\n\n", mine, orig);

    // --- Multiple %s Flags ---

    printf("Test 3: Double s\n");
    mine = ft_printf("%s %s\n", "Deep", "Thought");
    orig = printf("%s %s\n", "Deep", "Thought");
    printf("Return: mine %d | orig %d\n\n", mine, orig);

    printf("Test 4: Four s in a row (No spaces)\n");
    mine = ft_printf("%s%s%s%s\n", "1", "2", "3", "4");
    orig = printf("%s%s%s%s\n", "1", "2", "3", "4");
    printf("Return: mine %d | orig %d\n\n", mine, orig);

    // --- Characters embedded in the format string (not %c) ---

    printf("Test 5: String with special characters in format\n");
    mine = ft_printf("Tab\tNewline\nSlash\\ %s\n", "Success");
    orig = printf("Tab\tNewline\nSlash\\ %s\n", "Success");
    printf("Return: mine %d | orig %d\n\n", mine, orig);

    printf("Test 6: Characters surrounding s\n");
    mine = ft_printf("###%s!!!\n", "Attention");
    orig = printf("###%s!!!\n", "Attention");
    printf("Return: mine %d | orig %d\n\n", mine, orig);

    // --- Edge Cases & Long Strings ---

    printf("Test 7: Only s\n");
    mine = ft_printf("%s", "Just a string\n");
    orig = printf("%s", "Just a string\n");
    printf("Return: mine %d | orig %d\n\n", mine, orig);

    printf("Test 8: Long sentence with mixed s\n");
    mine = ft_printf("The %s is a %s that %s %s.\n", "cat", "beast", "eats", "fish");
    orig = printf("The %s is a %s that %s %s.\n", "cat", "beast", "eats", "fish");
    printf("Return: mine %d | orig %d\n\n", mine, orig);

    printf("Test 9: s with numbers as text\n");
    mine = ft_printf("The year is %s\n", "2026");
    orig = printf("The year is %s\n", "2026");
    printf("Return: mine %d | orig %d\n\n", mine, orig);

    // --- Percent Signs ---

    printf("Test 10: Literal percent sign with s\n");
    mine = ft_printf("Progress: %s%%\n", "100");
    orig = printf("Progress: %s%%\n", "100");
    printf("Return: mine %d | orig %d\n\n", mine, orig);

    // --- NULL Check ---
    // Note: Behavior for NULL strings is technically undefined in C, 
    // but most modern libcs print "(null)".
    printf("Test 11: NULL string pointer\n");
    mine = ft_printf("Pointer: %s\n", (char *)NULL);
    orig = printf("Pointer: %s\n", (char *)NULL);
    printf("Return: mine %d | orig %d\n\n", mine, orig);
}

void	ft_c_test(void)
{
	int	mine;
	int	orig;

	// Single character
	mine = ft_printf("mine: %c\n", 'A');
	orig = printf("orig: %c\n", 'A');
	printf("res: m:%d | o:%d\n\n", mine, orig);
	
	// Multiple characters back-to-back
	mine = ft_printf("mine: %c%c%c\n", '4', '2', '!');
	orig = printf("orig: %c%c%c\n", '4', '2', '!');
	printf("res: m:%d | o:%d\n\n", mine, orig);

	// The Null Character (Crucial test case)
	mine = ft_printf("mine: %c\n", '\0');
	orig = printf("orig: %c\n", '\0');
	printf("res: m:%d | o:%d\n\n", mine, orig);

	// Right alignment with width
mine = ft_printf("mine: [%5c]\n", 'A');
orig = printf("orig: [%5c]\n", 'A');
printf("res: m:%d | o:%d\n\n", mine, orig);

// Left alignment (if you implemented the '-' flag)
mine = ft_printf("mine: [%-5c]\n", 'B');
orig = printf("orig: [%-5c]\n", 'B');
printf("res: m:%d | o:%d\n\n", mine, orig);

// Large width
mine = ft_printf("mine: [%10c]\n", 'C');
orig = printf("orig: [%10c]\n", 'C');
printf("res: m:%d | o:%d\n\n", mine, orig);

// Right alignment with width
mine = ft_printf("mine: [%5c]\n", 'D');
orig = printf("orig: [%5c]\n", 'D');
printf("res: m:%d | o:%d\n\n", mine, orig);

// Left alignment (if you implemented the '-' flag)
mine = ft_printf("mine: [%-5c]\n", 'E');
orig = printf("orig: [%-5c]\n", 'E');
printf("res: m:%d | o:%d\n\n", mine, orig);

// Large width
mine = ft_printf("mine: [%10c]\n", 'F');
orig = printf("orig: [%10c]\n", 'F');
printf("res: m:%d | o:%d\n\n", mine, orig);

// Spaces inside and outside the format string
mine = ft_printf("mine:  %c  %c  \n", '1', '2');
orig = printf("orig:  %c  %c  \n", '1', '2');
printf("res: m:%d | o:%d\n\n", mine, orig);

// Non-printable characters (Tab, Newline)
mine = ft_printf("mine: %c%c%c\n", '\t', '\n', '\v');
orig = printf("orig: %c%c%c\n", '\t', '\n', '\v');
printf("res: m:%d | o:%d\n\n", mine, orig);

// Character passed as an int (common in C)
mine = ft_printf("mine: %c\n", 200); 
orig = printf("orig: %c\n", 200);
printf("res: m:%d | o:%d\n\n", mine, orig);

// Multiple chars in a row
orig = printf("Chars: %c %c %c", 'a', 'b', 'c');
printf(" -> %d\n", orig);
mine = ft_printf("Chars: %c %c %c", 'a', 'b', 'c');
printf(" -> %d\n", mine);

// Chars buried in long strings
orig = printf("Start %c Middle %c End", '1', '2');
printf(" -> %d\n", orig);
mine = ft_printf("Start %c Middle %c End", '1', '2');
printf(" -> %d\n", mine);

// Non-printable (Tab)
orig = printf("Tab: [%c]", '\t');
printf(" -> %d\n", orig);
mine = ft_printf("Tab: [%c]", '\t');
printf(" -> %d\n", mine);

// High ASCII/Negative values (Overflow check)
orig = printf("High: %c", 255);
printf(" -> %d\n", orig);
mine = ft_printf("High: %c", 255);
printf(" -> %d\n", mine);

// Mixed padding and text
orig = printf("Text %10c and %-10c tail", 'A', 'B');
printf(" -> %d\n", orig);
mine = ft_printf("Text %10c and %-10c tail", 'A', 'B');
printf(" -> %d\n", mine);

// Multiple widths in a row
orig = printf("%5c%5c%5c", '1', '2', '3');
printf(" -> %d\n", orig);
mine = ft_printf("%5c%5c%5c", '1', '2', '3');
printf(" -> %d\n", mine);

}
