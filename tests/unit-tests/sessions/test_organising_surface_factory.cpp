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
 * Authored by: Robert Carr <robert.carr@canonical.com>
 */

#include <mir_test_doubles/mock_surface_factory.h>

#include <mir/sessions/organising_surface_factory.h>
#include <mir/sessions/placement_strategy.h>
#include <mir/sessions/surface_creation_parameters.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace msess = mir::sessions;
namespace geom = mir::geometry;
namespace mtd = mir::test::doubles;

namespace
{

struct MockPlacementStrategy : public msess::PlacementStrategy
{
    MOCK_METHOD2(place, void(msess::SurfaceCreationParameters const&, msess::SurfaceCreationParameters&));
};

struct OrganisingSurfaceFactorySetup : public testing::Test
{
    void SetUp()
    {
        using namespace ::testing;
        
        underlying_surface_factory = std::make_shared<mtd::MockSurfaceFactory>();
        ON_CALL(*underlying_surface_factory, create_surface(_)).WillByDefault(Return(null_surface));

        placement_strategy = std::make_shared<MockPlacementStrategy>();
    }
    std::shared_ptr<msess::Surface> null_surface;
    std::shared_ptr<mtd::MockSurfaceFactory> underlying_surface_factory;
    std::shared_ptr<MockPlacementStrategy> placement_strategy;
};

struct SurfaceParameterUpdatingAction
{
    SurfaceParameterUpdatingAction(msess::SurfaceCreationParameters const& parameters)
        : parameters(parameters)
    {
    }
    void update_parameters(msess::SurfaceCreationParameters const& /* unusued_input_parameters */,
                           msess::SurfaceCreationParameters &output_parameters)
    {
        output_parameters = parameters;
    }
    
    msess::SurfaceCreationParameters parameters;
};

} // namespace 

TEST_F(OrganisingSurfaceFactorySetup, offers_create_surface_parameters_to_placement_strategy)
{
    using namespace ::testing;

    msess::OrganisingSurfaceFactory factory(underlying_surface_factory, placement_strategy);
    
    EXPECT_CALL(*underlying_surface_factory, create_surface(_)).Times(1);
    
    auto params = msess::a_surface();
    EXPECT_CALL(*placement_strategy, place(Ref(params), _)).Times(1);
    
    factory.create_surface(params);
}

TEST_F(OrganisingSurfaceFactorySetup, forwards_create_surface_parameters_from_placement_strategy_to_underlying_factory)
{
    using namespace ::testing;

    msess::OrganisingSurfaceFactory factory(underlying_surface_factory, placement_strategy);
    
    auto params = msess::a_surface();

    auto placed_params = params;
    placed_params.size.width = geom::Width{100};
    SurfaceParameterUpdatingAction param_updater(placed_params);
    
    EXPECT_CALL(*placement_strategy, place(Ref(params), _)).Times(1)
        .WillOnce(Invoke(&param_updater, &SurfaceParameterUpdatingAction::update_parameters));
    EXPECT_CALL(*underlying_surface_factory, create_surface(placed_params));
    
    factory.create_surface(params);
}



