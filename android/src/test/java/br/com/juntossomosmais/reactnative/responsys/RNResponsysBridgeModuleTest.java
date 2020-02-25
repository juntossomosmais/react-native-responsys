package br.com.juntossomosmais.reactnative.responsys;

import android.os.Build;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactMethod;
import com.pushio.manager.PushIOManager;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.powermock.api.mockito.PowerMockito;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.List;

import static br.com.juntossomosmais.support.Utils.getMethodsAnnotatedWith;
import static org.assertj.core.api.Assertions.assertThat;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.*;
import static org.powermock.api.mockito.PowerMockito.mockStatic;

@RunWith(PowerMockRunner.class)
@PrepareForTest({PushIOManager.class, Build.class})
public class RNResponsysBridgeModuleTest {
    private RNResponsysBridgeModule bridge;

    @Before
    public void beforeEachTest() throws Exception {
        bridge = new RNResponsysBridgeModule(mock(ReactApplicationContext.class));
        Field brandField = Build.class.getField("BRAND");
        brandField.setAccessible(true);
        brandField.set(null,"generic");
        Field deviceField = Build.class.getField("DEVICE");
        deviceField.setAccessible(true);
        deviceField.set(null,"generic");
    }

    @Test
    public void shouldExpose5MethodsToBeAvailableForReactNativeUsage() {
        List<Method> methods = getMethodsAnnotatedWith(RNResponsysBridgeModule.class, ReactMethod.class);

        assertThat(methods).hasSize(5);
    }

    @Test
    public void shouldRegisterUserId() {
        mockStatic(PushIOManager.class);
        PushIOManager mockPushIOManager = mock(PushIOManager.class);
        when(PushIOManager.getInstance(any())).thenReturn(mockPushIOManager);

        String someUserId = "some-user-id";
        bridge.registerUserId(someUserId);

        verify(mockPushIOManager).registerUserId(someUserId);
    }

    @Test
    public void shouldTrackEvent() {
        mockStatic(PushIOManager.class);
        PushIOManager mockPushIOManager = mock(PushIOManager.class);
        when(PushIOManager.getInstance(any())).thenReturn(mockPushIOManager);

        String someEvent = "some-event";
        bridge.trackEvent(someEvent);

        verify(mockPushIOManager).trackEvent(someEvent);
    }

    @Test
    public void shouldSetDeviceToken() {
        mockStatic(PushIOManager.class);
        PushIOManager mockPushIOManager = mock(PushIOManager.class);
        when(PushIOManager.getInstance(any())).thenReturn(mockPushIOManager);

        String someToken = "some-token";
        bridge.setDeviceToken(someToken);

        verify(mockPushIOManager).setDeviceToken(someToken);
    }

    @Test
    public void shouldRegisterApp() {
        mockStatic(PushIOManager.class);
        PushIOManager mockPushIOManager = mock(PushIOManager.class);
        when(PushIOManager.getInstance(any())).thenReturn(mockPushIOManager);

        boolean useLocation = false;
        bridge.registerApp(useLocation);

        verify(mockPushIOManager).registerApp(useLocation);
    }

    @Test
    public void shouldRetrieveDeviceId() {
        mockStatic(PushIOManager.class);
        PushIOManager mockPushIOManager = mock(PushIOManager.class);
        when(PushIOManager.getInstance(any())).thenReturn(mockPushIOManager);
        String fakeDeviceId = "fake-device-id";
        when(mockPushIOManager.getDeviceId()).thenReturn(fakeDeviceId);

        String deviceId = bridge.getDeviceId();

        verify(mockPushIOManager, times(1)).getDeviceId();
        assertThat(deviceId).isEqualTo(fakeDeviceId);
    }
}
