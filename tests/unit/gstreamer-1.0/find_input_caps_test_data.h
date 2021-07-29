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

#ifndef TCAM_TEST_FIND_INPUT_CAPS_DATA_H
#define TCAM_TEST_FIND_INPUT_CAPS_DATA_H

#include <string>
#include <vector>
#include "../../src/gstreamer-1.0/tcamgstbase/tcamgstbase.h"

struct fic_test_result
{
    std::string output_caps;
    struct tcam::gst::input_caps_required_modules modules;
};


struct fic_test_data_container
{
    std::string name;
    std::string input_caps;
    std::string sink_caps;
    struct tcam::gst::input_caps_toggles toggles;
    fic_test_result result;
};


void init_test_data(bool use_pimipi, bool use_dutlis);

std::vector<fic_test_data_container> get_test_data();


#endif /* TCAM_TEST_FIND_INPUT_CAPS_DATA_H */
