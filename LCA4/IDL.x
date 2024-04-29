struct values{
    float num1;
    float num2;
    char operation;
};

/*Programme, version and procedure definition*/

program COMPUTE{
    version COMPUTE_VERS{
        float ADD(values) =1;
        float SUB(values)=2;
	    float MUL(values)=3;
	    float DIV(values)=4;
        float POW(values)=5;
    } =7;

} = 456123789;