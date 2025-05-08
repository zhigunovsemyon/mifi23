#include "armstrong.h"
#include <assert.h>

int count_digits(int n)
{
	int res = 1;
	while (n >= 10)
		n /= 10, ++res;

	assert(res > 0);
	return res;
}

static int powi(int n, int p)
{
	int res = 1;
	while (p-- > 0)
		res *= n;

	return res;
}

/*Отсчёт идёт от 0, от младших разрядов к старшим.
 * Не предусматривает проверки на корректность*/
int get_nth_digit(int n, int i)
{
	return (n / powi(10, i)) % 10;
}

enum ArmstongResult check_armstrong(int num, int * sum)
{
	if (num < 0)
		return ARMSTRONG_FAIL;

	int dig_count = count_digits(num);
	*sum = powi(get_nth_digit(num, 0), dig_count);

	for (int i = dig_count - 1; i > 0; i--)
		*sum += powi(get_nth_digit(num, i), dig_count);

	if (*sum < 0)
		return ARMSTRONG_FAIL;

	return (num == *sum) ? ARMSTRONG_TRUE : ARMSTRONG_FALSE;
}
