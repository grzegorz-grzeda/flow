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
#ifndef FLOW_H
#define FLOW_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef void (*flow_node_executor_t)(void *context, const void *input, void **outputs);

typedef struct flow flow_t;

typedef struct flow_node flow_node_t;

flow_t *create_flow(void);

flow_node_t *create_flow_node(void *context, flow_node_executor_t execute, size_t output_count);

bool set_relation_between_flow_nodes(flow_node_t *output_node, size_t output_number, flow_node_t *input_node);

bool add_node_to_flow(flow_t*flow, flow_node_t *node);

bool process_flow(flow_t *flow, void *data);

#endif // FLOW_H