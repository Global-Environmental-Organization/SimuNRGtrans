/*
 * This file is part of the Simutrans-Extended project under the Artistic License.
 * (see LICENSE.txt)
 */

#ifndef BODEN_WASSER_H
#define BODEN_WASSER_H


#include "grund.h"

/**
 * The water ground models rivers and lakes in Simutrans.
 */
class wasser_t : public grund_t
{
protected:
	/// cache ribis to tiles connected by water
	ribi_t::ribi ribi;
	/// helper variable, ribis to canal tiles, where ships cannot turn left or right
	ribi_t::ribi canal_ribi;
	/// helper variable ribis for displaying (tiles with harbour are not considered connected to water for displaying)
	ribi_t::ribi display_ribi;
	/**
	 * This method also recalculates ribi and cache_ribi!
	 */
	void calc_image_internal(const bool calc_only_snowline_change);

public:

	wasser_t(loadsave_t *file, koord pos ) : grund_t(koord3d(pos,0) ), ribi(ribi_t::none), canal_ribi(ribi_t::none) { rdwr(file); }
	wasser_t(koord3d pos);

	inline bool is_water() const { return true; }

	// returns correct directions for water and none for the rest ...
	ribi_t::ribi get_weg_ribi(waytype_t typ) const { return (typ==water_wt) ? ribi : (ribi_t::ribi)ribi_t::none; }
	ribi_t::ribi get_weg_ribi_unmasked(waytype_t typ) const  { return (typ==water_wt) ? ribi : (ribi_t::ribi)ribi_t::none; }

	const char *get_name() const {return "Water";}
	grund_t::typ get_typ() const {return wasser;}

	// recalculates the water-specific ribis
	void recalc_ribis();

	// recalculates the water-specific ribis for this and all neighbouring water tiles
	void recalc_water_neighbours();

	// map rotation
	void rotate90();

	ribi_t::ribi get_canal_ribi() const { return canal_ribi; }
	ribi_t::ribi get_display_ribi() const { return display_ribi; }

	// static stuff from here on for water animation
	static int stage;
	static bool change_stage;

	static void prepare_for_refresh();
};

#endif
