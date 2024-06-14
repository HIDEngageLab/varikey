/**
 * \file random.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
	\brief Random number and sequences generator

	\internal
	\author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PULP_RANDOM_HPP__
#define __PULP_RANDOM_HPP__

#include "chunk.h"
#include "temperature_interface.hpp"

namespace pulp
{
	struct Random
	{
		Random(TemperatureInterface &instance) : instance(instance) {}

		void init();
		void create_sequence(chunk_t *const _sequence);

	private:
		TemperatureInterface &instance;
	};
}

#endif /* __PULP_RANDOM_HPP__ */
