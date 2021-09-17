#include <cmoc.h>
#include "extramfl.h"


int main(void)
{
	char value_a[] = "-4.2565";
	char value_b[] = "3.14156265";
	char value_c[] = "1.5";
	char value_d[] = "456.12";
	
	printf("%04x %c%c", static_buffer, 10, 13);
	
	struct float_struct fl_result_a;
	struct float_struct fl_result_b;
	struct float_struct fl_result_c;
	struct float_struct fl_result_d;
	
	init_extra();
	
	fin(value_a, &fl_result_a);
	print_float(&fl_result_a);
	
	fin(value_b, &fl_result_b);
	print_float(&fl_result_b);

	binary_op(&fl_result_a, &fl_result_b, &fl_result_c, ADDGO);
	
	print_float(&fl_result_a);
	print_float(&fl_result_b);
	print_float(&fl_result_c);
	char *result = pufout(&fl_result_c);
	printf("%c%c>%s<%c%c", 10, 13, result, 10, 13);
	
	unary_op(&fl_result_c, &fl_result_a, NEGGO);
	print_float(&fl_result_a);
	result = pufout(&fl_result_a);
	printf("%c%c>%s<%c%c", 10, 13, result, 10, 13);
	
	memcpy(&fl_result_b, &fl_result_a, 6);
	print_float(&fl_result_b);
	
	fin(value_b, &fl_result_b);
	print_float(&fl_result_b);
	result = pufout(&fl_result_b);
	printf("%c%c>%s<%c%c", 10, 13, result, 10, 13);
	unary_op(&fl_result_b, &fl_result_c, COS);
	print_float(&fl_result_c);
	result = pufout(&fl_result_c);
	printf("%c%c>%s<%c%c", 10, 13, result, 10, 13);
	
	fin(value_d, &fl_result_d);
	print_float(&fl_result_d);
	unsigned int val = to_unsigned_int(&fl_result_d);
	printf("%c%c>%u<%c%c", 10, 13, val, 10, 13);
	
	fin(value_a, &fl_result_a);
	print_float(&fl_result_a);
	int signed_val = to_int(&fl_result_a);
	printf("%c%c>%d<%c%c", 10, 13, signed_val, 10, 13);
		
	return 0;
}
