/*
 * Copyright © 2016 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Brandon Schaefer <brandon.schaefer@canonical.com>
 */

#include <boost/throw_exception.hpp>

#include "mir/events/touch_event.h"

MirTouchEvent::MirTouchEvent()
{
    event.initInput();
    event.getInput().initTouch();
    event.getInput().getTouch().initContacts(mir::capnp::TouchScreenEvent::MAX_COUNT);
}

size_t MirTouchEvent::contact_count() const
{
    return event.asReader().getInput().getTouch().getCount();
}

void MirTouchEvent::set_contact_count(size_t count)
{
    return event.getInput().getTouch().setCount(count);
}

void MirTouchEvent::throw_if_out_of_bounds(size_t index) const
{
    if (index > event.asReader().getInput().getTouch().getCount())
         BOOST_THROW_EXCEPTION(std::out_of_range("Out of bounds index in pointer coordinates"));
}

int MirTouchEvent::id(size_t index) const
{
    throw_if_out_of_bounds(index);

    return event.asReader().getInput().getTouch().getContacts()[index].getId();
}

void MirTouchEvent::set_id(size_t index, int id)
{
    throw_if_out_of_bounds(index);

    event.getInput().getTouch().getContacts()[index].setId(id);
}

float MirTouchEvent::x(size_t index) const
{
    throw_if_out_of_bounds(index);

    return event.asReader().getInput().getTouch().getContacts()[index].getX();
}

void MirTouchEvent::set_x(size_t index, float x)
{
    throw_if_out_of_bounds(index);

    event.getInput().getTouch().getContacts()[index].setX(x);
}

float MirTouchEvent::y(size_t index) const
{
    throw_if_out_of_bounds(index);

    return event.asReader().getInput().getTouch().getContacts()[index].getY();
}

void MirTouchEvent::set_y(size_t index, float y)
{
    throw_if_out_of_bounds(index);

    event.getInput().getTouch().getContacts()[index].setY(y);
}

float MirTouchEvent::touch_major(size_t index) const
{
    throw_if_out_of_bounds(index);

    return event.asReader().getInput().getTouch().getContacts()[index].getTouchMajor();
}

void MirTouchEvent::set_touch_major(size_t index, float major)
{
    throw_if_out_of_bounds(index);

    event.getInput().getTouch().getContacts()[index].setTouchMajor(major);
}

float MirTouchEvent::touch_minor(size_t index) const
{
    throw_if_out_of_bounds(index);

    return event.asReader().getInput().getTouch().getContacts()[index].getTouchMinor();
}

void MirTouchEvent::set_touch_minor(size_t index, float minor)
{
    throw_if_out_of_bounds(index);

    event.getInput().getTouch().getContacts()[index].setTouchMinor(minor);
}

float MirTouchEvent::pressure(size_t index) const
{
    throw_if_out_of_bounds(index);

    return event.asReader().getInput().getTouch().getContacts()[index].getPressure();
}

void MirTouchEvent::set_pressure(size_t index, float pressure)
{
    throw_if_out_of_bounds(index);

    event.getInput().getTouch().getContacts()[index].setPressure(pressure);
}

float MirTouchEvent::orientation(size_t index) const
{
    throw_if_out_of_bounds(index);

    return event.asReader().getInput().getTouch().getContacts()[index].getOrientation();
}

void MirTouchEvent::set_orientation(size_t index, float orientation)
{
    throw_if_out_of_bounds(index);

    event.getInput().getTouch().getContacts()[index].setOrientation(orientation);
}

MirTouchTooltype MirTouchEvent::tool_type(size_t index) const
{
    throw_if_out_of_bounds(index);

    return static_cast<MirTouchTooltype>(event.asReader().getInput().getTouch().getContacts()[index].getToolType());
}

void MirTouchEvent::set_tool_type(size_t index, MirTouchTooltype tool_type)
{
    throw_if_out_of_bounds(index);

    auto capnp_tool_type = static_cast<mir::capnp::TouchScreenEvent::Contact::ToolType>(tool_type);
    event.getInput().getTouch().getContacts()[index].setToolType(capnp_tool_type);
}

MirTouchAction MirTouchEvent::action(size_t index) const
{
    throw_if_out_of_bounds(index);

    return static_cast<MirTouchAction>(event.asReader().getInput().getTouch().getContacts()[index].getAction());
}

void MirTouchEvent::set_action(size_t index, MirTouchAction action)
{
    throw_if_out_of_bounds(index);

    event.getInput().getTouch().getContacts()[index].setAction(
        static_cast<mir::capnp::TouchScreenEvent::Contact::TouchAction>(action));
}
