#define _POSIX_C_SOURCE 199309L
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include <wayland-server.h>
#include <wlr/backend.h>
#include <wlr/session.h>
#include <wlr/render.h>
#include <wlr/render/gles2.h>
#include <wlr/types/wlr_output.h>
#include <wlr/wlcore/wl_shm.h>
#include <xkbcommon/xkbcommon.h>
#include "shared.h"

struct sample_state {
	struct wlr_renderer *renderer;
};

void handle_output_frame(struct output_state *output, struct timespec *ts) {
	struct compositor_state *state = output->compositor;
	struct sample_state *sample = state->data;
	struct wlr_output *wlr_output = output->output;

	wlr_renderer_begin(sample->renderer, wlr_output);
	// TODO: render surfaces
	wlr_renderer_end(sample->renderer);
}

int main() {
	struct sample_state state = { 0 };
	struct compositor_state compositor = { 0,
		.data = &state,
		.output_frame_cb = handle_output_frame,
	};
	compositor_init(&compositor);

	state.renderer = wlr_gles2_renderer_init();
	wlr_wl_shm_init(compositor.display);

	compositor_run(&compositor);
}