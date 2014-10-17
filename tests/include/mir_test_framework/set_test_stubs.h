/*
 * Copyright © 2014 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Alan Griffiths <alan@octopull.co.uk>
 */

#ifndef MIR_TEST_FRAMEWORK_SET_TEST_STUBS_H_
#define MIR_TEST_FRAMEWORK_SET_TEST_STUBS_H_

namespace mir { class Server; }

namespace mir_test_framework
{
/// Apply stubs that make tests independent of hardware
void set_test_stubs(mir::Server& server);
}

#endif /* MIR_TEST_FRAMEWORK_SET_TEST_STUBS_H_ */
