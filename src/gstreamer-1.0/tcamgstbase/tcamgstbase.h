/*
 * Copyright 2014 The Imaging Source Europe GmbH
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

#ifndef TCAM_GSTTCAMBASE_H
#define TCAM_GSTTCAMBASE_H


#include "../../base_types.h"

#include <gst/gst.h>
#include <cstdint>
#include <string>
#include <vector>

namespace tcam::gst
{

// Note: Returned element must be freed via gst_object_unref
GstElement* tcam_gst_find_camera_src(GstElement* element);


std::string get_plugin_version(const char* plugin_name);

/*
  extracts video/x-raw from caps and checks if only mono is present
*/
bool tcam_gst_raw_only_has_mono(const GstCaps* src_caps);


bool tcam_gst_is_bayer8_string(const char* fourcc);


bool tcam_gst_is_bayer10_string(const char* format_string);


bool tcam_gst_is_bayer10_packed_string(const char* format_string);


bool tcam_gst_is_bayer12_string(const char* format_string);


bool tcam_gst_is_bayer12_packed_string(const char* format_string);


bool tcam_gst_is_bayer16_string(const char* format_string);


bool tcam_gst_is_fourcc_rgb(const unsigned int fourcc);


bool tcam_gst_contains_mono_8_bit(const GstCaps* caps);


bool tcam_gst_contains_mono_10_bit(const GstCaps* caps);


bool tcam_gst_contains_mono_12_bit(const GstCaps* caps);


bool tcam_gst_contains_mono_16_bit(const GstCaps* caps);


bool tcam_gst_contains_bayer_10_bit(const GstCaps* caps);


bool tcam_gst_contains_bayer_12_bit(const GstCaps* caps);


std::vector<std::string> index_caps_formats(GstCaps* caps);


/**
 * caps only contain bayer
 */
bool gst_caps_are_bayer_only(const GstCaps* caps);


/**
 * Find the caps with the largest resolution and the highest framerate.
 * The format that will be selected is determined through internal ranking.
 * @param incoming - GstCaps from which to select
 * @return pointer to the largest caps, nullptr on error user has ownership
 */
GstCaps* tcam_gst_find_largest_caps(const GstCaps* incoming);


bool contains_bayer(const GstCaps* caps);
bool contains_mono(const GstCaps* caps);

bool contains_jpeg(const GstCaps* caps);


/**
 * @param elementname - name of the GstElement that shall be queried
 * @param padname - name of the static pad that shall be queried
 * @return GstCaps from static pad with name padname, can return nullptr
 */
GstCaps* get_caps_from_element_name(const char* elementname, const char* padname);


struct input_caps_required_modules
{
    bool tcamconvert = false;
    bool videoconvert = false;
    bool jpegdec = false;
    bool dutils = false;

    bool operator==(const input_caps_required_modules& other) const noexcept
    {
        if (tcamconvert == other.tcamconvert
            && videoconvert == other.videoconvert && jpegdec == other.jpegdec
            && dutils == other.dutils)
        {
            return true;
        }
        return false;
    }
};

struct input_caps_toggles
{
    bool use_dutils = false;
};


/**
 * @param available_caps - caps the source offers
 * @param wanted_caps - caps the sink wants, if null available_caps will be returned
 * @param requires_bayertransform(out) - will be set to true when the tcambayertransform element is required
 * @param requires_bayer2rgb(out) - will be set to true when the bayer2rgb element is required
 * @param requires_vidoeconvert(out) - will be set to true when the videoconvert element is required
 * @param requires_jpegconvert(out) - will be set to true when the jpegdec element is required
 * @param use_dutils(in) - false when dutils shall be ignored
 *
 * @return possible caps for the source
 */
GstCaps* find_input_caps(GstCaps* available_caps,
                         GstCaps* wanted_caps,
                         input_caps_required_modules& modules,
                         input_caps_toggles toggles);

tcam::image_scaling caps_get_scaling(GstCaps* caps);

}

#endif /* TCAM_GSTTCAMBASE_H */
