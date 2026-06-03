#include <stdio.h>
#include <limits.h>
#include "printf.h"

int main(void)
{
	int		orig;
	int		mine;
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

	return (0);
}
