jest.mock('react-native', () => ({
  NativeModules: {
    RNResponsysBridge: {
      registerUserId: jest.fn(),
      trackEvent: jest.fn(),
      setDeviceToken: jest.fn(),
      registerApp: jest.fn(),
      getDeviceId: jest.fn(),
    }
  }
}))

import { NativeModules } from 'react-native'
import ResponsysBridge from './index'

const { RNResponsysBridge } = NativeModules

beforeEach(() => {
  for (const property in NativeModules.RNResponsysBridge) {
    NativeModules.RNResponsysBridge[property].mockClear()
  }
})

test('Should register user ID', () => {
  const userId = 'some-user-id'
  ResponsysBridge.registerUserId(userId)

  expect(RNResponsysBridge.registerUserId).toHaveBeenCalledWith(userId)
})

test('Should trackt event', () => {
  const trackEvent = 'some-track-event'
  ResponsysBridge.trackEvent(trackEvent)

  expect(RNResponsysBridge.trackEvent).toHaveBeenCalledWith(trackEvent)
})

test('Should configure device token', () => {
  const deviceToken = 'some-device-token'
  ResponsysBridge.configureDeviceToken(deviceToken)

  expect(RNResponsysBridge.setDeviceToken).toHaveBeenCalledWith(deviceToken)
})

test('Should register app with default location', () => {
  ResponsysBridge.registerApp()

  expect(RNResponsysBridge.registerApp).toHaveBeenCalledWith(false)
})

test('Should register app using device location', () => {
  const useLocation = true
  ResponsysBridge.registerApp(useLocation)

  expect(RNResponsysBridge.registerApp).toHaveBeenCalledWith(useLocation)
})

test('Should retrieve device ID', () => {
  const fakeDeviceId = 'fake-device-id'
  NativeModules.RNResponsysBridge.getDeviceId.mockReturnValue(fakeDeviceId)
  const retrievedDeviceId = ResponsysBridge.retrieveDeviceId()

  expect(RNResponsysBridge.getDeviceId).toHaveBeenCalled()
  expect(retrievedDeviceId).toEqual(fakeDeviceId)
})
