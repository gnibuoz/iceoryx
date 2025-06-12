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

#include "iceoryx_platform/getopt.hpp"
#include "iceoryx_platform/logging.hpp"
#include "iceoryx_platform/windows.hpp"

#include <cstdio>
#include <cstring>
#include <iostream>

char* optarg = nullptr;
int optind = 1;
int optopt = 0;

int getopt_long(int argc, char* const argv[], const char* optstring, const struct option* longopts, int* longindex)
{
    if (optind >= argc)
    {
        return -1;
    }

    const char* current = argv[optind];

    // long option
    if (strncmp(current, "--", 2) == 0)
    {
        const char* name = current + 2;
        const char* value = nullptr;
        std::string optName;
        if (const char* eq = strchr(name, '='))
        {
            optName = std::string(name, eq - name);
            value = eq + 1;
        }
        else
        {
            optName = name;
        }

        for (int i = 0; longopts[i].name != nullptr; ++i)
        {
            if (optName == longopts[i].name)
            {
                if (longindex)
                {
                    *longindex = i;
                }

                if (longopts[i].has_arg == required_argument)
                {
                    if (value)
                    {
                        optarg = const_cast<char*>(value);
                    }
                    else if (optind + 1 < argc)
                    {
                        optind++;
                        optarg = argv[optind];
                    }
                    else
                    {
                        std::cerr << "Missing argument for option --" << optName << std::endl;
                        return '?';
                    }
                }
                else if (longopts[i].has_arg == optional_argument)
                {
                    optarg = value ? const_cast<char*>(value) : nullptr;
                }
                else
                {
                    optarg = nullptr;
                }

                optind++;
                return longopts[i].val;
            }
        }

        std::cerr << "Unknown option --" << optName << std::endl;
        optind++;
        return '?';
    }

    // short option
    if (current[0] == '-' && current[1] != '\0')
    {
        char opt = current[1];
        const char* optchar = strchr(optstring, opt);
        if (!optchar)
        {
            optopt = opt;
            std::cerr << "Unknown option -" << opt << std::endl;
            optind++;
            return '?';
        }

        if (*(optchar + 1) == ':')
        {
            // option requires argument
            if (current[2] != '\0')
            {
                optarg = const_cast<char*>(current + 2);
            }
            else if (optind + 1 < argc)
            {
                optind++;
                optarg = argv[optind];
            }
            else
            {
                std::cerr << "Missing argument for option -" << opt << std::endl;
                optind++;
                return '?';
            }
        }
        else
        {
            optarg = nullptr;
        }

        optind++;
        return opt;
    }

    return -1;
}
