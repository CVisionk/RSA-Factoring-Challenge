#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>

/**
 * calculate_long - factorize big number
 * @n: big number
 */

void calculate_long(mpz_t n)
{
	mpz_t i, rem, quotient;

	mpz_init_set_ui(i, 2);
	mpz_inits(rem, quotient, NULL);

	while (mpz_cmp(i, n) < 0)
	{
		mpz_mod(rem, n, i);
		if (mpz_cmp_ui(rem, 0) == 0)
		{
			mpz_tdiv_q(quotient, n, i);
			gmp_printf("%Zd=%Zd*%Zd\n", n, quotient, i);
			mpz_clears(i, rem, quotient, NULL);
			return;
		}
		mpz_add_ui(i, i, 1);
	}
	mpz_clears(i, rem, quotient, NULL);
}

/**
 * calculate - factorize number
 * @n: number
 * Return: 1 on success, 0 on fail.
 */

void calculate(long long int n)
{
	long long int i;

	for (i = 2; i * i <= n; i++)
	{
		if (n % i == 0)
		{
			printf("%lld=%lld*%lld\n", n, n / i, i);
			return;
		}
	}

}

/**
 * _read - readfile
 * @argv: arguements
 */

void _read(char argv[])
{
	FILE *fp;
	char lines[100][100];
	int line_count = 0;
	int i;

	fp = fopen(argv, "r");
	if (fp == NULL)
	{
		printf("Error opening the file.\n");
		return;
	}

	while (fgets(lines[line_count], 100, fp) != NULL && line_count < 100)
	{
		line_count++;
	}

	fclose(fp);
	for (i = 0; i < line_count; i++)
	{
		if (strlen(lines[i]) < 20)
		{
			long long int num = strtoll(lines[i], NULL, 10);

			calculate(num);
		} else
		{
			mpz_t num;

			mpz_init(num);
			mpz_set_str(num, lines[i], 10);
			calculate_long(num);
			mpz_clear(num);
		}
	}
}

/**
 * main - entry point
 * @argc: number of args
 * @argv: array of args
 * Return: 1 on success, 0 on fail.
 */

int main(int argc, char *argv[])
{
	int i;

	if (argc == 1)
	{
		printf("No arguments provided.\n");
		return (1);
	}
	for (i = 1; i < argc; i++)
		_read(argv[i]);
	return (0);
}
