#include "IDL.h"
#include <stdio.h>

float *
add_7_svc(values *argp, struct svc_req *rqstp)
{
	static float  result;
	result = argp->num1 + argp->num2;
	return &result;
}

float *
sub_7_svc(values *argp, struct svc_req *rqstp)
{
	static float  result;
	result = argp->num1 - argp->num2;
	return &result;
}

float *
mul_7_svc(values *argp, struct svc_req *rqstp)
{
	static float  result;
	result = argp->num1 * argp->num2;
	return &result;
}

float *
div_7_svc(values *argp, struct svc_req *rqstp)
{
	static float  result;
	result = argp->num1 / argp->num2;
	return &result;
}

float *
pow_7_svc(values *argp, struct svc_req *rqstp)
{
	static float  result;

	for (int i=0; i<argp->num2; i++)
	{
		result = result * argp->num1;
	}
	return &result;
}

