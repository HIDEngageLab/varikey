---
# HID control

layout: page
title: HID Control
permalink: /hid/
---

VariKey ist ein Modul mit HID interface für komfortable Steuerkomponenten einer eingebetteten Systems.

## Identität

The supported language is always English (0x0409).

The serial identifier is a string consisting of 12 hexadecimal characters. 
The default value is 12 '0's; upon the first startup, a unique serial identifier is generated once.

The device release number is represented in binary-coded decimal. The specification release number in binary-coded decimal is 0x0200 for USB 2.0.

The class code, assigned by the USB-IF, can be set 0x00 for interface-related class information or 0x03 for HID-Device.
The subclass code, assigned by the USB-IF, should be reset to zero if the bDeviceClass field is reset to zero.

The protocol code, assigned by the USB-IF, is used to identify the protocols that a device supports on a device basis according to the device class specification. 
If this field is reset to zero, it means the device does not use class-specific protocols on a device basis, but it may still use class-specific protocols on an interface basis.

The maximum packet size for endpoint zero is 64 bytes.

The USB Vendor Identifier (VID), normally assigned by the USB-IF, has a default value of 0xCAFE. 
The string identifier is equal to the platform identifier string (as listed in the table below).

The USB Product ID (PID) can be specified on a product-specific basis. 
The PID is assigned by the firmware manufacturer (VariKey) for each combination of platform and application identifier.
The default value for the VariKey Demo Product is 0x1101.
The product identifier is set according to the table below.

_Attention: The values of the identifiers have not been assigned by USB-IF. 
Since the modules are integral parts of an embedded system, only design considerations for potential conflicts with identifiers assigned by USB-IF should be taken into account._

### Software Revision

The software revision is described as `A.B.C.D.E`.

`A` The major software revision ranges from 0 to 255, and different revisions are fundamentally not compatible.

`B` The minor revision ranges from 0 to 255 and includes the functionality of a major revision. It may contain compatible extensions.

`C` The patch revision ranges from 0 to 255 and includes changes to the software or hardware without altering the functionality.

`D` The tweak revision ranges from 0 to 255 and involves changes to the software or hardware without altering the functionality.

`E` Unique firmware identifier (16 bits).

### Hardware Identifier

Verfügbare Hardware Identifier.

| Plattform (string) | Identifier (0-15) | Nummer (0-15) | Variant (0-15) | Comment |
| ------------------ | ----------------- | ------------- | -------------- | ------- |
| "VARIKEY"          | 1                 | 1             | 0              |         |
| "GOSSENMETRAWATT"  | 2                 | 1             | 0              |         |


### Application Identifier

VariKey Applications.

| Application (string) | Identifier (0-15) | Comment |
| -------------------- | ----------------- | ------- |
| "KEYPAD_DEMO"        | 1                 |         |
| "KEYPAD_10BWDB"      | 2                 |         |

## Control 

Short control sequences description.

### Mount

A `mounted`-event leads to a change in the backlighting to `TURBO`.
After 15 seconds, the program switches to `MOUNTED`.

### Unmount

A `unmounted`-event leads to a change in the backlighting to `UNMOUNTED`.

### Suspend

A `suspend`-event leads to a change in the backlighting to `SUSPENDED`.

### Resume

A `resume`-event leads to a change in the backlighting to `TURBO` and switched to `MOUNTED` in 15 seconds.

### Get Report

#### Serial

The request will be responded to with a 12-digit unique serial number.

#### Unique

The request will be responded to with a long integer, last 4 bytes of the unique serial number.

#### Gadget

This request provides the product identifier.

#### Hardware 

This request provides the hardware revision identifier.

#### Version

This request provides the software revision.

#### Temperature

This request provides the MCU core temperature.

### Set Report

#### Feature

#### Output

##### Keyboard

Keyboard events for `CAPSLOCK`, `SCROLLLOCK`, and `NUMLOCK` are interpreted as follows:

- `CAPSLOCK` toggles an alternative key layout on and off.
- `SCROLLLOCK` toggles an alternative layout for the scroll wheel on and off.
- `NUMLOCK` toggles the 10-key numeric keypad on and off.

The layout of the 10-key numeric keypad is provided in the table below.

|       |      |       |
| ----- | ---- | ----- |
| 1     | 2abc | 3def  |
| 4ghi  | 5jkl | 6mno  |
| 7pqrs | 8tuv | 9wxyz |
|       | 0_   |       |

##### Custom

The Custom Set Report can interpret one of the following commands.

**RESET**

Reset the keypad module.

**POSITION**

Set the cursor position on the display.

**ICON**

Draw a pre-saved icon at the current display position. 
The cursor is not moved.

**FONT_SIZE**

Set the font size for the next output.

**TEXT**

Output a text message.

**BACKLIGHT**

Change the backlighting.

**CONFIG**

Changed runtime module configuration.

