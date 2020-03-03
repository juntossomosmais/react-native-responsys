jest.mock('react-native', () => ({ NativeModules: {RNResponsysBridge: {registerUserId: jest.fn()}} }))

import { NativeModules } from 'react-native'
const { RNResponsysBridge } = NativeModules

import ResponsysBridge from './index'

test('Should register user ID', () => {
  let userId = 'some-user-id'
  ResponsysBridge.registerUserId(userId)

  expect(RNResponsysBridge.registerUserId).toHaveBeenCalledWith(userId);
})
