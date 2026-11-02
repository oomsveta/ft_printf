#include "cmocka.h"
#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// ("%#.0x", 0) -> ""
// ("%#.0X", 0) -> ""
// ("% .0i", 0) -> " "
// ("%+.0i", 0) -> "+"
// ("%03.2i", 1) -> " 01"
// 

static void test_ft_printf_percent(void **state)
{
    (void)state;

    int pipe_ends[2];
    char buffer[64] = {0};
    assert_int_equal(0, pipe(pipe_ends));
    const int read_end  = pipe_ends[0];
    const int write_end = pipe_ends[1];
    const int og_stdout = dup(STDOUT_FILENO);
    assert_int_not_equal(og_stdout, -1);
    assert_int_not_equal(dup2(write_end, STDOUT_FILENO), -1);

    int res = ft_printf("percent: %%");

    close(write_end);
    assert_int_not_equal(dup2(og_stdout, STDOUT_FILENO), -1);
    close(og_stdout);
    read(read_end, buffer, sizeof buffer);
    close(read_end);

    assert_int_equal(res, 10);
    assert_string_equal(buffer, "percent: %");
}

static void test_ft_printf_int_min(void **state)
{
    (void)state;

    int pipe_ends[2];
    char buffer[64] = {0};
    assert_int_equal(0, pipe(pipe_ends));
    const int read_end  = pipe_ends[0];
    const int write_end = pipe_ends[1];
    const int og_stdout = dup(STDOUT_FILENO);
    assert_int_not_equal(og_stdout, -1);
    assert_int_not_equal(dup2(write_end, STDOUT_FILENO), -1);

    int res = ft_printf("%i", INT_MIN);

    close(write_end);
    assert_int_not_equal(dup2(og_stdout, STDOUT_FILENO), -1);
    close(og_stdout);
    read(read_end, buffer, sizeof buffer);
    close(read_end);

    char expected[32];
    snprintf(expected, sizeof expected, "%i", INT_MIN);
    assert_string_equal(buffer, expected);
    assert_int_equal(res, strlen(expected));
}

static void test_ft_printf_int_max(void **state)
{
    (void)state;

    int pipe_ends[2];
    char buffer[64] = {0};
    assert_int_equal(0, pipe(pipe_ends));
    const int read_end  = pipe_ends[0];
    const int write_end = pipe_ends[1];
    const int og_stdout = dup(STDOUT_FILENO);
    assert_int_not_equal(og_stdout, -1);
    assert_int_not_equal(dup2(write_end, STDOUT_FILENO), -1);

    int res = ft_printf("%i", INT_MAX);

    close(write_end);
    assert_int_not_equal(dup2(og_stdout, STDOUT_FILENO), -1);
    close(og_stdout);
    read(read_end, buffer, sizeof buffer);
    close(read_end);

    char expected[32];
    snprintf(expected, sizeof expected, "%i", INT_MAX);
    assert_string_equal(buffer, expected);
    assert_int_equal(res, strlen(expected));
}

static void test_ft_printf_int_padded(void **state)
{
    (void)state;

    int pipe_ends[2];
    char buffer[64] = {0};
    assert_int_equal(0, pipe(pipe_ends));
    const int read_end  = pipe_ends[0];
    const int write_end = pipe_ends[1];
    const int og_stdout = dup(STDOUT_FILENO);
    assert_int_not_equal(og_stdout, -1);
    assert_int_not_equal(dup2(write_end, STDOUT_FILENO), -1);

    int res = ft_printf("%23i", INT_MIN);

    close(write_end);
    assert_int_not_equal(dup2(og_stdout, STDOUT_FILENO), -1);
    close(og_stdout);
    read(read_end, buffer, sizeof buffer);
    close(read_end);

    char expected[64];
    snprintf(expected, sizeof expected, "%23i", INT_MIN);
    assert_string_equal(buffer, expected);
    assert_int_equal(res, strlen(expected));
}

static void test_ft_printf_int_precision(void **state)
{
    (void)state;

    int pipe_ends[2];
    char buffer[64] = {0};
    assert_int_equal(0, pipe(pipe_ends));
    const int read_end  = pipe_ends[0];
    const int write_end = pipe_ends[1];
    const int og_stdout = dup(STDOUT_FILENO);
    assert_int_not_equal(og_stdout, -1);
    assert_int_not_equal(dup2(write_end, STDOUT_FILENO), -1);

    int res = ft_printf("%.3i", 7);

    close(write_end);
    assert_int_not_equal(dup2(og_stdout, STDOUT_FILENO), -1);
    close(og_stdout);
    read(read_end, buffer, sizeof buffer);
    close(read_end);

    assert_string_equal(buffer, "007");
    assert_int_equal(res, 3);
}

static void test_ft_printf_int_precision_and_width(void **state)
{
    (void)state;

    int pipe_ends[2];
    char buffer[64] = {0};
    assert_int_equal(0, pipe(pipe_ends));
    const int read_end  = pipe_ends[0];
    const int write_end = pipe_ends[1];
    const int og_stdout = dup(STDOUT_FILENO);
    assert_int_not_equal(og_stdout, -1);
    assert_int_not_equal(dup2(write_end, STDOUT_FILENO), -1);

    int res = ft_printf("%5.3i", 7);

    close(write_end);
    assert_int_not_equal(dup2(og_stdout, STDOUT_FILENO), -1);
    close(og_stdout);
    read(read_end, buffer, sizeof buffer);
    close(read_end);

    assert_string_equal(buffer, "  007");
    assert_int_equal(res, 5);
}

static void test_ft_printf_int_plus_flag(void **state)
{
    (void)state;

    int pipe_ends[2];
    char buffer[64] = {0};
    assert_int_equal(0, pipe(pipe_ends));
    const int read_end  = pipe_ends[0];
    const int write_end = pipe_ends[1];
    const int og_stdout = dup(STDOUT_FILENO);
    assert_int_not_equal(og_stdout, -1);
    assert_int_not_equal(dup2(write_end, STDOUT_FILENO), -1);

    int res = ft_printf("%+i %+d", 42, 0);

    close(write_end);
    assert_int_not_equal(dup2(og_stdout, STDOUT_FILENO), -1);
    close(og_stdout);
    read(read_end, buffer, sizeof buffer);
    close(read_end);

    assert_string_equal(buffer, "+42 +0");
    assert_int_equal(res, 6);
}

static void test_ft_printf_empty_string(void **state)
{
    (void)state;

    int pipe_ends[2];
    char buffer[64] = {0};
    assert_int_equal(0, pipe(pipe_ends));
    const int read_end  = pipe_ends[0];
    const int write_end = pipe_ends[1];
    const int og_stdout = dup(STDOUT_FILENO);
    assert_int_not_equal(og_stdout, -1);
    assert_int_not_equal(dup2(write_end, STDOUT_FILENO), -1);

    int res = ft_printf("");

    close(write_end);
    assert_int_not_equal(dup2(og_stdout, STDOUT_FILENO), -1);
    close(og_stdout);
    read(read_end, buffer, sizeof buffer);
    close(read_end);

    assert_int_equal(res, 0);
    assert_string_equal(buffer, "");
}

static void test_ft_printf_extra_arguments_are_ignored(void **state)
{
    (void)state;

    int pipe_ends[2];
    char buffer[64] = {0};
    assert_int_equal(0, pipe(pipe_ends));
    const int read_end  = pipe_ends[0];
    const int write_end = pipe_ends[1];
    const int og_stdout = dup(STDOUT_FILENO);
    dup2(write_end, STDOUT_FILENO);

    int res = ft_printf("shrek", 1, 2, 3);

    close(write_end);
    dup2(og_stdout, STDOUT_FILENO);
    close(og_stdout);
    read(read_end, buffer, sizeof buffer);
    close(read_end);

    assert_int_equal(res, 5);
    assert_string_equal(buffer, "shrek");
}

static void test_ft_printf_unknown_type_does_not_crash(void **state)
{
    (void)state;

    int pipe_ends[2];
    assert_int_equal(0, pipe(pipe_ends));
    const int read_end  = pipe_ends[0];
    const int write_end = pipe_ends[1];
    const int og_stdout = dup(STDOUT_FILENO);
    assert_int_not_equal(og_stdout, -1);
    assert_int_not_equal(dup2(write_end, STDOUT_FILENO), -1);

    ft_printf("%;");

    close(write_end);
    assert_int_not_equal(dup2(og_stdout, STDOUT_FILENO), -1);
    close(og_stdout);
    close(read_end);

    // No assertions. If it doesn't crash it's good.
}

static void test_ft_printf_format_ends_on_incomplete_spec(void **state)
{
    (void)state;

    int pipe_ends[2];
    assert_int_equal(0, pipe(pipe_ends));
    const int read_end  = pipe_ends[0];
    const int write_end = pipe_ends[1];
    const int og_stdout = dup(STDOUT_FILENO);
    assert_int_not_equal(og_stdout, -1);
    assert_int_not_equal(dup2(write_end, STDOUT_FILENO), -1);

    ft_printf("%");

    close(write_end);
    assert_int_not_equal(dup2(og_stdout, STDOUT_FILENO), -1);
    close(og_stdout);
    close(read_end);

    // No assertions. If it doesn't crash it's good.
}

/**
 * If no l length modifier is present, the int argument is converted to an
 * unsigned char, and the resulting character is written.
 */
static void test_ft_printf_c_conversion(void **state)
{
    (void)state;

    int pipe_ends[2];
    char buffer[64] = {0};
    assert_int_equal(0, pipe(pipe_ends));
    const int read_end  = pipe_ends[0];
    const int write_end = pipe_ends[1];
    const int og_stdout = dup(STDOUT_FILENO);
    dup2(write_end, STDOUT_FILENO);

    int res = ft_printf("%c%c", INT_MAX, -180);

    close(write_end);
    dup2(og_stdout, STDOUT_FILENO);
    close(og_stdout);
    read(read_end, buffer, sizeof buffer);
    close(read_end);

    assert_int_equal(res, 2);
    assert_string_equal(buffer, "\xffL");
}

static void test_ft_printf_c_null_byte(void **state)
{
    (void)state;

    int pipe_ends[2];
    char buffer[64] = {0};
    buffer[0] = 'x';
    assert_int_equal(0, pipe(pipe_ends));
    const int read_end  = pipe_ends[0];
    const int write_end = pipe_ends[1];
    const int og_stdout = dup(STDOUT_FILENO);
    dup2(write_end, STDOUT_FILENO);

    int res = ft_printf("%c", '\0');

    close(write_end);
    dup2(og_stdout, STDOUT_FILENO);
    close(og_stdout);
    read(read_end, buffer, sizeof buffer);
    close(read_end);

    assert_int_equal(res, 1);
    assert_string_equal(buffer, "");
}

int run_ft_printf_tests(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_ft_printf_percent),
        cmocka_unit_test(test_ft_printf_int_max),
        cmocka_unit_test(test_ft_printf_int_min),
        cmocka_unit_test(test_ft_printf_empty_string),
        cmocka_unit_test(test_ft_printf_extra_arguments_are_ignored),
        cmocka_unit_test(test_ft_printf_unknown_type_does_not_crash),
        cmocka_unit_test(test_ft_printf_format_ends_on_incomplete_spec),
        cmocka_unit_test(test_ft_printf_int_padded),
        cmocka_unit_test(test_ft_printf_int_precision),
        cmocka_unit_test(test_ft_printf_int_precision_and_width),
        cmocka_unit_test(test_ft_printf_int_plus_flag),
        cmocka_unit_test(test_ft_printf_c_conversion),
        cmocka_unit_test(test_ft_printf_c_null_byte),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
