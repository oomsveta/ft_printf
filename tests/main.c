int run_parser_tests(void);

int main(void)
{
    int failed_tests = 0;
    failed_tests += run_parser_tests();
    return failed_tests; 
}
