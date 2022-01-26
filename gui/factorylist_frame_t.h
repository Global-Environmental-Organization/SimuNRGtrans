/*
 * This file is part of the Simutrans-Extended project under the Artistic License.
 * (see LICENSE.txt)
 */

#ifndef GUI_FACTORYLIST_FRAME_T_H
#define GUI_FACTORYLIST_FRAME_T_H


#include "simwin.h"
#include "gui_frame.h"
#include "components/gui_scrollpane.h"
#include "components/gui_label.h"
#include "components/gui_combobox.h"
#include "factorylist_stats_t.h"
#include "../descriptor/goods_desc.h"
#include "../bauer/goods_manager.h"

#define FACTORYLIST_MODES 4

/*
 * Factory list window
 */
class factorylist_frame_t : public gui_frame_t, private action_listener_t
{
private:
	static const char *sort_text[factorylist::SORT_MODES];
	static const char *display_mode_text[FACTORYLIST_MODES];

	gui_combobox_t freight_type_c;
	gui_combobox_t sortedby;
	button_t sorteddir;
	button_t filter_within_network, btn_display_mode;
	factorylist_stats_t stats;
	gui_scrollpane_t scrolly;
	gui_aligned_container_t list;

	void fill_list();

	//static char name_filter[256];
	//char last_name_filter[256];
	//gui_textinput_t name_filter_input;

	/*
	 * All filter settings are static, so they are not reset each
	 * time the window closes.
	 */
	static factorylist::sort_mode_t sortby;
	static bool sortreverse;
	static bool filter_own_network;
	static uint8 filter_goods_catg;
	static uint8 display_mode;

	vector_tpl<const goods_desc_t *> viewable_freight_types;

public:
	factorylist_frame_t();

	const char *get_help_filename() const OVERRIDE {return "factorylist_filter.txt"; }

	static void set_sortierung(const factorylist::sort_mode_t& sm) { sortby = sm; }

	static bool get_reverse() { return sortreverse; }
	static void set_reverse(const bool& reverse) { sortreverse = reverse; }
	static bool get_filter_own_network() { return filter_own_network; }
	static void set_filter_goods_catg(uint8 g) { filter_goods_catg = g < goods_manager_t::INDEX_NONE ? 2 : g; }

	bool action_triggered(gui_action_creator_t*, value_t) OVERRIDE;

	void draw(scr_coord pos, scr_size size) OVERRIDE;

	void map_rotate90( sint16 ) OVERRIDE { fill_list(); }

	void rdwr(loadsave_t* file) OVERRIDE;

	uint32 get_rdwr_id() OVERRIDE { return magic_factorylist; }
};

#endif
