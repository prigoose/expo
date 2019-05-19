/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */
#pragma once

#ifdef __cplusplus
#define ABI33_0_0YG_EXTERN_C_BEGIN extern "C" {
#define ABI33_0_0YG_EXTERN_C_END }
#else
#define ABI33_0_0YG_EXTERN_C_BEGIN
#define ABI33_0_0YG_EXTERN_C_END
#endif

#ifdef _WINDLL
#define WIN_EXPORT __declspec(dllexport)
#else
#define WIN_EXPORT
#endif

#ifdef NS_ENUM
// Cannot use NSInteger as NSInteger has a different size than int (which is the
// default type of a enum). Therefor when linking the Yoga C library into obj-c
// the header is a missmatch for the Yoga ABI.
#define ABI33_0_0YG_ENUM_BEGIN(name) NS_ENUM(int, name)
#define ABI33_0_0YG_ENUM_END(name)
#else
#define ABI33_0_0YG_ENUM_BEGIN(name) enum name
#define ABI33_0_0YG_ENUM_END(name) name
#endif
