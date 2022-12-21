The interpreter_android_lite project is a lite version of the interpreter_android project that does not include Facebook or Push notifications (otherwise known as Google Cloud Messaging), this simplifies the build process somewhat if you do not need these commands.

The interpreter_android_prebuilt project is the Android interpreter with all the NDK compiling already done, you do not need to worry about cygwin or NDK with this project. Simply import it into eclipse and add your media and bytecode to assets/media. This project can be used to sign apps for uploading to the Google Play store.

The AGK NDK libraries for the lite versions are the same as the full versions, only the Java project files are different.

To change the package name:
- Open the AndroidManifest.xml and find all instances of com.mycompany.myapp and change them to your chosen package name. 
- Open IAPActivity.java and change the instance of import com.mycompany.myapp to your chosen package name.
- Open MyJavaActivity.java and change the instance of import com.mycompany.myapp to your chosen package name.
- Open res/values/strings.xml and change the app_name entry to your chosen app name

To change your license key for in app billing:
- Open AGKHelper.java and find the variable named base64EncodedPublicKey, chanage this to the key found in your Google Play developer console for your chosen app.