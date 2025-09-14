#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <minirt/vec3.h>

void	assert_result(char *name, bool result, bool expected)
{
	if (result == expected)
		printf("%-30s: %s\n", name, "\033[92mSUCCESS\033[0m");
	else
	{
		printf("%-30s: %s\n", name, "\033[91mFAILED\033[0m");
		exit(1);
	}
}

void	test_vec3_abs(void)
{
	const t_vec3 v1 = (t_vec3){2.0, 3.0, 6.0};
	const t_vec3 v2 = (t_vec3){4.0, 6.0, 12.0};
	const t_vec3 v3 = (t_vec3){5.0, 3.0, 8.0};

	const double abs1_1 = vec3_abs(v1);
	const double abs1_2 = 7;
	const double abs2_1 = vec3_abs(v2);
	const double abs2_2 = 14;
	const double abs3_1 = vec3_abs(v3);
	const double abs3_2 = 9.8994;

	assert_result("vec3_abs (case1)", (abs1_1 == abs1_2), true);
	assert_result("vec3_abs (case2)", (abs2_1 == abs2_2), true);
	assert_result("vec3_abs (case3)", (abs3_2 - EPSILON < abs3_1 && abs3_1 < abs3_2 + EPSILON), true);
}

void	test_vec3_dot_prod(void)
{
	const t_vec3 v1 = (t_vec3){2.0, 3.0, 6.0};
	const t_vec3 v2 = (t_vec3){4.0, 6.0, 12.0};

	const double dot_prod1_1 = vec3_dot_prod(v1, v1);
	const double dot_prod1_2 = 49;
	const double dot_prod2_1 = vec3_dot_prod(v2, v2);
	const double dot_prod2_2 = 196;
	const double dot_prod3_1 = vec3_dot_prod(v1, v2);
	const double dot_prod3_2 = 98;

	assert_result("vec3_dot_prod (case1)", (dot_prod1_1 == dot_prod1_2), true);
	assert_result("vec3_dot_prod (case2)", (dot_prod2_1 == dot_prod2_2), true);
	assert_result("vec3_dot_prod (case3)", (dot_prod3_1 == dot_prod3_2), true);
}

void	test_vec3_cross_prod(void)
{
	const t_vec3 v1 = (t_vec3){2.0, 3.0, 6.0};
	const t_vec3 v2 = (t_vec3){4.0, 6.0, 12.0};
	const t_vec3 v3 = (t_vec3){12.5, 8.8, 18.0};

	const t_vec3 cross_prod1 = vec3_cross_prod(v1, v2);
	const t_vec3 cross_prod2 = vec3_cross_prod(v1, v3);
	const t_vec3 cross_prod3 = vec3_cross_prod(v2, v3);

	const double dot_prod1 = vec3_dot_prod(cross_prod1, v1);
	const double dot_prod2 = vec3_dot_prod(cross_prod1, v2);
	const double dot_prod3 = vec3_dot_prod(cross_prod2, v1);
	const double dot_prod4 = vec3_dot_prod(cross_prod2, v3);
	const double dot_prod5 = vec3_dot_prod(cross_prod3, v2);
	const double dot_prod6 = vec3_dot_prod(cross_prod3, v3);

	assert_result("vec3_cross_prod (case1)", (dot_prod1 == 0), true);
	assert_result("vec3_cross_prod (case2)", (dot_prod2 == 0), true);
	assert_result("vec3_cross_prod (case3)", (dot_prod3 == 0), true);
	assert_result("vec3_cross_prod (case4)", (dot_prod4 == 0), true);
	assert_result("vec3_cross_prod (case5)", (dot_prod5 == 0), true);
	assert_result("vec3_cross_prod (case6)", (dot_prod6 == 0), true);
}

void	test_vec3_norm(void)
{
	const t_vec3 v1 = (t_vec3){2.0, 3.0, 6.0};
	const t_vec3 v2 = (t_vec3){4.0, 6.0, 12.0};
	const t_vec3 v3 = (t_vec3){12.5, 8.8, 18.0};

	const t_vec3 norm1 = vec3_norm(v1);
	const t_vec3 norm2 = vec3_norm(v2);
	const t_vec3 norm3 = vec3_norm(v3);

	const double abs1 = vec3_abs(norm1);
	const double abs2 = vec3_abs(norm2);
	const double abs3 = vec3_abs(norm3);
	
	assert_result("vec3_norm (case1)", (1 - EPSILON < abs1 && abs1 < 1 + EPSILON), true);
	assert_result("vec3_norm (case2)", (1 - EPSILON < abs2 && abs2 < 1 + EPSILON), true);
	assert_result("vec3_norm (case3)", (1 - EPSILON < abs3 && abs3 < 1 + EPSILON), true);
}

void	test_vec3_rad(void)
{
	const t_vec3 v1 = (t_vec3){2.0, 3.0, 6.0};
	const t_vec3 v2 = (t_vec3){32.1, 59.9, 1.13};
	const t_vec3 v3 = (t_vec3){12.5, 8.8, 18.0};

	const t_vec3 cross_prod1 = vec3_cross_prod(v1, v2);
	const t_vec3 cross_prod2 = vec3_cross_prod(v1, v3);
	const t_vec3 cross_prod3 = vec3_cross_prod(v2, v3);

	const double rad1 = vec3_rad(cross_prod1, v1);
	const double rad2 = vec3_rad(cross_prod1, v2);
	const double rad3 = vec3_rad(cross_prod2, v1);
	const double rad4 = vec3_rad(cross_prod2, v3);
	const double rad5 = vec3_rad(cross_prod3, v2);
	const double rad6 = vec3_rad(cross_prod3, v3);

	assert_result("vec3_rad (case1)", (0.5 * M_PI - EPSILON < rad1 && rad1 < 0.5 * M_PI + EPSILON), true);
	assert_result("vec3_rad (case2)", (0.5 * M_PI - EPSILON < rad2 && rad2 < 0.5 * M_PI + EPSILON), true);
	assert_result("vec3_rad (case3)", (0.5 * M_PI - EPSILON < rad3 && rad3 < 0.5 * M_PI + EPSILON), true);
	assert_result("vec3_rad (case4)", (0.5 * M_PI - EPSILON < rad4 && rad4 < 0.5 * M_PI + EPSILON), true);
	assert_result("vec3_rad (case5)", (0.5 * M_PI - EPSILON < rad5 && rad5 < 0.5 * M_PI + EPSILON), true);
	assert_result("vec3_rad (case6)", (0.5 * M_PI - EPSILON < rad6 && rad6 < 0.5 * M_PI + EPSILON), true);
}

int	main(void)
{
	test_vec3_abs();
	test_vec3_dot_prod();
	test_vec3_cross_prod();
	test_vec3_norm();
	test_vec3_rad();
}
