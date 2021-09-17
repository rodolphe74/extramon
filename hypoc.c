#include <cmoc.h>
#include "extramfl.h"
#include "extramgr.h"

int main()
{
	char str_loop_start[] = "0.0";
	char str_loop_end[] = "31.4159256";
	char str_inc[] = "0.2";
	char str_un[] = "1.0";
	char str_r[] = "50.0";
	char str_big_r[] = "80.0";
	int first_loop = 1;

	
	struct float_struct fl_loop_start;
	struct float_struct fl_loop_end;
	struct float_struct fl_inc;
	struct float_struct fl_un;
	struct float_struct fl_r;
	struct float_struct fl_big_r;
	struct float_struct fl_x;
	struct float_struct fl_y;
	struct float_struct fl_last_x;
	struct float_struct fl_last_y;
	struct float_struct fl_q;
	struct float_struct fl_q_moins_un;
	struct float_struct fl_q_moins_un_mul_theta;
	struct float_struct fl_res_a;
	struct float_struct fl_res_b;
	
	init_extra();
	
	fin(str_loop_start, &fl_loop_start);
	fin(str_loop_end, &fl_loop_end);
	fin(str_inc, &fl_inc);
	fin(str_un, &fl_un);
	fin(str_r, &fl_r);
	fin(str_big_r, &fl_big_r);
	
	binary_op(&fl_r, &fl_big_r, &fl_q, DIVGO);	/* R/r */
	
	while (cmp(&fl_loop_start, &fl_loop_end) < 0) {
		
		// q-1 > fl_q_moins_un
		binary_op(&fl_un, &fl_q, &fl_q_moins_un, SUBGO);
		
		
		// (q-1)*loop > fl_q_moins_un_mul_theta
		binary_op(&fl_q_moins_un, &fl_loop_start, 
			&fl_q_moins_un_mul_theta, MULTGO);
		
		// cos((q-1)*loop) > fl_res_a
		unary_op(&fl_q_moins_un_mul_theta, &fl_res_a, COS);
		
		// cos(loop) > fl_res_b
		unary_op(&fl_loop_start, &fl_res_b, COS);
		
		// (q-1)*cos(loop) > fl_res_b
		binary_op(&fl_q_moins_un, &fl_res_b, &fl_res_b, MULTGO);
		
		// fl_res_a + fl_res_b > fl_res_a
		binary_op(&fl_res_a, &fl_res_b, &fl_res_a, ADDGO);
		
		// r*fl_res_a > fl_x
		binary_op(&fl_r, &fl_res_a, &fl_x, MULTGO);
		
		
		
		// sin((q-1)*loop) > fl_res_a
		unary_op(&fl_q_moins_un_mul_theta, &fl_res_b, SIN);
		
		// sin(loop) > fl_res_b
		unary_op(&fl_loop_start, &fl_res_a, SIN);
		
		// (q-1)*sin(loop) > fl_res_b
		binary_op(&fl_q_moins_un, &fl_res_a, &fl_res_a, MULTGO);
		
		binary_op(&fl_res_b, &fl_res_a, &fl_res_a, SUBGO);
		
		// r*fl_res_a > fl_y
		binary_op(&fl_r, &fl_res_a, &fl_y, MULTGO);
		
	
		if (first_loop) {
			pset(to_int(&fl_x) + 160, to_int(&fl_y) + 100);
			first_loop = 0;
		} else {
			line(to_int(&fl_last_x) + 160, to_int(&fl_last_y) + 100, 
				to_int(&fl_x) + 160, to_int(&fl_y) + 100);
		}
		
		fl_last_x = fl_x;
		fl_last_y = fl_y;
		
		binary_op(&fl_loop_start, &fl_inc, &fl_loop_start, ADDGO);
	}
	
	return 0;
}
