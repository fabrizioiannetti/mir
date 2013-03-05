/*
 * Copyright © 2012 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Robert Carr <robert.carr@canonical.com>
 *              Daniel d'Andradra <daniel.dandrada@canonical.com>
 */

#include "mir/graphics/viewable_area.h"

#include "android_input_manager.h"
#include "android_input_constants.h"
#include "android_input_configuration.h"
#include "android_input_reader_policy.h"
#include "default_android_input_configuration.h"
#include "event_filter_dispatcher_policy.h"

#include <EventHub.h>
#include <InputDispatcher.h>
#include <InputReader.h>

#include <memory>
#include <vector>

namespace mg = mir::graphics;
namespace mi = mir::input;
namespace mia = mi::android;

mia::InputManager::InputManager(std::shared_ptr<mia::InputConfiguration> const& config,
                                std::shared_ptr<mg::ViewableArea> const& view_area,
                                std::shared_ptr<mi::CursorListener> const& cursor_listener)
  : event_hub(config->the_event_hub()),
    dispatcher(new droidinput::InputDispatcher(
        config->the_dispatcher_policy())),
    reader(new droidinput::InputReader(
        event_hub,
        new mia::InputReaderPolicy(view_area, cursor_listener),
        dispatcher)),
    reader_thread(new droidinput::InputReaderThread(reader)),
    dispatcher_thread(new droidinput::InputDispatcherThread(dispatcher))
{
    dispatcher->setInputDispatchMode(mia::DispatchEnabled, mia::DispatchUnfrozen);
    dispatcher->setInputFilterEnabled(true);
}

mia::InputManager::~InputManager()
{
}

void mia::InputManager::stop()
{
    dispatcher_thread->requestExit();
    dispatcher->setInputDispatchMode(mia::DispatchDisabled, mia::DispatchFrozen);
    dispatcher_thread->join();

    reader_thread->requestExit();
    event_hub->wake();
    reader_thread->join();
}

void mia::InputManager::start()
{
    reader_thread->run("InputReader", droidinput::PRIORITY_URGENT_DISPLAY);
    dispatcher_thread->run("InputDispatcher", droidinput::PRIORITY_URGENT_DISPLAY);
}

std::shared_ptr<mi::InputManager> mi::create_input_manager(
    const std::initializer_list<std::shared_ptr<mi::EventFilter> const>& event_filters,
    std::shared_ptr<mg::ViewableArea> const& view_area)
{
    static const std::shared_ptr<mi::CursorListener> null_cursor_listener{};
    auto config = std::make_shared<mia::DefaultInputConfiguration>(event_filters);

    return std::make_shared<mia::InputManager>(config, view_area,
        null_cursor_listener);
}
