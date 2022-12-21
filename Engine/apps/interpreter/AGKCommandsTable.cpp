#define ALL_AGK_CASES_DEFINE  \
\
    case AGKI_WORLDTOSCREENXR_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::WorldToScreenX( *(float*)g_p[1] );\
        break;\
\
    case AGKI_WORLDTOSCREENYR_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::WorldToScreenY( *(float*)g_p[1] );\
        break;\
\
    case AGKI_SCREENTOWORLDXR_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::ScreenToWorldX( *(float*)g_p[1] );\
        break;\
\
    case AGKI_SCREENTOWORLDYR_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::ScreenToWorldY( *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETRESOLUTIONMODE_INTEGER : inl_handleparams();\
        agk::SetResolutionMode( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETSYNCRATE_FLOAT_INTEGER : inl_handleparams();\
        agk::SetSyncRate( *(float*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETORIENTATIONALLOWED_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetOrientationAllowed( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_SETTRANSITIONMODE_INTEGER : inl_handleparams();\
        agk::SetTransitionMode( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETDISPLAYASPECT_FLOAT : inl_handleparams();\
        agk::SetDisplayAspect( *(float*)g_p[0] );\
        break;\
\
    case AGKI_GETCLR_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetCL( );\
        break;\
\
    case AGKI_SETSCISSOR_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetScissor( *(float*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_SETINTENDEDDEVICESIZE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetIntendedDeviceSize( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETDEVICEWIDTHR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetDeviceWidth( );\
        break;\
\
    case AGKI_GETDEVICEHEIGHTR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetDeviceHeight( );\
        break;\
\
    case AGKI_SETVIRTUALRESOLUTION_INTEGER_INTEGER : inl_handleparams();\
        agk::SetVirtualResolution( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_UPDATEDEVICESIZE_INTEGER_INTEGER : inl_handleparams();\
        agk::UpdateDeviceSize( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETVIRTUALWIDTHR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetVirtualWidth( );\
        break;\
\
    case AGKI_GETVIRTUALHEIGHTR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetVirtualHeight( );\
        break;\
\
    case AGKI_GETSCREENBOUNDSLEFTR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetScreenBoundsLeft( );\
        break;\
\
    case AGKI_GETSCREENBOUNDSRIGHTR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetScreenBoundsRight( );\
        break;\
\
    case AGKI_GETSCREENBOUNDSTOPR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetScreenBoundsTop( );\
        break;\
\
    case AGKI_GETSCREENBOUNDSBOTTOMR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetScreenBoundsBottom( );\
        break;\
\
    case AGKI_GETDISPLAYASPECTR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetDisplayAspect( );\
        break;\
\
    case AGKI_GETORIENTATIONR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetOrientation( );\
        break;\
\
    case AGKI_GETRESUMEDR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetResumed( );\
        break;\
\
    case AGKI_SETDEFAULTMAGFILTER_INTEGER : inl_handleparams();\
        agk::SetDefaultMagFilter( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETDEFAULTMINFILTER_INTEGER : inl_handleparams();\
        agk::SetDefaultMinFilter( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETDEFAULTWRAPU_INTEGER : inl_handleparams();\
        agk::SetDefaultWrapU( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETDEFAULTWRAPV_INTEGER : inl_handleparams();\
        agk::SetDefaultWrapV( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETVIEWOFFSET_FLOAT_FLOAT : inl_handleparams();\
        agk::SetViewOffset( *(float*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETVIEWZOOM_FLOAT : inl_handleparams();\
        agk::SetViewZoom( *(float*)g_p[0] );\
        break;\
\
    case AGKI_SETVIEWZOOMMODE_INTEGER : inl_handleparams();\
        agk::SetViewZoomMode( *(int*)g_p[0] );\
        break;\
\
    case AGKI_GETVIEWOFFSETXR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetViewOffsetX( );\
        break;\
\
    case AGKI_GETVIEWOFFSETYR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetViewOffsetY( );\
        break;\
\
    case AGKI_GETVIEWZOOMR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetViewZoom( );\
        break;\
\
    case AGKI_SYNC : inl_handleparams();\
        agk::Sync( );\
        break;\
\
    case AGKI_BREAK : inl_handleparams();\
        agk::Break( );\
        break;\
\
    case AGKI_STEPPHYSICS_FLOAT : inl_handleparams();\
        agk::StepPhysics( *(float*)g_p[0] );\
        break;\
\
    case AGKI_UPDATE_FLOAT : inl_handleparams();\
        agk::Update( *(float*)g_p[0] );\
        break;\
\
    case AGKI_UPDATE2D_FLOAT : inl_handleparams();\
        agk::Update2D( *(float*)g_p[0] );\
        break;\
\
    case AGKI_UPDATE3D_FLOAT : inl_handleparams();\
        agk::Update3D( *(float*)g_p[0] );\
        break;\
\
    case AGKI_RENDER2DBACK : inl_handleparams();\
        agk::Render2DBack( );\
        break;\
\
    case AGKI_RENDER : inl_handleparams();\
        agk::Render( );\
        break;\
\
    case AGKI_RENDER2DFRONT : inl_handleparams();\
        agk::Render2DFront( );\
        break;\
\
    case AGKI_RENDER3D : inl_handleparams();\
        agk::Render3D( );\
        break;\
\
    case AGKI_SWAP : inl_handleparams();\
        agk::Swap( );\
        break;\
\
    case AGKI_CLEARSCREEN : inl_handleparams();\
        agk::ClearScreen( );\
        break;\
\
    case AGKI_CLEARDEPTHBUFFER : inl_handleparams();\
        agk::ClearDepthBuffer( );\
        break;\
\
    case AGKI_SETGENERATEMIPMAPS_INTEGER : inl_handleparams();\
        agk::SetGenerateMipmaps( *(int*)g_p[0] );\
        break;\
\
    case AGKI_TIMERR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::Timer( );\
        break;\
\
    case AGKI_RESETTIMER : inl_handleparams();\
        agk::ResetTimer( );\
        break;\
\
    case AGKI_GETRUNTIMER_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRunTime( );\
        break;\
\
    case AGKI_GETSECONDSR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSeconds( );\
        break;\
\
    case AGKI_GETFRAMETIMER_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetFrameTime( );\
        break;\
\
    case AGKI_GETMILLISECONDSR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetMilliseconds( );\
        break;\
\
    case AGKI_SHA1R_STRING_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::Sha1( *(char**)g_p[1] );\
        break;\
\
    case AGKI_HTTPENCODER_STRING_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::HTTPEncode( *(char**)g_p[1] );\
        break;\
\
    case AGKI_HTTPDECODER_STRING_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::HTTPDecode( *(char**)g_p[1] );\
        break;\
\
    case AGKI_SETRANDOMSEED_INTEGER : inl_handleparams();\
        agk::SetRandomSeed( *(int*)g_p[0] );\
        break;\
\
    case AGKI_RANDOMR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::Random( );\
        break;\
\
    case AGKI_RANDOMR_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::Random( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_RANDOMSIGNR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::RandomSign( *(int*)g_p[1] );\
        break;\
\
    case AGKI_ATANFULLR_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::ATanFull( *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_ATANFULLRADR_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::ATanFullRad( *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETSORTTEXTURES_INTEGER : inl_handleparams();\
        agk::SetSortTextures( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETSORTDEPTH_INTEGER : inl_handleparams();\
        agk::SetSortDepth( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETSORTTRANSPARENTDEPTH_INTEGER : inl_handleparams();\
        agk::SetSortTransparentDepth( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETSORTCREATED_INTEGER : inl_handleparams();\
        agk::SetSortCreated( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SCREENFPSR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::ScreenFPS( );\
        break;\
\
    case AGKI_GETPOLYGONSDRAWNR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetPolygonsDrawn( );\
        break;\
\
    case AGKI_GETVERTICESPROCESSEDR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetVerticesProcessed( );\
        break;\
\
    case AGKI_ENABLECLEARDEPTH_INTEGER : inl_handleparams();\
        agk::EnableClearDepth( *(int*)g_p[0] );\
        break;\
\
    case AGKI_ENABLECLEARCOLOR_INTEGER : inl_handleparams();\
        agk::EnableClearColor( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETBORDERCOLOR_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetBorderColor( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_SETCLEARCOLOR_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetClearColor( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_LOADIMAGE_INTEGER_STRING_INTEGER : inl_handleparams();\
        agk::LoadImage( *(int*)g_p[0], *(char**)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_LOADIMAGE_INTEGER_STRING : inl_handleparams();\
        agk::LoadImage( *(int*)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_LOADIMAGER_INTEGER_STRING_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::LoadImage( *(char**)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_LOADIMAGER_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::LoadImage( *(char**)g_p[1] );\
        break;\
\
    case AGKI_LOADSUBIMAGE_INTEGER_INTEGER_STRING : inl_handleparams();\
        agk::LoadSubImage( *(int*)g_p[0], *(int*)g_p[1], *(char**)g_p[2] );\
        break;\
\
    case AGKI_LOADSUBIMAGER_INTEGER_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::LoadSubImage( *(int*)g_p[1], *(char**)g_p[2] );\
        break;\
\
    case AGKI_GETIMAGEEXISTSR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetImageExists( *(int*)g_p[1] );\
        break;\
\
    case AGKI_DELETEIMAGE_INTEGER : inl_handleparams();\
        agk::DeleteImage( *(int*)g_p[0] );\
        break;\
\
    case AGKI_DELETEALLIMAGES : inl_handleparams();\
        agk::DeleteAllImages( );\
        break;\
\
    case AGKI_GETIMAGEWIDTHR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetImageWidth( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETIMAGEHEIGHTR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetImageHeight( *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETIMAGEMINFILTER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetImageMinFilter( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETIMAGEMAGFILTER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetImageMagFilter( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETIMAGEWRAPU_INTEGER_INTEGER : inl_handleparams();\
        agk::SetImageWrapU( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETIMAGEWRAPV_INTEGER_INTEGER : inl_handleparams();\
        agk::SetImageWrapV( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETIMAGEMASK_INTEGER_INTEGER_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetImageMask( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3], *(int*)g_p[4], *(int*)g_p[5] );\
        break;\
\
    case AGKI_SETIMAGETRANSPARENTCOLOR_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetImageTransparentColor( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_SAVEIMAGE_INTEGER_STRING : inl_handleparams();\
        agk::SaveImage( *(int*)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_GETIMAGER_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::GetImage( *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_GETIMAGE_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::GetImage( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_GETIMAGEFILENAMER_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::GetImageFilename( *(int*)g_p[1] );\
        break;\
\
    case AGKI_COPYIMAGER_INTEGER_INTEGER_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CopyImage( *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3], *(int*)g_p[4], *(int*)g_p[5] );\
        break;\
\
    case AGKI_COPYIMAGE_INTEGER_INTEGER_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::CopyImage( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3], *(int*)g_p[4], *(int*)g_p[5] );\
        break;\
\
    case AGKI_SHOWCHOOSEIMAGESCREENR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::ShowChooseImageScreen( );\
        break;\
\
    case AGKI_ISCHOOSINGIMAGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::IsChoosingImage( );\
        break;\
\
    case AGKI_GETCHOSENIMAGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetChosenImage( );\
        break;\
\
    case AGKI_SHOWIMAGECAPTURESCREENR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::ShowImageCaptureScreen( );\
        break;\
\
    case AGKI_ISCAPTURINGIMAGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::IsCapturingImage( );\
        break;\
\
    case AGKI_GETCAPTUREDIMAGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetCapturedImage( );\
        break;\
\
    case AGKI_DECODEQRCODER_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::DecodeQRCode( *(int*)g_p[1] );\
        break;\
\
    case AGKI_ENCODEQRCODER_INTEGER_STRING_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::EncodeQRCode( *(char**)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_PRINTIMAGE_INTEGER_FLOAT : inl_handleparams();\
        agk::PrintImage( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETIMAGESAVEPIXELS_INTEGER : inl_handleparams();\
        agk::SetImageSavePixels( *(int*)g_p[0] );\
        break;\
\
    case AGKI_GETSPRITEIMAGEIDR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteImageID( *(int*)g_p[1] );\
        break;\
\
    case AGKI_CREATESPRITE_INTEGER_INTEGER : inl_handleparams();\
        agk::CreateSprite( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_CREATESPRITER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateSprite( *(int*)g_p[1] );\
        break;\
\
    case AGKI_LOADSPRITER_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::LoadSprite( *(char**)g_p[1] );\
        break;\
\
    case AGKI_LOADSPRITE_INTEGER_STRING : inl_handleparams();\
        agk::LoadSprite( *(int*)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_CLONESPRITE_INTEGER_INTEGER : inl_handleparams();\
        agk::CloneSprite( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_CLONESPRITER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CloneSprite( *(int*)g_p[1] );\
        break;\
\
    case AGKI_CREATEDUMMYSPRITE_INTEGER : inl_handleparams();\
        agk::CreateDummySprite( *(int*)g_p[0] );\
        break;\
\
    case AGKI_CREATEDUMMYSPRITER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateDummySprite( );\
        break;\
\
    case AGKI_GETSPRITEEXISTSR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteExists( *(int*)g_p[1] );\
        break;\
\
    case AGKI_DELETESPRITE_INTEGER : inl_handleparams();\
        agk::DeleteSprite( *(int*)g_p[0] );\
        break;\
\
    case AGKI_DELETEALLSPRITES : inl_handleparams();\
        agk::DeleteAllSprites( );\
        break;\
\
    case AGKI_SETSPRITEIMAGE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteImage( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEIMAGE_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteImage( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_SETSPRITEUV_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetSpriteUV( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5], *(float*)g_p[6], *(float*)g_p[7], *(float*)g_p[8] );\
        break;\
\
    case AGKI_RESETSPRITEUV_INTEGER : inl_handleparams();\
        agk::ResetSpriteUV( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETSPRITEPOSITION_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetSpritePosition( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETSPRITEPOSITIONBYOFFSET_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetSpritePositionByOffset( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETSPRITEX_INTEGER_FLOAT : inl_handleparams();\
        agk::SetSpriteX( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEY_INTEGER_FLOAT : inl_handleparams();\
        agk::SetSpriteY( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEANGLE_INTEGER_FLOAT : inl_handleparams();\
        agk::SetSpriteAngle( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEANGLERAD_INTEGER_FLOAT : inl_handleparams();\
        agk::SetSpriteAngleRad( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEDEPTH_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteDepth( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEFLIP_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteFlip( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_SETSPRITESNAP_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteSnap( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEVISIBLE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteVisible( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEACTIVE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteActive( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITEXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpriteX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITEYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpriteY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITEXBYOFFSETR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpriteXByOffset( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITEYBYOFFSETR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpriteYByOffset( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITEWIDTHR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpriteWidth( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITEANGLER_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpriteAngle( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITEANGLERADR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpriteAngleRad( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITEHEIGHTR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpriteHeight( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITEHITTESTR_INTEGER_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteHitTest( *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_GETSPRITEHITR_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteHit( *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_GETSPRITEHITGROUPR_INTEGER_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteHitGroup( *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_GETSPRITEHITCATEGORYR_INTEGER_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteHitCategory( *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_GETSPRITEDEPTHR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteDepth( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITECOLORREDR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteColorRed( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITECOLORGREENR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteColorGreen( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITECOLORBLUER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteColorBlue( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITECOLORALPHAR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteColorAlpha( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITEPLAYINGR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpritePlaying( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITEVISIBLER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteVisible( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITEACTIVER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteActive( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITEGROUPR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteGroup( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITEXFROMPIXELR_FLOAT_INTEGER_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpriteXFromPixel( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETSPRITEYFROMPIXELR_FLOAT_INTEGER_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpriteYFromPixel( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETSPRITEPIXELFROMXR_INTEGER_INTEGER_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpritePixelFromX( *(int*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_GETSPRITEPIXELFROMYR_INTEGER_INTEGER_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpritePixelFromY( *(int*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_GETWORLDXFROMSPRITER_FLOAT_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetWorldXFromSprite( *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_GETWORLDYFROMSPRITER_FLOAT_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetWorldYFromSprite( *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_GETSPRITEXFROMWORLDR_FLOAT_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpriteXFromWorld( *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_GETSPRITEYFROMWORLDR_FLOAT_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpriteYFromWorld( *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_SETSPRITESIZE_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetSpriteSize( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETSPRITEANIMATION_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteAnimation( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_ADDSPRITEANIMATIONFRAME_INTEGER_INTEGER : inl_handleparams();\
        agk::AddSpriteAnimationFrame( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_CLEARSPRITEANIMATIONFRAMES_INTEGER : inl_handleparams();\
        agk::ClearSpriteAnimationFrames( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETSPRITESPEED_INTEGER_FLOAT : inl_handleparams();\
        agk::SetSpriteSpeed( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_PLAYSPRITE_INTEGER : inl_handleparams();\
        agk::PlaySprite( *(int*)g_p[0] );\
        break;\
\
    case AGKI_PLAYSPRITE_INTEGER_FLOAT : inl_handleparams();\
        agk::PlaySprite( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_PLAYSPRITE_INTEGER_FLOAT_INTEGER : inl_handleparams();\
        agk::PlaySprite( *(int*)g_p[0], *(float*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_PLAYSPRITE_INTEGER_FLOAT_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::PlaySprite( *(int*)g_p[0], *(float*)g_p[1], *(int*)g_p[2], *(int*)g_p[3], *(int*)g_p[4] );\
        break;\
\
    case AGKI_STOPSPRITE_INTEGER : inl_handleparams();\
        agk::StopSprite( *(int*)g_p[0] );\
        break;\
\
    case AGKI_RESUMESPRITE_INTEGER : inl_handleparams();\
        agk::ResumeSprite( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETSPRITEFRAME_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteFrame( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITECURRENTFRAMER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteCurrentFrame( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITEFRAMECOUNTR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteFrameCount( *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITETRANSPARENCY_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteTransparency( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEOFFSET_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetSpriteOffset( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETSPRITECOLOR_INTEGER_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteColor( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3], *(int*)g_p[4] );\
        break;\
\
    case AGKI_SETSPRITECOLORRED_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteColorRed( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITECOLORGREEN_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteColorGreen( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITECOLORBLUE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteColorBlue( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITECOLORALPHA_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteColorAlpha( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEUVBORDER_INTEGER_FLOAT : inl_handleparams();\
        agk::SetSpriteUVBorder( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEUVOFFSET_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetSpriteUVOffset( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETSPRITEUVSCALE_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetSpriteUVScale( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_FIXSPRITETOSCREEN_INTEGER_INTEGER : inl_handleparams();\
        agk::FixSpriteToScreen( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITESCALE_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetSpriteScale( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETSPRITESCALEBYOFFSET_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetSpriteScaleByOffset( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETSPRITESCISSOR_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetSpriteScissor( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_DRAWSPRITE_INTEGER : inl_handleparams();\
        agk::DrawSprite( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETPHYSICSSCALE_FLOAT : inl_handleparams();\
        agk::SetPhysicsScale( *(float*)g_p[0] );\
        break;\
\
    case AGKI_SETPHYSICSGRAVITY_FLOAT_FLOAT : inl_handleparams();\
        agk::SetPhysicsGravity( *(float*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETPHYSICSDEBUGON : inl_handleparams();\
        agk::SetPhysicsDebugOn( );\
        break;\
\
    case AGKI_SETPHYSICSDEBUGOFF : inl_handleparams();\
        agk::SetPhysicsDebugOff( );\
        break;\
\
    case AGKI_SETPHYSICSTHREADING_INTEGER : inl_handleparams();\
        agk::SetPhysicsThreading( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETPHYSICSCCD_INTEGER : inl_handleparams();\
        agk::SetPhysicsCCD( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETPHYSICSSLEEPING_INTEGER : inl_handleparams();\
        agk::SetPhysicsSleeping( *(int*)g_p[0] );\
        break;\
\
    case AGKI_GETPHYSICSSOLVETIMER_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetPhysicsSolveTime( );\
        break;\
\
    case AGKI_GETPHYSICSISLANDCOUNTR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetPhysicsIslandCount( );\
        break;\
\
    case AGKI_SETPHYSICSMAXPOLYGONPOINTS_INTEGER : inl_handleparams();\
        agk::SetPhysicsMaxPolygonPoints( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETPHYSICSWALLTOP_INTEGER : inl_handleparams();\
        agk::SetPhysicsWallTop( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETPHYSICSWALLLEFT_INTEGER : inl_handleparams();\
        agk::SetPhysicsWallLeft( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETPHYSICSWALLRIGHT_INTEGER : inl_handleparams();\
        agk::SetPhysicsWallRight( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETPHYSICSWALLBOTTOM_INTEGER : inl_handleparams();\
        agk::SetPhysicsWallBottom( *(int*)g_p[0] );\
        break;\
\
    case AGKI_CREATEPHYSICSFORCER_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CreatePhysicsForce( *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5], *(int*)g_p[6] );\
        break;\
\
    case AGKI_DELETEPHYSICSFORCE_INTEGER : inl_handleparams();\
        agk::DeletePhysicsForce( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETPHYSICSFORCEPOSITION_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetPhysicsForcePosition( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETPHYSICSFORCEPOWER_INTEGER_FLOAT : inl_handleparams();\
        agk::SetPhysicsForcePower( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETPHYSICSFORCERANGE_INTEGER_FLOAT : inl_handleparams();\
        agk::SetPhysicsForceRange( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITESHAPE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteShape( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITESHAPEBOX_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetSpriteShapeBox( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5] );\
        break;\
\
    case AGKI_SETSPRITESHAPECIRCLE_INTEGER_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetSpriteShapeCircle( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_SETSPRITESHAPEPOLYGON_INTEGER_INTEGER_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetSpriteShapePolygon( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_ADDSPRITESHAPEBOX_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::AddSpriteShapeBox( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5] );\
        break;\
\
    case AGKI_ADDSPRITESHAPECIRCLE_INTEGER_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::AddSpriteShapeCircle( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_ADDSPRITESHAPEPOLYGON_INTEGER_INTEGER_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::AddSpriteShapePolygon( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_CLEARSPRITESHAPES_INTEGER : inl_handleparams();\
        agk::ClearSpriteShapes( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETSPRITEPHYSICSCOM_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetSpritePhysicsCOM( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_CALCULATESPRITEPHYSICSCOM_INTEGER : inl_handleparams();\
        agk::CalculateSpritePhysicsCOM( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETSPRITEPHYSICSON_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpritePhysicsOn( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEPHYSICSOFF_INTEGER : inl_handleparams();\
        agk::SetSpritePhysicsOff( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETSPRITEPHYSICSDELETE_INTEGER : inl_handleparams();\
        agk::SetSpritePhysicsDelete( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETSPRITEPHYSICSFRICTION_INTEGER_FLOAT : inl_handleparams();\
        agk::SetSpritePhysicsFriction( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEPHYSICSRESTITUTION_INTEGER_FLOAT : inl_handleparams();\
        agk::SetSpritePhysicsRestitution( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEPHYSICSCANROTATE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpritePhysicsCanRotate( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEPHYSICSVELOCITY_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetSpritePhysicsVelocity( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETSPRITEPHYSICSANGULARVELOCITY_INTEGER_FLOAT : inl_handleparams();\
        agk::SetSpritePhysicsAngularVelocity( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEPHYSICSDAMPING_INTEGER_FLOAT : inl_handleparams();\
        agk::SetSpritePhysicsDamping( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEPHYSICSANGULARDAMPING_INTEGER_FLOAT : inl_handleparams();\
        agk::SetSpritePhysicsAngularDamping( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEPHYSICSISBULLET_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpritePhysicsIsBullet( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEPHYSICSMASS_INTEGER_FLOAT : inl_handleparams();\
        agk::SetSpritePhysicsMass( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEPHYSICSISSENSOR_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpritePhysicsIsSensor( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEGROUP_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteGroup( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITECATEGORYBITS_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteCategoryBits( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITECATEGORYBIT_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteCategoryBit( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_SETSPRITECOLLIDEBITS_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteCollideBits( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITECOLLIDEBIT_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetSpriteCollideBit( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_SETSPRITEPHYSICSFORCE_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetSpritePhysicsForce( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_SETSPRITEPHYSICSTORQUE_INTEGER_FLOAT : inl_handleparams();\
        agk::SetSpritePhysicsTorque( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETSPRITEPHYSICSIMPULSE_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetSpritePhysicsImpulse( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_SETSPRITEPHYSICSANGULARIMPULSE_INTEGER_FLOAT : inl_handleparams();\
        agk::SetSpritePhysicsAngularImpulse( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITEPHYSICSVELOCITYXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpritePhysicsVelocityX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITEPHYSICSVELOCITYYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpritePhysicsVelocityY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITEPHYSICSANGULARVELOCITYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpritePhysicsAngularVelocity( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITEPHYSICSMASSR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpritePhysicsMass( *(int*)g_p[1] );\
        break;\
\
    case AGKI_DELETEJOINT_INTEGER : inl_handleparams();\
        agk::DeleteJoint( *(int*)g_p[0] );\
        break;\
\
    case AGKI_GETJOINTEXISTSR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetJointExists( *(int*)g_p[1] );\
        break;\
\
    case AGKI_CREATEDISTANCEJOINT_INTEGER_INTEGER_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT_INTEGER : inl_handleparams();\
        agk::CreateDistanceJoint( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5], *(float*)g_p[6], *(int*)g_p[7] );\
        break;\
\
    case AGKI_CREATEREVOLUTEJOINT_INTEGER_INTEGER_INTEGER_FLOAT_FLOAT_INTEGER : inl_handleparams();\
        agk::CreateRevoluteJoint( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(int*)g_p[5] );\
        break;\
\
    case AGKI_CREATEPRISMATICJOINT_INTEGER_INTEGER_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT_INTEGER : inl_handleparams();\
        agk::CreatePrismaticJoint( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5], *(float*)g_p[6], *(int*)g_p[7] );\
        break;\
\
    case AGKI_CREATEPULLEYJOINT_INTEGER_INTEGER_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT_INTEGER : inl_handleparams();\
        agk::CreatePulleyJoint( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5], *(float*)g_p[6], *(float*)g_p[7], *(float*)g_p[8], *(float*)g_p[9], *(float*)g_p[10], *(float*)g_p[11], *(int*)g_p[12] );\
        break;\
\
    case AGKI_CREATEMOUSEJOINT_INTEGER_INTEGER_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::CreateMouseJoint( *(int*)g_p[0], *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_CREATELINEJOINT_INTEGER_INTEGER_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT_INTEGER : inl_handleparams();\
        agk::CreateLineJoint( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5], *(float*)g_p[6], *(int*)g_p[7] );\
        break;\
\
    case AGKI_CREATEWELDJOINT_INTEGER_INTEGER_INTEGER_FLOAT_FLOAT_INTEGER : inl_handleparams();\
        agk::CreateWeldJoint( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(int*)g_p[5] );\
        break;\
\
    case AGKI_CREATEGEARJOINT_INTEGER_INTEGER_INTEGER_FLOAT : inl_handleparams();\
        agk::CreateGearJoint( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_CREATEDISTANCEJOINTR_INTEGER_INTEGER_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateDistanceJoint( *(int*)g_p[1], *(int*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5], *(float*)g_p[6], *(int*)g_p[7] );\
        break;\
\
    case AGKI_CREATEREVOLUTEJOINTR_INTEGER_INTEGER_INTEGER_FLOAT_FLOAT_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateRevoluteJoint( *(int*)g_p[1], *(int*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(int*)g_p[5] );\
        break;\
\
    case AGKI_CREATEPRISMATICJOINTR_INTEGER_INTEGER_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CreatePrismaticJoint( *(int*)g_p[1], *(int*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5], *(float*)g_p[6], *(int*)g_p[7] );\
        break;\
\
    case AGKI_CREATEPULLEYJOINT2_INTEGER_INTEGER_FLOAT_INTEGER : inl_handleparams();\
        agk::CreatePulleyJoint2( *(int*)g_p[0], *(int*)g_p[1], *(float*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_FINISHPULLEYJOINTR_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::FinishPulleyJoint( *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5], *(float*)g_p[6], *(float*)g_p[7], *(float*)g_p[8] );\
        break;\
\
    case AGKI_CREATEMOUSEJOINTR_INTEGER_INTEGER_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateMouseJoint( *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_CREATELINEJOINTR_INTEGER_INTEGER_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateLineJoint( *(int*)g_p[1], *(int*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5], *(float*)g_p[6], *(int*)g_p[7] );\
        break;\
\
    case AGKI_CREATEWELDJOINTR_INTEGER_INTEGER_INTEGER_FLOAT_FLOAT_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateWeldJoint( *(int*)g_p[1], *(int*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(int*)g_p[5] );\
        break;\
\
    case AGKI_CREATEGEARJOINTR_INTEGER_INTEGER_INTEGER_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateGearJoint( *(int*)g_p[1], *(int*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_SETJOINTLIMITON_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetJointLimitOn( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETJOINTLIMITOFF_INTEGER : inl_handleparams();\
        agk::SetJointLimitOff( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETJOINTMOTORON_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetJointMotorOn( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETJOINTMOTOROFF_INTEGER : inl_handleparams();\
        agk::SetJointMotorOff( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETJOINTMOUSETARGET_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetJointMouseTarget( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_GETJOINTREACTIONFORCEXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetJointReactionForceX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETJOINTREACTIONFORCEYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetJointReactionForceY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETJOINTREACTIONTORQUER_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetJointReactionTorque( *(int*)g_p[1] );\
        break;\
\
    case AGKI_PHYSICSRAYCASTR_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::PhysicsRayCast( *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_PHYSICSRAYCASTGROUPR_INTEGER_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::PhysicsRayCastGroup( *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5] );\
        break;\
\
    case AGKI_PHYSICSRAYCASTCATEGORYR_INTEGER_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::PhysicsRayCastCategory( *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5] );\
        break;\
\
    case AGKI_SPRITERAYCASTSINGLER_INTEGER_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::SpriteRayCastSingle( *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5] );\
        break;\
\
    case AGKI_SPRITERAYCASTR_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::SpriteRayCast( *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_SPRITERAYCASTGROUPR_INTEGER_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::SpriteRayCastGroup( *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5] );\
        break;\
\
    case AGKI_SPRITERAYCASTCATEGORYR_INTEGER_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::SpriteRayCastCategory( *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5] );\
        break;\
\
    case AGKI_GETRAYCASTSPRITEIDR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRayCastSpriteID( );\
        break;\
\
    case AGKI_GETRAYCASTXR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRayCastX( );\
        break;\
\
    case AGKI_GETRAYCASTYR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRayCastY( );\
        break;\
\
    case AGKI_GETRAYCASTNORMALXR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRayCastNormalX( );\
        break;\
\
    case AGKI_GETRAYCASTNORMALYR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRayCastNormalY( );\
        break;\
\
    case AGKI_GETRAYCASTFRACTIONR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRayCastFraction( );\
        break;\
\
    case AGKI_GETSPRITEINBOXR_INTEGER_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteInBox( *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5] );\
        break;\
\
    case AGKI_GETSPRITEINCIRCLER_INTEGER_INTEGER_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteInCircle( *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_GETSPRITECOLLISIONR_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteCollision( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETSPRITEDISTANCER_FLOAT_INTEGER_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpriteDistance( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETSPRITEDISTANCEPOINT1XR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpriteDistancePoint1X( );\
        break;\
\
    case AGKI_GETSPRITEDISTANCEPOINT1YR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpriteDistancePoint1Y( );\
        break;\
\
    case AGKI_GETSPRITEDISTANCEPOINT2XR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpriteDistancePoint2X( );\
        break;\
\
    case AGKI_GETSPRITEDISTANCEPOINT2YR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpriteDistancePoint2Y( );\
        break;\
\
    case AGKI_GETFIRSTCONTACTR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetFirstContact( );\
        break;\
\
    case AGKI_GETNEXTCONTACTR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetNextContact( );\
        break;\
\
    case AGKI_GETCONTACTWORLDXR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetContactWorldX( );\
        break;\
\
    case AGKI_GETCONTACTWORLDYR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetContactWorldY( );\
        break;\
\
    case AGKI_GETCONTACTSPRITEID1R_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetContactSpriteID1( );\
        break;\
\
    case AGKI_GETCONTACTSPRITEID2R_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetContactSpriteID2( );\
        break;\
\
    case AGKI_GETSPRITEFIRSTCONTACTR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteFirstContact( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSPRITENEXTCONTACTR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteNextContact( );\
        break;\
\
    case AGKI_GETSPRITECONTACTWORLDXR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpriteContactWorldX( );\
        break;\
\
    case AGKI_GETSPRITECONTACTWORLDYR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetSpriteContactWorldY( );\
        break;\
\
    case AGKI_GETSPRITECONTACTSPRITEID2R_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSpriteContactSpriteID2( );\
        break;\
\
    case AGKI_GETPHYSICSCOLLISIONR_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetPhysicsCollision( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETPHYSICSCOLLISIONXR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetPhysicsCollisionX( );\
        break;\
\
    case AGKI_GETPHYSICSCOLLISIONYR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetPhysicsCollisionY( );\
        break;\
\
    case AGKI_GETPHYSICSCOLLISIONWORLDXR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetPhysicsCollisionWorldX( );\
        break;\
\
    case AGKI_GETPHYSICSCOLLISIONWORLDYR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetPhysicsCollisionWorldY( );\
        break;\
\
    case AGKI_CREATEPARTICLES_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::CreateParticles( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_CREATEPARTICLESR_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateParticles( *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_GETPARTICLESEXISTSR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetParticlesExists( *(int*)g_p[1] );\
        break;\
\
    case AGKI_DELETEPARTICLES_INTEGER : inl_handleparams();\
        agk::DeleteParticles( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETPARTICLESPOSITION_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetParticlesPosition( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETPARTICLESDEPTH_INTEGER_INTEGER : inl_handleparams();\
        agk::SetParticlesDepth( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETPARTICLESFREQUENCY_INTEGER_FLOAT : inl_handleparams();\
        agk::SetParticlesFrequency( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETPARTICLESSTARTZONE_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetParticlesStartZone( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_SETPARTICLESDIRECTION_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetParticlesDirection( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETPARTICLESVELOCITYRANGE_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetParticlesVelocityRange( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETPARTICLESANGLE_INTEGER_FLOAT : inl_handleparams();\
        agk::SetParticlesAngle( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETPARTICLESANGLERAD_INTEGER_FLOAT : inl_handleparams();\
        agk::SetParticlesAngleRad( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETPARTICLESSIZE_INTEGER_FLOAT : inl_handleparams();\
        agk::SetParticlesSize( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETPARTICLESLIFE_INTEGER_FLOAT : inl_handleparams();\
        agk::SetParticlesLife( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETPARTICLESMAX_INTEGER_INTEGER : inl_handleparams();\
        agk::SetParticlesMax( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_RESETPARTICLECOUNT_INTEGER : inl_handleparams();\
        agk::ResetParticleCount( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETPARTICLESIMAGE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetParticlesImage( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETPARTICLESVISIBLE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetParticlesVisible( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETPARTICLESACTIVE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetParticlesActive( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETPARTICLESCOLORINTERPOLATION_INTEGER_INTEGER : inl_handleparams();\
        agk::SetParticlesColorInterpolation( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETPARTICLESXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetParticlesX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETPARTICLESYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetParticlesY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETPARTICLESDEPTHR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetParticlesDepth( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETPARTICLESVISIBLER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetParticlesVisible( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETPARTICLESACTIVER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetParticlesActive( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETPARTICLESFREQUENCYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetParticlesFrequency( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETPARTICLESDIRECTIONXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetParticlesDirectionX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETPARTICLESDIRECTIONYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetParticlesDirectionY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETPARTICLESANGLER_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetParticlesAngle( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETPARTICLESANGLERADR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetParticlesAngleRad( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETPARTICLESSIZER_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetParticlesSize( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETPARTICLESLIFER_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetParticlesLife( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETPARTICLESMAXREACHEDR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetParticlesMaxReached( *(int*)g_p[1] );\
        break;\
\
    case AGKI_ADDPARTICLESFORCE_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::AddParticlesForce( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_CLEARPARTICLESFORCES_INTEGER : inl_handleparams();\
        agk::ClearParticlesForces( *(int*)g_p[0] );\
        break;\
\
    case AGKI_ADDPARTICLESCOLORKEYFRAME_INTEGER_FLOAT_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::AddParticlesColorKeyFrame( *(int*)g_p[0], *(float*)g_p[1], *(int*)g_p[2], *(int*)g_p[3], *(int*)g_p[4], *(int*)g_p[5] );\
        break;\
\
    case AGKI_CLEARPARTICLESCOLORS_INTEGER : inl_handleparams();\
        agk::ClearParticlesColors( *(int*)g_p[0] );\
        break;\
\
    case AGKI_FIXPARTICLESTOSCREEN_INTEGER_INTEGER : inl_handleparams();\
        agk::FixParticlesToScreen( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_UPDATEPARTICLES_INTEGER_FLOAT : inl_handleparams();\
        agk::UpdateParticles( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_CREATETEXT_INTEGER_STRING : inl_handleparams();\
        agk::CreateText( *(int*)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_CREATETEXTR_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateText( *(char**)g_p[1] );\
        break;\
\
    case AGKI_GETTEXTEXISTSR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetTextExists( *(int*)g_p[1] );\
        break;\
\
    case AGKI_DELETETEXT_INTEGER : inl_handleparams();\
        agk::DeleteText( *(int*)g_p[0] );\
        break;\
\
    case AGKI_DELETEALLTEXT : inl_handleparams();\
        agk::DeleteAllText( );\
        break;\
\
    case AGKI_SETTEXTSTRING_INTEGER_STRING : inl_handleparams();\
        agk::SetTextString( *(int*)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_SETTEXTPOSITION_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetTextPosition( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETTEXTX_INTEGER_FLOAT : inl_handleparams();\
        agk::SetTextX( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETTEXTY_INTEGER_FLOAT : inl_handleparams();\
        agk::SetTextY( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETTEXTALIGNMENT_INTEGER_INTEGER : inl_handleparams();\
        agk::SetTextAlignment( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETTEXTSIZE_INTEGER_FLOAT : inl_handleparams();\
        agk::SetTextSize( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETTEXTSPACING_INTEGER_FLOAT : inl_handleparams();\
        agk::SetTextSpacing( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETTEXTLINESPACING_INTEGER_FLOAT : inl_handleparams();\
        agk::SetTextLineSpacing( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETTEXTDEPTH_INTEGER_INTEGER : inl_handleparams();\
        agk::SetTextDepth( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETTEXTVISIBLE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetTextVisible( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETTEXTCOLOR_INTEGER_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetTextColor( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3], *(int*)g_p[4] );\
        break;\
\
    case AGKI_SETTEXTCOLORRED_INTEGER_INTEGER : inl_handleparams();\
        agk::SetTextColorRed( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETTEXTCOLORGREEN_INTEGER_INTEGER : inl_handleparams();\
        agk::SetTextColorGreen( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETTEXTCOLORBLUE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetTextColorBlue( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETTEXTCOLORALPHA_INTEGER_INTEGER : inl_handleparams();\
        agk::SetTextColorAlpha( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETTEXTCOLORREDR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetTextColorRed( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETTEXTCOLORGREENR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetTextColorGreen( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETTEXTCOLORBLUER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetTextColorBlue( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETTEXTCOLORALPHAR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetTextColorAlpha( *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETTEXTCHARPOSITION_INTEGER_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetTextCharPosition( *(int*)g_p[0], *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_SETTEXTCHARX_INTEGER_INTEGER_FLOAT : inl_handleparams();\
        agk::SetTextCharX( *(int*)g_p[0], *(int*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETTEXTCHARY_INTEGER_INTEGER_FLOAT : inl_handleparams();\
        agk::SetTextCharY( *(int*)g_p[0], *(int*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETTEXTCHARANGLE_INTEGER_INTEGER_FLOAT : inl_handleparams();\
        agk::SetTextCharAngle( *(int*)g_p[0], *(int*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETTEXTCHARANGLERAD_INTEGER_INTEGER_FLOAT : inl_handleparams();\
        agk::SetTextCharAngleRad( *(int*)g_p[0], *(int*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETTEXTCHARCOLOR_INTEGER_INTEGER_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetTextCharColor( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3], *(int*)g_p[4], *(int*)g_p[5] );\
        break;\
\
    case AGKI_SETTEXTCHARCOLORRED_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetTextCharColorRed( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_SETTEXTCHARCOLORGREEN_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetTextCharColorGreen( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_SETTEXTCHARCOLORBLUE_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetTextCharColorBlue( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_SETTEXTCHARCOLORALPHA_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetTextCharColorAlpha( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETTEXTCHARXR_FLOAT_INTEGER_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetTextCharX( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETTEXTCHARYR_FLOAT_INTEGER_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetTextCharY( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETTEXTCHARANGLER_FLOAT_INTEGER_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetTextCharAngle( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETTEXTCHARANGLERADR_FLOAT_INTEGER_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetTextCharAngleRad( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETTEXTCHARCOLORREDR_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetTextCharColorRed( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETTEXTCHARCOLORGREENR_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetTextCharColorGreen( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETTEXTCHARCOLORBLUER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetTextCharColorBlue( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETTEXTCHARCOLORALPHAR_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetTextCharColorAlpha( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETTEXTXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetTextX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETTEXTYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetTextY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETTEXTLENGTHR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetTextLength( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETTEXTTOTALWIDTHR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetTextTotalWidth( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETTEXTTOTALHEIGHTR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetTextTotalHeight( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETTEXTHITTESTR_INTEGER_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::GetTextHitTest( *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_SETTEXTFONTIMAGE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetTextFontImage( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETTEXTEXTENDEDFONTIMAGE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetTextExtendedFontImage( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETTEXTDEFAULTFONTIMAGE_INTEGER : inl_handleparams();\
        agk::SetTextDefaultFontImage( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETTEXTDEFAULTEXTENDEDFONTIMAGE_INTEGER : inl_handleparams();\
        agk::SetTextDefaultExtendedFontImage( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETTEXTDEFAULTMINFILTER_INTEGER : inl_handleparams();\
        agk::SetTextDefaultMinFilter( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETTEXTDEFAULTMAGFILTER_INTEGER : inl_handleparams();\
        agk::SetTextDefaultMagFilter( *(int*)g_p[0] );\
        break;\
\
    case AGKI_FIXTEXTTOSCREEN_INTEGER_INTEGER : inl_handleparams();\
        agk::FixTextToScreen( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETTEXTMAXWIDTH_INTEGER_FLOAT : inl_handleparams();\
        agk::SetTextMaxWidth( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETTEXTSCISSOR_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetTextScissor( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_GETTEXTVISIBLER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetTextVisible( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETTEXTDEPTHR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetTextDepth( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETTEXTSIZER_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetTextSize( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETTEXTSPACINGR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetTextSpacing( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETTEXTLINESPACINGR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetTextLineSpacing( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETTEXTSTRINGR_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::GetTextString( *(int*)g_p[1] );\
        break;\
\
    case AGKI_PRINT_STRING : inl_handleparams();\
        agk::Print( *(char**)g_p[0] );\
        break;\
\
    case AGKI_PRINT_INTEGER : inl_handleparams();\
        agk::Print( *(int*)g_p[0] );\
        break;\
\
    case AGKI_PRINT_FLOAT : inl_handleparams();\
        agk::Print( *(float*)g_p[0] );\
        break;\
\
    case AGKI_PRINTC_STRING : inl_handleparams();\
        agk::PrintC( *(char**)g_p[0] );\
        break;\
\
    case AGKI_PRINTC_INTEGER : inl_handleparams();\
        agk::PrintC( *(int*)g_p[0] );\
        break;\
\
    case AGKI_PRINTC_FLOAT : inl_handleparams();\
        agk::PrintC( *(float*)g_p[0] );\
        break;\
\
    case AGKI_SETPRINTSIZE_FLOAT : inl_handleparams();\
        agk::SetPrintSize( *(float*)g_p[0] );\
        break;\
\
    case AGKI_SETPRINTSPACING_FLOAT : inl_handleparams();\
        agk::SetPrintSpacing( *(float*)g_p[0] );\
        break;\
\
    case AGKI_SETPRINTCOLOR_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetPrintColor( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_SETPRINTCOLOR_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetPrintColor( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_GETRAWTOUCHCOUNTR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawTouchCount( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWFIRSTTOUCHEVENTR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawFirstTouchEvent( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWNEXTTOUCHEVENTR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawNextTouchEvent( );\
        break;\
\
    case AGKI_GETRAWTOUCHTYPER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawTouchType( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWTOUCHSTARTXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawTouchStartX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWTOUCHSTARTYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawTouchStartY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWTOUCHCURRENTXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawTouchCurrentX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWTOUCHCURRENTYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawTouchCurrentY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWTOUCHLASTXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawTouchLastX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWTOUCHLASTYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawTouchLastY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWTOUCHRELEASEDR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawTouchReleased( *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETRAWTOUCHVALUE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetRawTouchValue( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWTOUCHVALUER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawTouchValue( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWTOUCHTIMER_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawTouchTime( *(int*)g_p[1] );\
        break;\
\
    case AGKI_LOADSOUND_INTEGER_STRING : inl_handleparams();\
        agk::LoadSound( *(int*)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_LOADSOUNDR_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::LoadSound( *(char**)g_p[1] );\
        break;\
\
    case AGKI_PLAYSOUND_INTEGER : inl_handleparams();\
        agk::PlaySound( *(int*)g_p[0] );\
        break;\
\
    case AGKI_PLAYSOUND_INTEGER_INTEGER : inl_handleparams();\
        agk::PlaySound( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_PLAYSOUND_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::PlaySound( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_PLAYSOUND_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::PlaySound( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_STOPSOUND_INTEGER : inl_handleparams();\
        agk::StopSound( *(int*)g_p[0] );\
        break;\
\
    case AGKI_DELETESOUND_INTEGER : inl_handleparams();\
        agk::DeleteSound( *(int*)g_p[0] );\
        break;\
\
    case AGKI_GETSOUNDEXISTSR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSoundExists( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSOUNDINSTANCESR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSoundInstances( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSOUNDSPLAYINGR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSoundsPlaying( *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETSOUNDSYSTEMVOLUME_INTEGER : inl_handleparams();\
        agk::SetSoundSystemVolume( *(int*)g_p[0] );\
        break;\
\
    case AGKI_LOADMUSICR_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::LoadMusic( *(char**)g_p[1] );\
        break;\
\
    case AGKI_LOADMUSIC_INTEGER_STRING : inl_handleparams();\
        agk::LoadMusic( *(int*)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_SETMUSICFILEVOLUME_INTEGER_INTEGER : inl_handleparams();\
        agk::SetMusicFileVolume( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_PLAYMUSIC : inl_handleparams();\
        agk::PlayMusic( );\
        break;\
\
    case AGKI_PLAYMUSIC_INTEGER : inl_handleparams();\
        agk::PlayMusic( *(int*)g_p[0] );\
        break;\
\
    case AGKI_PLAYMUSIC_INTEGER_INTEGER : inl_handleparams();\
        agk::PlayMusic( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_PLAYMUSIC_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::PlayMusic( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_PAUSEMUSIC : inl_handleparams();\
        agk::PauseMusic( );\
        break;\
\
    case AGKI_RESUMEMUSIC : inl_handleparams();\
        agk::ResumeMusic( );\
        break;\
\
    case AGKI_STOPMUSIC : inl_handleparams();\
        agk::StopMusic( );\
        break;\
\
    case AGKI_DELETEMUSIC_INTEGER : inl_handleparams();\
        agk::DeleteMusic( *(int*)g_p[0] );\
        break;\
\
    case AGKI_GETMUSICPLAYINGR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetMusicPlaying( );\
        break;\
\
    case AGKI_SETMUSICSYSTEMVOLUME_INTEGER : inl_handleparams();\
        agk::SetMusicSystemVolume( *(int*)g_p[0] );\
        break;\
\
    case AGKI_GETMUSICEXISTSR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetMusicExists( *(int*)g_p[1] );\
        break;\
\
    case AGKI_RECORDSOUND_STRING : inl_handleparams();\
        agk::RecordSound( *(char**)g_p[0] );\
        break;\
\
    case AGKI_STOPSOUNDRECORDING : inl_handleparams();\
        agk::StopSoundRecording( );\
        break;\
\
    case AGKI_ISSOUNDRECORDINGR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::IsSoundRecording( );\
        break;\
\
    case AGKI_DELETEFILE_STRING : inl_handleparams();\
        agk::DeleteFile( *(char**)g_p[0] );\
        break;\
\
    case AGKI_GETFILEEXISTSR_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::GetFileExists( *(char**)g_p[1] );\
        break;\
\
    case AGKI_CHOOSERAWFILER_STRING_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::ChooseRawFile( *(char**)g_p[1] );\
        break;\
\
    case AGKI_OPENTOWRITE_INTEGER_STRING_INTEGER : inl_handleparams();\
        agk::OpenToWrite( *(int*)g_p[0], *(char**)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_OPENTOWRITE_INTEGER_STRING : inl_handleparams();\
        agk::OpenToWrite( *(int*)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_OPENTOWRITER_INTEGER_STRING_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::OpenToWrite( *(char**)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_OPENTOWRITER_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::OpenToWrite( *(char**)g_p[1] );\
        break;\
\
    case AGKI_OPENTOREADR_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::OpenToRead( *(char**)g_p[1] );\
        break;\
\
    case AGKI_OPENTOREAD_INTEGER_STRING : inl_handleparams();\
        agk::OpenToRead( *(int*)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_FILEISOPENR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::FileIsOpen( *(int*)g_p[1] );\
        break;\
\
    case AGKI_CLOSEFILE_INTEGER : inl_handleparams();\
        agk::CloseFile( *(int*)g_p[0] );\
        break;\
\
    case AGKI_FILEEOFR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::FileEOF( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETFILESIZER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetFileSize( *(int*)g_p[1] );\
        break;\
\
    case AGKI_WRITEBYTE_INTEGER_INTEGER : inl_handleparams();\
        agk::WriteByte( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_WRITEINTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::WriteInteger( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_WRITEFLOAT_INTEGER_FLOAT : inl_handleparams();\
        agk::WriteFloat( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_WRITESTRING_INTEGER_STRING : inl_handleparams();\
        agk::WriteString( *(int*)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_WRITELINE_INTEGER_STRING : inl_handleparams();\
        agk::WriteLine( *(int*)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_READBYTER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::ReadByte( *(int*)g_p[1] );\
        break;\
\
    case AGKI_READINTEGERR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::ReadInteger( *(int*)g_p[1] );\
        break;\
\
    case AGKI_READFLOATR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::ReadFloat( *(int*)g_p[1] );\
        break;\
\
    case AGKI_READSTRINGR_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::ReadString( *(int*)g_p[1] );\
        break;\
\
    case AGKI_READLINER_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::ReadLine( *(int*)g_p[1] );\
        break;\
\
    case AGKI_STRR_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::Str( *(int*)g_p[1] );\
        break;\
\
    case AGKI_STRR_STRING_FLOAT : inl_handleparams();\
        *(char**)g_p[0] = agk::Str( *(float*)g_p[1] );\
        break;\
\
    case AGKI_STRR_STRING_FLOAT_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::Str( *(float*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_BINR_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::Bin( *(int*)g_p[1] );\
        break;\
\
    case AGKI_HEXR_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::Hex( *(int*)g_p[1] );\
        break;\
\
    case AGKI_VALR_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::Val( *(char**)g_p[1] );\
        break;\
\
    case AGKI_VALR_INTEGER_STRING_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::Val( *(char**)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_VALFLOATR_FLOAT_STRING : inl_handleparams();\
        *(float*)g_p[0] = agk::ValFloat( *(char**)g_p[1] );\
        break;\
\
    case AGKI_LEFTR_STRING_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::Left( *(char**)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_RIGHTR_STRING_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::Right( *(char**)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_MIDR_STRING_STRING_INTEGER_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::Mid( *(char**)g_p[1], *(int*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_ASCR_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::Asc( *(char**)g_p[1] );\
        break;\
\
    case AGKI_LENR_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::Len( *(char**)g_p[1] );\
        break;\
\
    case AGKI_CHRR_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::Chr( *(int*)g_p[1] );\
        break;\
\
    case AGKI_LOWERR_STRING_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::Lower( *(char**)g_p[1] );\
        break;\
\
    case AGKI_UPPERR_STRING_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::Upper( *(char**)g_p[1] );\
        break;\
\
    case AGKI_SPACESR_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::Spaces( *(int*)g_p[1] );\
        break;\
\
    case AGKI_COUNTSTRINGTOKENSR_INTEGER_STRING_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::CountStringTokens( *(char**)g_p[1], *(char**)g_p[2] );\
        break;\
\
    case AGKI_GETSTRINGTOKENR_STRING_STRING_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::GetStringToken( *(char**)g_p[1], *(char**)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_GETCURRENTDIRR_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetCurrentDir( );\
        break;\
\
    case AGKI_GETFOLDERR_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetFolder( );\
        break;\
\
    case AGKI_SETFOLDERR_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::SetFolder( *(char**)g_p[1] );\
        break;\
\
    case AGKI_GETFIRSTFOLDERR_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetFirstFolder( );\
        break;\
\
    case AGKI_GETNEXTFOLDERR_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetNextFolder( );\
        break;\
\
    case AGKI_GETFIRSTFILER_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetFirstFile( );\
        break;\
\
    case AGKI_GETNEXTFILER_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetNextFile( );\
        break;\
\
    case AGKI_CREATEBROADCASTLISTENERR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateBroadcastListener( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETBROADCASTMESSAGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetBroadcastMessage( *(int*)g_p[1] );\
        break;\
\
    case AGKI_DELETEBROADCASTLISTENER_INTEGER : inl_handleparams();\
        agk::DeleteBroadcastListener( *(int*)g_p[0] );\
        break;\
\
    case AGKI_HOSTNETWORKR_INTEGER_STRING_STRING_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::HostNetwork( *(char**)g_p[1], *(char**)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_SETNETWORKNOMORECLIENTS_INTEGER : inl_handleparams();\
        agk::SetNetworkNoMoreClients( *(int*)g_p[0] );\
        break;\
\
    case AGKI_JOINNETWORKR_INTEGER_STRING_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::JoinNetwork( *(char**)g_p[1], *(char**)g_p[2] );\
        break;\
\
    case AGKI_JOINNETWORKR_INTEGER_STRING_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::JoinNetwork( *(char**)g_p[1], *(int*)g_p[2], *(char**)g_p[3] );\
        break;\
\
    case AGKI_ISNETWORKACTIVER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::IsNetworkActive( *(int*)g_p[1] );\
        break;\
\
    case AGKI_CLOSENETWORK_INTEGER : inl_handleparams();\
        agk::CloseNetwork( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETNETWORKLATENCY_INTEGER_INTEGER : inl_handleparams();\
        agk::SetNetworkLatency( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETNETWORKMYCLIENTIDR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetNetworkMyClientID( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETNETWORKNUMCLIENTSR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetNetworkNumClients( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETNETWORKFIRSTCLIENTR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetNetworkFirstClient( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETNETWORKNEXTCLIENTR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetNetworkNextClient( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETNETWORKCLIENTDISCONNECTEDR_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetNetworkClientDisconnected( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_DELETENETWORKCLIENT_INTEGER_INTEGER : inl_handleparams();\
        agk::DeleteNetworkClient( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETNETWORKCLIENTNAMER_STRING_INTEGER_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::GetNetworkClientName( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETNETWORKCLIENTPINGR_FLOAT_INTEGER_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetNetworkClientPing( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETNETWORKSERVERIDR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetNetworkServerID( *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETNETWORKLOCALINTEGER_INTEGER_STRING_INTEGER : inl_handleparams();\
        agk::SetNetworkLocalInteger( *(int*)g_p[0], *(char**)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_SETNETWORKLOCALINTEGER_INTEGER_STRING_INTEGER_INTEGER : inl_handleparams();\
        agk::SetNetworkLocalInteger( *(int*)g_p[0], *(char**)g_p[1], *(int*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_SETNETWORKLOCALFLOAT_INTEGER_STRING_FLOAT : inl_handleparams();\
        agk::SetNetworkLocalFloat( *(int*)g_p[0], *(char**)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETNETWORKLOCALFLOAT_INTEGER_STRING_FLOAT_INTEGER : inl_handleparams();\
        agk::SetNetworkLocalFloat( *(int*)g_p[0], *(char**)g_p[1], *(float*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_GETNETWORKCLIENTINTEGERR_INTEGER_INTEGER_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::GetNetworkClientInteger( *(int*)g_p[1], *(int*)g_p[2], *(char**)g_p[3] );\
        break;\
\
    case AGKI_GETNETWORKCLIENTFLOATR_FLOAT_INTEGER_INTEGER_STRING : inl_handleparams();\
        *(float*)g_p[0] = agk::GetNetworkClientFloat( *(int*)g_p[1], *(int*)g_p[2], *(char**)g_p[3] );\
        break;\
\
    case AGKI_CREATENETWORKMESSAGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateNetworkMessage( );\
        break;\
\
    case AGKI_ADDNETWORKMESSAGEINTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::AddNetworkMessageInteger( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_ADDNETWORKMESSAGEFLOAT_INTEGER_FLOAT : inl_handleparams();\
        agk::AddNetworkMessageFloat( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_ADDNETWORKMESSAGESTRING_INTEGER_STRING : inl_handleparams();\
        agk::AddNetworkMessageString( *(int*)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_GETNETWORKMESSAGEFROMIPR_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::GetNetworkMessageFromIP( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETNETWORKMESSAGEFROMCLIENTR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetNetworkMessageFromClient( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETNETWORKMESSAGEINTEGERR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetNetworkMessageInteger( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETNETWORKMESSAGEFLOATR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetNetworkMessageFloat( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETNETWORKMESSAGESTRINGR_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::GetNetworkMessageString( *(int*)g_p[1] );\
        break;\
\
    case AGKI_DELETENETWORKMESSAGE_INTEGER : inl_handleparams();\
        agk::DeleteNetworkMessage( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SENDNETWORKMESSAGE_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SendNetworkMessage( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETNETWORKMESSAGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetNetworkMessage( *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETNETWORKCLIENTUSERDATA_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetNetworkClientUserData( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_GETNETWORKCLIENTUSERDATAR_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetNetworkClientUserData( *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_CREATEHTTPCONNECTIONR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateHTTPConnection( );\
        break;\
\
    case AGKI_DELETEHTTPCONNECTION_INTEGER : inl_handleparams();\
        agk::DeleteHTTPConnection( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETHTTPHOSTR_INTEGER_INTEGER_STRING_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::SetHTTPHost( *(int*)g_p[1], *(char**)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_SETHTTPHOSTR_INTEGER_INTEGER_STRING_INTEGER_STRING_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::SetHTTPHost( *(int*)g_p[1], *(char**)g_p[2], *(int*)g_p[3], *(char**)g_p[4], *(char**)g_p[5] );\
        break;\
\
    case AGKI_CLOSEHTTPCONNECTION_INTEGER : inl_handleparams();\
        agk::CloseHTTPConnection( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SENDHTTPREQUESTR_STRING_INTEGER_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::SendHTTPRequest( *(int*)g_p[1], *(char**)g_p[2] );\
        break;\
\
    case AGKI_SENDHTTPREQUESTR_STRING_INTEGER_STRING_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::SendHTTPRequest( *(int*)g_p[1], *(char**)g_p[2], *(char**)g_p[3] );\
        break;\
\
    case AGKI_SENDHTTPREQUESTASYNCR_INTEGER_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::SendHTTPRequestASync( *(int*)g_p[1], *(char**)g_p[2] );\
        break;\
\
    case AGKI_SENDHTTPREQUESTASYNCR_INTEGER_INTEGER_STRING_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::SendHTTPRequestASync( *(int*)g_p[1], *(char**)g_p[2], *(char**)g_p[3] );\
        break;\
\
    case AGKI_SENDHTTPFILER_INTEGER_INTEGER_STRING_STRING_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::SendHTTPFile( *(int*)g_p[1], *(char**)g_p[2], *(char**)g_p[3], *(char**)g_p[4] );\
        break;\
\
    case AGKI_GETHTTPRESPONSER_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::GetHTTPResponse( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETHTTPRESPONSEREADYR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetHTTPResponseReady( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETHTTPFILER_INTEGER_INTEGER_STRING_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::GetHTTPFile( *(int*)g_p[1], *(char**)g_p[2], *(char**)g_p[3] );\
        break;\
\
    case AGKI_GETHTTPFILER_INTEGER_INTEGER_STRING_STRING_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::GetHTTPFile( *(int*)g_p[1], *(char**)g_p[2], *(char**)g_p[3], *(char**)g_p[4] );\
        break;\
\
    case AGKI_GETHTTPFILECOMPLETER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetHTTPFileComplete( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETHTTPFILEPROGRESSR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetHTTPFileProgress( *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETERRORMODE_INTEGER : inl_handleparams();\
        agk::SetErrorMode( *(int*)g_p[0] );\
        break;\
\
    case AGKI_GETLASTERRORR_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetLastError( );\
        break;\
\
    case AGKI_GETERROROCCURREDR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetErrorOccurred( );\
        break;\
\
    case AGKI_MESSAGE_STRING : inl_handleparams();\
        agk::Message( *(char**)g_p[0] );\
        break;\
\
    case AGKI_GETJOYSTICKEXISTSR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetJoystickExists( );\
        break;\
\
    case AGKI_GETRAWMOUSEXR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawMouseX( );\
        break;\
\
    case AGKI_GETRAWMOUSEYR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawMouseY( );\
        break;\
\
    case AGKI_GETRAWMOUSEWHEELR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawMouseWheel( );\
        break;\
\
    case AGKI_GETRAWMOUSEWHEELDELTAR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawMouseWheelDelta( );\
        break;\
\
    case AGKI_GETRAWMOUSELEFTPRESSEDR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawMouseLeftPressed( );\
        break;\
\
    case AGKI_GETRAWMOUSELEFTSTATER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawMouseLeftState( );\
        break;\
\
    case AGKI_GETRAWMOUSELEFTRELEASEDR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawMouseLeftReleased( );\
        break;\
\
    case AGKI_GETRAWMOUSERIGHTPRESSEDR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawMouseRightPressed( );\
        break;\
\
    case AGKI_GETRAWMOUSERIGHTSTATER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawMouseRightState( );\
        break;\
\
    case AGKI_GETRAWMOUSERIGHTRELEASEDR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawMouseRightReleased( );\
        break;\
\
    case AGKI_GETRAWMOUSEMIDDLEPRESSEDR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawMouseMiddlePressed( );\
        break;\
\
    case AGKI_GETRAWMOUSEMIDDLESTATER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawMouseMiddleState( );\
        break;\
\
    case AGKI_GETRAWMOUSEMIDDLERELEASEDR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawMouseMiddleReleased( );\
        break;\
\
    case AGKI_GETRAWACCELXR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawAccelX( );\
        break;\
\
    case AGKI_GETRAWACCELYR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawAccelY( );\
        break;\
\
    case AGKI_GETRAWACCELZR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawAccelZ( );\
        break;\
\
    case AGKI_COMPLETERAWJOYSTICKDETECTION : inl_handleparams();\
        agk::CompleteRawJoystickDetection( );\
        break;\
\
    case AGKI_GETRAWJOYSTICKEXISTSR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawJoystickExists( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWJOYSTICKXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawJoystickX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWJOYSTICKYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawJoystickY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWJOYSTICKZR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawJoystickZ( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWJOYSTICKRXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawJoystickRX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWJOYSTICKRYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawJoystickRY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWJOYSTICKRZR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawJoystickRZ( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWJOYSTICKBUTTONPRESSEDR_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawJoystickButtonPressed( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETRAWJOYSTICKBUTTONSTATER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawJoystickButtonState( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETRAWJOYSTICKBUTTONRELEASEDR_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawJoystickButtonReleased( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_SETRAWJOYSTICKDEADZONE_FLOAT : inl_handleparams();\
        agk::SetRawJoystickDeadZone( *(float*)g_p[0] );\
        break;\
\
    case AGKI_ADDVIRTUALJOYSTICK_INTEGER_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::AddVirtualJoystick( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_DELETEVIRTUALJOYSTICK_INTEGER : inl_handleparams();\
        agk::DeleteVirtualJoystick( *(int*)g_p[0] );\
        break;\
\
    case AGKI_GETVIRTUALJOYSTICKEXISTSR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetVirtualJoystickExists( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETVIRTUALJOYSTICKXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetVirtualJoystickX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETVIRTUALJOYSTICKYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetVirtualJoystickY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETVIRTUALJOYSTICKALPHA_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetVirtualJoystickAlpha( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_SETVIRTUALJOYSTICKPOSITION_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetVirtualJoystickPosition( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETVIRTUALJOYSTICKSIZE_INTEGER_FLOAT : inl_handleparams();\
        agk::SetVirtualJoystickSize( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETVIRTUALJOYSTICKACTIVE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetVirtualJoystickActive( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETVIRTUALJOYSTICKVISIBLE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetVirtualJoystickVisible( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETVIRTUALJOYSTICKIMAGEINNER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetVirtualJoystickImageInner( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETVIRTUALJOYSTICKIMAGEOUTER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetVirtualJoystickImageOuter( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETVIRTUALJOYSTICKDEADZONE_FLOAT : inl_handleparams();\
        agk::SetVirtualJoystickDeadZone( *(float*)g_p[0] );\
        break;\
\
    case AGKI_ADDVIRTUALBUTTON_INTEGER_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::AddVirtualButton( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_DELETEVIRTUALBUTTON_INTEGER : inl_handleparams();\
        agk::DeleteVirtualButton( *(int*)g_p[0] );\
        break;\
\
    case AGKI_GETVIRTUALBUTTONEXISTSR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetVirtualButtonExists( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETVIRTUALBUTTONPRESSEDR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetVirtualButtonPressed( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETVIRTUALBUTTONRELEASEDR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetVirtualButtonReleased( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETVIRTUALBUTTONSTATER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetVirtualButtonState( *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETVIRTUALBUTTONCOLOR_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetVirtualButtonColor( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_SETVIRTUALBUTTONALPHA_INTEGER_INTEGER : inl_handleparams();\
        agk::SetVirtualButtonAlpha( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETVIRTUALBUTTONPOSITION_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetVirtualButtonPosition( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETVIRTUALBUTTONSIZE_INTEGER_FLOAT : inl_handleparams();\
        agk::SetVirtualButtonSize( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETVIRTUALBUTTONACTIVE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetVirtualButtonActive( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETVIRTUALBUTTONVISIBLE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetVirtualButtonVisible( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETVIRTUALBUTTONIMAGEUP_INTEGER_INTEGER : inl_handleparams();\
        agk::SetVirtualButtonImageUp( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETVIRTUALBUTTONIMAGEDOWN_INTEGER_INTEGER : inl_handleparams();\
        agk::SetVirtualButtonImageDown( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETVIRTUALBUTTONTEXT_INTEGER_STRING : inl_handleparams();\
        agk::SetVirtualButtonText( *(int*)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_GETRAWKEYPRESSEDR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawKeyPressed( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWKEYSTATER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawKeyState( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWKEYRELEASEDR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawKeyReleased( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWLASTKEYR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawLastKey( );\
        break;\
\
    case AGKI_GETDIRECTIONXR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetDirectionX( );\
        break;\
\
    case AGKI_GETDIRECTIONYR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetDirectionY( );\
        break;\
\
    case AGKI_GETDIRECTIONANGLER_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetDirectionAngle( );\
        break;\
\
    case AGKI_GETDIRECTIONSPEEDR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetDirectionSpeed( );\
        break;\
\
    case AGKI_GETPOINTERPRESSEDR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetPointerPressed( );\
        break;\
\
    case AGKI_GETPOINTERRELEASEDR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetPointerReleased( );\
        break;\
\
    case AGKI_GETPOINTERSTATER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetPointerState( );\
        break;\
\
    case AGKI_GETPOINTERXR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetPointerX( );\
        break;\
\
    case AGKI_GETPOINTERYR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetPointerY( );\
        break;\
\
    case AGKI_GETJOYSTICKXR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetJoystickX( );\
        break;\
\
    case AGKI_GETJOYSTICKYR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetJoystickY( );\
        break;\
\
    case AGKI_SETJOYSTICKDEADZONE_FLOAT : inl_handleparams();\
        agk::SetJoystickDeadZone( *(float*)g_p[0] );\
        break;\
\
    case AGKI_SETJOYSTICKSCREENPOSITION_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetJoystickScreenPosition( *(float*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_GETBUTTONPRESSEDR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetButtonPressed( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETBUTTONSTATER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetButtonState( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETBUTTONRELEASEDR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetButtonReleased( *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETBUTTONSCREENPOSITION_INTEGER_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetButtonScreenPosition( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_STARTTEXTINPUT : inl_handleparams();\
        agk::StartTextInput( );\
        break;\
\
    case AGKI_STARTTEXTINPUT_STRING : inl_handleparams();\
        agk::StartTextInput( *(char**)g_p[0] );\
        break;\
\
    case AGKI_STOPTEXTINPUT : inl_handleparams();\
        agk::StopTextInput( );\
        break;\
\
    case AGKI_GETTEXTINPUTSTATER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetTextInputState( );\
        break;\
\
    case AGKI_GETTEXTINPUTCOMPLETEDR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetTextInputCompleted( );\
        break;\
\
    case AGKI_GETTEXTINPUTCANCELLEDR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetTextInputCancelled( );\
        break;\
\
    case AGKI_GETTEXTINPUTR_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetTextInput( );\
        break;\
\
    case AGKI_GETLASTCHARR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetLastChar( );\
        break;\
\
    case AGKI_SETCURSORBLINKTIME_FLOAT : inl_handleparams();\
        agk::SetCursorBlinkTime( *(float*)g_p[0] );\
        break;\
\
    case AGKI_SETTEXTINPUTMAXCHARS_INTEGER : inl_handleparams();\
        agk::SetTextInputMaxChars( *(int*)g_p[0] );\
        break;\
\
    case AGKI_CREATEEDITBOX_INTEGER : inl_handleparams();\
        agk::CreateEditBox( *(int*)g_p[0] );\
        break;\
\
    case AGKI_CREATEEDITBOXR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateEditBox( );\
        break;\
\
    case AGKI_GETEDITBOXEXISTSR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetEditBoxExists( *(int*)g_p[1] );\
        break;\
\
    case AGKI_DELETEEDITBOX_INTEGER : inl_handleparams();\
        agk::DeleteEditBox( *(int*)g_p[0] );\
        break;\
\
    case AGKI_GETEDITBOXHASFOCUSR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetEditBoxHasFocus( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETCURRENTEDITBOXR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetCurrentEditBox( );\
        break;\
\
    case AGKI_SETEDITBOXPOSITION_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetEditBoxPosition( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETEDITBOXSIZE_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetEditBoxSize( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETEDITBOXDEPTH_INTEGER_INTEGER : inl_handleparams();\
        agk::SetEditBoxDepth( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETEDITBOXBORDERSIZE_INTEGER_FLOAT : inl_handleparams();\
        agk::SetEditBoxBorderSize( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETEDITBOXBORDERCOLOR_INTEGER_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetEditBoxBorderColor( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3], *(int*)g_p[4] );\
        break;\
\
    case AGKI_SETEDITBOXBACKGROUNDCOLOR_INTEGER_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetEditBoxBackgroundColor( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3], *(int*)g_p[4] );\
        break;\
\
    case AGKI_SETEDITBOXTEXT_INTEGER_STRING : inl_handleparams();\
        agk::SetEditBoxText( *(int*)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_SETEDITBOXTEXTCOLOR_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetEditBoxTextColor( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_SETEDITBOXCURSORCOLOR_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetEditBoxCursorColor( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_SETEDITBOXFONTIMAGE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetEditBoxFontImage( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETEDITBOXEXTENDEDFONTIMAGE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetEditBoxExtendedFontImage( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETEDITBOXTEXTSIZE_INTEGER_FLOAT : inl_handleparams();\
        agk::SetEditBoxTextSize( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETEDITBOXFOCUS_INTEGER_INTEGER : inl_handleparams();\
        agk::SetEditBoxFocus( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETEDITBOXACTIVE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetEditBoxActive( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETEDITBOXVISIBLE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetEditBoxVisible( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETEDITBOXBORDERIMAGE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetEditBoxBorderImage( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETEDITBOXBACKGROUNDIMAGE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetEditBoxBackgroundImage( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETEDITBOXCURSORBLINKTIME_INTEGER_FLOAT : inl_handleparams();\
        agk::SetEditBoxCursorBlinkTime( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETEDITBOXCURSORWIDTH_INTEGER_FLOAT : inl_handleparams();\
        agk::SetEditBoxCursorWidth( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_SETEDITBOXMAXCHARS_INTEGER_INTEGER : inl_handleparams();\
        agk::SetEditBoxMaxChars( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETEDITBOXMAXLINES_INTEGER_INTEGER : inl_handleparams();\
        agk::SetEditBoxMaxLines( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETEDITBOXMULTILINE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetEditBoxMultiLine( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETEDITBOXSCISSOR_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetEditBoxScissor( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_SETEDITBOXPASSWORDMODE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetEditBoxPasswordMode( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETEDITBOXUSEALTERNATEINPUT_INTEGER_INTEGER : inl_handleparams();\
        agk::SetEditBoxUseAlternateInput( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETEDITBOXWRAPMODE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetEditBoxWrapMode( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_FIXEDITBOXTOSCREEN_INTEGER_INTEGER : inl_handleparams();\
        agk::FixEditBoxToScreen( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETEDITBOXTEXTR_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::GetEditBoxText( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETEDITBOXXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetEditBoxX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETEDITBOXYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetEditBoxY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETEDITBOXWIDTHR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetEditBoxWidth( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETEDITBOXHEIGHTR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetEditBoxHeight( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETEDITBOXCHANGEDR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetEditBoxChanged( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETEDITBOXACTIVER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetEditBoxActive( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETEDITBOXVISIBLER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetEditBoxVisible( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETEDITBOXLINESR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetEditBoxLines( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETMANAGEDSPRITEDRAWNCOUNTR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetManagedSpriteDrawnCount( );\
        break;\
\
    case AGKI_GETMANAGEDSPRITECOUNTR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetManagedSpriteCount( );\
        break;\
\
    case AGKI_GETMANAGEDSPRITESORTEDCOUNTR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetManagedSpriteSortedCount( );\
        break;\
\
    case AGKI_GETPIXELSDRAWNR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetPixelsDrawn( );\
        break;\
\
    case AGKI_GETMANAGEDSPRITEDRAWCALLSR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetManagedSpriteDrawCalls( );\
        break;\
\
    case AGKI_GETPARTICLEDRAWNPOINTCOUNTR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetParticleDrawnPointCount( );\
        break;\
\
    case AGKI_GETPARTICLEDRAWNQUADCOUNTR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetParticleDrawnQuadCount( );\
        break;\
\
    case AGKI_GETUPDATETIMER_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetUpdateTime( );\
        break;\
\
    case AGKI_GETPHYSICSTIMER_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetPhysicsTime( );\
        break;\
\
    case AGKI_GETDRAWINGSETUPTIMER_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetDrawingSetupTime( );\
        break;\
\
    case AGKI_GETDRAWINGTIMER_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetDrawingTime( );\
        break;\
\
    case AGKI_GETLOADEDIMAGESR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetLoadedImages( );\
        break;\
\
    case AGKI_GETUNASSIGNEDIMAGESR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetUnassignedImages( );\
        break;\
\
    case AGKI_GETUNASSIGNEDIMAGEFILENAMER_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::GetUnassignedImageFileName( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETLEAPYEARR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetLeapYear( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETUNIXFROMDATER_INTEGER_INTEGER_INTEGER_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetUnixFromDate( *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3], *(int*)g_p[4], *(int*)g_p[5], *(int*)g_p[6] );\
        break;\
\
    case AGKI_GETYEARFROMUNIXR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetYearFromUnix( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETMONTHFROMUNIXR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetMonthFromUnix( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETDAYSFROMUNIXR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetDaysFromUnix( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETHOURSFROMUNIXR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetHoursFromUnix( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETMINUTESFROMUNIXR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetMinutesFromUnix( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSECONDSFROMUNIXR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetSecondsFromUnix( *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETINNERACTIVEDETAILS_STRING : inl_handleparams();\
        agk::SetInneractiveDetails( *(char**)g_p[0] );\
        break;\
\
    case AGKI_CREATEADVERT_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::CreateAdvert( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_CREATEADVERTEX_INTEGER_INTEGER_INTEGER_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::CreateAdvertEx( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3], *(float*)g_p[4], *(float*)g_p[5] );\
        break;\
\
    case AGKI_SETADVERTPOSITION_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetAdvertPosition( *(float*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETADVERTLOCATION_INTEGER_INTEGER_FLOAT : inl_handleparams();\
        agk::SetAdvertLocation( *(int*)g_p[0], *(int*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETADVERTLOCATIONEX_INTEGER_INTEGER_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetAdvertLocationEx( *(int*)g_p[0], *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_DELETEADVERT : inl_handleparams();\
        agk::DeleteAdvert( );\
        break;\
\
    case AGKI_CREATEZIP_INTEGER_STRING : inl_handleparams();\
        agk::CreateZip( *(int*)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_CREATEZIPR_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateZip( *(char**)g_p[1] );\
        break;\
\
    case AGKI_ADDZIPENTRY_INTEGER_STRING_STRING : inl_handleparams();\
        agk::AddZipEntry( *(int*)g_p[0], *(char**)g_p[1], *(char**)g_p[2] );\
        break;\
\
    case AGKI_CLOSEZIP_INTEGER : inl_handleparams();\
        agk::CloseZip( *(int*)g_p[0] );\
        break;\
\
    case AGKI_EXTRACTZIP_STRING_STRING : inl_handleparams();\
        agk::ExtractZip( *(char**)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_LOG_STRING : inl_handleparams();\
        agk::Log( *(char**)g_p[0] );\
        break;\
\
    case AGKI_RATEAPP_STRING : inl_handleparams();\
        agk::RateApp( *(char**)g_p[0] );\
        break;\
\
    case AGKI_RATEAPP_STRING_STRING : inl_handleparams();\
        agk::RateApp( *(char**)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_RATEAPP_STRING_STRING_STRING : inl_handleparams();\
        agk::RateApp( *(char**)g_p[0], *(char**)g_p[1], *(char**)g_p[2] );\
        break;\
\
    case AGKI_INAPPPURCHASESETTITLE_STRING : inl_handleparams();\
        agk::InAppPurchaseSetTitle( *(char**)g_p[0] );\
        break;\
\
    case AGKI_INAPPPURCHASEADDPRODUCTID_STRING_INTEGER : inl_handleparams();\
        agk::InAppPurchaseAddProductID( *(char**)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_INAPPPURCHASESETUP : inl_handleparams();\
        agk::InAppPurchaseSetup( );\
        break;\
\
    case AGKI_GETINAPPPURCHASEAVAILABLER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetInAppPurchaseAvailable( *(int*)g_p[1] );\
        break;\
\
    case AGKI_INAPPPURCHASEACTIVATE_INTEGER : inl_handleparams();\
        agk::InAppPurchaseActivate( *(int*)g_p[0] );\
        break;\
\
    case AGKI_GETINAPPPURCHASESTATER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetInAppPurchaseState( );\
        break;\
\
    case AGKI_INAPPPURCHASERESTORE : inl_handleparams();\
        agk::InAppPurchaseRestore( );\
        break;\
\
    case AGKI_SETADMOBDETAILS_STRING : inl_handleparams();\
        agk::SetAdMobDetails( *(char**)g_p[0] );\
        break;\
\
    case AGKI_SETADVERTVISIBLE_INTEGER : inl_handleparams();\
        agk::SetAdvertVisible( *(int*)g_p[0] );\
        break;\
\
    case AGKI_REQUESTADVERTREFRESH : inl_handleparams();\
        agk::RequestAdvertRefresh( );\
        break;\
\
    case AGKI_TWITTERSETUP_STRING_STRING : inl_handleparams();\
        agk::TwitterSetup( *(char**)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_TWITTERMESSAGE_STRING : inl_handleparams();\
        agk::TwitterMessage( *(char**)g_p[0] );\
        break;\
\
    case AGKI_FACEBOOKSETUP_STRING : inl_handleparams();\
        agk::FacebookSetup( *(char**)g_p[0] );\
        break;\
\
    case AGKI_GETFACEBOOKLOGGEDINR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetFacebookLoggedIn( );\
        break;\
\
    case AGKI_FACEBOOKGETUSERIDR_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::FacebookGetUserID( );\
        break;\
\
    case AGKI_FACEBOOKGETUSERNAMER_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::FacebookGetUserName( );\
        break;\
\
    case AGKI_FACEBOOKLOGIN : inl_handleparams();\
        agk::FacebookLogin( );\
        break;\
\
    case AGKI_FACEBOOKLOGOUT : inl_handleparams();\
        agk::FacebookLogout( );\
        break;\
\
    case AGKI_FACEBOOKPOSTONMYWALL_STRING_STRING_STRING_STRING_STRING : inl_handleparams();\
        agk::FacebookPostOnMyWall( *(char**)g_p[0], *(char**)g_p[1], *(char**)g_p[2], *(char**)g_p[3], *(char**)g_p[4] );\
        break;\
\
    case AGKI_FACEBOOKPOSTONFRIENDSWALL_STRING_STRING_STRING_STRING_STRING_STRING : inl_handleparams();\
        agk::FacebookPostOnFriendsWall( *(char**)g_p[0], *(char**)g_p[1], *(char**)g_p[2], *(char**)g_p[3], *(char**)g_p[4], *(char**)g_p[5] );\
        break;\
\
    case AGKI_FACEBOOKINVITEFRIEND_STRING_STRING : inl_handleparams();\
        agk::FacebookInviteFriend( *(char**)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_FACEBOOKSHOWLIKEBUTTON_STRING_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::FacebookShowLikeButton( *(char**)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3], *(int*)g_p[4] );\
        break;\
\
    case AGKI_FACEBOOKDESTROYLIKEBUTTON : inl_handleparams();\
        agk::FacebookDestroyLikeButton( );\
        break;\
\
    case AGKI_FACEBOOKGETFRIENDS : inl_handleparams();\
        agk::FacebookGetFriends( );\
        break;\
\
    case AGKI_FACEBOOKGETFRIENDSSTATER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::FacebookGetFriendsState( );\
        break;\
\
    case AGKI_FACEBOOKGETFRIENDSCOUNTR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::FacebookGetFriendsCount( );\
        break;\
\
    case AGKI_FACEBOOKGETFRIENDSNAMER_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::FacebookGetFriendsName( *(int*)g_p[1] );\
        break;\
\
    case AGKI_FACEBOOKGETFRIENDSIDR_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::FacebookGetFriendsID( *(int*)g_p[1] );\
        break;\
\
    case AGKI_FACEBOOKDOWNLOADFRIENDSPHOTO_INTEGER : inl_handleparams();\
        agk::FacebookDownloadFriendsPhoto( *(int*)g_p[0] );\
        break;\
\
    case AGKI_GETFACEBOOKDOWNLOADSTATER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetFacebookDownloadState( );\
        break;\
\
    case AGKI_GETFACEBOOKDOWNLOADFILER_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetFacebookDownloadFile( );\
        break;\
\
    case AGKI_NOTIFICATIONCREATE_STRING_STRING_STRING : inl_handleparams();\
        agk::NotificationCreate( *(char**)g_p[0], *(char**)g_p[1], *(char**)g_p[2] );\
        break;\
\
    case AGKI_GETNOTIFICATIONR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetNotification( );\
        break;\
\
    case AGKI_GETNOTIFICATIONDATAR_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetNotificationData( );\
        break;\
\
    case AGKI_NOTIFICATIONRESET : inl_handleparams();\
        agk::NotificationReset( );\
        break;\
\
    case AGKI_DRAWLINE_FLOAT_FLOAT_FLOAT_FLOAT_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::DrawLine( *(float*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(int*)g_p[4], *(int*)g_p[5], *(int*)g_p[6] );\
        break;\
\
    case AGKI_CREATEMEMBLOCKR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateMemblock( *(int*)g_p[1] );\
        break;\
\
    case AGKI_CREATEMEMBLOCK_INTEGER_INTEGER : inl_handleparams();\
        agk::CreateMemblock( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETMEMBLOCKEXISTSR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetMemblockExists( *(int*)g_p[1] );\
        break;\
\
    case AGKI_DELETEMEMBLOCK_INTEGER : inl_handleparams();\
        agk::DeleteMemblock( *(int*)g_p[0] );\
        break;\
\
    case AGKI_GETMEMBLOCKSIZER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetMemblockSize( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETMEMBLOCKBYTER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetMemblockByte( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETMEMBLOCKSHORTR_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetMemblockShort( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETMEMBLOCKINTR_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetMemblockInt( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_GETMEMBLOCKFLOATR_FLOAT_INTEGER_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetMemblockFloat( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_SETMEMBLOCKBYTE_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetMemblockByte( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_SETMEMBLOCKSHORT_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetMemblockShort( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_SETMEMBLOCKINT_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetMemblockInt( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_SETMEMBLOCKFLOAT_INTEGER_INTEGER_FLOAT : inl_handleparams();\
        agk::SetMemblockFloat( *(int*)g_p[0], *(int*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_CREATEMEMBLOCKFROMIMAGE_INTEGER_INTEGER : inl_handleparams();\
        agk::CreateMemblockFromImage( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_CREATEMEMBLOCKFROMIMAGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateMemblockFromImage( *(int*)g_p[1] );\
        break;\
\
    case AGKI_CREATEIMAGEFROMMEMBLOCK_INTEGER_INTEGER : inl_handleparams();\
        agk::CreateImageFromMemblock( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_CREATEIMAGEFROMMEMBLOCKR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateImageFromMemblock( *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETGLOBAL3DDEPTH_INTEGER : inl_handleparams();\
        agk::SetGlobal3DDepth( *(int*)g_p[0] );\
        break;\
\
    case AGKI_CREATEOBJECTBOX_INTEGER_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::CreateObjectBox( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_CREATEOBJECTBOXR_INTEGER_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateObjectBox( *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_CREATEOBJECTSPHERE_INTEGER_FLOAT_INTEGER_INTEGER : inl_handleparams();\
        agk::CreateObjectSphere( *(int*)g_p[0], *(float*)g_p[1], *(int*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_CREATEOBJECTSPHERER_INTEGER_FLOAT_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateObjectSphere( *(float*)g_p[1], *(int*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_CREATEOBJECTCONE_INTEGER_FLOAT_FLOAT_INTEGER : inl_handleparams();\
        agk::CreateObjectCone( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_CREATEOBJECTCONER_INTEGER_FLOAT_FLOAT_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateObjectCone( *(float*)g_p[1], *(float*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_CREATEOBJECTCYLINDER_INTEGER_FLOAT_FLOAT_INTEGER : inl_handleparams();\
        agk::CreateObjectCylinder( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_CREATEOBJECTCYLINDERR_INTEGER_FLOAT_FLOAT_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateObjectCylinder( *(float*)g_p[1], *(float*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_CREATEOBJECTPLANE_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::CreateObjectPlane( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_CREATEOBJECTPLANER_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::CreateObjectPlane( *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_LOADOBJECTR_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::LoadObject( *(char**)g_p[1] );\
        break;\
\
    case AGKI_LOADOBJECTR_INTEGER_STRING_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::LoadObject( *(char**)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_LOADOBJECT_INTEGER_STRING : inl_handleparams();\
        agk::LoadObject( *(int*)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_LOADOBJECT_INTEGER_STRING_FLOAT : inl_handleparams();\
        agk::LoadObject( *(int*)g_p[0], *(char**)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_CLONEOBJECTR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::CloneObject( *(int*)g_p[1] );\
        break;\
\
    case AGKI_CLONEOBJECT_INTEGER_INTEGER : inl_handleparams();\
        agk::CloneObject( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_INSTANCEOBJECTR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::InstanceObject( *(int*)g_p[1] );\
        break;\
\
    case AGKI_INSTANCEOBJECT_INTEGER_INTEGER : inl_handleparams();\
        agk::InstanceObject( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTEXISTSR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetObjectExists( *(int*)g_p[1] );\
        break;\
\
    case AGKI_DELETEOBJECT_INTEGER : inl_handleparams();\
        agk::DeleteObject( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETOBJECTPOSITION_INTEGER_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetObjectPosition( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_SETOBJECTROTATION_INTEGER_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetObjectRotation( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_SETOBJECTROTATIONQUAT_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetObjectRotationQuat( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_SETOBJECTSCALE_INTEGER_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetObjectScale( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_MOVEOBJECTLOCALX_INTEGER_FLOAT : inl_handleparams();\
        agk::MoveObjectLocalX( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_MOVEOBJECTLOCALY_INTEGER_FLOAT : inl_handleparams();\
        agk::MoveObjectLocalY( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_MOVEOBJECTLOCALZ_INTEGER_FLOAT : inl_handleparams();\
        agk::MoveObjectLocalZ( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_ROTATEOBJECTLOCALX_INTEGER_FLOAT : inl_handleparams();\
        agk::RotateObjectLocalX( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_ROTATEOBJECTLOCALY_INTEGER_FLOAT : inl_handleparams();\
        agk::RotateObjectLocalY( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_ROTATEOBJECTLOCALZ_INTEGER_FLOAT : inl_handleparams();\
        agk::RotateObjectLocalZ( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_ROTATEOBJECTGLOBALX_INTEGER_FLOAT : inl_handleparams();\
        agk::RotateObjectGlobalX( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_ROTATEOBJECTGLOBALY_INTEGER_FLOAT : inl_handleparams();\
        agk::RotateObjectGlobalY( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_ROTATEOBJECTGLOBALZ_INTEGER_FLOAT : inl_handleparams();\
        agk::RotateObjectGlobalZ( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTZR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectZ( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTANGLEXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectAngleX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTANGLEYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectAngleY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTANGLEZR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectAngleZ( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTQUATWR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectQuatW( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTQUATXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectQuatX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTQUATYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectQuatY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTQUATZR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectQuatZ( *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETOBJECTLOOKAT_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetObjectLookAt( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_SETOBJECTIMAGE_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetObjectImage( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_SETOBJECTSHADER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetObjectShader( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETOBJECTCOLOR_INTEGER_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetObjectColor( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3], *(int*)g_p[4] );\
        break;\
\
    case AGKI_SETOBJECTLIGHTMODE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetObjectLightMode( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETOBJECTDEPTHREADMODE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetObjectDepthReadMode( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETOBJECTDEPTHWRITE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetObjectDepthWrite( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETOBJECTTRANSPARENCY_INTEGER_INTEGER : inl_handleparams();\
        agk::SetObjectTransparency( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETOBJECTCULLMODE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetObjectCullMode( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETOBJECTVISIBLE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetObjectVisible( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTDEPTHREADMODER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetObjectDepthReadMode( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTDEPTHWRITER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetObjectDepthWrite( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTTRANSPARENCYR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetObjectTransparency( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTCULLMODER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetObjectCullMode( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTVISIBLER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetObjectVisible( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTINSCREENR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetObjectInScreen( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETSCREENXFROM3DR_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetScreenXFrom3D( *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_GETSCREENYFROM3DR_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetScreenYFrom3D( *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_GET3DVECTORXFROMSCREENR_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::Get3DVectorXFromScreen( *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_GET3DVECTORYFROMSCREENR_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::Get3DVectorYFromScreen( *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_GET3DVECTORZFROMSCREENR_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::Get3DVectorZFromScreen( *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETOBJECTCOLLISIONMODE_INTEGER_INTEGER : inl_handleparams();\
        agk::SetObjectCollisionMode( *(int*)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_OBJECTRAYCASTR_INTEGER_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::ObjectRayCast( *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5], *(float*)g_p[6], *(float*)g_p[7] );\
        break;\
\
    case AGKI_OBJECTSPHERECASTR_INTEGER_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::ObjectSphereCast( *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5], *(float*)g_p[6], *(float*)g_p[7], *(float*)g_p[8] );\
        break;\
\
    case AGKI_OBJECTSPHERESLIDER_INTEGER_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::ObjectSphereSlide( *(int*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5], *(float*)g_p[6], *(float*)g_p[7], *(float*)g_p[8] );\
        break;\
\
    case AGKI_GETOBJECTRAYCASTNUMHITSR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetObjectRayCastNumHits( );\
        break;\
\
    case AGKI_GETOBJECTRAYCASTHITIDR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetObjectRayCastHitID( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTRAYCASTXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectRayCastX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTRAYCASTYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectRayCastY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTRAYCASTZR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectRayCastZ( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTRAYCASTSLIDEXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectRayCastSlideX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTRAYCASTSLIDEYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectRayCastSlideY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTRAYCASTSLIDEZR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectRayCastSlideZ( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTRAYCASTNORMALXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectRayCastNormalX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTRAYCASTNORMALYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectRayCastNormalY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTRAYCASTNORMALZR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectRayCastNormalZ( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTRAYCASTBOUNCEXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectRayCastBounceX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTRAYCASTBOUNCEYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectRayCastBounceY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTRAYCASTBOUNCEZR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectRayCastBounceZ( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETOBJECTRAYCASTDISTANCER_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetObjectRayCastDistance( *(int*)g_p[1] );\
        break;\
\
    case AGKI_LOADSHADERR_INTEGER_STRING_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::LoadShader( *(char**)g_p[1], *(char**)g_p[2] );\
        break;\
\
    case AGKI_LOADSHADER_INTEGER_STRING_STRING : inl_handleparams();\
        agk::LoadShader( *(int*)g_p[0], *(char**)g_p[1], *(char**)g_p[2] );\
        break;\
\
    case AGKI_SETSHADERCONSTANTBYNAME_INTEGER_STRING_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetShaderConstantByName( *(int*)g_p[0], *(char**)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(float*)g_p[5] );\
        break;\
\
    case AGKI_SETCAMERAPOSITION_INTEGER_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetCameraPosition( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_SETCAMERAROTATIONQUAT_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetCameraRotationQuat( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_SETCAMERAROTATION_INTEGER_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetCameraRotation( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_MOVECAMERALOCALX_INTEGER_FLOAT : inl_handleparams();\
        agk::MoveCameraLocalX( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_MOVECAMERALOCALY_INTEGER_FLOAT : inl_handleparams();\
        agk::MoveCameraLocalY( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_MOVECAMERALOCALZ_INTEGER_FLOAT : inl_handleparams();\
        agk::MoveCameraLocalZ( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_ROTATECAMERALOCALX_INTEGER_FLOAT : inl_handleparams();\
        agk::RotateCameraLocalX( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_ROTATECAMERALOCALY_INTEGER_FLOAT : inl_handleparams();\
        agk::RotateCameraLocalY( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_ROTATECAMERALOCALZ_INTEGER_FLOAT : inl_handleparams();\
        agk::RotateCameraLocalZ( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_ROTATECAMERAGLOBALX_INTEGER_FLOAT : inl_handleparams();\
        agk::RotateCameraGlobalX( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_ROTATECAMERAGLOBALY_INTEGER_FLOAT : inl_handleparams();\
        agk::RotateCameraGlobalY( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_ROTATECAMERAGLOBALZ_INTEGER_FLOAT : inl_handleparams();\
        agk::RotateCameraGlobalZ( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_GETCAMERAXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetCameraX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETCAMERAYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetCameraY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETCAMERAZR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetCameraZ( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETCAMERAANGLEXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetCameraAngleX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETCAMERAANGLEYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetCameraAngleY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETCAMERAANGLEZR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetCameraAngleZ( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETCAMERAQUATWR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetCameraQuatW( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETCAMERAQUATXR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetCameraQuatX( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETCAMERAQUATYR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetCameraQuatY( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETCAMERAQUATZR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetCameraQuatZ( *(int*)g_p[1] );\
        break;\
\
    case AGKI_SETCAMERALOOKAT_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetCameraLookAt( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4] );\
        break;\
\
    case AGKI_SETCAMERARANGE_INTEGER_FLOAT_FLOAT : inl_handleparams();\
        agk::SetCameraRange( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_SETCAMERAFOV_INTEGER_FLOAT : inl_handleparams();\
        agk::SetCameraFOV( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_CREATELIGHTPOINT_INTEGER_FLOAT_FLOAT_FLOAT_FLOAT_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::CreateLightPoint( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(float*)g_p[4], *(int*)g_p[5], *(int*)g_p[6], *(int*)g_p[7] );\
        break;\
\
    case AGKI_GETLIGHTPOINTEXISTSR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetLightPointExists( *(int*)g_p[1] );\
        break;\
\
    case AGKI_DELETELIGHTPOINT_INTEGER : inl_handleparams();\
        agk::DeleteLightPoint( *(int*)g_p[0] );\
        break;\
\
    case AGKI_CLEARLIGHTPOINTS : inl_handleparams();\
        agk::ClearLightPoints( );\
        break;\
\
    case AGKI_SETLIGHTPOINTPOSITION_INTEGER_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetLightPointPosition( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_SETLIGHTPOINTCOLOR_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetLightPointColor( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_SETLIGHTPOINTRADIUS_INTEGER_FLOAT : inl_handleparams();\
        agk::SetLightPointRadius( *(int*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_CREATELIGHTDIRECTIONAL_INTEGER_FLOAT_FLOAT_FLOAT_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::CreateLightDirectional( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3], *(int*)g_p[4], *(int*)g_p[5], *(int*)g_p[6] );\
        break;\
\
    case AGKI_GETLIGHTDIRECTIONALEXISTSR_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetLightDirectionalExists( *(int*)g_p[1] );\
        break;\
\
    case AGKI_DELETELIGHTDIRECTIONAL_INTEGER : inl_handleparams();\
        agk::DeleteLightDirectional( *(int*)g_p[0] );\
        break;\
\
    case AGKI_CLEARLIGHTDIRECTIONALS : inl_handleparams();\
        agk::ClearLightDirectionals( );\
        break;\
\
    case AGKI_SETLIGHTDIRECTIONALDIRECTION_INTEGER_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetLightDirectionalDirection( *(int*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_SETLIGHTDIRECTIONALCOLOR_INTEGER_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        agk::SetLightDirectionalColor( *(int*)g_p[0], *(int*)g_p[1], *(int*)g_p[2], *(int*)g_p[3] );\
        break;\
\
    case AGKI_GETDEVICENAMER_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetDeviceName( );\
        break;\
\
    case AGKI_GETAPPNAMER_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetAppName( );\
        break;\
\
    case AGKI_GETDEVICELANGUAGER_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetDeviceLanguage( );\
        break;\
\
    case AGKI_SETEXPANSIONFILEVERSION_INTEGER : inl_handleparams();\
        agk::SetExpansionFileVersion( *(int*)g_p[0] );\
        break;\
\
    case AGKI_GETEXPANSIONFILESTATER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetExpansionFileState( );\
        break;\
\
    case AGKI_DOWNLOADEXPANSIONFILE : inl_handleparams();\
        agk::DownloadExpansionFile( );\
        break;\
\
    case AGKI_GETEXPANSIONFILEPROGRESSR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetExpansionFileProgress( );\
        break;\
\
    case AGKI_SETWINDOWTITLE_STRING : inl_handleparams();\
        agk::SetWindowTitle( *(char**)g_p[0] );\
        break;\
\
    case AGKI_SLEEP_INTEGER : inl_handleparams();\
        agk::Sleep( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETVSYNC_INTEGER : inl_handleparams();\
        agk::SetVSync( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SINR_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::Sin( *(float*)g_p[1] );\
        break;\
\
    case AGKI_COSR_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::Cos( *(float*)g_p[1] );\
        break;\
\
    case AGKI_TANR_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::Tan( *(float*)g_p[1] );\
        break;\
\
    case AGKI_SINRADR_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::SinRad( *(float*)g_p[1] );\
        break;\
\
    case AGKI_COSRADR_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::CosRad( *(float*)g_p[1] );\
        break;\
\
    case AGKI_TANRADR_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::TanRad( *(float*)g_p[1] );\
        break;\
\
    case AGKI_ASINR_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::ASin( *(float*)g_p[1] );\
        break;\
\
    case AGKI_ACOSR_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::ACos( *(float*)g_p[1] );\
        break;\
\
    case AGKI_ATANR_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::ATan( *(float*)g_p[1] );\
        break;\
\
    case AGKI_ATAN2R_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::ATan2( *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_ASINRADR_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::ASinRad( *(float*)g_p[1] );\
        break;\
\
    case AGKI_ACOSRADR_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::ACosRad( *(float*)g_p[1] );\
        break;\
\
    case AGKI_ATANRADR_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::ATanRad( *(float*)g_p[1] );\
        break;\
\
    case AGKI_ATAN2RADR_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::ATan2Rad( *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_TRUNCR_INTEGER_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::Trunc( *(float*)g_p[1] );\
        break;\
\
    case AGKI_FLOORR_INTEGER_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::Floor( *(float*)g_p[1] );\
        break;\
\
    case AGKI_CEILR_INTEGER_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::Ceil( *(float*)g_p[1] );\
        break;\
\
    case AGKI_ROUNDR_INTEGER_FLOAT : inl_handleparams();\
        *(int*)g_p[0] = agk::Round( *(float*)g_p[1] );\
        break;\
\
    case AGKI_SQRTR_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::Sqrt( *(float*)g_p[1] );\
        break;\
\
    case AGKI_ABSR_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::Abs( *(float*)g_p[1] );\
        break;\
\
    case AGKI_MODR_INTEGER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::Mod( *(int*)g_p[1], *(int*)g_p[2] );\
        break;\
\
    case AGKI_FMODR_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::FMod( *(float*)g_p[1], *(float*)g_p[2] );\
        break;\
\
    case AGKI_LOADVIDEOR_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::LoadVideo( *(char**)g_p[1] );\
        break;\
\
    case AGKI_DELETEVIDEO : inl_handleparams();\
        agk::DeleteVideo( );\
        break;\
\
    case AGKI_SETVIDEODIMENSIONS_FLOAT_FLOAT_FLOAT_FLOAT : inl_handleparams();\
        agk::SetVideoDimensions( *(float*)g_p[0], *(float*)g_p[1], *(float*)g_p[2], *(float*)g_p[3] );\
        break;\
\
    case AGKI_PLAYVIDEO : inl_handleparams();\
        agk::PlayVideo( );\
        break;\
\
    case AGKI_PAUSEVIDEO : inl_handleparams();\
        agk::PauseVideo( );\
        break;\
\
    case AGKI_STOPVIDEO : inl_handleparams();\
        agk::StopVideo( );\
        break;\
\
    case AGKI_GETVIDEOPLAYINGR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetVideoPlaying( );\
        break;\
\
    case AGKI_GETVIDEOPOSITIONR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetVideoPosition( );\
        break;\
\
    case AGKI_GETVIDEODURATIONR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetVideoDuration( );\
        break;\
\
    case AGKI_SETVIDEOVOLUME_FLOAT : inl_handleparams();\
        agk::SetVideoVolume( *(float*)g_p[0] );\
        break;\
\
    case AGKI_GETVIDEOWIDTHR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetVideoWidth( );\
        break;\
\
    case AGKI_GETVIDEOHEIGHTR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetVideoHeight( );\
        break;\
\
    case AGKI_SETRAWWRITEPATH_STRING : inl_handleparams();\
        agk::SetRawWritePath( *(char**)g_p[0] );\
        break;\
\
    case AGKI_GETWRITEPATHR_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetWritePath( );\
        break;\
\
    case AGKI_GETREADPATHR_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetReadPath( );\
        break;\
\
    case AGKI_SETCURRENTDIRR_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::SetCurrentDir( *(char**)g_p[1] );\
        break;\
\
    case AGKI_MAKEFOLDERR_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::MakeFolder( *(char**)g_p[1] );\
        break;\
\
    case AGKI_DELETEFOLDER_STRING : inl_handleparams();\
        agk::DeleteFolder( *(char**)g_p[0] );\
        break;\
\
    case AGKI_GETACCELEROMETEREXISTSR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetAccelerometerExists( );\
        break;\
\
    case AGKI_GETMULTITOUCHEXISTSR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetMultiTouchExists( );\
        break;\
\
    case AGKI_GETMOUSEEXISTSR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetMouseExists( );\
        break;\
\
    case AGKI_GETKEYBOARDEXISTSR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetKeyboardExists( );\
        break;\
\
    case AGKI_GETCAMERAEXISTSR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetCameraExists( );\
        break;\
\
    case AGKI_SETRAWMOUSEVISIBLE_INTEGER : inl_handleparams();\
        agk::SetRawMouseVisible( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETRAWMOUSEPOSITION_FLOAT_FLOAT : inl_handleparams();\
        agk::SetRawMousePosition( *(float*)g_p[0], *(float*)g_p[1] );\
        break;\
\
    case AGKI_GETDAYOFWEEKR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetDayOfWeek( );\
        break;\
\
    case AGKI_GETCURRENTDATER_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetCurrentDate( );\
        break;\
\
    case AGKI_GETCURRENTTIMER_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetCurrentTime( );\
        break;\
\
    case AGKI_OPENBROWSER_STRING : inl_handleparams();\
        agk::OpenBrowser( *(char**)g_p[0] );\
        break;\
\
    case AGKI_GETINTERNETSTATER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetInternetState( );\
        break;\
\
    case AGKI_PUSHNOTIFICATIONSETUPR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::PushNotificationSetup( );\
        break;\
\
    case AGKI_GETPUSHNOTIFICATIONTOKENR_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetPushNotificationToken( );\
        break;\
\
    case AGKI_GETNOTIFICATIONTYPER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetNotificationType( );\
        break;\
\
    case AGKI_SETNOTIFICATIONIMAGE_INTEGER : inl_handleparams();\
        agk::SetNotificationImage( *(int*)g_p[0] );\
        break;\
\
    case AGKI_SETNOTIFICATIONTEXT_STRING : inl_handleparams();\
        agk::SetNotificationText( *(char**)g_p[0] );\
        break;\
\
    case AGKI_GETNFCEXISTSR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetNFCExists( );\
        break;\
\
    case AGKI_GETGEOLOCATIONEXISTSR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetGeolocationExists( );\
        break;\
\
    case AGKI_GETCOMPASSEXISTSR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetCompassExists( );\
        break;\
\
    case AGKI_GETGYROMETEREXISTSR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetGyrometerExists( );\
        break;\
\
    case AGKI_GETINCLINOMETEREXISTSR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetInclinometerExists( );\
        break;\
\
    case AGKI_GETLIGHTSENSOREXISTSR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetLightSensorExists( );\
        break;\
\
    case AGKI_GETORIENTATIONSENSOREXISTSR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetOrientationSensorExists( );\
        break;\
\
    case AGKI_GETRAWNFCCOUNTR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawNFCCount( );\
        break;\
\
    case AGKI_GETRAWFIRSTNFCDEVICER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawFirstNFCDevice( );\
        break;\
\
    case AGKI_GETRAWNEXTNFCDEVICER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawNextNFCDevice( );\
        break;\
\
    case AGKI_GETRAWNFCNAMER_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::GetRawNFCName( *(int*)g_p[1] );\
        break;\
\
    case AGKI_SENDRAWNFCDATAR_INTEGER_INTEGER_STRING : inl_handleparams();\
        *(int*)g_p[0] = agk::SendRawNFCData( *(int*)g_p[1], *(char**)g_p[2] );\
        break;\
\
    case AGKI_GETRAWNFCDATASTATER_INTEGER_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetRawNFCDataState( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWNFCDATAR_STRING_INTEGER : inl_handleparams();\
        *(char**)g_p[0] = agk::GetRawNFCData( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWGEOLATITUDER_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawGeoLatitude( );\
        break;\
\
    case AGKI_GETRAWGEOLONGITUDER_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawGeoLongitude( );\
        break;\
\
    case AGKI_GETRAWGEOCITYR_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetRawGeoCity( );\
        break;\
\
    case AGKI_GETRAWGEOCOUNTRYR_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetRawGeoCountry( );\
        break;\
\
    case AGKI_GETRAWGEOPOSTALCODER_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetRawGeoPostalCode( );\
        break;\
\
    case AGKI_GETRAWGEOSTATER_STRING : inl_handleparams();\
        *(char**)g_p[0] = agk::GetRawGeoState( );\
        break;\
\
    case AGKI_GETRAWCOMPASSNORTHR_FLOAT_INTEGER : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawCompassNorth( *(int*)g_p[1] );\
        break;\
\
    case AGKI_GETRAWGYROVELOCITYXR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawGyroVelocityX( );\
        break;\
\
    case AGKI_GETRAWGYROVELOCITYYR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawGyroVelocityY( );\
        break;\
\
    case AGKI_GETRAWGYROVELOCITYZR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawGyroVelocityZ( );\
        break;\
\
    case AGKI_GETRAWINCLINOPITCHR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawInclinoPitch( );\
        break;\
\
    case AGKI_GETRAWINCLINOROLLR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawInclinoRoll( );\
        break;\
\
    case AGKI_GETRAWINCLINOYAWR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawInclinoYaw( );\
        break;\
\
    case AGKI_GETRAWLIGHTLEVELR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawLightLevel( );\
        break;\
\
    case AGKI_GETRAWORIENTATIONXR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawOrientationX( );\
        break;\
\
    case AGKI_GETRAWORIENTATIONYR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawOrientationY( );\
        break;\
\
    case AGKI_GETRAWORIENTATIONZR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawOrientationZ( );\
        break;\
\
    case AGKI_GETRAWORIENTATIONWR_FLOAT : inl_handleparams();\
        *(float*)g_p[0] = agk::GetRawOrientationW( );\
        break;\
\
    case AGKI_GETGAMECENTEREXISTSR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetGameCenterExists( );\
        break;\
\
    case AGKI_GAMECENTERSETUP : inl_handleparams();\
        agk::GameCenterSetup( );\
        break;\
\
    case AGKI_GAMECENTERLOGIN : inl_handleparams();\
        agk::GameCenterLogin( );\
        break;\
\
    case AGKI_GETGAMECENTERLOGGEDINR_INTEGER : inl_handleparams();\
        *(int*)g_p[0] = agk::GetGameCenterLoggedIn( );\
        break;\
\
    case AGKI_GAMECENTERSUBMITSCORE_INTEGER_STRING : inl_handleparams();\
        agk::GameCenterSubmitScore( *(int*)g_p[0], *(char**)g_p[1] );\
        break;\
\
    case AGKI_GAMECENTERSHOWLEADERBOARD_STRING : inl_handleparams();\
        agk::GameCenterShowLeaderBoard( *(char**)g_p[0] );\
        break;\
\
    case AGKI_GAMECENTERSUBMITACHIEVEMENT_STRING_INTEGER : inl_handleparams();\
        agk::GameCenterSubmitAchievement( *(char**)g_p[0], *(int*)g_p[1] );\
        break;\
\
    case AGKI_GAMECENTERACHIEVEMENTSSHOW : inl_handleparams();\
        agk::GameCenterAchievementsShow( );\
        break;\
\
    case AGKI_GAMECENTERACHIEVEMENTSRESET : inl_handleparams();\
        agk::GameCenterAchievementsReset( );\
        break;