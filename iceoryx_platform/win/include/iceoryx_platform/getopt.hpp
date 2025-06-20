// Copyright (c) 2020 by Robert Bosch GmbH. All rights reserved.
// Copyright (c) 2021 by Apex.AI Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0
#ifndef IOX_HOOFS_WIN_PLATFORM_GETOPT_HPP
#define IOX_HOOFS_WIN_PLATFORM_GETOPT_HPP

#include <string>
#include <vector>

struct option
{
    const char* name;
    int has_arg;
    int* flag;
    int val;
};

constexpr int no_argument = 0;
constexpr int required_argument = 1;
constexpr int optional_argument = 2;

extern char* optarg;
extern int optind;
extern int optopt;

int getopt_long(int argc, char* const argv[], const char* optstring,
                const struct option* longopts, int* longindex);

#endif // IOX_HOOFS_WIN_PLATFORM_GETOPT_HPP
