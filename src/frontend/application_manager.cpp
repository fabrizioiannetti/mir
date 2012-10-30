/*
 * Copyright © 2012 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Thomas Voss <thomas.voss@canonical.com>
 */

#include "mir/frontend/application_manager.h"
#include "mir/frontend/application_session.h"

#include <memory>
#include <cassert>
#include <algorithm>

namespace mf = mir::frontend;

mf::ApplicationManager::ApplicationManager(std::shared_ptr<ms::ApplicationSurfaceOrganiser> organiser, 
                                           std::shared_ptr<mf::ApplicationSessionContainer> model,
                                           std::shared_ptr<mf::ApplicationFocusStrategy> strategy,
                                           std::shared_ptr<mf::ApplicationFocusMechanism> mechanism) : surface_organiser(organiser),
                                                                                                       app_model(model),
                                                                                                       focus_strategy(strategy),
                                                                                                       focus_mechanism(mechanism)
															     
{
    assert(surface_organiser);
    assert(strategy);
    assert(model);
    assert(mechanism);
}

std::shared_ptr<mf::ApplicationSession> mf::ApplicationManager::open_session(std::string name)
{
    std::shared_ptr<mf::ApplicationSession> session(new mf::ApplicationSession(surface_organiser, name));
  
    app_model->insert_session(session);
    focus_application = session;
    focus_mechanism->focus(app_model, session);
  
    return session;
}

void mf::ApplicationManager::close_session(std::shared_ptr<mf::ApplicationSession> session)
{
    if (session == focus_application.lock())
    {
        focus_application = focus_strategy->previous_focus_app(session);
        focus_mechanism->focus(app_model, focus_application.lock());
    }
    app_model->remove_session(session);
}

void mf::ApplicationManager::focus_next()
{
    auto focused = focus_application.lock();
    if (focused == NULL)
    {
        return;
    }
    auto next_focus = focus_strategy->next_focus_app(focused).lock();
    focus_application = next_focus;
    focus_mechanism->focus(app_model, next_focus);
}
