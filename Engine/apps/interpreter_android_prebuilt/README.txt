The interpreter_android_prebuilt project is the Android interpreter with all the NDK compiling already done, you do not need to worry about cygwin or NDK with this project. 

Simply import it into eclipse and add your media and bytecode to assets/media. You may also need to import the facebook project as this project depends on it unless you hack out the references to it.

This project can be used to sign apps for uploading to the Google Play store.

To change the package name:
- Open the AndroidManifest.xml and find all instances of com.mycompany.myapp and change them to your chosen package name. 
- Open GCMIntentService.java and change the package field at the top to your chosen package, after the change it will be underlined in red, hover over it and when a popup appears choose "Move ..."
- Open IAPActivity.java and change the instance of import com.mycompany.myapp to your chosen package name.
- Open MyFacebookActivity.java and change the instance of import com.mycompany.myapp to your chosen package name.
- Open MyJavaActivity.java and change the instance of import com.mycompany.myapp to your chosen package name.
- Open res/values/strings.xml and change the app_name entry to your chosen app name

To change your license key for in app billing:
- Open AGKHelper.java and find the variable named base64EncodedPublicKey, chanage this to the key found in your Google Play developer console for your chosen app.