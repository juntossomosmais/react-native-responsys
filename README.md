# React Native

An honest react native project to bridge Oracle Responsys SDK.

## How to setup your project

First install this native module:

    npm install @juntossomosmais/react-native-responsys

React Native does automatic linking from 0.60 version onwards, but if you're using an older version, then do the following:

    react-native link @juntossomosmais/react-native-responsys

### iOS

TODO.

### Android

If your are using a version older than 0.60, then follow the steps:

1. Insert the following lines inside the dependencies block in `android/app/build.gradle`:
   ```
     implementation project(':juntossomosmais_react-native-responsys')
   ```
2. Open up `android/app/src/main/java/[...]/MainActivity.java`

- Add `import br.com.juntossomosmais.reactnative.responsys.RNResponsysBridgePackage;` to the imports at the top of the file
- Add `new RNResponsysBridgePackage()` to the list returned by the `getPackages()` method

---

Add the following in your `AndroidManifest.xml`:

```xml
    .....
    <!-- Do not forget to follow Oracle Responsys documentation regarding permissions -->
    .....
    <application ....>
        <!-- Do not forget to follow Oracle Responsys documentation -->
        <service
            android:name="br.com.juntossomosmais.reactnative.responsys.RNResponsysBridgeListenerService"
            android:exported="false">
            <intent-filter>
                <action android:name="com.google.firebase.MESSAGING_EVENT" />
            </intent-filter>
        </service>
     .....
```

### Oracle Setup

In order to use it, you must follow Oracle guide to configure either for Android and iOS:

- [Steps to configure your Android project](https://docs.oracle.com/cloud/latest/marketingcs_gs/OMCFB/android/step-by-step/)
- [Steps to configure your iOS project](https://docs.oracle.com/cloud/latest/marketingcs_gs/OMCFB/ios/step-by-step/)

## How to receive push notifications

In case you have multiple push SDKs (sample with Firebase Messaging):

```javascript
import firebase from 'react-native-firebase'
import ResponsysBridge from '@juntossomosmais/react-native-responsys'

const messaging = firebase.messaging()

messaging
  .getToken()
  .then((token) => {
    ResponsysBridge.configureDeviceToken(token)
    const useLocation = false
    ResponsysBridge.registerApp(useLocation)
  })
  .catch((e) => {
    console.error(`Something went wrong with your setup: ${e}`)
  })
```

Or simply:

```javascript
import ResponsysBridge from '@juntossomosmais/react-native-responsys'

const useLocation = false
ResponsysBridge.registerApp(useLocation)
```

## Useful links

Regarding Oracle Responsys:

- [Organization which has all repositories related to Oracle Marketing Cloud](https://github.com/pushio)
- [Android SDK (Push IO Manager)](https://github.com/pushio/PushIOManager_Android)
- [Everything related to Android integration](https://docs.oracle.com/cloud/latest/marketingcs_gs/OMCFB/android/)
- [iOS SDK (Push IO Manager)](https://github.com/pushio/PushIOManager_iOS)
- [Everything related to iOS integration](https://docs.oracle.com/cloud/latest/marketingcs_gs/OMCFB/ios/)

Native Module:

- [Modules for iOS](https://facebook.github.io/react-native/docs/native-modules-ios)
- [Modules for Android](https://facebook.github.io/react-native/docs/native-modules-android)
- [Swift in React Native - The Ultimate Guide Part 1: Modules](https://teabreak.e-spres-oh.com/swift-in-react-native-the-ultimate-guide-part-1-modules-9bb8d054db03)

## How to setup your development environment

You should use Node v12.13.1

After downloading this project, you can execute in the root folder:

    npm install

After it, using IntelliJ open the folder [android](android) to start to work. For iOS is the same logic, using AppCode open the folder [ios](ios).

## Important notice

The purpose of this App and even this README is not fully closed.
