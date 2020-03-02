package br.com.juntossomosmais.reactnative.responsys;

import android.util.Log;
import androidx.annotation.NonNull;
import com.google.firebase.messaging.FirebaseMessagingService;
import com.google.firebase.messaging.RemoteMessage;
import com.pushio.manager.PushIOManager;

public class RNResponsysBridgeListenerService extends FirebaseMessagingService {
    private static final String TAG = RNResponsysBridgeListenerService.class.getSimpleName();

    @Override
    public void onMessageReceived(@NonNull RemoteMessage remoteMessage) {
        super.onMessageReceived(remoteMessage);
        Log.i(TAG, "New message received!");
        try {
            PushIOManager instance = getPushIOManager();
            Log.i(TAG, "Checking if is from Oracle Responsys...");
            if (instance.isResponsysPush(remoteMessage)) {
                Log.i(TAG, "It is! Handling the message...");
                instance.handleMessage(remoteMessage);
            }
        } catch (Exception exception) {
            Log.e(TAG, "PushIOManager or another internal logic has a problem", exception);
        }
    }

    @Override
    public void onNewToken(@NonNull String token) {
        super.onNewToken(token);
        Log.i(TAG, "Configuring token...");
        getPushIOManager().setDeviceToken(token);
    }

    private PushIOManager getPushIOManager() {
        return PushIOManager.getInstance(getApplicationContext());
    }
}
