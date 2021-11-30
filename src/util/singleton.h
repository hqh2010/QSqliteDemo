/*
 * Copyright (c) 2020-2021. demo Software Ltd. All rights reserved.
 *
 * Author:     xxxxxx <xxxxxx@163.com>
 *
 * Maintainer: xxxxxx <xxxxxx@163.com>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include <mutex>
#include <unordered_map>
#include <vector>
namespace repo {
namespace util {



template<typename T>
class Single
{
public:
    static T *get()
    {
        static T instance;
        return &instance;
    }

    T *operator->() const
    {
        return get();
    }

protected:
    Single() {};
    ~Single() {};

public:
    Single(const Single &) = delete;
    Single &operator=(const Single &single) = delete;
    Single &operator=(const Single &&single) = delete;
};

} // namespace util
} // namespace repo