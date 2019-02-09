/*
 * xdg_decoration_unstable.h
 *
 */

#ifndef SRC_SERVER_FRONTEND_WAYLAND_XDG_DECORATION_V1_H_
#define SRC_SERVER_FRONTEND_WAYLAND_XDG_DECORATION_V1_H_

#include "generated/xdg-decoration-unstable-v1_wrapper.h"

namespace mir
{
namespace frontend
{

class Shell;
class WlSeat;
class OutputManager;

class XdgDecorationManagerV1 : public wayland::XdgDecorationManagerV1
{
public:
	XdgDecorationManagerV1(struct wl_display* display, std::shared_ptr<Shell> const shell, WlSeat& seat,
            OutputManager* output_manager);

    virtual void destroy(struct wl_client* client, struct wl_resource* resource);
    virtual void get_toplevel_decoration(struct wl_client* client, struct wl_resource* resource, uint32_t id, struct wl_resource* toplevel);
};

class XdgToplevelDecorationV1 : public wayland::XdgToplevelDecorationV1 {
    virtual void destroy();
    virtual void set_mode(uint32_t mode);
    virtual void unset_mode();
};

}
}


#endif /* SRC_SERVER_FRONTEND_WAYLAND_XDG_DECORATION_V1_H_ */
