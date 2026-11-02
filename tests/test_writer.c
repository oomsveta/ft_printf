#include "cmocka.h"
#include "ft_printf_internals.h"
#include <stdbool.h>

static void test_put_padded_basic(void **state)
{
    (void)state;

    t_ctx ctx = {0};
    ctx.current_spec.width = 10;

    put_padded(&ctx, "shrek", 5);

    assert_memory_equal(ctx.buffer.data, "     shrek", 10);
    assert_uint_equal(ctx.buffer.length, 10);
}

static void test_put_padded_zero(void **state)
{
    (void)state;

    t_ctx ctx = {0};
    ctx.current_spec.width = 10;
    ctx.current_spec.flags.pad_with_zeros = true;

    put_padded(&ctx, "shrek", 5);

    assert_memory_equal(ctx.buffer.data, "00000shrek", 10);
    assert_uint_equal(ctx.buffer.length, 10);
}

static void test_put_padded_left_justify(void **state)
{
    (void)state;

    t_ctx ctx = {0};
    ctx.current_spec.width = 10;
    ctx.current_spec.flags.left_justify = true;

    put_padded(&ctx, "shrek", 5);

    assert_memory_equal(ctx.buffer.data, "shrek     ", 10);
    assert_uint_equal(ctx.buffer.length, 10);
}

int run_writer_tests(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_put_padded_basic),
        cmocka_unit_test(test_put_padded_zero),
        cmocka_unit_test(test_put_padded_left_justify),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
