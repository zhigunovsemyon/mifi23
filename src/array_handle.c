#include "array_handle.h"
#include "armstrong.h"
#include <assert.h>
#include <malloc.h>
#include <stddef.h>
#include <string.h>

constexpr size_t size_int = sizeof(int);
constexpr int STEP = 32;

int get_array(int ** arr)
{
	if (!arr)
		return -1;

	int len = 0, capacity = 0;
	*arr = nullptr; // Зануление указателя перед началом работы

	do {
		assert(capacity >= 0);
		assert(len >= 0);
		int tmp;
		printf("Введите %d-ое число: ", len + 1);

		/*Если ввод завершён, возврат числа введённых элементов*/
		if (1 != scanf("%d", &tmp))
			return len;

		/*Если место в выделенной памяти заканчивается*/
		if (capacity < len + 1) {
			int * ptr = (int *)realloc(
				*arr, size_int * (size_t)(capacity += STEP));
			if (!ptr) {
				/*Освобождение памяти старого указателя*/
				free(*arr);
				/*Возврат кода ошибки при нехватке памяти*/
				return -1;
			}
			*arr = ptr;
		}

		assert(*arr != nullptr);
		/*Перезапись крайнего элемента*/
		(*arr)[len++] = tmp;

	} while (true);
}

void print_array(int const * arr, int len)
{
	putchar('\n');
	for (int i = 0; i < len; ++i)
		printf("%d ", arr[i]);
	putchar('\n');
}

static enum ArmstongResult armstong_wrap(int n)
{
	int dumb;
	return check_armstrong(n, &dumb);
}

static int sum_of_digits (int num)
{
	int count = count_digits(num);
	int sum = get_nth_digit(num, 0);
	assert(count >= 0);

	for (int i = 1; i < count; ++i)
		sum += get_nth_digit(num,i);

	assert(sum >= 0);
	return sum;
}

bool modify_array(int ** arr, int * plen, int min)
{
	if (!arr || !plen)
		return true;
	if (!(*arr))
		return true;

	for (int *ptr, i = 0; i < *plen; ++i) {
		if (sum_of_digits((*arr)[i]) < min) {
			assert(*plen > 0);
			assert(*plen > i);
			memmove((*arr) + i, (*arr) + i + 1,
				size_int * (size_t)(--(*plen) - i));

			/*Отброс назад на тот же индекс*/
			--i;
			continue;
		}

		/*Если число не является числом Армстронга, переход к
		 * следующему*/
		if (ARMSTRONG_TRUE != armstong_wrap((*arr)[i]))
			continue;

		ptr = (int *)realloc(*arr, size_int * (size_t)(++(*plen)));
		if (!ptr) {
			/*Освобождение памяти старого указателя*/
			free(*arr);
			/*Возврат кода ошибки при нехватке памяти*/
			return true;
		}
		*arr = ptr;
		assert(*arr != nullptr);

		assert((*plen - i - 1) >= 0);
		memmove(*arr + i + 1, *arr + i,
			size_int * (size_t)(*plen - i - 1));
		/* (*arr)[i]=(*arr)[i + 1]; нет нужды из-за работы memmove() */
		i++; /*Перескок на следующий элемент*/
	}
	return false;
}
