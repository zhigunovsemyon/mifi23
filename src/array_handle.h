#ifndef ARRAY_HANDLE_H_
#define ARRAY_HANDLE_H_

/* Получение из строки массива целых чисел.
 * Выделяет память, перезаписывает переданный указатель.
 * Возвращает размер массива, либо -1 при ошибке*/
int get_array (int **, char const *);

void print_array (int const *, int len);

/*Модификация массива в соответствии с задачей*/
bool modify_array(int **, int * plen, int min);

#endif 
