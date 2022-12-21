IOS COMPILE FAILURE ON FACEBOOKSDK
==================================

Due to the way AGK is compiled on a Windows System, some of the FacebookSDK files which originate from a Mac System are irreversably corrupted during the installation process. To fix this issue so you can successfully compile your iOS apps and the AGK Player, follow the steps below:

Problem Warning
---------------

ignoring file ../../platform/apple/Source/Social Plugins/FacebookSDK/FacebookSDK.framework/FacebookSDK, file was built for unsupported file format ( 0x6c 0x69 0x6e 0x6b 0x20 0x2e 0x2f 0x56 0x65 0x72 0x73 0x69 0x6f 0x6e 0x73 0x2f ) which is not the architecture being linked (armv7): ../../platform/apple/Source/Social Plugins/FacebookSDK/FacebookSDK.framework/FacebookSDK

Solution Steps
--------------

1. After you copy the files to your Mac System
2. Enter the folder: platform\apple\Source\Social Plugins\FacebookSDK
3. Entirely delete the item: FacebookSDK.framework
4. Double click the file: FacebookSDK.framework.zip
5. This will extract a new uncorrupted copy of the folder to your Mac System
6. Compile your AGK iOS apps as normal
