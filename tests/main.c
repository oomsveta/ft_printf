int run_parser_tests(void);
int run_writer_tests(void);
int run_ft_printf_tests(void);
int run_ft_printf_tests_undefined(void);

int main(void)
{
    int failed_tests = 0;
    failed_tests += run_parser_tests();
    failed_tests += run_writer_tests();
    failed_tests += run_ft_printf_tests();
    failed_tests += run_ft_printf_tests_undefined();
    return failed_tests; 
}
