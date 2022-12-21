Limiting an app to portrait or landscape in the Blackberry player project is controlled in the bar-descriptor.xml file in the Application tab. Set the Orientation field to portrait, landscape, or auto-orient for all 4 directions. You must also change Core.cpp where is says 
    if (EXIT_SUCCESS != bbutil_init_egl(screen_ctx, GL_ES_2, PORTRAIT))
to read LANDSCAPE if needed instead.