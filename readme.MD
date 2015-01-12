s3eHidController
================
This extension for Marmalade allows you to read input such as DPad, A/B/X/Y
buttons & analog stick values from a "HID" controller on PC or Mac.

A HID controller might be connected via USB or Bluetooth.
Typically you need to install drivers on your machine, though many controllers
will use generic drivers or Windows will install them for you.

NB: The keys/axis may not be mapped to the correct values for some controllers!

Currently this extension has mappings for:

- XBox 360 (and compatible) gamepads via Bluetooth or USB
- PS3 Six-Axis controller connected via USB or a Bluetooth dongle. Note that
  for PS3 Six-Axis controllers to work, you will require a 3rd-party driver
  such as MotionJoy.

The Windows extension uses the older 7.1.0 WDK (Windows Driver Kit). If you
want to edit/rebuild, you'll need to install that (license didn't let me
redistribute). That supports XP and newer.

Status 12/01/2015: I've renamed and am currently heavily refactoring this
extension. I've checked in built libs. The checked in version works with
360 gamepad on Windows 8 at least. Ouya pad works but key mappings are wrong.
Not tested or build on Mac yet but likely to work.

Plans: Support more devices via config mapping files (map device ID to keycode
mappings). Integrate with similar Android and iOS extensions that I'm
workign on, via a new C++ class. Add Marmalade Quick wrapper.

Original docs from before my fiddling are in the legacy_docs folder.

  
Setting up and testing controllers
----------------------------------

### Windows

Many controllers will install automatically on modern Windows.
To test gamepads are working:

- Start > Search > Type "joy.cpl" Enter
- Your pad should be listed
- Click Properties > Test
- Should be able to test all buttons
- If you want to add new mappings, that will also show you how the buttons get
  mapped.

Setting up an Xbox 360 controller on PC:
support.xbox.com/en-GB/xbox-360/accessories/connect-wired-controller-computer

For the Ouya bluetooth controller, I found it worked out of the box but key
codes are wrong. The extension needs to map its keys/axes... Will prob hard
code first and then do via config file.

### Mac OS X

You will need a drive for you HID device to support the controller.
Please use the Xbox 360 Controller Driver written by Colin Munro:
http://tattiebogle.net/index.php/ProjectRoot/Xbox360Controller


Credit where it's due!
----------------------

- Original (360Controller) extension by: http://www.baysidegames.net/blog/?p=94
- Mac support provided by Halfbot.com (M. Samuel)
- Refactoring, rename and some tweeks: nickchops (Nick Smith)
- Wrapper code utilized from: https://github.com/derekvanvliet/Xbox360ControllerManager.git
