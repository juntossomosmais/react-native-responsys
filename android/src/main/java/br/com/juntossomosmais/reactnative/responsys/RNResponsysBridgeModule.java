package br.com.juntossomosmais.reactnative.responsys;

import android.os.Build;
import android.util.Log;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.pushio.manager.PushIOManager;

public class RNResponsysBridgeModule extends ReactContextBaseJavaModule {

    public RNResponsysBridgeModule(ReactApplicationContext reactContext) {
        super(reactContext);
    }

    private PushIOManager getPushIOManager() {
        if (isEmulator()) {
            PushIOManager.setLoggingEnabled(true);
            PushIOManager.setLogLevel(Log.VERBOSE);
        }
        return PushIOManager.getInstance(getReactApplicationContext());
    }

    private boolean isEmulator() {
        return (Build.BRAND.startsWith("generic") && Build.DEVICE.startsWith("generic"))
            || Build.FINGERPRINT.startsWith("generic")
            || Build.FINGERPRINT.startsWith("unknown")
            || Build.HARDWARE.contains("goldfish")
            || Build.HARDWARE.contains("ranchu")
            || Build.MODEL.contains("google_sdk")
            || Build.MODEL.contains("Emulator")
            || Build.MODEL.contains("Android SDK built for x86")
            || Build.MANUFACTURER.contains("Genymotion")
            || Build.PRODUCT.contains("sdk_google")
            || Build.PRODUCT.contains("google_sdk")
            || Build.PRODUCT.contains("sdk")
            || Build.PRODUCT.contains("sdk_x86")
            || Build.PRODUCT.contains("vbox86p")
            || Build.PRODUCT.contains("emulator")
            || Build.PRODUCT.contains("simulator");
    }

    @Override
    public String getName() {
        return "RNResponsysBridge";
    }

    @ReactMethod
    public void registerUserId(String userId) {
        getPushIOManager().registerUserId(userId);
    }

    @ReactMethod
    public void trackEvent(String event) {
        getPushIOManager().trackEvent(event);
    }

    @ReactMethod
    public void setDeviceToken(String deviceToken) {
        getPushIOManager().setDeviceToken(deviceToken);
    }

    @ReactMethod
    public void registerApp(boolean useLocation){
        getPushIOManager().registerApp(useLocation);
    }

    @ReactMethod
    public String getDeviceId() {
        return getPushIOManager().getDeviceId();
    }
}
