/*
 * Copyright © 2013 Canonical Ltd.
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
 * Authored by: Alexandros Frantzis <alexandros.frantzis@canonical.com>
 */

#include "server_configuration.h"
#include "mir/graphics/display_configuration_policy.h"
#include "mir/graphics/display_configuration.h"

#include <string>

namespace me = mir::examples;
namespace mg = mir::graphics;
namespace geom = mir::geometry;

namespace
{

char const* const display_config_opt = "display-config";
char const* const clone_opt_val = "clone";
char const* const sidebyside_opt_val = "sidebyside";
char const* const single_opt_val = "single";

class SideBySideDisplayConfigurationPolicy : public mg::DisplayConfigurationPolicy
{
public:
    void apply_to(mg::DisplayConfiguration& conf)
    {
        size_t const preferred_mode_index{0};
        int max_x = 0;

        conf.for_each_output(
            [&](mg::DisplayConfigurationOutput const& conf_output)
            {
                if (conf_output.connected && conf_output.modes.size() > 0)
                {
                    conf.configure_output(conf_output.id, true, geom::Point{max_x, 0},
                                          preferred_mode_index);
                    max_x += conf_output.modes[preferred_mode_index].size.width.as_int();
                }
                else
                {
                    conf.configure_output(conf_output.id, false, conf_output.top_left,
                                          conf_output.current_mode_index);
                }
            });
    }
};

class SingleDisplayConfigurationPolicy : public mg::DisplayConfigurationPolicy
{
public:
    void apply_to(mg::DisplayConfiguration& conf)
    {
        size_t const preferred_mode_index{0};
        bool done{false};

        conf.for_each_output(
            [&](mg::DisplayConfigurationOutput const& conf_output)
            {
                if (!done && conf_output.connected && conf_output.modes.size() > 0)
                {
                    conf.configure_output(conf_output.id, true, geom::Point{0, 0},
                                          preferred_mode_index);
                    done = true;
                }
                else
                {
                    conf.configure_output(conf_output.id, false, conf_output.top_left,
                                          conf_output.current_mode_index);
                }
            });
    }
};

}

me::ServerConfiguration::ServerConfiguration(int argc, char const** argv)
    : DefaultServerConfiguration(argc, argv)
{
    namespace po = boost::program_options;

    add_options()
        (display_config_opt, po::value<std::string>(),
            "Display configuration [{clone,sidebyside,single}:default=clone]");
}

std::shared_ptr<mg::DisplayConfigurationPolicy>
me::ServerConfiguration::the_display_configuration_policy()
{
    return display_configuration_policy(
        [this]() -> std::shared_ptr<mg::DisplayConfigurationPolicy>
        {
            auto display_config = the_options()->get(display_config_opt, clone_opt_val);

            if (display_config == sidebyside_opt_val)
                return std::make_shared<SideBySideDisplayConfigurationPolicy>();
            else if (display_config == single_opt_val)
                return std::make_shared<SingleDisplayConfigurationPolicy>();
            else
                return DefaultServerConfiguration::the_display_configuration_policy();
        });
}
