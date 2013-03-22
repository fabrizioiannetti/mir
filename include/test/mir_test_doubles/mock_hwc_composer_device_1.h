/*
 * Copyright © 2013 Canonical Ltd.
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
 * Authored by: Kevin DuBois <kevin.dubois@canonical.com>
 */

#ifndef MIR_TEST_DOUBLES_MOCK_HWC_COMPOSER_DEVICE_1_H_
#define MIR_TEST_DOUBLES_MOCK_HWC_COMPOSER_DEVICE_1_H_

#include <hardware/hwcomposer.h>
#include <gmock/gmock.h>

namespace mir
{
namespace test
{
namespace doubles
{

class ICSHardwareComposerInterface
{
public:
    virtual void registerProcs_interface(struct hwc_composer_device_1* dev, hwc_procs_t const* procs) = 0;

};

class MockHWCComposerDevice1 : public hwc_composer_device_1, public ICSHardwareComposerInterface
{
public:
    MockHWCComposerDevice1()
    {
        common.version = HWC_DEVICE_API_VERSION_1_1;

        registerProcs = hook_registerProcs; 
    }

    MOCK_METHOD2(registerProcs_interface, void(struct hwc_composer_device_1*, hwc_procs_t const*));
    static void hook_registerProcs(struct hwc_composer_device_1* mock_hwc, hwc_procs_t const* procs)
    {
        MockHWCComposerDevice1* mocker = static_cast<MockHWCComposerDevice1*>(mock_hwc);
        return mocker->registerProcs_interface(mock_hwc, procs);
    }
};

}
}
}

#endif /* MIR_TEST_DOUBLES_MOCK_HWC_COMPOSER_DEVICE_1_H_ */
