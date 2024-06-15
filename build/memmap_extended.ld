/*
    Copyright (c) 2023, Roman Koch, koch.roman@gmail.com
    SPDX-License-Identifier: MIT
*/

/*
    Define a 32 bytes big section for unit test purposes
*/
SECTIONS
{
    .utest_custom_section 0x2003FFE0 (NOLOAD): 
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__utest_custom_section_start = .);
        KEEP(*(.utest_custom_section))
        /*
        *(.utest_custom_section)
        */
        PROVIDE_HIDDEN (__utest_custom_section_end = .);
    } > RAM 

    . = __utest_custom_section_start + 32;
}