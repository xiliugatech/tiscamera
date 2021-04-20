/*
 * Copyright 2021 The Imaging Source Europe GmbH
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

#pragma once

#include "PropertyInterfaces.h"

#include <linux/videodev2.h>
#include <map>
#include <memory>
#include <string>


namespace tcam::v4l2
{
struct v4l2_genicam_mapping;
}

namespace tcam::property
{


class V4L2PropertyBackend;

class V4L2PropertyIntegerImpl : public IPropertyInteger
{
public:
    V4L2PropertyIntegerImpl(struct v4l2_queryctrl* queryctrl,
                            struct v4l2_ext_control* ctrl,
                            std::shared_ptr<V4L2PropertyBackend> backend,
                            const tcam::v4l2::v4l2_genicam_mapping* mapping = nullptr);

    virtual std::string get_name() const final
    {
        return m_name;
    };
    virtual PropertyFlags get_flags() const final
    {
        return m_flags;
    };

    virtual int64_t get_min() const final
    {
        return m_min;
    };
    virtual int64_t get_max() const final
    {
        return m_max;
    };
    virtual int64_t get_step() const final
    {
        return m_step;
    };
    virtual int64_t get_default() const final
    {
        return m_default;
    };
    virtual int64_t get_value() const final;

    virtual bool set_value(int64_t new_value) final;

private:
    bool valid_value(int64_t val);

    std::weak_ptr<V4L2PropertyBackend> m_cam;

    std::string m_name;
    PropertyFlags m_flags;

    int64_t m_min;
    int64_t m_max;
    int64_t m_step;
    int64_t m_default;

    int m_v4l2_id;
};


class V4L2PropertyDoubleImpl : public IPropertyFloat
{
public:
    V4L2PropertyDoubleImpl(const std::string& name, int id);
    V4L2PropertyDoubleImpl(struct v4l2_queryctrl* queryctrl,
                           struct v4l2_ext_control* ctrl,
                           std::shared_ptr<V4L2PropertyBackend> backend,
                           const tcam::v4l2::v4l2_genicam_mapping* mapping = nullptr);

    virtual std::string get_name() const final
    {
        return m_name;
    };
    virtual PropertyFlags get_flags() const final
    {
        return m_flags;
    };

    virtual double get_min() const final
    {
        return m_min;
    };
    virtual double get_max() const final
    {
        return m_max;
    };
    virtual double get_step() const final
    {
        return m_step;
    };
    virtual double get_default() const final
    {
        return m_default;
    };
    virtual double get_value() const final;

    virtual bool set_value(double new_value) final;

private:
    bool valid_value(double val);

    std::weak_ptr<V4L2PropertyBackend> m_cam;

    std::string m_name;
    PropertyFlags m_flags;

    double m_min;
    double m_max;
    double m_step;
    double m_default;

    int m_v4l2_id;
};


class V4L2PropertyBoolImpl : public IPropertyBool
{
public:
    V4L2PropertyBoolImpl(struct v4l2_queryctrl* queryctrl,
                         struct v4l2_ext_control* ctrl,
                         std::shared_ptr<V4L2PropertyBackend> backend,
                         const tcam::v4l2::v4l2_genicam_mapping* mapping = nullptr);

    virtual std::string get_name() const final
    {
        return m_name;
    };
    virtual PropertyFlags get_flags() const final
    {
        return m_flags;
    };

    virtual bool get_default() const final
    {
        return m_default;
    };
    virtual bool get_value() const final;

    virtual bool set_value(bool new_value) final;

private:
    std::weak_ptr<V4L2PropertyBackend> m_cam;

    std::string m_name;
    PropertyFlags m_flags;

    bool m_default;

    int m_v4l2_id;
};


class V4L2PropertyCommandImpl : public IPropertyCommand
{
public:
    V4L2PropertyCommandImpl(struct v4l2_queryctrl* queryctrl,
                            struct v4l2_ext_control* ctrl,
                            std::shared_ptr<V4L2PropertyBackend> backend,
                            const tcam::v4l2::v4l2_genicam_mapping* mapping = nullptr);

    virtual std::string get_name() const final
    {
        return m_name;
    };
    virtual PropertyFlags get_flags() const final
    {
        return m_flags;
    };

    virtual bool execute() final;

private:
    std::weak_ptr<V4L2PropertyBackend> m_cam;

    std::string m_name;
    PropertyFlags m_flags;

    int m_v4l2_id;
};


class V4L2PropertyEnumImpl : public IPropertyEnum
{
public:
    V4L2PropertyEnumImpl(struct v4l2_queryctrl* queryctrl,
                         struct v4l2_ext_control* ctrl,
                         std::shared_ptr<V4L2PropertyBackend> backend,
                         const tcam::v4l2::v4l2_genicam_mapping* mapping = nullptr);

    virtual std::string get_name() const final
    {
        return m_name;
    };
    virtual PropertyFlags get_flags() const final
    {
        return m_flags;
    };

    virtual bool set_value_str(const std::string& new_value) final;
    virtual bool set_value(int new_value) final;

    virtual std::string get_value() const final;
    virtual int get_value_int() const final;

    virtual std::string get_default() const final
    {
        return m_default;
    };

    virtual std::vector<std::string> get_entries() const final;

private:
    bool valid_value(int value);

    std::map<int, std::string> m_entries;
    std::weak_ptr<V4L2PropertyBackend> m_cam;

    std::string m_name;
    PropertyFlags m_flags;

    std::string m_default;

    int m_v4l2_id;
};


} // namespace tcam::property