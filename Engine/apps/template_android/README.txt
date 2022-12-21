The template_android project is a bare bones project for tier 2 development and requires you to use the Android NDK with cygwin to compile your projects. See the tier 2 help files for more details.

To change the package name:
- Open the AndroidManifest.xml and find all instances of com.mycompany.mytemplate and change them to your chosen package name. 
- Open GCMIntentService.java and change the package field at the top to your chosen package, after the change it will be underlined in red, hover over it and when a popup appears choose "Move ..."
- Open IAPActivity.java and change the instance of import com.mycompany.mytemplate to your chosen package name.
- Open MyFacebookActivity.java and change the instance of import com.mycompany.mytemplate to your chosen package name.
- Open MyJavaActivity.java and change the instance of import com.mycompany.mytemplate to your chosen package name.
- Open res/values/strings.xml and change the app_name entry to your chosen app name

To change your license key for in app billing:
- Open AGKHelper.java and find the variable named base64EncodedPublicKey, chanage this to the key found in your Google Play developer console for your chosen app.