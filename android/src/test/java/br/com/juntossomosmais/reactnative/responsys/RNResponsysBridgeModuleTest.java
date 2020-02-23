package br.com.juntossomosmais.reactnative.responsys;

import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactMethod;
import com.pushio.manager.PushIOManager;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

import java.lang.reflect.Method;
import java.util.List;

import static br.com.juntossomosmais.support.Utils.getMethodsAnnotatedWith;
import static org.assertj.core.api.Assertions.assertThat;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.*;
import static org.powermock.api.mockito.PowerMockito.mockStatic;

@RunWith(PowerMockRunner.class)
@PrepareForTest({PushIOManager.class})
public class RNResponsysBridgeModuleTest {

    @Test
    public void shouldExposeTwoMethodToBeAvailableForReactNativeUsage() {
        List<Method> methods = getMethodsAnnotatedWith(RNResponsysBridgeModule.class, ReactMethod.class);

        assertThat(methods).hasSize(2);

        Method firstMethod = methods.get(0);
        Method secondMethod = methods.get(1);

        assertThat(firstMethod.getName()).isEqualTo("registerUserId");
        assertThat(secondMethod.getName()).isEqualTo("trackEvent");
    }

    @Test
    public void shouldRegisterUserId() {
        RNResponsysBridgeModule bridge = new RNResponsysBridgeModule(mock(ReactApplicationContext.class));

        mockStatic(PushIOManager.class);
        PushIOManager mockPushIOManager = mock(PushIOManager.class);
        when(PushIOManager.getInstance(any())).thenReturn(mockPushIOManager);

        String someUserId = "some-user-id";
        bridge.registerUserId(someUserId);

        verify(mockPushIOManager).registerUserId(someUserId);
    }

    @Test
    public void shouldTrackEvent() {
        RNResponsysBridgeModule bridge = new RNResponsysBridgeModule(mock(ReactApplicationContext.class));

        mockStatic(PushIOManager.class);
        PushIOManager mockPushIOManager = mock(PushIOManager.class);
        when(PushIOManager.getInstance(any())).thenReturn(mockPushIOManager);

        String someEvent = "some-event";
        bridge.trackEvent(someEvent);

        verify(mockPushIOManager).trackEvent(someEvent);
    }
}
