
#pragma once

//#include <gst/gst.h>

#include "tcamprop_system_base.h"

#include <optional>
#include <string>
#include <vector>

struct _TcamProp;
struct _GstElement;
struct _GValue;

namespace tcamprop_system
{
_TcamProp* to_TcamProp(_GstElement* elem) noexcept;

std::vector<std::string> get_property_names(_TcamProp* elem);

bool has_property(_TcamProp* elem, const char* name);
bool has_property(_TcamProp* elem, const char* name, prop_type type);
bool get_value(_TcamProp* elem, const char* name, _GValue& val);
auto get_flags(_TcamProp* elem, const char* name) -> std::optional<prop_flags>;
auto get_category(_TcamProp* elem, const char* name) -> std::optional<std::string>;
auto get_prop_type(_TcamProp* elem, const char* name) -> std::optional<prop_type>;

template<typename T> auto get_range(_TcamProp* elem, const char* name) -> std::optional<T> = delete;

template<>
auto get_range<prop_range_integer>(_TcamProp* elem, const char* name)
    -> std::optional<prop_range_integer>;
template<>
auto get_range<prop_range_real>(_TcamProp* elem, const char* name)
    -> std::optional<prop_range_real>;

template<typename T> auto get_value(_TcamProp* elem, const char* name) -> std::optional<T> = delete;
template<> auto get_value<bool>(_TcamProp* elem, const char* name) -> std::optional<bool>;
template<> auto get_value<double>(_TcamProp* elem, const char* name) -> std::optional<double>;
template<> auto get_value<int>(_TcamProp* elem, const char* name) -> std::optional<int>;

void set_value(_TcamProp* elem, const char* name, bool value_to_set);
void set_value(_TcamProp* elem, const char* name, int value_to_set);
void set_value(_TcamProp* elem, const char* name, double value_to_set);

auto get_menu_items(_TcamProp* prop, const char* menu_name) -> std::vector<std::string>;
} // namespace tcamprop_system