/*
 * This file is part of the Simutrans-Extended project under the Artistic License.
 * (see LICENSE.txt)
 */

#ifndef GUI_LINE_WAITING_CARGO_H
#define GUI_LINE_WAITING_CARGO_H


#include "components/gui_component.h"
#include "components/gui_aligned_container.h"
#include "components/gui_label.h"
#include "../simline.h"
#include "../simhalt.h"


class gui_halt_waiting_catg_t : public gui_aligned_container_t
{
	halthandle_t halt;
	uint8 catg_index;
	cbuffer_t buf;

	// for update flag.
	uint32 update_seed = 0;

public:
	gui_halt_waiting_catg_t(halthandle_t h, uint8 catg);

	void update();

	void draw(scr_coord offset) OVERRIDE;

	scr_size get_max_size() const OVERRIDE { return get_min_size(); }
};


class gui_line_waiting_status_t : public gui_aligned_container_t
{
	linehandle_t line;

	schedule_t *schedule;

	bool show_name=true;

public:
	gui_line_waiting_status_t(linehandle_t line);

	void init();

	// for reload from the save
	void set_line(linehandle_t line_) { line = line_; init(); }
	void set_show_name(bool yesno) { show_name = yesno; init(); }

	void draw(scr_coord offset) OVERRIDE;
};

#endif
