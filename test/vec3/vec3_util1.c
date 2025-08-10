#include <stdio.h>
#include <stdlib.h>
#include <minirt/vec3.h>

void	assert_result(char *name, bool result, bool expected)
{
	if (result == expected)
		printf("%-20s: %s\n", name, "\033[92mSUCESS\033[0m");
	else
	{
		printf("%-30s: %s\n", name, "\033[91mFAIL\033[0m");
		exit(1);
	}
}

void	test_vec3_init(void)
{
	const t_vec3 v1 = vec3_init(2.0, 3.0, 6.0);
	const t_vec3 v2 = vec3_init(4.0, 6.0, 12.0);

	assert_result("vec3_init (case1)", (v1.x == 2.0 && v1.y == 3.0 && v1.z == 6.0), true);
	assert_result("vec3_init (case2)", (v2.x == 4.0 && v2.y == 6.0 && v2.z == 12.0), true);
	assert_result("vec3_init (case3)", (v2.x == v1.x * 2 && v2.y == v1.y * 2 && v2.z == v1.z * 2), true);
}

void	test_vec3_eq(void)
{
	const t_vec3 v1 = vec3_init(2.0, 3.0, 6.0);
	const t_vec3 v2 = vec3_init(2.0 + EPSILON / 2, 3.0 + EPSILON / 2, 6.0 + EPSILON / 2);
	const t_vec3 v3 = vec3_init(4.0, 3.0, 6.0);
	const t_vec3 v4 = vec3_init(2.0, 6.0, 6.0);
	const t_vec3 v5 = vec3_init(2.0, 3.0, 12.0);
	const t_vec3 v6 = vec3_init(4.0, 6.0, 12.0);

	assert_result("vec3_eq (case1)", vec3_eq(v1, v2), true);
	assert_result("vec3_eq (case2)", vec3_eq(v1, v3), false);
	assert_result("vec3_eq (case3)", vec3_eq(v1, v4), false);
	assert_result("vec3_eq (case4)", vec3_eq(v1, v5), false);
	assert_result("vec3_eq (case5)", vec3_eq(v1, v6), false);
}

void	test_vec3_add(void)
{
	const t_vec3 v1_1 = vec3_init(2.0, 3.0, 6.0);
	const t_vec3 v1_2 = vec3_init(4.0, 6.0, 12.0);
	const t_vec3 v1_3 = vec3_init(6.0, 9.0, 18.0);
	const t_vec3 v1_4 = vec3_add(v1_1, v1_2);

	const t_vec3 v2_1 = vec3_init(3.8, 15.4, 12.3);
	const t_vec3 v2_2 = vec3_init(-3.8, -15.4, -12.3);
	const t_vec3 v2_3 = vec3_init(0, 0, 0);
	const t_vec3 v2_4 = vec3_add(v2_1, v2_2);

	assert_result("vec3_add (case1)", vec3_eq(v1_3, v1_4), true);
	assert_result("vec3_add (case2)", vec3_eq(v2_3, v2_4), true);
}

void	test_vec3_sub(void)
{
	const t_vec3 v1_1 = vec3_init(2.0, 3.0, 6.0);
	const t_vec3 v1_2 = vec3_init(4.0, 6.0, 12.0);
	const t_vec3 v1_3 = vec3_init(-2.0, -3.0, -6.0);
	const t_vec3 v1_4 = vec3_sub(v1_1, v1_2);

	const t_vec3 v2_1 = vec3_init(3.8, 15.4, 12.3);
	const t_vec3 v2_2 = vec3_init(-3.8, -15.4, -12.3);
	const t_vec3 v2_3 = vec3_init(7.6, 30.8, 24.6);
	const t_vec3 v2_4 = vec3_sub(v2_1, v2_2);

	assert_result("vec3_sub (case1)", vec3_eq(v1_3, v1_4), true);
	assert_result("vec3_sub (case2)", vec3_eq(v2_3, v2_4), true);
}

void	test_vec3_mult(void)
{
	const t_vec3 v1_1 = vec3_init(2.0, 3.0, 6.0);
	const t_vec3 v1_2 = vec3_init(4.0, 6.0, 12.0);
	const t_vec3 v1_3 = vec3_mult(2, v1_1);

	const t_vec3 v2_1 = vec3_init(3.8, 15.4, 12.3);
	const t_vec3 v2_2 = vec3_init(38, 154, 123);
	const t_vec3 v2_3 = vec3_mult(10, v2_1);

	const t_vec3 v3_1 = vec3_init(30, 64, 22);
	const t_vec3 v3_2 = vec3_init(-15, -32, -11);
	const t_vec3 v3_3 = vec3_mult(-0.5, v3_1);

	assert_result("vec3_mult (case1)", vec3_eq(v1_2, v1_3), true);
	assert_result("vec3_mult (case2)", vec3_eq(v2_2, v2_3), true);
	assert_result("vec3_mult (case3)", vec3_eq(v3_2, v3_3), true);
}

int	main(void)
{
	printf("[vec3_util1]\n");
	test_vec3_init();
	test_vec3_eq();
	test_vec3_add();
	test_vec3_sub();
	test_vec3_mult();
	printf("\n");
}
