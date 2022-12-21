/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

//BEGIN_INCLUDE(all)
#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>
#include <android/configuration.h>
#include <android/window.h>

int checkformat( ANativeActivity* pActivity );
void init(void *ptr);
void updateptr(void *ptr);
void updateptr2(void *ptr);
void clearptr(void *ptr);
int gettextstate();
void begin();
void loop();
void updatesize();
void setaccel( float x, float y, float z );
void touchdown( int id, float x, float y );
void touchmoved( int id, float x, float y );
void touchup( int id, float x, float y );
void mousedown( int id );
void mousemoved( int id, float x, float y );
void mouseup( int id );
void joystickaxis( int id, int stick, int axis, float value );
void joystickbutton( int id, int button, int state );
void keydown( int key );
void keyup( int key );
void cleanup();
void pauseapp();
void resumeapp();
void resumeapp2();
void exit(int);
void reset();
void devicerotate();

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

//0=16bit (faster), 1=32bit
#define g_iColorMode 1

/**
 * Our saved state data.
 */
struct saved_state {
    float angle;
    int32_t x;
    int32_t y;
};


/**
 * Shared state for our app.
 */
struct engine {
    struct android_app* app;

    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    ASensorEventQueue* sensorEventQueue;

    int animating;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int32_t width;
    int32_t height;
    struct saved_state state;
};

struct egldata {
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    struct ANativeActivity *activity;
};

EGLConfig config;

extern float AMotionEvent_getAxisValue(const AInputEvent* motion_event, int32_t axis, size_t pointer_index);
static typeof(AMotionEvent_getAxisValue) *p_AMotionEvent_getAxisValue;
#define AMotionEvent_getAxisValue (*p_AMotionEvent_getAxisValue)
#include <dlfcn.h>

/**
 * Initialize an EGL context for the current display.
 */
static int engine_init_display(struct engine* engine) {
    // initialize OpenGL ES and EGL

	static int done = 0;

    /*
     * Here specify the attributes of the desired configuration.
     * Below, we select an EGLConfig with at least 8 bits per color
     * component compatible with on-screen windows
     */

#if g_iColorMode == 0
	// select 16 bit back buffer for performance
    const EGLint attribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BUFFER_SIZE, 16,
            EGL_DEPTH_SIZE, 16,
            EGL_STENCIL_SIZE, 0,
            EGL_CONFIG_CAVEAT, EGL_NONE,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_NONE
    };
#else
    // select 32 bit back buffer for quality
    const EGLint attribs[] = {
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_BLUE_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_RED_SIZE, 8,
				EGL_ALPHA_SIZE, 8,
                EGL_BUFFER_SIZE, 32,
                EGL_DEPTH_SIZE, 16,
                EGL_STENCIL_SIZE, 0,
                EGL_CONFIG_CAVEAT, EGL_NONE,
                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                EGL_NONE
        };
#endif

    EGLint w, h, dummy, format;
    EGLint numConfigs;
    EGLSurface surface;
    EGLContext context;

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, 0, 0);

    /* Here, the application chooses the configuration it desires. In this
     * sample, we have a very simplified selection process, where we pick
     * the first EGLConfig that matches our criteria */
    EGLConfig allConfigs[20];
    eglChooseConfig(display, attribs, allConfigs, 20, &numConfigs);
    config = allConfigs[0];

    if ( numConfigs == 0 )
    {
    	LOGW( "Failed to find suitable render format" );
    	exit(0);
    	//return 0;
    }

    int i = 0;
    for ( i = 0; i < numConfigs; i++ )
    {
    	if ( i > 19 ) continue;
    	EGLint red;
    	EGLint green;
    	EGLint blue;
    	EGLint alpha;
    	EGLint depth;
    	EGLint stencil;
    	EGLint window;
    	EGLint render;
    	eglGetConfigAttrib( display, allConfigs[i], EGL_RED_SIZE, &red );
    	eglGetConfigAttrib( display, allConfigs[i], EGL_GREEN_SIZE, &green );
    	eglGetConfigAttrib( display, allConfigs[i], EGL_BLUE_SIZE, &blue );
    	eglGetConfigAttrib( display, allConfigs[i], EGL_ALPHA_SIZE, &alpha );
    	eglGetConfigAttrib( display, allConfigs[i], EGL_DEPTH_SIZE, &depth );
    	eglGetConfigAttrib( display, allConfigs[i], EGL_STENCIL_SIZE, &stencil );
    	eglGetConfigAttrib( display, allConfigs[i], EGL_SURFACE_TYPE, &window );
    	eglGetConfigAttrib( display, allConfigs[i], EGL_NATIVE_VISUAL_ID, &format );
    	eglGetConfigAttrib( display, allConfigs[i], EGL_RENDERABLE_TYPE, &render );

    	LOGW( "R: %d, G: %d, B: %d, A: %d, D: %d, W: %d, F: %d, S: %d, R: %d", red, green, blue, alpha, depth, window, format, stencil, render );
    }

    int formatIndex = 0;

    // check for devices that need special render formats (Wildfire S being one)
    if ( checkformat( engine->app->activity ) > 0 )
    {
    	LOGW( "Adjusting render format for device" );

    	for ( i = 0; i < numConfigs; i++ )
		{
			if ( i > 19 ) continue;
			eglGetConfigAttrib( display, allConfigs[i], EGL_NATIVE_VISUAL_ID, &format );
			if ( format > 0 )
			{
				config = allConfigs[i];
				formatIndex = -1;
				break;
			}
		}
    }

    //eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    //int result = ANativeWindow_setBuffersGeometry(engine->app->window, 640, 480, 0);
    //LOGW( "Result: %d", result );

    surface = eglCreateWindowSurface(display, config, engine->app->window, NULL);
	while ( surface == EGL_NO_SURFACE )
	{
		LOGW( "Failed to create EGL surface: %d, trying different format", eglGetError() );

		formatIndex++;
		if ( formatIndex >= numConfigs || formatIndex > 19 )
		{
			LOGW( "Failed to find compatible format" );
			return -1;
		}

		config = allConfigs[ formatIndex ];
		surface = eglCreateWindowSurface(display, config, engine->app->window, NULL);
	}

    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
	 * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
	 * As soon as we picked a EGLConfig, we can safely reconfigure the
	 * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
	eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
	int result = ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);
	LOGW( "Result: %d", result );

	const EGLint contextAttribList[] = {EGL_CONTEXT_CLIENT_VERSION, 2,EGL_NONE};
	context = eglCreateContext(display, config, NULL, contextAttribList);
    if ( context == EGL_NO_CONTEXT )
	{
		LOGW( "Failed to create EGL context: %d", eglGetError() );
		return -1;
	}

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
    	int error = eglGetError();
        LOGW("Unable to eglMakeCurrent: %d", eglGetError());
        return -1;
    }

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    LOGW( "Width: %d Height: %d", w, h );

    engine->display = display;
    engine->context = context;
    engine->surface = surface;
    engine->width = w;
    engine->height = h;
    engine->state.angle = 0;

    struct egldata data;
    data.display = display;
    data.surface = surface;
    data.context = context;
    data.activity = engine->app->activity;

    if ( done != 0 )
    {
    	LOGW( "Updating" );
    	updateptr( &data );
    }
    else
    {
    	LOGW( "Initialising" );
    	init( &data );
    }

    //begin();

    p_AMotionEvent_getAxisValue = dlsym(RTLD_DEFAULT, "AMotionEvent_getAxisValue");

    done = 1;
    return 0;
}

/**
 * Just the current frame in the display.
 */
static void engine_draw_frame(struct engine* engine) {
    if (engine->display == NULL) {
        // No display.
        return;
    }

    if (engine->surface == NULL) {
		// No surface.
		return;
	}

    loop();
}

/**
 * Tear down the EGL context currently associated with the display.
 */
static void engine_term_display(struct engine* engine)
{
	//cleanup();

    if (engine->display != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (engine->context != EGL_NO_CONTEXT) {
            eglDestroyContext(engine->display, engine->context);
        }
        if (engine->surface != EGL_NO_SURFACE) {
            eglDestroySurface(engine->display, engine->surface);
        }
        eglTerminate(engine->display);
    }
    engine->animating = 0;
    engine->display = EGL_NO_DISPLAY;
    engine->context = EGL_NO_CONTEXT;
    engine->surface = EGL_NO_SURFACE;
}

int initialised = 0;

/**
 * Process the next input event.
 */
enum {AXIS_X = 0, AXIS_Y = 1, AXIS_RX = 11, AXIS_RY = 14, AXIS_DPADX = 15, AXIS_DPADY = 16, AXIS_LT = 17, AXIS_RT = 18};

static int32_t engine_handle_input(struct android_app* app, AInputEvent* event)
{
	if ( initialised == 0 ) return 0;

	struct engine* engine = (struct engine*)app->userData;
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
	{
		// touch event

		int action = AMotionEvent_getAction( event ) & 0xff;
		int pointer = (AMotionEvent_getAction( event ) >> 8) & 0xff;
		int flags = AMotionEvent_getFlags( event );
		int pointers = AMotionEvent_getPointerCount( event );
		int id = AMotionEvent_getPointerId( event, pointer );
		int device = AInputEvent_getDeviceId( event );
		int source = AInputEvent_getSource( event );

		float x = AMotionEvent_getX( event, pointer );
		float y = AMotionEvent_getY( event, pointer );
		float size = AMotionEvent_getSize( event, pointer );
		float pressure = AMotionEvent_getPressure( event, pointer );
		//LOGW("Action: %d, pointer: %d, count: %d, id: %d, flags: %d, X: %.1f, Y: %.1f", action, pointer, pointers, id, flags, x, y);
		//if ( action != 2 ) LOGW("Action: %d, pointer: %d, count: %d, id: %d", action, pointer, pointers, id);
		//else LOGW("Pressure: %f, Size: %f, x: %f, y: %f, id: %d", pressure, size, x, y, id);

		switch ( action )
		{
			case 0:
			case 5:
				{
					if ( source == AINPUT_SOURCE_MOUSE ) mousedown( 0 );
					else touchdown( id, x, y );
					break;
				}
			case 1:
			case 3:
			case 6:
				{
					if ( source == AINPUT_SOURCE_MOUSE ) mouseup( 0 );
					else touchup( id, x, y );
					break;
				}
			case 2:
				{
					if ( source == AINPUT_SOURCE_TOUCHSCREEN )
					{
						// touch screen
						touchmoved( id, x, y );

						// only the primary pointer sends move messages so get the other pointer positions while we are here
						if ( pointers > 1 )
						{
							int i = 1;
							for ( i = 1; i < pointers; i++ )
							{
								int id = AMotionEvent_getPointerId( event, i );
								x = AMotionEvent_getX( event, i );
								y = AMotionEvent_getY( event, i );
								touchmoved( id, x, y );
							}
						}
					}
					else
					{
						// joystick?
						float lx = AMotionEvent_getAxisValue(event, AXIS_X, pointer);
						float ly = AMotionEvent_getAxisValue(event, AXIS_Y, pointer);
						float rx = AMotionEvent_getAxisValue(event, AXIS_RX, pointer);
						float ry = AMotionEvent_getAxisValue(event, AXIS_RY, pointer);
						float lt = AMotionEvent_getAxisValue(event, AXIS_LT, pointer);
						float rt = AMotionEvent_getAxisValue(event, AXIS_RT, pointer);

						joystickaxis( device, 0, 0, lx );
						joystickaxis( device, 0, 1, ly );
						joystickaxis( device, 0, 2, lt );
						joystickaxis( device, 1, 0, rx );
						joystickaxis( device, 1, 1, ry );
						joystickaxis( device, 1, 2, rt );

						float dx = AMotionEvent_getAxisValue(event, AXIS_DPADX, pointer);
						float dy = AMotionEvent_getAxisValue(event, AXIS_DPADY, pointer);

						static maxdevice = 6;
						static int* usesdpadaxis = 0;
						if ( usesdpadaxis == 0 )
						{
							usesdpadaxis = (int*) malloc( 6*4 );
							int i;
							for(i = 0; i < 6; i++ ) usesdpadaxis[i] = 0;
						}

						if ( dx < -0.9 || dx > 0.9 || dy < -0.9 || dy > 0.9 )
						{
							if ( device >= maxdevice )
							{
								int* temp = (int*) malloc( (device+5)*4 );
								int i;
								for(i = 0; i < maxdevice; i++ ) temp[i] = usesdpadaxis[i];
								maxdevice = device+1;
								free( usesdpadaxis );
								usesdpadaxis = temp;
							}

							usesdpadaxis[ device ] = 1;
						}

						if ( usesdpadaxis[ device ] == 1 )
						{
							// xbox controller produces axis events for the dpad
							if ( dx < -0.9 ) { joystickbutton(device,12,1); keydown(AKEYCODE_DPAD_LEFT); }
							else { joystickbutton(device,12,0); keyup(AKEYCODE_DPAD_LEFT); }

							if ( dx > 0.9 ) { joystickbutton(device,14,1); keydown(AKEYCODE_DPAD_RIGHT); }
							else { joystickbutton(device,14,0); keyup(AKEYCODE_DPAD_RIGHT); }

							if ( dy < -0.9 ) { joystickbutton(device,13,1); keydown(AKEYCODE_DPAD_UP); }
							else { joystickbutton(device,13,0); keyup(AKEYCODE_DPAD_UP); }

							if ( dy > 0.9 ) { joystickbutton(device,15,1); keydown(AKEYCODE_DPAD_DOWN); }
							else { joystickbutton(device,15,0); keyup(AKEYCODE_DPAD_DOWN); }
						}

						//LOGW("Joystick X1: %.1f, Y1: %.1f, X2: %.1f, Y2: %.1f, LT: %.1f, RT: %.1f", lx,ly, rx, ry, lt, rt);
						//LOGW("Joystick DX: %.1f, DY: %.1f", dx,dy);
					}
					break;
				}
			case 7: // mouse movement (Ouya touchpad reports itself as a mouse)
				{
					mousemoved( 0, x, y );
					break;
				}
			// ouya also sends these duplicates for mouse clicking?
			//case 10: mousedown(0); break;
			//case 9: mouseup(0); break;

			default: break;
		}

		return 1;
	}
	else if ( AInputEvent_getType(event) == AINPUT_EVENT_TYPE_KEY )
	{
		// key event

		int action = AKeyEvent_getAction( event );
		int flags = AKeyEvent_getFlags( event );
		int keyCode = AKeyEvent_getKeyCode( event );
		int device = AInputEvent_getDeviceId( event );
		int source = AInputEvent_getSource( event );

		int gamepad = 1;
		// 0x400 = gamepad
		if ( (source & 0x400) != 0 )
		{
			// set joystick buttons instead
			int state = (action == AKEY_EVENT_ACTION_DOWN) ? 1 : 0;

			switch(keyCode)
			{
				case 96:  joystickbutton(device,0,state); break; //0
				case 99:  joystickbutton(device,2,state); break; //2
				case 100: joystickbutton(device,3,state); break; //3
				case 97:  joystickbutton(device,1,state); break; //1

				case 82: joystickbutton(device,7,state); break; // Home //7
				case 108: joystickbutton(device,7,state); break; // Start //7

				case 102: joystickbutton(device,4,state); break; // L1 //4
				case 104: joystickbutton(device,10,state); break; // L2 //10
				case 106: joystickbutton(device,8,state); break; // L3 //8
				case 103: joystickbutton(device,5,state); break; // R1 //5
				case 105: joystickbutton(device,11,state); break; // R2 //11
				case 107: joystickbutton(device,9,state); break; // R3 //9

				// let dpad buttons fall through to non-gamepad input for left/right/up/down as well
				case AKEYCODE_DPAD_LEFT: joystickbutton(device,12,state); gamepad = 0; break;
				case AKEYCODE_DPAD_UP: joystickbutton(device,13,state); gamepad = 0; break;
				case AKEYCODE_DPAD_RIGHT: joystickbutton(device,14,state); gamepad = 0; break;
				case AKEYCODE_DPAD_DOWN: joystickbutton(device,15,state); gamepad = 0; break;

				default: gamepad = 0; break;
			}
		}
		else gamepad = 0;

		//LOGW("Action: %d, flags: %d, keyCode: %d", action, flags, keyCode);
		if ( gamepad == 0 )
		{
			switch( action )
			{
				case AKEY_EVENT_ACTION_DOWN:
				{
					keydown( keyCode );
					break;
				}

				case AKEY_EVENT_ACTION_UP:
				{
					keyup( keyCode );
					break;
				}
			}
		}

		/*
		if ( keyCode == AKEYCODE_BACK )
		{
			// if the back key is pressed whilst the keyboard is active this will crash the Nexus 7, return a marker value (2) to handle it in the native app glue
			if ( gettextstate() == 0 ) return 2; // keyboard is active
			else return 1;
		}
		*/
		if ( keyCode == AKEYCODE_HOME /*|| keyCode == AKEYCODE_MENU*/ ) return 0;
		//if ( keyCode == AKEYCODE_MENU && action == AKEY_EVENT_ACTION_UP ) return 0;
		if ( keyCode == AKEYCODE_VOLUME_DOWN || keyCode == AKEYCODE_VOLUME_UP ) return 0;
		return 1;
	}
	return 0;
}

int currOrien = 0;

/**
 * Process the next main command.
 */
static void engine_handle_cmd(struct android_app* app, int32_t cmd)
{
    struct engine* engine = (struct engine*)app->userData;
    switch (cmd) {
        case APP_CMD_SAVE_STATE:
        	LOGI("Save State");
            // The system has asked us to save our current state.  Do so.
            engine->app->savedState = malloc(sizeof(struct saved_state));
            *((struct saved_state*)engine->app->savedState) = engine->state;
            engine->app->savedStateSize = sizeof(struct saved_state);
            break;
        case APP_CMD_PAUSE:
        	LOGI("App Paused");
        	if (engine->accelerometerSensor != NULL) {
				ASensorEventQueue_disableSensor(engine->sensorEventQueue, engine->accelerometerSensor);
			}
        	engine->animating = 0;
        	if ( initialised > 0 ) pauseapp();
        	break;
        case APP_CMD_RESUME:
        	LOGI("App Resumed");
        	resumeapp();
        	engine->animating = 1;
        	if (engine->accelerometerSensor != NULL) {
				ASensorEventQueue_enableSensor(engine->sensorEventQueue,
						engine->accelerometerSensor);
				ASensorEventQueue_setEventRate(engine->sensorEventQueue, engine->accelerometerSensor, 100*1000);
			}
        	break;
        case APP_CMD_INIT_WINDOW:
        	LOGI("Window Init");
            // The window is being shown, get it ready.
            if (engine->app->window != NULL) {
                engine_init_display(engine);
                initialised = 1;
            }
            resumeapp2();
            break;
        case APP_CMD_TERM_WINDOW:
        	LOGI("Window Terminate");
            // The window is being hidden or closed, clean it up.
        	engine_term_display(engine);
            break;
        case APP_CMD_GAINED_FOCUS:
        	LOGI("Gained Focus");
            break;
        case APP_CMD_LOST_FOCUS:
        	LOGI("Lost Focus");
            break;

       case APP_CMD_CONFIG_CHANGED:
       {
    	   usleep( 100000 );

    	   AConfiguration *config2 = AConfiguration_new();
    	   AConfiguration_fromAssetManager( config2, engine->app->activity->assetManager);
    	   int orien = AConfiguration_getOrientation( config2 );
    	   LOGW("Orientation: %d",orien);
    	   AConfiguration_delete( config2 );

    	   //if ( orien != currOrien )
    	   {
			   if (engine->surface == EGL_NO_SURFACE) break;

			   engine->animating = 0;
			   eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
			   eglDestroySurface(engine->display, engine->surface);

			   engine->surface = eglCreateWindowSurface(engine->display, config, engine->app->window, NULL);
			   if (eglMakeCurrent(engine->display, engine->surface, engine->surface, engine->context) == EGL_FALSE)
			   {
				   int error = eglGetError();
				   LOGW("Unable to eglMakeCurrent: %d", eglGetError());
				   break;
			   }

			   EGLint w, h;
			   eglQuerySurface(engine->display, engine->surface, EGL_WIDTH, &w);
			   eglQuerySurface(engine->display, engine->surface, EGL_HEIGHT, &h);

			   LOGW("Width: %d Height: %d",w,h);

			   engine->width = w;
			   engine->height = h;
			   engine->state.angle = 0;

			   struct egldata data;
			   data.display = engine->display;
			   data.surface = engine->surface;
			   data.context = engine->context;
			   data.activity = engine->app->activity;

			   updateptr2( &data );
//			   devicerotate();
			   engine->animating = 1;
    	   }

    	   currOrien = orien;
    	   break;
       }

    }
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* state) {
    struct engine engine;

    ANativeActivity_setWindowFlags( state->activity, AWINDOW_FLAG_KEEP_SCREEN_ON, 0 );

    // Make sure glue isn't stripped.
    app_dummy();

    memset(&engine, 0, sizeof(engine));
    state->userData = &engine;
    state->onAppCmd = engine_handle_cmd;
    state->onInputEvent = engine_handle_input;
    engine.app = state;

    // Prepare to monitor accelerometer
    engine.sensorManager = ASensorManager_getInstance();
    engine.accelerometerSensor = ASensorManager_getDefaultSensor(engine.sensorManager,
            ASENSOR_TYPE_ACCELEROMETER);
    engine.sensorEventQueue = ASensorManager_createEventQueue(engine.sensorManager,
            state->looper, LOOPER_ID_USER, NULL, NULL);

    if (state->savedState != NULL) {
        // We are starting with a previous saved state; restore from it.
        engine.state = *(struct saved_state*)state->savedState;
    }

    // loop waiting for stuff to do.

    while (1) {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.

        while ( (ident=ALooper_pollAll( 0, NULL, &events, (void**)&source)) >= 0 )
        {
            // Process this event.
            if (source != NULL) {
                source->process(state, source);
            }

            // If a sensor has data, process it now.
            if (ident == LOOPER_ID_USER)
            {
                if (engine.accelerometerSensor != NULL)
                {
                	ASensorEvent event;
                    while ( ASensorEventQueue_getEvents(engine.sensorEventQueue, &event, 1) > 0)
                    {
                    	//LOGW( "Accel status: %d", event.acceleration.status );
                    	setaccel( event.acceleration.x, event.acceleration.y, event.acceleration.z );
                    }
                }
            }

            // Check if we are exiting.
            if (state->destroyRequested != 0)
            {
                engine_term_display(&engine);
                return;
            }
        }

        if (engine.animating)
        {
            engine_draw_frame(&engine);
        }
        else
        {
        	usleep( 20000 );
        }
    }
}
//END_INCLUDE(all)
