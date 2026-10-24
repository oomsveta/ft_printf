int run_parser_tests(void);
int run_writer_tests(void);

int main(void)
{
    int failed_tests = 0;
    failed_tests += run_parser_tests();
    failed_tests += run_writer_tests();
    return failed_tests; 
}
