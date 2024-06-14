# Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
# SPDX-License-Identifier: MIT

#basic definitions
set(HEADER_FILE "build_number.h")
set(CACHE_FILE "build_number.cache")

#Reading data from file + incrementation
IF(EXISTS ${CACHE_FILE})
    file(READ ${CACHE_FILE} INCREMENTED_VALUE)
    math(EXPR INCREMENTED_VALUE "${INCREMENTED_VALUE}+1")
	if(INCREMENTED_VALUE GREATER "65535")
		set(INCREMENTED_VALUE "0")
	endif(INCREMENTED_VALUE GREATER "65535")
ELSE()
    set(INCREMENTED_VALUE "0")
ENDIF()

#Update the cache
file(WRITE ${CACHE_FILE} "${INCREMENTED_VALUE}")

#Create the header
if (NOT DEFINED IDENTITY_DIRECTORY)
	message(WARNING "Identity files directory not defined.")
	set(IDENTITY_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../src/engine/identity")
endif()
set(BUILD_NUMBER_FULL_FILE_NAME "${IDENTITY_DIRECTORY}/${HEADER_FILE}")
message("Generate build number ${INCREMENTED_VALUE} for the next build to ${BUILD_NUMBER_FULL_FILE_NAME}")
file(WRITE "${BUILD_NUMBER_FULL_FILE_NAME}" 
"/*	
	Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
	SPDX-License-Identifier: MIT
*/

#ifndef __BUILD_NUMBER_H__
#define __BUILD_NUMBER_H__

// Attention: autogenerated file
#define BUILD_NUMBER ${INCREMENTED_VALUE}

#endif /* __BUILD_NUMBER_H__ */
")
