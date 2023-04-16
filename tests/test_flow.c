#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "flow.h"

static void flow_node_simple_executor_0(void *context, const void *input, void **outputs)
{
    function_called();
}

static void flow_node_simple_executor_1(void *context, const void *input, void **outputs)
{
    function_called();
}

static void flow_node_simple_executor_2(void *context, const void *input, void **outputs)
{
    function_called();
}

static void simple_test(void **state)
{
    flow_t *f = create_flow();
    flow_node_t *n0 = create_flow_node(NULL, flow_node_simple_executor_0, 1);
    flow_node_t *n1 = create_flow_node(NULL, flow_node_simple_executor_1, 1);
    flow_node_t *n2 = create_flow_node(NULL, flow_node_simple_executor_2, 1);

    add_node_to_flow(f, n0);
    add_node_to_flow(f, n1);
    add_node_to_flow(f, n2);

    expect_function_call(flow_node_simple_executor_0);
    expect_function_call(flow_node_simple_executor_1);
    expect_function_call(flow_node_simple_executor_2);
    process_flow(f, NULL);
}

int main(int argc, char **argv)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(simple_test),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}