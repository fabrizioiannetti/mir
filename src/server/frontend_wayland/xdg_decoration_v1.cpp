/*
 * xdg_decoration_unstable.cpp
 *
 */

#include "xdg_decoration_v1.h"

namespace mf = mir::frontend;

namespace mir
{
namespace frontend
{

XdgDecorationManagerV1::XdgDecorationManagerV1(struct wl_display* display, std::shared_ptr<mf::Shell> const shell, WlSeat& seat,
        OutputManager* output_manager) :
	wayland::XdgDecorationManagerV1(display, 1) {
	// TODO:
	(void) display;
	(void) shell;
	(void) seat;
	(void) output_manager;
}

void XdgDecorationManagerV1::destroy(struct wl_client* client, struct wl_resource* resource) {
	// TODO:
	(void) client;
	(void) resource;
}

void XdgDecorationManagerV1::get_toplevel_decoration(struct wl_client* client, struct wl_resource* resource, uint32_t id, struct wl_resource* toplevel) {
	// TODO:
	(void) client;
	(void) resource;
	(void) id;
	(void) toplevel;
}


void XdgToplevelDecorationV1::destroy() {
	// TODO:
}

void XdgToplevelDecorationV1::set_mode(uint32_t mode) {
	// TODO:
	(void) mode;
}

void XdgToplevelDecorationV1::unset_mode() {
	// TODO:
}

}
}
