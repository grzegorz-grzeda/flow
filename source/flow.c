/**
 * MIT License
 * Copyright (c) 2023 Grzegorz Grzęda
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "flow.h"
#include <stdlib.h>

#define FLOW_MAX_NODE_COUNT (20)
#define FLOW_OUTPUT_SIZE (32)

typedef uint8_t output_buffer[FLOW_OUTPUT_SIZE];

typedef struct flow_node {
    output_buffer *outputs;
    size_t output_count;
    void *input;
    flow_node_executor_t execute;
    void *context;
    struct flow_node *next;
} flow_node_t;

typedef struct flow {
    flow_node_t *first;
    flow_node_t *last;
} flow_t;


flow_t *create_flow(void)
{
    return calloc(1, sizeof(flow_t));
}

flow_node_t *create_flow_node(void *context, flow_node_executor_t execute, size_t output_count)
{
    flow_node_t *node = calloc(1, sizeof(flow_node_t));
    if (node) {
        node->context = context;
        node->execute = execute;
        node->outputs = calloc(output_count, sizeof(output_buffer));
        if (node->outputs) {
            node->output_count = output_count;
        }
    }
    return node;
}

bool set_relation_between_flow_nodes(flow_node_t *output_node, size_t output_number, flow_node_t *input_node)
{
    if (!output_node || !input_node || (output_node->output_count <= output_number)) {
        return false;
    }
    input_node->input = output_node->outputs + output_number;
    return true;
}

bool add_node_to_flow(flow_t *flow, flow_node_t *node)
{
    if (!flow || !node) {
        return false;
    }
    if (!flow->first) {
        flow->first = node;
    } else {
        flow->last->next = node;
    }
    flow->last = node;
    return true;
}

bool process_flow(flow_t *flow, void *data)
{
    if (!flow || !flow->first) {
        return false;
    }
    flow->first->input = data;
    for (flow_node_t *node = flow->first; node; node = node->next) {
        node->execute(node->context, node->input, (void**)node->outputs);
    }
    return true;
}