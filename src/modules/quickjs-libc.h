/*
 * QuickJS C library
 *
 * Copyright (c) 2017-2018 Fabrice Bellard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef QUICKJS_LIBC_H
#define QUICKJS_LIBC_H
#include "quickjs-libc.c"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "quickjs.h"
#endif /* QUICKJS_LIBC_H */

#ifdef __cplusplus
extern "C" {
#endif

static JSModuleDef *js_init_module_std(JSContext *ctx, const char *module_name);
static JSModuleDef *js_init_module_os(JSContext *ctx, const char *module_name);
static JSModuleDef *js_init_module_bjson(JSContext *ctx, const char *module_name);
static void js_std_add_helpers(JSContext *ctx, int argc, char **argv);
static int js_std_loop(JSContext *ctx);
static JSValue js_std_await(JSContext *ctx, JSValue obj);
static void js_std_init_handlers(JSRuntime *rt);
static void js_std_free_handlers(JSRuntime *rt);
static void js_std_dump_error(JSContext *ctx);
static uint8_t *js_load_file(JSContext *ctx, size_t *pbuf_len, const char *filename);
static int js_module_set_import_meta(JSContext *ctx, JSValue func_val,
                              bool use_realpath, bool is_main);
static JSModuleDef *js_module_loader(JSContext *ctx,
                              const char *module_name, void *opaque);
static void js_std_eval_binary(JSContext *ctx, const uint8_t *buf, size_t buf_len,
                        int flags);
static void js_std_promise_rejection_tracker(JSContext *ctx, JSValue promise,
                                      JSValue reason,
                                      bool is_handled, void *opaque);
static void js_std_set_worker_new_context_func(JSContext *(*func)(JSRuntime *rt));
static void js_std_set_worker_new_runtime_func(JSRuntime *(*func)());
static JSValue js_postMessage(JSContext *ctx,JSValue worker,int argc, JSValue *argv);
static JSValue js_copyWorker(JSContext *from, JSContext *to);

#ifdef __cplusplus
} /* extern "C" { */
#endif
