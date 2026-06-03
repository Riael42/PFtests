#include <stdio.h>
#include <stddef.h>
#include <limits.h>
#include "../includes/ft_printf.h"

int main(void)
{
	int mine, orig;

	// ---------------------------------------------------------
	// %d (Signed Decimal) Flag
	// ---------------------------------------------------------
	
	// Test: Min Int
	mine = ft_printf("min int: %d\n", INT_MIN);
	orig = printf("min int: %d\n", INT_MIN); 
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig); 

	// Test: Negative Number
	mine = ft_printf("negative number: %d\n", -42);
	orig = printf("negative number: %d\n", -42); 
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig); 

	// Test: Zero
	mine = ft_printf("zero: %d\n", 0);
	orig = printf("zero: %d\n", 0); 
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig); 

	// Test: Positive Number
	mine = ft_printf("positive number: %d\n", 42);
	orig = printf("positive number: %d\n", 42); 
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig); 

	// Test: Positive Max
	mine = ft_printf("max int: %d\n", INT_MAX);
	orig = printf("max int: %d\n", INT_MAX); 
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig); 

	ft_printf("--- Moving on to the %%u (unsigned) flag ---\n\n");

	// ---------------------------------------------------------
	// %u (Unsigned Decimal) Flag
	// ---------------------------------------------------------

	// Test: Zero
	mine = ft_printf("unsigned zero: %u\n", 0);
	orig = printf("unsigned zero: %u\n", 0); 
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig); 

	// Test: Positive Number
	mine = ft_printf("unsigned positive: %u\n", 150);
	orig = printf("unsigned positive: %u\n", 150); 
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig); 

	// Test: Unsigned Max
	mine = ft_printf("unsigned max: %u\n", UINT_MAX);
	orig = printf("unsigned max: %u\n", UINT_MAX); 
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig); 

	ft_printf("--- Moving on to the %%x (hex lowercase) flag ---\n\n");

	// ---------------------------------------------------------
	// %x (Hexadecimal Lowercase) Flag
	// ---------------------------------------------------------

	// Test: Zero
	mine = ft_printf("hex zero: %x\n", 0);
	orig = printf("hex zero: %x\n", 0); 
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig); 

	// Test: Small Hex
	mine = ft_printf("hex small: %x\n", 255);
	orig = printf("hex small: %x\n", 255); 
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig); 

	// Test: Large Hex
	mine = ft_printf("hex max: %x\n", UINT_MAX);
	orig = printf("hex max: %x\n", UINT_MAX); 
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig); 

	ft_printf("--- Moving on to the %%s (string) flag ---\n\n");

	// ---------------------------------------------------------
	// %s (String) Flag
	// ---------------------------------------------------------

	// Test: Standard String
	mine = ft_printf("string: %s\n", "Hello World");
	orig = printf("string: %s\n", "Hello World"); 
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig); 

	// Test: Empty String
	mine = ft_printf("empty string: %s\n", "");
	orig = printf("empty string: %s\n", ""); 
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig); 

	// Note: NULL strings can cause segfaults in standard printf depending on OS.
	// If you're on Linux, printf usually handles it as (null).

	mine = ft_printf("%s", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	orig = printf("%s", "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig);

	mine = ft_printf("                %s                      ", NULL);
  //  orig = printf("                %s                      ", (char *)NULL);
  //  ft_printf("my value: %d\n og value: %d\n\n", mine, orig);

  // ---------------------------------------------------------
	// %c (Character) - The "Null" Trap
	// ---------------------------------------------------------
	ft_printf("--- Moving on to the %%c flag ---\n\n");

	// Test: Standard Char
	mine = ft_printf("char: %c\n", 'A');
	orig = printf("char: %c\n", 'A');
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig);

	// Test: The Null Byte (Crucial: Should print nothing but count 1)
	mine = ft_printf("null char: %c\n", '\0');
	orig = printf("null char: %c\n", '\0');
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig);

	// ---------------------------------------------------------
	// %p (Pointer) - Memory Lane
	// ---------------------------------------------------------
	ft_printf("--- Moving on to the %%p flag ---\n\n");

	// Test: A real address
	int x = 42;
	mine = ft_printf("pointer to x: %p\n", &x);
	orig = printf("pointer to x: %p\n", &x);
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig);

	// Test: NULL pointer
	// Note: Some OS print (nil), some 0x0. Mac and Linux differ!
	mine = ft_printf("null pointer: %p\n", NULL);
	orig = printf("null pointer: %p\n", NULL);
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig);

	// ---------------------------------------------------------
	// %% (Percent) - Inception
	// ---------------------------------------------------------
	ft_printf("--- Moving on to the %%%% flag ---\n\n");

	// Test: Single percent
	mine = ft_printf("percent: %%\n");
	orig = printf("percent: %%\n");
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig);

	// Test: Double trouble
	mine = ft_printf("double percent: %%%%\n");
	orig = printf("double percent: %%%%\n");
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig);

	// ---------------------------------------------------------
	// THE GAUNTLET - Mixed & Strange
	// ---------------------------------------------------------
	ft_printf("--- ENTERING THE GAUNTLET ---\n\n");

	// Test: Mixing types in one go
	mine = ft_printf("Mix: %c %s %p %d %i %u %x %X %%\n", 'B', "babobo", &mine, -42, 42, 420, 42, 42);
	orig = printf("Mix: %c %s %p %d %i %u %x %X %%\n", 'B', "babobo", &mine, -42, 42, 420, 42, 42);
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig);

	// Test: The "Empty" Format (Should print nothing, return 0)
	mine = ft_printf("");
	orig = printf("");
	ft_printf("Empty string test - mine: %d | og: %d\n\n", mine, orig);

	// Test: Passing INT_MIN to unsigned (This tests your type casting)
	mine = ft_printf("INT_MIN as unsigned: %u\n", INT_MIN);
	orig = printf("INT_MIN as unsigned: %u\n", INT_MIN);
	ft_printf("my value: %d\n og value: %d\n\n", mine, orig);

	return (0);
}
