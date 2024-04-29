
#include "IDL.h"
#include <stdio.h>

float compute_7(char *host, float a, float b, char op)
{
	CLIENT *clnt;
	float *result_1;
	values add_7_arg;
	float *result_2;
	values sub_7_arg;
	float *result_3;
	values mul_7_arg;
	float *result_4;
	values div_7_arg;
	float *result_5;
	values pow_7_arg;

	if (op == '+')
	{

		add_7_arg.num1 = a;
		add_7_arg.num2 = b;
		add_7_arg.operation = op;

		clnt = clnt_create(host, COMPUTE, COMPUTE_VERS, "udp");
		if (clnt == NULL)
		{
			clnt_pcreateerror(host);
			exit(1);
		}

		result_1 = add_7(&add_7_arg, clnt);
		if (result_1 == (float *)NULL)
		{
			clnt_perror(clnt, "call failed");
		}

		clnt_destroy(clnt);

		return (*result_1);
	}

	else if (op == '-')
	{
		sub_7_arg.num1 = a;
		sub_7_arg.num2 = b;
		sub_7_arg.operation = op;

		clnt = clnt_create(host, COMPUTE, COMPUTE_VERS, "udp");
		if (clnt == NULL)
		{
			clnt_pcreateerror(host);
			exit(1);
		}

		result_2 = sub_7(&sub_7_arg, clnt);
		if (result_2 == (float *)NULL)
		{
			clnt_perror(clnt, "call failed");
		}

		clnt_destroy(clnt);

		return (*result_2);
	}

	else if (op == '*')
	{
		mul_7_arg.num1 = a;
		mul_7_arg.num2 = b;
		mul_7_arg.operation = op;

		clnt = clnt_create(host, COMPUTE, COMPUTE_VERS, "udp");
		if (clnt == NULL)
		{
			clnt_pcreateerror(host);
			exit(1);
		}

		result_3 = mul_7(&mul_7_arg, clnt);
		if (result_3 == (float *)NULL)
		{
			clnt_perror(clnt, "call failed");
		}

		clnt_destroy(clnt);

		return (*result_3);
	}

	else if (op == '/')
	{
		if (b == 0)
		{
			printf("You are trying to divide by zero. Please insert a valid number.\n");
			exit(0);
		}
		else
		{
			div_7_arg.num1 = a;
			div_7_arg.num2 = b;
			div_7_arg.operation = op;

			clnt = clnt_create(host, COMPUTE, COMPUTE_VERS, "udp");
			if (clnt == NULL)
			{
				clnt_pcreateerror(host);
				exit(1);
			}

			result_4 = div_7(&div_7_arg, clnt);
			if (result_4 == (float *)NULL)
			{
				clnt_perror(clnt, "call failed");
			}

			clnt_destroy(clnt);

			return (*result_4);
		}
	}

	else if (op == '^')
	{
		pow_7_arg.num1 = a;
		pow_7_arg.num2 = b;
		pow_7_arg.operation = op;

		clnt = clnt_create(host, COMPUTE, COMPUTE_VERS, "udp");
		if (clnt == NULL)
		{
			clnt_pcreateerror(host);
			exit(1);
		}

		result_5 = pow_7(&pow_7_arg, clnt);
		if (result_5 == (float *)NULL)
		{
			clnt_perror(clnt, "call failed");
		}

		clnt_destroy(clnt);

		return (*result_5);
	}

	else
	{
		printf("Invalid operation. Please insert a valid operation.\n");
		exit(0);
	}
}

int main(int argc, char *argv[])
{
	char *host;

	float number1, number2;
	char oper;
	printf("Enter the 2 numbers followed by the operation to perform:\n");
	scanf("%f", &number1);
	scanf("%f", &number2);
	scanf("%s", &oper);

	host = argv[1];
	printf("Answer= %f\n", compute_7(host, number1, number2, oper));
	exit(0);
}