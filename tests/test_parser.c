#include "cmocka.h"
#include "ft_printf_internals.h"
#include <limits.h>
#include <stdarg.h>
#include <string.h>

static t_ctx init_ctx(const char *cursor)
{
    t_ctx ctx = {0};
    ctx.current_specifier.cursor = cursor;
    return ctx;
}

static void test_parse_flags_multiple_flags(void **state)
{
    (void)state;

    t_ctx ctx = init_ctx("-+#d");
    parse_flags(&ctx);

    t_flags expected = (t_flags){
        .left_justify = true,           // -
        .force_sign = true,             // +
        .alternate_form = true,         // #
        .reserve_sign_space = false,    // space
        .pad_with_zeros = false,        // 0
    };
    t_flags obtained = ctx.current_specifier.flags;
    assert_memory_equal(&expected, &obtained, sizeof(t_flags));
}

static void test_parse_flags_plus_beats_space(void **state)
{
    (void)state;

    t_ctx ctx = init_ctx(" + d");
    parse_flags(&ctx);

    t_flags flags = ctx.current_specifier.flags;
    assert_true(flags.force_sign);          // +
    assert_false(flags.reserve_sign_space); // space
}

static void test_parse_flags_minus_beats_zero(void **state)
{
    (void)state;

    t_ctx ctx = init_ctx("0-0d");
    parse_flags(&ctx);

    t_flags flags = ctx.current_specifier.flags;
    assert_true(flags.left_justify);    // -
    assert_false(flags.pad_with_zeros); // 0
}

static void test_parse_flags_skips_unsupported_flags(void **state)
{
    (void)state;

    t_ctx ctx = init_ctx("I'+d");
    parse_flags(&ctx);

    t_flags flags = ctx.current_specifier.flags;
    // if + is reached it means I and ' have been skipped
    assert_true(flags.force_sign);
}

static void test_parse_flags_does_nothing_on_empty_string(void **state)
{
    (void)state;

    t_ctx ctx = init_ctx("");
    parse_flags(&ctx);

    t_flags flags = ctx.current_specifier.flags;
    assert_memory_equal(&(t_flags){0}, &flags, sizeof(t_flags));
}

static void test_parse_width_basic(void **state)
{
    (void)state;

    const char *format_str = "1337d";
    t_ctx ctx = init_ctx(format_str);
    parse_width(&ctx);

    assert_int_equal(1337, ctx.current_specifier.width);
    assert_ptr_equal(strchr(format_str, 'd'), ctx.current_specifier.cursor);
}

static void test_parse_width_overflow(void **state)
{
    (void)state;

    t_ctx ctx = init_ctx("99999999999999999999999d");
    parse_width(&ctx);

    assert_int_equal(0, ctx.current_specifier.width);
    assert_int_equal(ERR_WIDTH_OVERFLOW, ctx.errno);
}

typedef bool (*t_parser_fn)(t_ctx *ctx);

static void call_with_va_args(t_parser_fn fn, t_ctx *ctx, ...)
{
    va_start(ctx->args, ctx);
    fn(ctx);
    va_end(ctx->args);
}

static void test_parse_width_from_args_basic(void **state)
{
    (void)state;

    const char *format_str = "*d";
    t_ctx ctx = init_ctx(format_str);

    call_with_va_args(parse_width, &ctx, 10);

    assert_int_equal(10, ctx.current_specifier.width);
    assert_ptr_equal(strchr(format_str, 'd'), ctx.current_specifier.cursor);
}

static void test_parse_width_from_args_negative_val(void **state)
{
    (void)state;

    const char *format_str = "*d";
    t_ctx ctx = init_ctx(format_str);

    call_with_va_args(parse_width, &ctx, -10);

    assert_true(ctx.current_specifier.flags.left_justify);
    assert_int_equal(10, ctx.current_specifier.width);
    assert_ptr_equal(strchr(format_str, 'd'), ctx.current_specifier.cursor);
}

static void test_parse_width_from_args_int_min(void **state)
{
    (void)state;

    t_ctx ctx = init_ctx("*d");

    call_with_va_args(parse_width, &ctx, INT_MIN);

    assert_true(ctx.current_specifier.flags.left_justify);
    assert_int_equal(0, ctx.current_specifier.width);
    assert_int_equal(ctx.errno, ERR_WIDTH_OVERFLOW);
}

static void test_parse_width_from_args_neg_disables_zero_flag(void **state)
{
    (void)state;

    const char *format_str = "*d";
    t_ctx ctx = init_ctx(format_str);
    ctx.current_specifier.flags.pad_with_zeros = true;  // set '0' flag

    call_with_va_args(parse_width, &ctx, -42);

    // Providing a negative width is equivalent to setting the '-' flag.
    assert_true(ctx.current_specifier.flags.left_justify);
    // '-' flag is incompatible with '0' flag. If both are defined, '-' wins.
    assert_false(ctx.current_specifier.flags.pad_with_zeros);
    assert_int_equal(42, ctx.current_specifier.width);
    assert_ptr_equal(strchr(format_str, 'd'), ctx.current_specifier.cursor);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_parse_flags_multiple_flags),
        cmocka_unit_test(test_parse_flags_plus_beats_space),
        cmocka_unit_test(test_parse_flags_minus_beats_zero),
        cmocka_unit_test(test_parse_flags_skips_unsupported_flags),
        cmocka_unit_test(test_parse_flags_does_nothing_on_empty_string),

        cmocka_unit_test(test_parse_width_basic),
        cmocka_unit_test(test_parse_width_overflow),
    
        cmocka_unit_test(test_parse_width_from_args_basic),
        cmocka_unit_test(test_parse_width_from_args_negative_val),
        cmocka_unit_test(test_parse_width_from_args_int_min),
        cmocka_unit_test(test_parse_width_from_args_neg_disables_zero_flag),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
