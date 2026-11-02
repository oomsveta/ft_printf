#include "cmocka.h"
#include "ft_printf.h"
#include <unistd.h>

static void test_ft_printf_percent_width(void **state)
{
    (void)state;

    char buffer[64] = {0};
    int pipe_ends[2];
    assert_int_equal(0, pipe(pipe_ends));
    const int read_end  = pipe_ends[0];
    const int write_end = pipe_ends[1];
    const int og_stdout = dup(STDOUT_FILENO);
    dup2(write_end, STDOUT_FILENO);

    int res = ft_printf("%5%");

    close(write_end);
    dup2(og_stdout, STDOUT_FILENO);
    close(og_stdout);
    read(read_end, buffer, sizeof buffer);
    close(read_end);

    assert_int_equal(res, 5);
    assert_string_equal(buffer, "    %");
}

static void test_ft_printf_unknown_type(void **state)
{
    (void)state;

    char buffer[64] = {0};
    int pipe_ends[2];
    assert_int_equal(0, pipe(pipe_ends));
    const int read_end  = pipe_ends[0];
    const int write_end = pipe_ends[1];
    const int og_stdout = dup(STDOUT_FILENO);
    assert_int_not_equal(og_stdout, -1);
    assert_int_not_equal(dup2(write_end, STDOUT_FILENO), -1);

    int res = ft_printf("%; %%");

    close(write_end);
    dup2(og_stdout, STDOUT_FILENO);
    close(og_stdout);
    read(read_end, buffer, sizeof buffer);
    close(read_end);

    // My behavior choice: printf prints the conversion spec as is and
    // continues the formatting as normal.
    assert_int_equal(res, 4);
    assert_string_equal(buffer, "%; %");
}

static void test_ft_printf_unknown_type_with_flags(void **state)
{
    (void)state;

    char buffer[64] = {0};
    int pipe_ends[2];
    assert_int_equal(0, pipe(pipe_ends));
    const int read_end  = pipe_ends[0];
    const int write_end = pipe_ends[1];
    const int og_stdout = dup(STDOUT_FILENO);
    assert_int_not_equal(og_stdout, -1);
    assert_int_not_equal(dup2(write_end, STDOUT_FILENO), -1);

    int res = ft_printf("% -0#+; %%");

    close(write_end);
    dup2(og_stdout, STDOUT_FILENO);
    close(og_stdout);
    read(read_end, buffer, sizeof buffer);
    close(read_end);

    assert_string_equal(buffer, "%#+-; %");
    assert_int_equal(res, 7);
}

int run_ft_printf_tests_undefined(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_ft_printf_percent_width),
        cmocka_unit_test(test_ft_printf_unknown_type),
        cmocka_unit_test(test_ft_printf_unknown_type_with_flags),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
