/**
 * Copyright 2012 Facebook
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.facebook;

import android.Manifest;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.*;
import android.content.pm.*;
import android.content.pm.PackageManager.NameNotFoundException;
import android.net.Uri;
import android.os.*;
import android.support.v4.app.Fragment;
import android.support.v4.content.LocalBroadcastManager;
import android.text.TextUtils;
import android.util.Log;
import android.webkit.CookieSyncManager;
import com.facebook.android.DialogError;
import com.facebook.android.Facebook.DialogListener;
import com.facebook.android.FacebookError;
import com.facebook.android.FbDialog;
import com.facebook.android.Util;

import java.io.*;
import java.lang.ref.WeakReference;
import java.util.*;

/**
 * <p>
 * Session is used to authenticate a user and manage the user's session with
 * Facebook.
 * </p>
 * <p>
 * Sessions must be opened before they can be used to make a Request. When a
 * Session is created, it attempts to initialize itself from a TokenCache.
 * Closing the session can optionally clear this cache.  The Session lifecycle
 * uses {@link SessionState SessionState} to indicate its state.
 * </p>
 * <p>
 * Instances of Session provide state change notification via a callback
 * interface, {@link Session.StatusCallback StatusCallback}.
 * </p>
 */
public class Session implements Serializable {
    private static final long serialVersionUID = 1L;

    /**
     * The logging tag used by Session.
     */
    public static final String TAG = Session.class.getCanonicalName();

    /**
     * The default activity code used for authorization.
     * 
     * @see #openForRead(OpenRequest)
     *      open
     */
    public static final int DEFAULT_AUTHORIZE_ACTIVITY_CODE = 0xface;

    /**
     * If Session authorization fails and provides a web view error code, the
     * web view error code is stored in the Bundle returned from
     * {@link #getAuthorizationBundle getAuthorizationBundle} under this key.
     */
    public static final String WEB_VIEW_ERROR_CODE_KEY = "com.facebook.sdk.WebViewErrorCode";

    /**
     * If Session authorization fails and provides a failing url, the failing
     * url is stored in the Bundle returned from {@link #getAuthorizationBundle
     * getAuthorizationBundle} under this key.
     */
    public static final String WEB_VIEW_FAILING_URL_KEY = "com.facebook.sdk.FailingUrl";

    /**
     * The action used to indicate that the active session has been set. This should
     * be used as an action in an IntentFilter and BroadcastReceiver registered with
     * the {@link android.support.v4.content.LocalBroadcastManager}.
     */
    public static final String ACTION_ACTIVE_SESSION_SET = "com.facebook.sdk.ACTIVE_SESSION_SET";

    /**
     * The action used to indicate that the active session has been set to null. This should
     * be used as an action in an IntentFilter and BroadcastReceiver registered with
     * the {@link android.support.v4.content.LocalBroadcastManager}.
     */
    public static final String ACTION_ACTIVE_SESSION_UNSET = "com.facebook.sdk.ACTIVE_SESSION_UNSET";

    /**
     * The action used to indicate that the active session has been opened. This should
     * be used as an action in an IntentFilter and BroadcastReceiver registered with
     * the {@link android.support.v4.content.LocalBroadcastManager}.
     */
    public static final String ACTION_ACTIVE_SESSION_OPENED = "com.facebook.sdk.ACTIVE_SESSION_OPENED";

    /**
     * The action used to indicate that the active session has been closed. This should
     * be used as an action in an IntentFilter and BroadcastReceiver registered with
     * the {@link android.support.v4.content.LocalBroadcastManager}.
     */
    public static final String ACTION_ACTIVE_SESSION_CLOSED = "com.facebook.sdk.ACTIVE_SESSION_CLOSED";
    
    /**
     * Session takes application id as a constructor parameter. If this is null,
     * Session will attempt to load the application id from
     * application/meta-data using this String as the key.
     */
    public static final String APPLICATION_ID_PROPERTY = "com.facebook.sdk.ApplicationId";

    private static Object staticLock = new Object();
    private static Session activeSession;
    private static volatile Context staticContext;

    // Token extension constants
    private static final int TOKEN_EXTEND_THRESHOLD_SECONDS = 24 * 60 * 60; // 1
                                                                            // day
    private static final int TOKEN_EXTEND_RETRY_SECONDS = 60 * 60; // 1 hour

    private static final String SESSION_BUNDLE_SAVE_KEY = "com.facebook.sdk.Session.saveSessionKey";
    private static final String AUTH_BUNDLE_SAVE_KEY = "com.facebook.sdk.Session.authBundleKey";
    private static final String PUBLISH_PERMISSION_PREFIX = "publish";
    private static final String MANAGE_PERMISSION_PREFIX = "manage";
    @SuppressWarnings("serial")
    private static final Set<String> OTHER_PUBLISH_PERMISSIONS = new HashSet<String>() {{
        add("ads_management");
        add("create_event");
        add("rsvp_event");
    }};

    private String applicationId;
    private SessionState state;
    private AccessToken tokenInfo;
    private Date lastAttemptedTokenExtendDate = new Date(0);
    private boolean shouldAutoPublish = true;

    private AuthorizationRequest pendingRequest;

    // The following are not serialized with the Session object
    private volatile Bundle authorizationBundle;
    private List<StatusCallback> callbacks;
    private Handler handler;
    private AutoPublishAsyncTask autoPublishAsyncTask;
    // This is the object that synchronizes access to state and tokenInfo
    private Object lock = new Object();
    private TokenCache tokenCache;
    private volatile TokenRefreshRequest currentTokenRefreshRequest;

    /**
     * Serialization proxy for the Session class. This is version 1 of
     * serialization. Future serializations may differ in format. This
     * class should not be modified. If serializations formats change,
     * create a new class SerializationProxyVx.
     */
    private static class SerializationProxyV1 implements Serializable {
        private static final long serialVersionUID = 7663436173185080063L;
        private final String applicationId;
        private final SessionState state;
        private final AccessToken tokenInfo;
        private final Date lastAttemptedTokenExtendDate;
        private final boolean shouldAutoPublish;
        private final AuthorizationRequest pendingRequest;

        SerializationProxyV1(String applicationId, SessionState state,
                AccessToken tokenInfo, Date lastAttemptedTokenExtendDate,
                boolean shouldAutoPublish, AuthorizationRequest pendingRequest) {
            this.applicationId = applicationId;
            this.state = state;
            this.tokenInfo = tokenInfo;
            this.lastAttemptedTokenExtendDate = lastAttemptedTokenExtendDate;
            this.shouldAutoPublish = shouldAutoPublish;
            this.pendingRequest = pendingRequest;
        }

        private Object readResolve() {
            return new Session(applicationId, state, tokenInfo,
                    lastAttemptedTokenExtendDate, shouldAutoPublish, pendingRequest);
        }
    }

    /**
     * Used by version 1 of the serialization proxy, do not modify.
     */
    private Session(String applicationId, SessionState state,
            AccessToken tokenInfo, Date lastAttemptedTokenExtendDate,
            boolean shouldAutoPublish, AuthorizationRequest pendingRequest) {
        this.applicationId = applicationId;
        this.state = state;
        this.tokenInfo = tokenInfo;
        this.lastAttemptedTokenExtendDate = lastAttemptedTokenExtendDate;
        this.shouldAutoPublish = shouldAutoPublish;
        this.pendingRequest = pendingRequest;
        lock = new Object();
        handler = new Handler(Looper.getMainLooper());
        currentTokenRefreshRequest = null;
        tokenCache = null;
        callbacks = new ArrayList<StatusCallback>();
    }

    /**
     * Initializes a new Session with the specified context.
     * 
     * @param currentContext
     *            The Activity or Service creating this Session.
     */
    public Session(Context currentContext) {
        this(currentContext, null, null, true);
    }

    Session(Context context, String applicationId, TokenCache tokenCache, boolean shouldAutoPublish) {
        // if the application ID passed in is null, try to get it from the
        // meta-data in the manifest.
        if ((context != null) && (applicationId == null)) {
            applicationId = getMetadataApplicationId(context);
        }

        Validate.notNull(applicationId, "applicationId");

        initializeStaticContext(context);

        if (tokenCache == null) {
            tokenCache = new SharedPreferencesTokenCache(staticContext);
        }

        this.applicationId = applicationId;
        this.tokenCache = tokenCache;
        this.state = SessionState.CREATED;
        this.pendingRequest = null;
        this.callbacks = new ArrayList<StatusCallback>();
        this.handler = new Handler(Looper.getMainLooper());
        this.shouldAutoPublish = shouldAutoPublish;

        Bundle tokenState = tokenCache.load();
        if (TokenCache.hasTokenInformation(tokenState)) {
            Date cachedExpirationDate = TokenCache.getDate(tokenState, TokenCache.EXPIRATION_DATE_KEY);
            Date now = new Date();

            if ((cachedExpirationDate == null) || cachedExpirationDate.before(now)) {
                // If expired or we require new permissions, clear out the
                // current token cache.
                tokenCache.clear();
                this.tokenInfo = AccessToken.createEmptyToken(Collections.<String>emptyList());
            } else {
                // Otherwise we have a valid token, so use it.
                this.tokenInfo = AccessToken.createFromCache(tokenState);
                this.state = SessionState.CREATED_TOKEN_LOADED;
            }
        } else {
            this.tokenInfo = AccessToken.createEmptyToken(Collections.<String>emptyList());
        }
    }

    /**
     * Returns a Bundle containing data that was returned from facebook during
     * authorization.
     * 
     * @return a Bundle containing data that was returned from facebook during
     *         authorization.
     */
    public final Bundle getAuthorizationBundle() {
        synchronized (this.lock) {
            return this.authorizationBundle;
        }
    }

    /**
     * Returns a boolean indicating whether the session is opened.
     * 
     * @return a boolean indicating whether the session is opened.
     */
    public final boolean isOpened() {
        synchronized (this.lock) {
            return this.state.isOpened();
        }
    }

    public final boolean isClosed() {
        synchronized (this.lock) {
            return this.state.isClosed();
        }
    }

    /**
     * Returns the current state of the Session.
     * See {@link SessionState} for details.
     * 
     * @return the current state of the Session.
     */
    public final SessionState getState() {
        synchronized (this.lock) {
            return this.state;
        }
    }

    /**
     * Returns the application id associated with this Session.
     * 
     * @return the application id associated with this Session.
     */
    public final String getApplicationId() {
        return this.applicationId;
    }

    /**
     * Returns the access token String.
     * 
     * @return the access token String.
     */
    public final String getAccessToken() {
        synchronized (this.lock) {
            return this.tokenInfo.getToken();
        }
    }

    /**
     * <p>
     * Returns the Date at which the current token will expire.
     * </p>
     * <p>
     * Note that Session automatically attempts to extend the lifetime of Tokens
     * as needed when facebook requests are made.
     * </p>
     * 
     * @return the Date at which the current token will expire.
     */
    public final Date getExpirationDate() {
        synchronized (this.lock) {
            return this.tokenInfo.getExpires();
        }
    }

    /**
     * <p>
     * Returns the list of permissions associated with the session.
     * </p>
     * <p>
     * If there is a valid token, this represents the permissions granted by
     * that token. This can change during calls to
     * {@link #reauthorizeForRead(com.facebook.Session.ReauthorizeRequest)}
     * or {@link #reauthorizeForPublish(com.facebook.Session.ReauthorizeRequest)}.
     * </p>
     * 
     * @return the list of permissions associated with the session.
     */
    public final List<String> getPermissions() {
        synchronized (this.lock) {
            return this.tokenInfo.getPermissions();
        }
    }

    /**
     * <p>
     * Logs a user in to Facebook.
     * </p>
     * <p>
     * A session may not be used with {@link Request Request} and other classes
     * in the SDK until it is open. If, prior to calling open, the session is in
     * the {@link SessionState#CREATED_TOKEN_LOADED CREATED_TOKEN_LOADED}
     * state, and the requested permissions are a subset of the previously authorized
     * permissions, then the Session becomes usable immediately with no user interaction.
     * </p>
     * <p>
     * The permissions associated with the openRequest passed to this method must
     * be read permissions only (or null/empty). It is not allowed to pass publish
     * permissions to this method and will result in an exception being thrown.
     * </p>
     * <p>
     * Any open method must be called at most once, and cannot be called after the
     * Session is closed. Calling the method at an invalid time will result in
     * UnsuportedOperationException.
     * </p>
     *
     * @param openRequest
     *         the open request, can be null only if the Session is in the
     *         {@link SessionState#CREATED_TOKEN_LOADED CREATED_TOKEN_LOADED} state
     *
     * @throws FacebookException
     *         if any publish permissions are requested
     */
    public final void openForRead(OpenRequest openRequest) {
        open(openRequest, AuthorizationType.READ);
    }

    /**
     * <p>
     * Logs a user in to Facebook.
     * </p>
     * <p>
     * A session may not be used with {@link Request Request} and other classes
     * in the SDK until it is open. If, prior to calling open, the session is in
     * the {@link SessionState#CREATED_TOKEN_LOADED CREATED_TOKEN_LOADED}
     * state, and the requested permissions are a subset of the previously authorized
     * permissions, then the Session becomes usable immediately with no user interaction.
     * </p>
     * <p>
     * The permissions associated with the openRequest passed to this method must
     * be publish permissions only and must be non-empty. Any read permissions
     * will result in a warning, and may fail during server-side authorization.
     * </p>
     * <p>
     * Any open method must be called at most once, and cannot be called after the
     * Session is closed. Calling the method at an invalid time will result in
     * UnsuportedOperationException.
     * </p>
     *
     * @param openRequest
     *         the open request, can be null only if the Session is in the
     *         {@link SessionState#CREATED_TOKEN_LOADED CREATED_TOKEN_LOADED} state
     *
     * @throws FacebookException
     *         if the passed in request is null or has no permissions set.
     */
    public final void openForPublish(OpenRequest openRequest) {
        open(openRequest, AuthorizationType.PUBLISH);
    }

    /**
     * <p>
     * Logs a user in to Facebook.
     * </p>
     * <p>
     * A session may not be used with {@link Request Request} and other classes
     * in the SDK until it is open. If, prior to calling open, the session is in
     * the {@link SessionState#CREATED_TOKEN_LOADED CREATED_TOKEN_LOADED}
     * state, then the Session becomes usable immediately with no user interaction.
     * Otherwise, this will open the Session with basic permissions.
     * </p>
     * <p>
     * Any open method must be called at most once, and cannot be called after the
     * Session is closed. Calling the method at an invalid time will result in
     * UnsuportedOperationException.
     * </p>
     *
     * @param activity
     *         the Activity used to open the Session
     */
    public final void openForRead(Activity activity) {
        openForRead(new OpenRequest(activity));
    }

    /**
     * <p>
     * Logs a user in to Facebook.
     * </p>
     * <p>
     * A session may not be used with {@link Request Request} and other classes
     * in the SDK until it is open. If, prior to calling open, the session is in
     * the {@link SessionState#CREATED_TOKEN_LOADED CREATED_TOKEN_LOADED}
     * state, then the Session becomes usable immediately with no user interaction.
     * Otherwise, this will open the Session with basic permissions.
     * </p>
     * <p>
     * Any open method must be called at most once, and cannot be called after the
     * Session is closed. Calling the method at an invalid time will result in
     * UnsuportedOperationException.
     * </p>
     *
     * @param fragment
     *         the Fragment used to open the Session
     */
    public final void openForRead(Fragment fragment) {
        openForRead(new OpenRequest(fragment));
    }

    /**
     * <p>
     * Logs a user in to Facebook.
     * </p>
     * <p>
     * This method should only be called if the session is in
     * the {@link SessionState#CREATED_TOKEN_LOADED CREATED_TOKEN_LOADED}
     * state.
     * </p>
     * <p>
     * Any open method must be called at most once, and cannot be called after the
     * Session is closed. Calling the method at an invalid time will result in
     * UnsuportedOperationException.
     * </p>
     *
     * @throws UnsupportedOperationException
     *          If the session is in an invalid state.
     */
    public final void open() {
        if (state.equals(SessionState.CREATED_TOKEN_LOADED)) {
            openForRead((OpenRequest) null);
        } else {
            throw new UnsupportedOperationException(String.format(
                    "Cannot call open without an OpenRequest when the state is %s",
                    state.toString()));
        }
    }

    /**
     * <p>
     * Reauthorizes the Session, with additional read permissions.
     * </p>
     * <p>
     * If successful, this will update the set of permissions on this session to
     * match the newPermissions. If this fails, the Session remains unchanged.
     * </p>
     * <p>
     * The permissions associated with the reauthorizeRequest passed to this method must
     * be read permissions only (or null/empty). It is not allowed to pass publish
     * permissions to this method and will result in an exception being thrown.
     * </p>
     *
     * @param reauthorizeRequest the reauthorization request
     */
    public final void reauthorizeForRead(ReauthorizeRequest reauthorizeRequest) {
        reauthorize(reauthorizeRequest, AuthorizationType.READ);
    }

    /**
     * <p>
     * Reauthorizes the Session, with additional publish permissions.
     * </p>
     * <p>
     * If successful, this will update the set of permissions on this session to
     * match the newPermissions. If this fails, the Session remains unchanged.
     * </p>
     * <p>
     * The permissions associated with the reauthorizeRequest passed to this method must
     * be publish permissions only and must be non-empty. Any read permissions
     * will result in a warning, and may fail during server-side authorization.
     * </p>
     *
     * @param reauthorizeRequest the reauthorization request
     */
    public final void reauthorizeForPublish(ReauthorizeRequest reauthorizeRequest) {
        reauthorize(reauthorizeRequest, AuthorizationType.PUBLISH);
    }

    /**
     * Provides an implementation for {@link Activity#onActivityResult
     * onActivityResult} that updates the Session based on information returned
     * during the authorization flow. The Activity that calls open or
     * reauthorize should forward the resulting onActivityResult call here to
     * update the Session state based on the contents of the resultCode and
     * data.
     * 
     * @param currentActivity
     *            The Activity that is forwarding the onActivityResult call.
     * @param requestCode
     *            The requestCode parameter from the forwarded call. When this
     *            onActivityResult occurs as part of facebook authorization
     *            flow, this value is the activityCode passed to open or
     *            authorize.
     * @param resultCode
     *            An int containing the resultCode parameter from the forwarded
     *            call.
     * @param data
     *            The Intent passed as the data parameter from the forwarded
     *            call.
     * @return A boolean indicating whether the requestCode matched a pending
     *         authorization request for this Session.
     */
    public final boolean onActivityResult(Activity currentActivity, int requestCode, int resultCode, Intent data) {
        Validate.notNull(currentActivity, "currentActivity");

        initializeStaticContext(currentActivity);

        AuthorizationRequest currentRequest = null;
        AuthorizationRequest retryRequest = null;
        AccessToken newToken = null;
        Exception exception = null;

        synchronized (lock) {
            if (pendingRequest == null || (requestCode != pendingRequest.getRequestCode())) {
                return false;
            } else {
                currentRequest = pendingRequest;
            }
        }

        this.authorizationBundle = null;

        if (resultCode == Activity.RESULT_CANCELED) {
            if (data == null) {
                // User pressed the 'back' button
                exception = new FacebookOperationCanceledException("Log in was canceled by the user");
            } else {
                this.authorizationBundle = data.getExtras();
                exception = new FacebookAuthorizationException(this.authorizationBundle.getString("error"));
            }
        } else if (resultCode == Activity.RESULT_OK) {
            Validate.notNull(data, "data");

            this.authorizationBundle = data.getExtras();
            String error = this.authorizationBundle.getString("error");
            if (error == null) {
                error = this.authorizationBundle.getString("error_type");
            }
            if (error != null) {
                if (ServerProtocol.errorsProxyAuthDisabled.contains(error)) {
                    retryRequest = currentRequest.setLoginBehavior(SessionLoginBehavior.SUPPRESS_SSO);
                } else if (ServerProtocol.errorsUserCanceled.contains(error)) {
                    exception = new FacebookOperationCanceledException("User canceled log in.");
                } else {
                    String description = this.authorizationBundle.getString("error_description");
                    if (description != null) {
                        error = error + ": " + description;
                    }
                    exception = new FacebookAuthorizationException(error);
                }
            } else {
                newToken = AccessToken.createFromSSO(currentRequest.permissions, data);
            }
        }

        if (retryRequest != null) {
            synchronized (lock) {
                if (pendingRequest == currentRequest) {
                    pendingRequest = retryRequest;
                } else {
                    retryRequest = null;
                }
            }
            authorize(retryRequest);
        } else {
            finishAuth(newToken, exception);
        }

        return true;
    }

    /**
     * Closes the local in-memory Session object, but does not clear the
     * persisted token cache.
     */
    @SuppressWarnings("incomplete-switch")
    public final void close() {
        synchronized (this.lock) {
            final SessionState oldState = this.state;

            switch (this.state) {
            case CREATED:
            case OPENING:
                this.state = SessionState.CLOSED_LOGIN_FAILED;
                postStateChange(oldState, this.state, new FacebookException(
                        "Log in attempt aborted."));
                break;

            case CREATED_TOKEN_LOADED:
            case OPENED:
            case OPENED_TOKEN_UPDATED:
                this.state = SessionState.CLOSED;
                postStateChange(oldState, this.state, null);
                break;
            }
        }
    }

    /**
     * Closes the local in-memory Session object and clears any persisted token
     * cache related to the Session.
     */
    public final void closeAndClearTokenInformation() {
        if (this.tokenCache != null) {
            this.tokenCache.clear();
        }
        Utility.clearFacebookCookies(staticContext);
        close();
    }

    @Override
    public final String toString() {
        return new StringBuilder().append("{Session").append(" state:").append(this.state).append(", token:")
                .append((this.tokenInfo == null) ? "null" : this.tokenInfo).append(", appId:")
                .append((this.applicationId == null) ? "null" : this.applicationId).append("}").toString();
    }

    /**
     * <p>
     * Do not use this method.
     * </p>
     * <p>
     * Refreshes the token based on information obtained from the Facebook
     * class. This is exposed to enable the com.facebook.android.Facebook class
     * to refresh the token in its underlying Session. Normally Session
     * automatically updates its token. This is only provided for backwards
     * compatibility and may be removed in a future release.
     * </p>
     * 
     * @param bundle
     *            Opaque Bundle of data from the Facebook class.
     */
    public void internalRefreshToken(Bundle bundle) {
        synchronized (this.lock) {
            final SessionState oldState = this.state;

            switch (this.state) {
            case OPENED:
                this.state = SessionState.OPENED_TOKEN_UPDATED;
                postStateChange(oldState, this.state, null);
                break;
            case OPENED_TOKEN_UPDATED:
                break;
            default:
                // Silently ignore attempts to refresh token if we are not open
                Log.d(TAG, "refreshToken ignored in state " + this.state);
                return;
            }
            this.tokenInfo = AccessToken.createForRefresh(this.tokenInfo, bundle);
            if (this.tokenCache != null) {
                this.tokenCache.save(this.tokenInfo.toCacheBundle());
            }
        }
    }

    private Object writeReplace() {
        return new SerializationProxyV1(applicationId, state, tokenInfo,
                lastAttemptedTokenExtendDate, shouldAutoPublish, pendingRequest);
    }

    // have a readObject that throws to prevent spoofing
    private void readObject(ObjectInputStream stream) throws InvalidObjectException {
        throw new InvalidObjectException("Cannot readObject, serialization proxy required");
    }

    /**
     * Save the Session object into the supplied Bundle.
     *
     * @param session the Session to save
     * @param bundle the Bundle to save the Session to
     */
    public static final void saveSession(Session session, Bundle bundle) {
        if (bundle != null && session != null) {
            ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
            try {
                new ObjectOutputStream(outputStream).writeObject(session);
            } catch (IOException e) {
                throw new FacebookException("Unable to save session.", e);
            }
            bundle.putByteArray(SESSION_BUNDLE_SAVE_KEY, outputStream.toByteArray());
            bundle.putBundle(AUTH_BUNDLE_SAVE_KEY, session.authorizationBundle);
        }
    }

    /**
     * Restores the saved session from a Bundle, if any. Returns the restored Session or
     * null if it could not be restored.
     *
     * @param context
     *            the Activity or Service creating the Session, must not be null
     * @param cache
     *            the TokenCache to use to load and store the token. If this is
     *            null, a default token cache that stores data in
     *            SharedPreferences will be used
     * @param callback
     *            the callback to notify for Session state changes, can be null
     * @param bundle
     *            the bundle to restore the Session from
     * @return the restored Session, or null
     */
    public static final Session restoreSession(
            Context context, TokenCache cache, StatusCallback callback, Bundle bundle) {
        if (bundle == null) {
            return null;
        }
        byte[] data = bundle.getByteArray(SESSION_BUNDLE_SAVE_KEY);
        if (data != null) {
            ByteArrayInputStream is = new ByteArrayInputStream(data);
            try {
                Session session = (Session) (new ObjectInputStream(is)).readObject();
                initializeStaticContext(context);
                if (cache != null) {
                    session.tokenCache = cache;
                } else {
                    session.tokenCache = new SharedPreferencesTokenCache(context);
                }
                if (callback != null) {
                    session.addCallback(callback);
                }
                session.authorizationBundle =  bundle.getBundle(AUTH_BUNDLE_SAVE_KEY);
                return session;
            } catch (ClassNotFoundException e) {
                Log.w(TAG, "Unable to restore session", e);
            } catch (IOException e) {
                Log.w(TAG, "Unable to restore session.", e);
            }
        }
        return null;
    }


    /**
     * Returns the current active Session, or null if there is none.
     * 
     * @return the current active Session, or null if there is none.
     */
    public static final Session getActiveSession() {
        synchronized (Session.staticLock) {
            return Session.activeSession;
        }
    }

    /**
     * <p>
     * Sets the current active Session.
     * </p>
     * <p>
     * The active Session is used implicitly by predefined Request factory
     * methods as well as optionally by UI controls in the sdk.
     * </p>
     * <p>
     * It is legal to set this to null, or to a Session that is not yet open.
     * </p>
     * 
     * @param session
     *            A Session to use as the active Session, or null to indicate
     *            that there is no active Session.
     */
    public static final void setActiveSession(Session session) {
        synchronized (Session.staticLock) {
            if (session != Session.activeSession) {
                Session oldSession = Session.activeSession;

                if (oldSession != null) {
                    oldSession.close();
                }

                Session.activeSession = session;

                if (oldSession != null) {
                    postActiveSessionAction(Session.ACTION_ACTIVE_SESSION_UNSET);
                }

                if (session != null) {
                    postActiveSessionAction(Session.ACTION_ACTIVE_SESSION_SET);

                    if (session.isOpened()) {
                        postActiveSessionAction(Session.ACTION_ACTIVE_SESSION_OPENED);
                    }
                }
            }
        }
    }

    /**
     * Create a new Session, and if a token cache is available, open the
     * Session and make it active without any user interaction.
     *
     * @param context
     *         The Context creating this session
     * @return The new session or null if one could not be created
     */
    public static Session openActiveSession(Context context) {
        return openActiveSession(context, false, null);
    }

    /**
     * If allowLoginUI is true, this will create a new Session, make it active, and
     * open it. If the default token cache is not available, then this will request
     * basic permissions. If the default token cache is available and cached tokens
     * are loaded, this will use the cached token and associated permissions.
     * <p/>
     * If allowedLoginUI is false, this will only create the active session and open
     * it if it requires no user interaction (i.e. the token cache is available and
     * there are cached tokens).
     *
     * @param activity
     *            The Activity that is opening the new Session.
     * @param allowLoginUI
     *            if false, only sets the active session and opens it if it
     *            does not require user interaction
     * @return The new Session or null if one could not be created
     */
    public static Session openActiveSession(Activity activity, boolean allowLoginUI) {
        return openActiveSession(activity, allowLoginUI, (StatusCallback) null);
    }

    /**
     * If allowLoginUI is true, this will create a new Session, make it active, and
     * open it. If the default token cache is not available, then this will request
     * basic permissions. If the default token cache is available and cached tokens
     * are loaded, this will use the cached token and associated permissions.
     * <p/>
     * If allowedLoginUI is false, this will only create the active session and open
     * it if it requires no user interaction (i.e. the token cache is available and
     * there are cached tokens).
     * 
     * @param activity
     *            The Activity that is opening the new Session.
     * @param allowLoginUI
     *            if false, only sets the active session and opens it if it
     *            does not require user interaction
     * @param callback
     *            The {@link StatusCallback SessionStatusCallback} to
     *            notify regarding Session state changes.
     * @return The new Session or null if one could not be created
     */
    public static Session openActiveSession(Activity activity, boolean allowLoginUI,
            StatusCallback callback) {
        return openActiveSession(activity, allowLoginUI, new OpenRequest(activity).setCallback(callback));
    }

    /**
     * If allowLoginUI is true, this will create a new Session, make it active, and
     * open it. If the default token cache is not available, then this will request
     * basic permissions. If the default token cache is available and cached tokens
     * are loaded, this will use the cached token and associated permissions.
     * <p/>
     * If allowedLoginUI is false, this will only create the active session and open
     * it if it requires no user interaction (i.e. the token cache is available and
     * there are cached tokens).
     *
     * @param context
     *            The Activity or Service creating this Session
     * @param fragment
     *            The Fragment that is opening the new Session.
     * @param allowLoginUI
     *            if false, only sets the active session and opens it if it
     *            does not require user interaction
     * @return The new Session or null if one could not be created
     */
    public static Session openActiveSession(Context context, Fragment fragment, boolean allowLoginUI) {
        return openActiveSession(context, fragment, allowLoginUI, null);
    }

    /**
     * If allowLoginUI is true, this will create a new Session, make it active, and
     * open it. If the default token cache is not available, then this will request
     * basic permissions. If the default token cache is available and cached tokens
     * are loaded, this will use the cached token and associated permissions.
     * <p/>
     * If allowedLoginUI is false, this will only create the active session and open
     * it if it requires no user interaction (i.e. the token cache is available and
     * there are cached tokens).
     *
     * @param context
     *            The Activity or Service creating this Session
     * @param fragment
     *            The Fragment that is opening the new Session.
     * @param allowLoginUI
     *            if false, only sets the active session and opens it if it
     *            does not require user interaction
     * @param callback
     *            The {@link StatusCallback SessionStatusCallback} to
     *            notify regarding Session state changes.
     * @return The new Session or null if one could not be created
     */
    public static Session openActiveSession(Context context, Fragment fragment,
            boolean allowLoginUI, StatusCallback callback) {
        return openActiveSession(context, allowLoginUI, new OpenRequest(fragment).setCallback(callback));
    }

    private static Session openActiveSession(Context context, boolean allowLoginUI, OpenRequest openRequest) {
        Session session = new Builder(context).build();
        if (SessionState.CREATED_TOKEN_LOADED.equals(session.getState()) || allowLoginUI) {
            setActiveSession(session);
            if (openRequest != null) {
                session.openForRead(openRequest);
            } else {
                session.open();
            }
            return session;
        }
        return null;
    }

    static Context getStaticContext() {
        return staticContext;
    }

    static void initializeStaticContext(Context currentContext) {
        if ((currentContext != null) && (staticContext == null)) {
            Context applicationContext = currentContext.getApplicationContext();
            staticContext = (applicationContext != null) ? applicationContext : currentContext;
        }
    }

    void authorize(AuthorizationRequest request) {
        boolean started = false;

        autoPublishAsync();

        if (!started && request.allowKatana()) {
            started = tryKatanaProxyAuth(request);
        }
        if (!started && request.allowWebView()) {
            started = tryDialogAuth(request);
        }

        if (!started) {
            synchronized (this.lock) {
                final SessionState oldState = this.state;

                switch (this.state) {
                    case CLOSED:
                    case CLOSED_LOGIN_FAILED:
                        return;

                    default:
                        this.state = SessionState.CLOSED_LOGIN_FAILED;
                        postStateChange(oldState, this.state, new FacebookException("Log in attempt failed."));
                }
            }
        }
    }

    public final void addCallback(StatusCallback callback) {
        synchronized(callbacks) {
            if (callback != null && !callbacks.contains(callback)) {
                callbacks.add(callback);
            }
        }
    }

    public final void removeCallback(StatusCallback callback) {
        synchronized(callbacks) {
            callbacks.remove(callback);
        }
    }

    private void open(OpenRequest openRequest, AuthorizationType authType) {
        validatePermissions(openRequest, authType);
        validateLoginBehavior(openRequest);
        SessionState newState;
        synchronized (this.lock) {
            if (pendingRequest != null) {
                throw new UnsupportedOperationException(
                        "Session: an attempt was made to open a session that has a pending request.");
            }
            final SessionState oldState = this.state;

            switch (this.state) {
                case CREATED:
                    this.state = newState = SessionState.OPENING;
                    if (openRequest == null) {
                        throw new IllegalArgumentException("openRequest cannot be null when opening a new Session");
                    }
                    pendingRequest = openRequest;
                    break;
                case CREATED_TOKEN_LOADED:
                    if (openRequest != null && !Utility.isNullOrEmpty(openRequest.getPermissions())) {
                        if (!Utility.isSubset(openRequest.getPermissions(), getPermissions())) {
                            pendingRequest = openRequest;
                        }
                    }
                    if (pendingRequest == null) {
                        this.state = newState = SessionState.OPENED;
                    } else {
                        this.state = newState = SessionState.OPENING;
                    }
                    break;
                default:
                    throw new UnsupportedOperationException(
                            "Session: an attempt was made to open an already opened session.");
            }
            if (openRequest != null) {
                addCallback(openRequest.getCallback());
            }
            this.postStateChange(oldState, newState, null);
        }

        if (newState == SessionState.OPENING) {
            authorize(openRequest);
        }
    }

    private void reauthorize(ReauthorizeRequest reauthorizeRequest, AuthorizationType authType) {
        validatePermissions(reauthorizeRequest, authType);
        validateLoginBehavior(reauthorizeRequest);
        if (reauthorizeRequest != null) {
            synchronized (this.lock) {
                if (pendingRequest != null) {
                    throw new UnsupportedOperationException(
                            "Session: an attempt was made to reauthorize a session that has a pending request.");
                }
                switch (this.state) {
                    case OPENED:
                    case OPENED_TOKEN_UPDATED:
                        pendingRequest = reauthorizeRequest;
                        break;
                    default:
                        throw new UnsupportedOperationException(
                                "Session: an attempt was made to reauthorize a session that is not currently open.");
                }
            }

            authorize(reauthorizeRequest);
        }
    }

    private void validateLoginBehavior(AuthorizationRequest request) {
        if (request != null && !request.suppressLoginActivityVerification &&
                (SessionLoginBehavior.SSO_WITH_FALLBACK.equals(request.getLoginBehavior()) ||
                 SessionLoginBehavior.SUPPRESS_SSO.equals(request.getLoginBehavior()))) {
            Intent intent = new Intent();
            intent.setClass(getStaticContext(), LoginActivity.class);
            if (!resolveIntent(intent, false)) {
                throw new FacebookException(String.format(
                        "Cannot use SessionLoginBehavior %s when %s is not declared as an activity in AndroidManifest.xml",
                        request.getLoginBehavior(), LoginActivity.class.getName()));
            }
        }
    }

    private void validatePermissions(AuthorizationRequest request, AuthorizationType authType) {
        if (request == null || Utility.isNullOrEmpty(request.getPermissions())) {
            if (AuthorizationType.PUBLISH.equals(authType)) {
                throw new FacebookException("Cannot request publish authorization with no permissions.");
            }
            return; // nothing to check
        }
        for (String permission : request.getPermissions()) {
            if (isPublishPermission(permission)) {
                if (AuthorizationType.READ.equals(authType)) {
                    throw new FacebookException(
                            String.format(
                                    "Cannot pass a publish permission (%s) to a request for read authorization",
                                    permission));
                }
            } else {
                if (AuthorizationType.PUBLISH.equals(authType)) {
                    Log.w(TAG,
                            String.format(
                                    "Should not pass a read permission (%s) to a request for publish authorization",
                                    permission));
                }
            }
        }
    }

    private boolean isPublishPermission(String permission) {
        return permission != null &&
                (permission.startsWith(PUBLISH_PERMISSION_PREFIX) ||
                        permission.startsWith(MANAGE_PERMISSION_PREFIX) ||
                        OTHER_PUBLISH_PERMISSIONS.contains(permission));

    }

    private boolean tryActivityAuth(Intent intent, AuthorizationRequest request, boolean validateSignature) {
        intent.putExtra("client_id", this.applicationId);

        if (!Utility.isNullOrEmpty(request.getPermissions())) {
            intent.putExtra("scope", TextUtils.join(",", request.getPermissions()));
        }

        if (!resolveIntent(intent, validateSignature)) {
            return false;
        }

        try {
            request.getStartActivityDelegate().startActivityForResult(intent, request.getRequestCode());
        } catch (ActivityNotFoundException e) {
            return false;
        }
        return true;
    }

    private boolean resolveIntent(Intent intent, boolean validateSignature) {
        ResolveInfo resolveInfo = getStaticContext().getPackageManager().resolveActivity(intent, 0);
        if ((resolveInfo == null) ||
                (validateSignature && !validateFacebookAppSignature(resolveInfo.activityInfo.packageName))) {
            return false;
        }
        return true;
    }

    private boolean tryDialogAuth(final AuthorizationRequest request) {
        Intent intent = new Intent();

        intent.setClass(getStaticContext(), LoginActivity.class);
        if (tryActivityAuth(intent, request, false)) {
            return true;
        }

        Log.w(TAG,
                String.format("Please add %s as an activity to your AndroidManifest.xml",
                        LoginActivity.class.getName()));

        int permissionCheck = getStaticContext().checkCallingOrSelfPermission(Manifest.permission.INTERNET);
        Activity activityContext = request.getStartActivityDelegate().getActivityContext();
        if (permissionCheck != PackageManager.PERMISSION_GRANTED) {
            AlertDialog.Builder builder = new AlertDialog.Builder(activityContext);
            builder.setTitle("AndroidManifest Error");
            builder.setMessage("WebView login requires INTERNET permission");
            builder.create().show();
            return false;
        }

        Bundle parameters = new Bundle();
        if (!Utility.isNullOrEmpty(request.getPermissions())) {
            String scope = TextUtils.join(",", request.getPermissions());
            parameters.putString(ServerProtocol.DIALOG_PARAM_SCOPE, scope);
        }

        // The call to clear cookies will create the first instance of CookieSyncManager if necessary
        Utility.clearFacebookCookies(getStaticContext());

        DialogListener listener = new DialogListener() {
            public void onComplete(Bundle bundle) {
                // Ensure any cookies set by the dialog are saved
                CookieSyncManager.getInstance().sync();
                AccessToken newToken = AccessToken.createFromDialog(request.getPermissions(), bundle);
                Session.this.authorizationBundle = bundle;
                Session.this.finishAuth(newToken, null);
            }

            public void onError(DialogError error) {
                Bundle bundle = new Bundle();
                bundle.putInt(WEB_VIEW_ERROR_CODE_KEY, error.getErrorCode());
                bundle.putString(WEB_VIEW_FAILING_URL_KEY, error.getFailingUrl());
                Session.this.authorizationBundle = bundle;

                Exception exception = new FacebookAuthorizationException(error.getMessage());
                Session.this.finishAuth(null, exception);
            }

            public void onFacebookError(FacebookError error) {
                Exception exception = new FacebookAuthorizationException(error.getMessage());
                Session.this.finishAuth(null, exception);
            }

            public void onCancel() {
                Exception exception = new FacebookOperationCanceledException("User canceled log in.");
                Session.this.finishAuth(null, exception);
            }
        };

        parameters.putString(ServerProtocol.DIALOG_PARAM_DISPLAY, "touch");
        parameters.putString(ServerProtocol.DIALOG_PARAM_REDIRECT_URI, "fbconnect://success");
        parameters.putString(ServerProtocol.DIALOG_PARAM_TYPE, "user_agent");
        parameters.putString(ServerProtocol.DIALOG_PARAM_CLIENT_ID, this.applicationId);

        Uri uri = Utility.buildUri(ServerProtocol.DIALOG_AUTHORITY, ServerProtocol.DIALOG_OAUTH_PATH, parameters);
        new FbDialog(activityContext, uri.toString(), listener).show();

        return true;
    }

    private boolean tryKatanaProxyAuth(AuthorizationRequest request) {
        Intent intent = new Intent();

        intent.setClassName(NativeProtocol.KATANA_PACKAGE, NativeProtocol.KATANA_PROXY_AUTH_ACTIVITY);
        return tryActivityAuth(intent, request, true);
    }

    private boolean validateFacebookAppSignature(String packageName) {
        PackageInfo packageInfo = null;
        try {
            packageInfo = staticContext.getPackageManager().getPackageInfo(packageName,
                    PackageManager.GET_SIGNATURES);
        } catch (NameNotFoundException e) {
            return false;
        }

        for (Signature signature : packageInfo.signatures) {
            if (signature.toCharsString().equals(NativeProtocol.KATANA_SIGNATURE)) {
                return true;
            }
        }

        return false;
    }

    @SuppressWarnings("incomplete-switch")
    void finishAuth(AccessToken newToken, Exception exception) {
        // If the token we came up with is expired/invalid, then auth failed.
        if ((newToken != null) && newToken.isInvalid()) {
            newToken = null;
            exception = new FacebookException("Invalid access token.");
        }

        // Update the cache if we have a new token.
        if ((newToken != null) && (this.tokenCache != null)) {
            this.tokenCache.save(newToken.toCacheBundle());
        }

        synchronized (this.lock) {
            final SessionState oldState = this.state;

            switch (this.state) {
            case OPENING:
            case OPENED:
            case OPENED_TOKEN_UPDATED:
                if (newToken != null) {
                    this.tokenInfo = newToken;
                    this.state = (oldState == SessionState.OPENING) ? SessionState.OPENED
                            : SessionState.OPENED_TOKEN_UPDATED;
                } else if (exception != null) {
                    this.state = (oldState == SessionState.OPENING) ? SessionState.CLOSED_LOGIN_FAILED
                            : oldState;
                }
                postStateChange(oldState, this.state, exception);
                break;
            }
            pendingRequest = null;
        }
    }

    void postStateChange(final SessionState oldState, final SessionState newState, final Exception exception) {
        synchronized(callbacks) {
            // Need to schedule the callbacks inside the same queue to preserve ordering.
            // Otherwise these callbacks could have been added to the queue before the SessionTracker
            // gets the ACTIVE_SESSION_SET action.
            Runnable runCallbacks = new Runnable() {
                public void run() {
                    for (final StatusCallback callback : callbacks) {
                        Runnable closure = new Runnable() {
                            public void run() {
                                // This can be called inside a synchronized block.
                                callback.call(Session.this, newState, exception);
                            }
                        };
        
                        runWithHandlerOrExecutor(handler, closure);
                    }
                }
            };
            runWithHandlerOrExecutor(handler, runCallbacks);
        }

        if (this == Session.activeSession) {
            if (oldState.isOpened() != newState.isOpened()) {
                if (newState.isOpened()) {
                    postActiveSessionAction(Session.ACTION_ACTIVE_SESSION_OPENED);
                } else {
                    postActiveSessionAction(Session.ACTION_ACTIVE_SESSION_CLOSED);
                }
            }
        }
    }

    static void postActiveSessionAction(String action) {
        final Intent intent = new Intent(action);

        LocalBroadcastManager.getInstance(getStaticContext()).sendBroadcast(intent);
    }

    private static void runWithHandlerOrExecutor(Handler handler, Runnable runnable) {
        if (handler != null) {
            handler.post(runnable);
        } else {
            Settings.getExecutor().execute(runnable);
        }
    }

    void extendAccessTokenIfNeeded() {
        if (shouldExtendAccessToken()) {
            extendAccessToken();
        }
    }

    void extendAccessToken() {
        TokenRefreshRequest newTokenRefreshRequest = null;
        synchronized (this.lock) {
            if (currentTokenRefreshRequest == null) {
                newTokenRefreshRequest = new TokenRefreshRequest();
                currentTokenRefreshRequest = newTokenRefreshRequest;
            }
        }

        if (newTokenRefreshRequest != null) {
            newTokenRefreshRequest.bind();
        }
    }

    boolean shouldExtendAccessToken() {
        if (currentTokenRefreshRequest != null) {
            return false;
        }

        boolean result = false;

        Date now = new Date();

        if (state.isOpened() && tokenInfo.getIsSSO()
                && now.getTime() - lastAttemptedTokenExtendDate.getTime() > TOKEN_EXTEND_RETRY_SECONDS * 1000
                && now.getTime() - tokenInfo.getLastRefresh().getTime() > TOKEN_EXTEND_THRESHOLD_SECONDS * 1000) {
            result = true;
        }

        return result;
    }

    AccessToken getTokenInfo() {
        return tokenInfo;
    }

    void setTokenInfo(AccessToken tokenInfo) {
        this.tokenInfo = tokenInfo;
    }

    Date getLastAttemptedTokenExtendDate() {
        return lastAttemptedTokenExtendDate;
    }

    void setLastAttemptedTokenExtendDate(Date lastAttemptedTokenExtendDate) {
        this.lastAttemptedTokenExtendDate = lastAttemptedTokenExtendDate;
    }

    void setCurrentTokenRefreshRequest(TokenRefreshRequest request) {
        this.currentTokenRefreshRequest = request;
    }

    static String getMetadataApplicationId(Context context) {
        try {
            ApplicationInfo ai = context.getPackageManager().getApplicationInfo(
                    context.getPackageName(), PackageManager.GET_META_DATA);
            if (ai.metaData != null) {
                return ai.metaData.getString(APPLICATION_ID_PROPERTY);
            }
        } catch (NameNotFoundException e) {
            // if we can't find it in the manifest, just return null
        }

        return null;
    }

    class TokenRefreshRequest implements ServiceConnection {

        final Messenger messageReceiver = new Messenger(
                new TokenRefreshRequestHandler(Session.this, this));

        Messenger messageSender = null;

        public void bind() {
            Intent intent = new Intent();
            intent.setClassName(NativeProtocol.KATANA_PACKAGE, NativeProtocol.KATANA_TOKEN_REFRESH_ACTIVITY);

            ResolveInfo resolveInfo = staticContext.getPackageManager().resolveService(intent, 0);
            if (resolveInfo != null && validateFacebookAppSignature(resolveInfo.serviceInfo.packageName)
                    && staticContext.bindService(intent, new TokenRefreshRequest(), Context.BIND_AUTO_CREATE)) {
                setLastAttemptedTokenExtendDate(new Date());
            } else {
                cleanup();
            }
        }

        public void onServiceConnected(ComponentName className, IBinder service) {
            messageSender = new Messenger(service);
            refreshToken();
        }

        public void onServiceDisconnected(ComponentName arg) {
            cleanup();

            // We returned an error so there's no point in
            // keeping the binding open.
            staticContext.unbindService(TokenRefreshRequest.this);
        }

        private void cleanup() {
            if (currentTokenRefreshRequest == this) {
                currentTokenRefreshRequest = null;
            }
        }

        private void refreshToken() {
            Bundle requestData = new Bundle();
            requestData.putString(AccessToken.ACCESS_TOKEN_KEY, getTokenInfo().getToken());

            Message request = Message.obtain();
            request.setData(requestData);
            request.replyTo = messageReceiver;

            try {
                messageSender.send(request);
            } catch (RemoteException e) {
                cleanup();
            }
        }
        
    }

    // Creating a static Handler class to reduce the possibility of a memory leak.
    // Handler objects for the same thread all share a common Looper object, which they post messages
    // to and read from. As messages contain target Handler, as long as there are messages with target
    // handler in the message queue, the handler cannot be garbage collected. If handler is not static,
    // the instance of the containing class also cannot be garbage collected even if it is destroyed.
    static class TokenRefreshRequestHandler extends Handler {

        private WeakReference<Session> sessionWeakReference;
        private WeakReference<TokenRefreshRequest> refreshRequestWeakReference;

        TokenRefreshRequestHandler(Session session, TokenRefreshRequest refreshRequest) {
            super(Looper.getMainLooper());
            sessionWeakReference = new WeakReference<Session>(session);
            refreshRequestWeakReference = new WeakReference<TokenRefreshRequest>(refreshRequest);
        }

        @Override
        public void handleMessage(Message msg) {
            String token = msg.getData().getString(AccessToken.ACCESS_TOKEN_KEY);
            Session session = sessionWeakReference.get();

            if (session != null && token != null) {
                session.internalRefreshToken(msg.getData());
            }

            TokenRefreshRequest request = refreshRequestWeakReference.get();
            if (request != null) {
                // The refreshToken function should be called rarely,
                // so there is no point in keeping the binding open.
                staticContext.unbindService(request);
                request.cleanup();
            }
        }
    }

    /**
     * Provides asynchronous notification of Session state changes.
     * 
     * @see Session#open open
     */
    public interface StatusCallback {
        public void call(Session session, SessionState state, Exception exception);
    }
    
    @Override
    public int hashCode() {
        return 0;
    }
    
    @Override
    public boolean equals(Object otherObj) {
        if (!(otherObj instanceof Session)) {
            return false;
        }
        Session other = (Session) otherObj;
        
        return areEqual(other.applicationId, applicationId) &&
                areEqual(other.authorizationBundle, authorizationBundle) &&
                areEqual(other.state, state) &&
                areEqual(other.getExpirationDate(), getExpirationDate());
    }
    
    private static boolean areEqual(Object a, Object b) {
        if (a == null) {
            return b == null;
        } else {
            return a.equals(b);
        }
    }

    /**
     * Builder class used to create a Session.
     */
    public static final class Builder {
        private final Context context;
        private String applicationId;
        private TokenCache tokenCache;
        private boolean shouldAutoPublishInstall = true;

        /**
         * Constructs a new Builder associated with the context.
         *
         * @param context the Activity or Service starting the Session
         */
        public Builder(Context context) {
            this.context = context;
        }

        /**
         * Sets the application id for the Session.
         *
         * @param applicationId the application id
         * @return the Builder instance
         */
        public Builder setApplicationId(final String applicationId) {
            this.applicationId = applicationId;
            return this;
        }

        /**
         * Sets the TokenCache for the Session.
         *
         * @param tokenCache the token cache to use
         * @return the Builder instance
         */
        public Builder setTokenCache(final TokenCache tokenCache) {
            this.tokenCache = tokenCache;
            return this;
        }

        public Builder setShouldAutoPublishInstall(boolean shouldAutoPublishInstall) {
            this.shouldAutoPublishInstall = shouldAutoPublishInstall;
            return this;
        }

        /**
         * Build the Session.
         *
         * @return a new Session
         */
        public Session build() {
            return new Session(context, applicationId, tokenCache, shouldAutoPublishInstall);
        }
    }

    private interface StartActivityDelegate {
        public void startActivityForResult(Intent intent, int requestCode);

        public Activity getActivityContext();
    }

    enum AuthorizationType {
        READ,
        PUBLISH
    }

    private void autoPublishAsync() {
        AutoPublishAsyncTask asyncTask = null;
        synchronized (this) {
            if (autoPublishAsyncTask == null && shouldAutoPublish) {
                // copy the application id to guarantee thread safety against our container.
                String applicationId = Session.this.applicationId;

                // skip publish if we don't have an application id.
                if (applicationId != null) {
                    asyncTask = autoPublishAsyncTask = new AutoPublishAsyncTask(applicationId, staticContext);
                }
            }
        }

        if (asyncTask != null) {
            asyncTask.execute();
        }
    }

    /**
     * Async implementation to allow auto publishing to not block the ui thread.
     */
    private class AutoPublishAsyncTask extends AsyncTask<Void, Void, Void> {
        private final String mApplicationId;
        private final Context mApplicationContext;

        public AutoPublishAsyncTask(String applicationId, Context context) {
            mApplicationId = applicationId;
            mApplicationContext = context.getApplicationContext();
        }

        @Override
        protected Void doInBackground(Void... voids) {
            try {
                Settings.publishInstall(mApplicationContext, mApplicationId);
            } catch (Exception e) {
                Util.logd("Facebook-publish", e.getMessage());
            }
            return null;
        }

        @Override
        protected void onPostExecute(Void result) {
            // always clear out the publisher to allow other invocations.
            synchronized (Session.this) {
                autoPublishAsyncTask = null;
            }
        }
    }

    public static class AuthorizationRequest implements Serializable {

        private static final long serialVersionUID = 1L;

        private final StartActivityDelegate startActivityDelegate;
        private SessionLoginBehavior loginBehavior = SessionLoginBehavior.SSO_WITH_FALLBACK;
        private int requestCode = DEFAULT_AUTHORIZE_ACTIVITY_CODE;
        private StatusCallback statusCallback;
        private boolean suppressLoginActivityVerification = false;
        private List<String> permissions = Collections.emptyList();

        AuthorizationRequest(final Activity activity) {
            startActivityDelegate = new StartActivityDelegate() {
                public void startActivityForResult(Intent intent, int requestCode) {
                    activity.startActivityForResult(intent, requestCode);
                }

                public Activity getActivityContext() {
                    return activity;
                }
            };
        }

        AuthorizationRequest(final Fragment fragment) {
            startActivityDelegate = new StartActivityDelegate() {
                public void startActivityForResult(Intent intent, int requestCode) {
                    fragment.startActivityForResult(intent, requestCode);
                }

                public Activity getActivityContext() {
                    return fragment.getActivity();
                }
            };
        }

        /**
         * Constructor to be used for V1 serialization only, DO NOT CHANGE.
         */
        private AuthorizationRequest(SessionLoginBehavior loginBehavior, int requestCode,
                List<String> permissions, boolean suppressLoginActivityVerification) {
            startActivityDelegate = new StartActivityDelegate() {
                public void startActivityForResult(Intent intent, int requestCode) {
                    throw new UnsupportedOperationException(
                            "Cannot create an AuthorizationRequest without a valid Activity or Fragment");
                }

                public Activity getActivityContext() {
                    throw new UnsupportedOperationException(
                            "Cannot create an AuthorizationRequest without a valid Activity or Fragment");
                }
            };
            this.loginBehavior = loginBehavior;
            this.requestCode = requestCode;
            this.permissions = permissions;
            this.suppressLoginActivityVerification = suppressLoginActivityVerification;
        }

        /**
         * Used for backwards compatibility with Facebook.java only, DO NOT USE.
         *
         * @param suppressVerification
         */
        public void suppressLoginActivityVerification(boolean suppressVerification) {
            suppressLoginActivityVerification = suppressVerification;
        }

        AuthorizationRequest setCallback(StatusCallback statusCallback) {
            this.statusCallback = statusCallback;
            return this;
        }

        StatusCallback getCallback() {
            return statusCallback;
        }

        AuthorizationRequest setLoginBehavior(SessionLoginBehavior loginBehavior) {
            if (loginBehavior != null) {
                this.loginBehavior = loginBehavior;
            }
            return this;
        }

        SessionLoginBehavior getLoginBehavior() {
            return loginBehavior;
        }

        AuthorizationRequest setRequestCode(int requestCode) {
            if (requestCode >= 0) {
                this.requestCode = requestCode;
            }
            return this;
        }

        int getRequestCode() {
            return requestCode;
        }

        AuthorizationRequest setPermissions(List<String> permissions) {
            if (permissions != null) {
                this.permissions = permissions;
            }
            return this;
        }

        List<String> getPermissions() {
            return permissions;
        }

        StartActivityDelegate getStartActivityDelegate() {
            return startActivityDelegate;
        }

        boolean allowKatana() {
            switch (loginBehavior) {
                case SSO_ONLY: return true;
                case SUPPRESS_SSO: return false;
                default: return true;
            }
        }

        boolean allowWebView() {
            switch (loginBehavior) {
                case SSO_ONLY: return false;
                case SUPPRESS_SSO: return true;
                default: return true;
            }
        }

        // package private so subclasses can use it
        Object writeReplace() {
            return new AuthRequestSerializationProxyV1(loginBehavior, requestCode, permissions,
                    suppressLoginActivityVerification);
        }

        // have a readObject that throws to prevent spoofing
        // package private so subclasses can use it
        void readObject(ObjectInputStream stream) throws InvalidObjectException {
            throw new InvalidObjectException("Cannot readObject, serialization proxy required");
        }

        private static class AuthRequestSerializationProxyV1 implements Serializable {
            private static final long serialVersionUID = -8748347685113614927L;
            private final SessionLoginBehavior loginBehavior;
            private final int requestCode;
            private boolean suppressLoginActivityVerification;
            private final List<String> permissions;

            private AuthRequestSerializationProxyV1(SessionLoginBehavior loginBehavior,
                    int requestCode, List<String> permissions, boolean suppressVerification) {
                this.loginBehavior = loginBehavior;
                this.requestCode = requestCode;
                this.permissions = permissions;
                this.suppressLoginActivityVerification = suppressVerification;
            }

            private Object readResolve() {
                return new AuthorizationRequest(loginBehavior, requestCode, permissions,
                        suppressLoginActivityVerification);
            }
        }
    }

    /**
     * A request used to open a Session.
     */
    public static final class OpenRequest extends AuthorizationRequest {
        private static final long serialVersionUID = 1L;

        /**
         * Constructs an OpenRequest.
         *
         * @param activity the Activity to use to open the Session
         */
        public OpenRequest(Activity activity) {
            super(activity);
        }

        /**
         * Constructs an OpenRequest.
         *
         * @param fragment the Fragment to use to open the Session
         */
        public OpenRequest(Fragment fragment) {
            super(fragment);
        }

        /**
         * Sets the StatusCallback for the OpenRequest.
         *
         * @param statusCallback
         *            The {@link StatusCallback SessionStatusCallback} to
         *            notify regarding Session state changes.
         * @return the OpenRequest object to allow for chaining
         */
        public final OpenRequest setCallback(StatusCallback statusCallback) {
            super.setCallback(statusCallback);
            return this;
        }

        /**
         * Sets the login behavior for the OpenRequest.
         *
         * @param loginBehavior
         *            The {@link SessionLoginBehavior SessionLoginBehavior} that
         *            specifies what behaviors should be attempted during
         *            authorization.
         * @return the OpenRequest object to allow for chaining
         */
        public final OpenRequest setLoginBehavior(SessionLoginBehavior loginBehavior) {
            super.setLoginBehavior(loginBehavior);
            return this;
        }

        /**
         * Sets the request code for the OpenRequest.
         *
         * @param requestCode
         *            An integer that identifies this request. This integer will be used
         *            as the request code in {@link Activity#onActivityResult
         *            onActivityResult}. This integer should be >= 0. If a value < 0 is
         *            passed in, then a default value will be used.
         * @return the OpenRequest object to allow for chaining
         */
        public final OpenRequest setRequestCode(int requestCode) {
            super.setRequestCode(requestCode);
            return this;
        }

        /**
         * Sets the permissions for the OpenRequest.
         *
         * @param permissions
         *            A List&lt;String&gt; representing the permissions to request
         *            during the authentication flow. A null or empty List
         *            represents basic permissions.
         * @return the OpenRequest object to allow for chaining
         */
        public final OpenRequest setPermissions(List<String> permissions) {
            super.setPermissions(permissions);
            return this;
        }
    }

    /**
     * A request to be used to reauthorize a Session.
     */
    public static final class ReauthorizeRequest extends AuthorizationRequest {
        private static final long serialVersionUID = 1L;

        /**
         * Constructs a ReauthorizeRequest.
         *
         * @param activity the Activity used to reauthorize
         * @param permissions additional permissions to request
         */
        public ReauthorizeRequest(Activity activity, List<String> permissions) {
            super(activity);
            setPermissions(permissions);
        }

        /**
         * Constructs a ReauthorizeRequest.
         *
         * @param fragment the Fragment used to reauthorize
         * @param permissions additional permissions to request
         */
        public ReauthorizeRequest(Fragment fragment, List<String> permissions) {
            super(fragment);
            setPermissions(permissions);
        }

        /**
         * Sets the StatusCallback for the ReauthorizeRequest.
         *
         * @param statusCallback
         *            The {@link StatusCallback SessionStatusCallback} to
         *            notify regarding Session state changes.
         * @return the ReauthorizeRequest object to allow for chaining
         */
        public final ReauthorizeRequest setCallback(StatusCallback statusCallback) {
            super.setCallback(statusCallback);
            return this;
        }

        /**
         * Sets the login behavior for the ReauthorizeRequest.
         *
         * @param loginBehavior
         *            The {@link SessionLoginBehavior SessionLoginBehavior} that
         *            specifies what behaviors should be attempted during
         *            authorization.
         * @return the ReauthorizeRequest object to allow for chaining
         */
        public final ReauthorizeRequest setLoginBehavior(SessionLoginBehavior loginBehavior) {
            super.setLoginBehavior(loginBehavior);
            return this;
        }

        /**
         * Sets the request code for the ReauthorizeRequest.
         *
         * @param requestCode
         *            An integer that identifies this request. This integer will be used
         *            as the request code in {@link Activity#onActivityResult
         *            onActivityResult}. This integer should be >= 0. If a value < 0 is
         *            passed in, then a default value will be used.
         * @return the ReauthorizeRequest object to allow for chaining
         */
        public final ReauthorizeRequest setRequestCode(int requestCode) {
            super.setRequestCode(requestCode);
            return this;
        }
    }
}
