/*
 * Copyright 2019 The Imaging Source Europe GmbH
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "aravis_api.h"

#include "AravisDevice.h"
#include "aravis_utils.h"

#include <cstring>

DeviceInterface* open_aravis_device(const struct tcam_device_info* device)
{
    return new AravisDevice(DeviceInfo(*device));
}


size_t get_aravis_device_list_size()
{
    return get_gige_device_count();
}


/**
 * @return number of copied device_infos
 */
size_t get_aravis_device_list(struct tcam_device_info* array, size_t array_size)
{
    auto vec = get_gige_device_list();

    if (vec.size() > array_size)
    {
        return 0;
    }

    for (const auto& v : vec)
    {
        auto i = v.get_info();
        memcpy(array, &i, sizeof(struct tcam_device_info));
        array++;
    }

    return vec.size();
}
