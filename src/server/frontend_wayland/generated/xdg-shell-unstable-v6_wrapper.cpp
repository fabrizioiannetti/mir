/*
 * AUTOGENERATED - DO NOT EDIT
 *
 * This file is generated from xdg-shell-unstable-v6.xml
 * To regenerate, run the “refresh-wayland-wrapper” target.
 */

#include <experimental/optional>
#include <boost/throw_exception.hpp>
#include <boost/exception/diagnostic_information.hpp>

#include "xdg-shell-unstable-v6_wrapper.h"

#include "mir/fd.h"
#include "mir/log.h"

namespace mfw = mir::frontend::wayland;

// XdgShellV6

struct zxdg_shell_v6_interface const mfw::XdgShellV6::vtable = {
    destroy_thunk,
    create_positioner_thunk,
    get_xdg_surface_thunk,
    pong_thunk};

// XdgPositionerV6

struct zxdg_positioner_v6_interface const mfw::XdgPositionerV6::vtable = {
    destroy_thunk,
    set_size_thunk,
    set_anchor_rect_thunk,
    set_anchor_thunk,
    set_gravity_thunk,
    set_constraint_adjustment_thunk,
    set_offset_thunk};

// XdgSurfaceV6

struct zxdg_surface_v6_interface const mfw::XdgSurfaceV6::vtable = {
    destroy_thunk,
    get_toplevel_thunk,
    get_popup_thunk,
    set_window_geometry_thunk,
    ack_configure_thunk};

// XdgToplevelV6

struct zxdg_toplevel_v6_interface const mfw::XdgToplevelV6::vtable = {
    destroy_thunk,
    set_parent_thunk,
    set_title_thunk,
    set_app_id_thunk,
    show_window_menu_thunk,
    move_thunk,
    resize_thunk,
    set_max_size_thunk,
    set_min_size_thunk,
    set_maximized_thunk,
    unset_maximized_thunk,
    set_fullscreen_thunk,
    unset_fullscreen_thunk,
    set_minimized_thunk};

// XdgPopupV6

struct zxdg_popup_v6_interface const mfw::XdgPopupV6::vtable = {
    destroy_thunk,
    grab_thunk};
