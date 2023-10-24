/**
 * \file rp2040_timestamp.hpp
 * \author Koch, Roman (koch.roman@gmail.com)
 *
 * Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
 * SPDX-License-Identifier: MIT
 */

/**
	\brief Timestamp

	\internal
	\author Roman Koch, koch.roman@gmail.com
*/

#ifndef __PULP_TIMESTAMP_HPP__
#define __PULP_TIMESTAMP_HPP__

#include <stdint.h>

#include "component_interface.hpp"

namespace platform
{
	namespace soc
	{
		struct RP2040Timestamp : public pulp::ComponentInterface
		{
			virtual ~RP2040Timestamp() {}

			virtual void initialize() {}
			virtual void shutdown() {}

			void reset(void);
			uint64_t get_value(void);
		};
	}
}

#endif /* __PULP_TIMESTAMP_HPP__ */
