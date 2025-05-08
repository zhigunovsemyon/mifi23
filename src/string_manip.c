#include "string_manip.h"
#include "array_handle.h"
#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

constexpr size_t size_int = sizeof(int);
constexpr int STEP = 32;

// INT_MIN = -2147483648

static char * nums_to_string(int const * nums, int count)
{
	if (!nums)
		return nullptr;

	char * ret = nullptr;
	size_t len = 1 // длина массива с \0
		,
	       capacity = 0; // максимальная ёмкость массива
	for (int i = 0; i < count; ++i) {
		char buf[12]; // 12 -- длина INT_MIN со знаком и \0
		sprintf(buf, "%d ", nums[i]);

		/*Если место в выделенной памяти заканчивается*/
		if (capacity < len + strlen(buf)) {
			char * ptr = (char *)realloc(
				ret, size_int * (size_t)(capacity += STEP));
			if (!ptr) {
				/*Освобождение памяти старого указателя*/
				free(ret);
				/*Возврат кода ошибки при нехватке памяти*/
				return nullptr;
			}
			ret = ptr;
			/*Зануление новой памяти*/
			memset(ret + len - 1, 0, capacity - len - 1);
		}

		assert(ret != nullptr);

		len += strlen(buf);
		strcat(ret, buf);

		assert(len == 1 + strlen(ret));
	}
	return ret;
}

ssize_t getline_wrap(char ** restrict lineptr, FILE * restrict stream)
{
	size_t dumb;
	return getline(lineptr, &dumb, stream);
}

char * modify_string(char const * line, int min)
{
	if (!line)
		return nullptr;

	int * nums;
	int count = get_array(&nums, line);
	if (count < 0) {
		free(nums);
		return nullptr;
	}

	if (modify_array(&nums, &count, min)) {
		free(nums);
		return nullptr;
	}

	/*Если ни одного числа не осталось -- возврат пустой строки*/
	if (count == 0) {
		free(nums);
		return (char *)calloc(1, sizeof(char));
	}

	char * newstr = nums_to_string(nums, count);

	free(nums);
	return newstr;
}
