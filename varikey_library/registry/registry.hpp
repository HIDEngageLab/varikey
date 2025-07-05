// SPDX-FileCopyrightText: 2023 Roman Koch <koch.roman@gmail.com>
// SPDX-License-Identifier: MIT
// SPDX-FileContributor: Roman Koch <koch.roman@gmail.com>
// SPDX-FileComment: Registry interface for parameter management
// SPDX-FileType: SOURCE

#pragma once

#include "macros.hpp"
#include "registry_defines.hpp"

namespace registry
{
	extern void initialize(void);
	extern void shutdown(void);

	extern result_t is_ready(void);
}
