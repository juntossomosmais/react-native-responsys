package br.com.juntossomosmais.reactnative.responsys;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.pushio.manager.PushIOManager;

public class RNResponsysBridgeModule extends ReactContextBaseJavaModule {
    private final ReactApplicationContext reactContext;

    public RNResponsysBridgeModule(ReactApplicationContext reactContext) {
        super(reactContext);
        this.reactContext = reactContext;
    }

    private PushIOManager getPushIOManager() {
        return PushIOManager.getInstance(getReactApplicationContext());
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
}
