import { NativeModules } from 'react-native'

const { RNResponsysBridge } = NativeModules

const ResponsysBridge = {
  registerUserId: function (userId) {
    // Convert to string to prevent iOS conversion error
    RNResponsysBridge.registerUserId('' + userId)
  },
  trackEvent: function (eventName) {
    RNResponsysBridge.trackEvent(eventName)
  },
}

export default ResponsysBridge
