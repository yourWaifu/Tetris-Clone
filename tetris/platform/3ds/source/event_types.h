#pragma once
typedef enum
{
	SDL_FIRSTEVENT = 0,     /**< Unused (do not remove) */

							/* Application events */
	SDL_QUIT = 0x100, /**< User-requested quit */

					  /* These application events have special meaning on iOS, see README-ios.md for details */
	SDL_APP_TERMINATING,        /**< The application is being terminated by the OS
								Called on iOS in applicationWillTerminate()
								Called on Android in onDestroy()
								*/
	SDL_APP_LOWMEMORY,          /**< The application is low on memory, free memory if possible.
								Called on iOS in applicationDidReceiveMemoryWarning()
								Called on Android in onLowMemory()
								*/
	SDL_APP_WILLENTERBACKGROUND, /**< The application is about to enter the background
								 Called on iOS in applicationWillResignActive()
								 Called on Android in onPause()
								 */
	SDL_APP_DIDENTERBACKGROUND, /**< The application did enter the background and may not get CPU for some time
								Called on iOS in applicationDidEnterBackground()
								Called on Android in onPause()
								*/
	SDL_APP_WILLENTERFOREGROUND, /**< The application is about to enter the foreground
								 Called on iOS in applicationWillEnterForeground()
								 Called on Android in onResume()
								 */
	SDL_APP_DIDENTERFOREGROUND, /**< The application is now interactive
								Called on iOS in applicationDidBecomeActive()
								Called on Android in onResume()
								*/

								/* Window events */
	SDL_WINDOWEVENT = 0x200, /**< Window state change */
	SDL_SYSWMEVENT,             /**< System specific event */

								/* Keyboard events */
	SDL_KEYDOWN = 0x300, /**< Key pressed */
	SDL_KEYUP,                  /**< Key released */
	SDL_TEXTEDITING,            /**< Keyboard text editing (composition) */
	SDL_TEXTINPUT,              /**< Keyboard text input */

								/* Mouse events */
	SDL_MOUSEMOTION = 0x400, /**< Mouse moved */
	SDL_MOUSEBUTTONDOWN,        /**< Mouse button pressed */
	SDL_MOUSEBUTTONUP,          /**< Mouse button released */
	SDL_MOUSEWHEEL,             /**< Mouse wheel motion */

								/* Joystick events */
	SDL_JOYAXISMOTION = 0x600, /**< Joystick axis motion */
	SDL_JOYBALLMOTION,          /**< Joystick trackball motion */
	SDL_JOYHATMOTION,           /**< Joystick hat position change */
	SDL_JOYBUTTONDOWN,          /**< Joystick button pressed */
	SDL_JOYBUTTONUP,            /**< Joystick button released */
	SDL_JOYDEVICEADDED,         /**< A new joystick has been inserted into the system */
	SDL_JOYDEVICEREMOVED,       /**< An opened joystick has been removed */

								/* Game controller events */
	SDL_CONTROLLERAXISMOTION = 0x650, /**< Game controller axis motion */
	SDL_CONTROLLERBUTTONDOWN,          /**< Game controller button pressed */
	SDL_CONTROLLERBUTTONUP,            /**< Game controller button released */
	SDL_CONTROLLERDEVICEADDED,         /**< A new Game controller has been inserted into the system */
	SDL_CONTROLLERDEVICEREMOVED,       /**< An opened Game controller has been removed */
	SDL_CONTROLLERDEVICEREMAPPED,      /**< The controller mapping was updated */

									   /* Touch events */
	SDL_FINGERDOWN = 0x700,
	SDL_FINGERUP,
	SDL_FINGERMOTION,

	/* Gesture events */
	SDL_DOLLARGESTURE = 0x800,
	SDL_DOLLARRECORD,
	SDL_MULTIGESTURE,

	/* Clipboard events */
	SDL_CLIPBOARDUPDATE = 0x900, /**< The clipboard changed */

								 /* Drag and drop events */
	SDL_DROPFILE = 0x1000, /**< The system requests a file open */

						   /* Audio hotplug events */
	SDL_AUDIODEVICEADDED = 0x1100, /**< A new audio device is available */
	SDL_AUDIODEVICEREMOVED,        /**< An audio device has been removed. */

								   /* Render events */
	SDL_RENDER_TARGETS_RESET = 0x2000, /**< The render targets have been reset and their contents need to be updated */
	SDL_RENDER_DEVICE_RESET, /**< The device has been reset and all textures need to be recreated */

							 /** Events ::SDL_USEREVENT through ::SDL_LASTEVENT are for your use,
							 *  and should be allocated with SDL_RegisterEvents()
							 */
	SDL_USEREVENT = 0x8000,

	/**
	*  This last event is only for bounding internal arrays
	*/
	SDL_LASTEVENT = 0xFFFF
} SDL_EventType;