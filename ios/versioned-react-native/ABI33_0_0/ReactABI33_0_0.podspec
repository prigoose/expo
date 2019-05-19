# coding: utf-8
# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))
version = package['version']

source = { :git => 'https://github.com/facebook/react-native.git' }
if version == '1000.0.0'
  # This is an unpublished version, use the latest commit hash of the react-native repo, which we’re presumably in.
  source[:commit] = `git rev-parse HEAD`.strip
else
  source[:tag] = "v#{version}"
end

folly_compiler_flags = '-DFOLLY_NO_CONFIG -DFOLLY_MOBILE=1 -DFOLLY_USE_LIBCPP=1'
folly_version = '2018.10.22.00'

Pod::Spec.new do |s|
  s.name                    = "ReactABI33_0_0"
  s.version                 = version
  s.summary                 = package["description"]
  s.description             = <<-DESC
                                React Native apps are built using the React JS
                                framework, and render directly to native UIKit
                                elements using a fully asynchronous architecture.
                                There is no browser and no HTML. We have picked what
                                we think is the best set of features from these and
                                other technologies to build what we hope to become
                                the best product development framework available,
                                with an emphasis on iteration speed, developer
                                delight, continuity of technology, and absolutely
                                beautiful and fast products with no compromises in
                                quality or capability.
                             DESC
  s.homepage                = "http://facebook.github.io/react-native/"
  s.license                 = package["license"]
  s.author                  = "Facebook"
  s.source                  = { :path => "." }
  s.default_subspec         = "Core"
  s.requires_arc            = true
  s.platforms               = { :ios => "9.0", :tvos => "9.2" }
  s.pod_target_xcconfig     = { "CLANG_CXX_LANGUAGE_STANDARD" => "c++14" }
  s.preserve_paths          = "package.json", "LICENSE", "LICENSE-docs"
  s.cocoapods_version       = ">= 1.2.0"

  s.subspec "Core" do |ss|
    ss.dependency             "yogaABI33_0_0", "#{package["version"]}.React"
    ss.source_files         = "React/**/*.{c,h,m,mm,S,cpp}"
    ss.exclude_files        = "**/__tests__/*",
                              "IntegrationTests/*",
                              "React/DevSupport/*",
                              "React/Inspector/*",
                              "ReactCommon/ABI33_0_0yoga/*",
                              "React/Cxx*/*",
                              "React/Fabric/**/*"
    ss.ios.exclude_files    = "React/**/ABI33_0_0RCTTV*.*"
    ss.tvos.exclude_files   = "React/Modules/RCTClipboard*",
                              "React/Views/RCTDatePicker*",
                              "React/Views/RCTPicker*",
                              "React/Views/RCTRefreshControl*",
                              "React/Views/RCTSlider*",
                              "React/Views/RCTSwitch*",
                              "React/Views/RCTWebView*"
    ss.compiler_flags       = folly_compiler_flags
    ss.header_dir           = "ReactABI33_0_0"
    ss.framework            = "JavaScriptCore"
    ss.libraries            = "stdc++"
    ss.pod_target_xcconfig  = { "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/ReactCommon\"" }
  end

  s.subspec "Expo" do |ss|
    ss.dependency         "ReactABI33_0_0/Core"
    ss.dependency         "ABI33_0_0UMCore"
    ss.dependency         "ABI33_0_0UMReactNativeAdapter"
    ss.dependency         "ABI33_0_0UMBarCodeScannerInterface"
    ss.dependency         "ABI33_0_0UMCameraInterface"
    ss.dependency         "ABI33_0_0UMConstantsInterface"
    ss.dependency         "ABI33_0_0UMFaceDetectorInterface"
    ss.dependency         "ABI33_0_0UMFileSystemInterface"
    ss.dependency         "ABI33_0_0UMFontInterface"
    ss.dependency         "ABI33_0_0UMImageLoaderInterface"
    ss.dependency         "ABI33_0_0UMPermissionsInterface"
    ss.dependency         "ABI33_0_0UMSensorsInterface"
    ss.dependency         "ABI33_0_0UMTaskManagerInterface"
    ss.dependency         "ABI33_0_0EXAdsAdMob"
    ss.dependency         "ABI33_0_0EXAdsFacebook"
    ss.dependency         "ABI33_0_0EXAmplitude"
    ss.dependency         "ABI33_0_0EXSegment"
    ss.dependency         "ABI33_0_0EXAppAuth"
    ss.dependency         "ABI33_0_0EXAppLoaderProvider"
    ss.dependency         "ABI33_0_0EXAV"
    ss.dependency         "ABI33_0_0EXBackgroundFetch"
    ss.dependency         "ABI33_0_0EXBarCodeScanner"
    ss.dependency         "ABI33_0_0EXBlur"
    ss.dependency         "ABI33_0_0EXBrightness"
    ss.dependency         "ABI33_0_0EXCalendar"
    ss.dependency         "ABI33_0_0EXCamera"
    ss.dependency         "ABI33_0_0EXConstants"
    ss.dependency         "ABI33_0_0EXContacts"
    ss.dependency         "ABI33_0_0EXCrypto"
    ss.dependency         "ABI33_0_0EXDocumentPicker"
    ss.dependency         "ABI33_0_0EXFacebook"
    ss.dependency         "ABI33_0_0EXFaceDetector"
    ss.dependency         "ABI33_0_0EXFileSystem"
    ss.dependency         "ABI33_0_0EXFont"
    ss.dependency         "ABI33_0_0EXGL"
    ss.dependency         "EXGL-CPP"
    ss.dependency         "ABI33_0_0EXGoogleSignIn"
    ss.dependency         "ABI33_0_0EXHaptics"
    ss.dependency         "ABI33_0_0EXImageManipulator"
    ss.dependency         "ABI33_0_0EXImagePicker"
    ss.dependency         "ABI33_0_0EXKeepAwake"
    ss.dependency         "ABI33_0_0EXLinearGradient"
    ss.dependency         "ABI33_0_0EXLocalAuthentication"
    ss.dependency         "ABI33_0_0EXLocalization"
    ss.dependency         "ABI33_0_0EXLocation"
    ss.dependency         "ABI33_0_0EXMailComposer"
    ss.dependency         "ABI33_0_0EXMediaLibrary"
    ss.dependency         "ABI33_0_0EXPermissions"
    ss.dependency         "ABI33_0_0EXPrint"
    ss.dependency         "ABI33_0_0EXRandom"
    ss.dependency         "ABI33_0_0EXSecureStore"
    ss.dependency         "ABI33_0_0EXSensors"
    ss.dependency         "ABI33_0_0EXSharing"
    ss.dependency         "ABI33_0_0EXSMS"
    ss.dependency         "ABI33_0_0EXSpeech"
    ss.dependency         "ABI33_0_0EXSQLite"
    ss.dependency         "ABI33_0_0EXTaskManager"
    ss.dependency         "ABI33_0_0EXVideoThumbnails"
    ss.dependency         "ABI33_0_0EXWebBrowser"
    ss.dependency         "Amplitude-iOS"
    ss.dependency         "Analytics"
    ss.dependency         "AppAuth"
    ss.dependency         "FBAudienceNetwork"
    ss.dependency         "FBSDKCoreKit"
    ss.dependency         "FBSDKLoginKit"
    ss.dependency         "GoogleSignIn"
    ss.dependency         "GoogleMaps"
    ss.dependency         "Google-Maps-iOS-Utils"
    ss.dependency         "lottie-ios"
    ss.dependency         "JKBigInteger2"
    ss.dependency         "Branch"
    ss.dependency         "Google-Mobile-Ads-SDK"
    ss.source_files     = "Expo/Core/**/*.{h,m}"
  end

  s.subspec "ExpoOptional" do |ss|
    ss.dependency         "ReactABI33_0_0/Expo"
    ss.source_files     = "Expo/Optional/**/*.{h,m}"
  end

  s.subspec "CxxBridge" do |ss|
    ss.dependency             "Folly", folly_version
    ss.dependency             "ReactABI33_0_0/Core"
    ss.dependency             "ReactABI33_0_0/cxxReactABI33_0_0"
    ss.dependency             "ReactABI33_0_0/ABI33_0_0jsiexecutor"
    ss.compiler_flags       = folly_compiler_flags
    ss.private_header_files = "React/Cxx*/*.h"
    ss.source_files         = "React/Cxx*/*.{h,m,mm}"
  end

  s.subspec "DevSupport" do |ss|
    ss.dependency             "ReactABI33_0_0/Core"
    ss.dependency             "ReactABI33_0_0/RCTWebSocket"
    ss.source_files         = "React/DevSupport/*",
                              "React/Inspector/*"
  end

  s.subspec "RCTFabric" do |ss|
    ss.dependency             "Folly", folly_version
    ss.dependency             "ReactABI33_0_0/Core"
    ss.dependency             "ReactABI33_0_0/ABI33_0_0fabric"
    ss.compiler_flags       = folly_compiler_flags
    ss.source_files         = "React/Fabric/**/*.{c,h,m,mm,S,cpp}"
    ss.exclude_files        = "**/tests/*"
    ss.header_dir           = "ReactABI33_0_0"
    ss.framework            = "JavaScriptCore"
    ss.pod_target_xcconfig  = { "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/ReactCommon\"" }
  end

  s.subspec "tvOS" do |ss|
    ss.dependency             "ReactABI33_0_0/Core"
    ss.source_files         = "React/**/RCTTV*.{h,m}"
  end

  s.subspec "ABI33_0_0jsinspector" do |ss|
    ss.source_files         = "ReactCommon/ABI33_0_0jsinspector/*.{cpp,h}"
    ss.private_header_files = "ReactCommon/ABI33_0_0jsinspector/*.h"
    ss.pod_target_xcconfig  = { "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/ReactCommon\"" }
  end

  s.subspec "ABI33_0_0jsiexecutor" do |ss|
    ss.dependency             "ReactABI33_0_0/cxxReactABI33_0_0"
    ss.dependency             "ReactABI33_0_0/ABI33_0_0jsi"
    ss.dependency             "Folly", folly_version
    ss.dependency             "DoubleConversion"
    ss.dependency             "glog"
    ss.compiler_flags       = folly_compiler_flags
    ss.source_files         = "ReactCommon/ABI33_0_0jsiexecutor/jsireact/*.{cpp,h}"
    ss.private_header_files = "ReactCommon/ABI33_0_0jsiexecutor/jsireact/*.h"
    ss.header_dir           = "jsireact"
    ss.pod_target_xcconfig  = { "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/ReactCommon\", \"$(PODS_TARGET_SRCROOT)/ReactCommon/ABI33_0_0jsiexecutor\"" }
  end

  s.subspec "ABI33_0_0jsi" do |ss|
    ss.dependency             "Folly", folly_version
    ss.dependency             "DoubleConversion"
    ss.dependency             "glog"
    ss.compiler_flags       = folly_compiler_flags
    ss.source_files         = "ReactCommon/ABI33_0_0jsi/*.{cpp,h}"
    ss.private_header_files = "ReactCommon/ABI33_0_0jsi/*.h"
    ss.framework            = "JavaScriptCore"
    ss.pod_target_xcconfig  = { "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/ReactCommon\"" }
  end

  s.subspec "PrivateDatabase" do |ss|
    ss.source_files         = "ReactCommon/privatedata/*.{cpp,h}"
    ss.private_header_files = "ReactCommon/privatedata/*.h"
    ss.pod_target_xcconfig  = { "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/ReactCommon\"" }
  end

  s.subspec "cxxReactABI33_0_0" do |ss|
    ss.dependency             "ReactABI33_0_0/ABI33_0_0jsinspector"
    ss.dependency             "boost-for-react-native", "1.63.0"
    ss.dependency             "Folly", folly_version
    ss.dependency             "DoubleConversion"
    ss.dependency             "glog"
    ss.compiler_flags       = folly_compiler_flags
    ss.source_files         = "ReactCommon/cxxReactABI33_0_0/*.{cpp,h}"
    ss.exclude_files        = "ReactCommon/cxxReactABI33_0_0/SampleCxxModule.*"
    ss.private_header_files = "ReactCommon/cxxReactABI33_0_0/*.h"
    ss.pod_target_xcconfig  = { "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/ReactCommon\" \"$(PODS_ROOT)/boost-for-react-native\" \"$(PODS_ROOT)/DoubleConversion\" \"$(PODS_ROOT)/Folly\"" }
  end

  s.subspec "ABI33_0_0fabric" do |ss|
    ss.subspec "activityindicator" do |sss|
      sss.dependency             "Folly", folly_version
      sss.compiler_flags       = folly_compiler_flags
      sss.source_files         = "ReactCommon/ABI33_0_0fabric/activityindicator/**/*.{cpp,h}"
      sss.exclude_files        = "**/tests/*"
      sss.header_dir           = "ABI33_0_0fabric/activityindicator"
      sss.pod_target_xcconfig  = { "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/ReactCommon\" \"$(PODS_ROOT)/Folly\"" }
    end

    ss.subspec "attributedstring" do |sss|
      sss.dependency             "Folly", folly_version
      sss.compiler_flags       = folly_compiler_flags
      sss.source_files         = "ReactCommon/ABI33_0_0fabric/attributedstring/**/*.{cpp,h}"
      sss.exclude_files        = "**/tests/*"
      sss.header_dir           = "ABI33_0_0fabric/attributedstring"
      sss.pod_target_xcconfig  = { "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/ReactCommon\" \"$(PODS_ROOT)/Folly\"" }
    end

    ss.subspec "core" do |sss|
      sss.dependency             "Folly", folly_version
      sss.compiler_flags       = folly_compiler_flags
      sss.source_files         = "ReactCommon/ABI33_0_0fabric/core/**/*.{cpp,h}"
      sss.exclude_files        = "**/tests/*"
      sss.header_dir           = "ABI33_0_0fabric/core"
      sss.pod_target_xcconfig  = { "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/ReactCommon\" \"$(PODS_ROOT)/Folly\"" }
    end

    ss.subspec "debug" do |sss|
      sss.dependency             "Folly", folly_version
      sss.compiler_flags       = folly_compiler_flags
      sss.source_files         = "ReactCommon/ABI33_0_0fabric/debug/**/*.{cpp,h}"
      sss.exclude_files        = "**/tests/*"
      sss.header_dir           = "ABI33_0_0fabric/debug"
      sss.pod_target_xcconfig  = { "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/ReactCommon\" \"$(PODS_ROOT)/Folly\"" }
    end

    ss.subspec "graphics" do |sss|
      sss.dependency             "Folly", folly_version
      sss.compiler_flags       = folly_compiler_flags
      sss.source_files         = "ReactCommon/ABI33_0_0fabric/graphics/**/*.{cpp,h}"
      sss.exclude_files        = "**/tests/*"
      sss.header_dir           = "ABI33_0_0fabric/graphics"
      sss.pod_target_xcconfig  = { "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/ReactCommon\" \"$(PODS_ROOT)/Folly\"" }
    end

    ss.subspec "scrollview" do |sss|
      sss.dependency             "Folly", folly_version
      sss.compiler_flags       = folly_compiler_flags
      sss.source_files         = "ReactCommon/ABI33_0_0fabric/scrollview/**/*.{cpp,h}"
      sss.exclude_files        = "**/tests/*"
      sss.header_dir           = "ABI33_0_0fabric/scrollview"
      sss.pod_target_xcconfig  = { "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/ReactCommon\" \"$(PODS_ROOT)/Folly\"" }
    end

    ss.subspec "text" do |sss|
      sss.dependency             "Folly", folly_version
      sss.compiler_flags       = folly_compiler_flags
      sss.source_files         = "ReactCommon/ABI33_0_0fabric/text/**/*.{cpp,h}"
      sss.exclude_files        = "**/tests/*"
      sss.header_dir           = "ABI33_0_0fabric/text"
      sss.pod_target_xcconfig  = { "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/ReactCommon\" \"$(PODS_ROOT)/Folly\"" }
    end

    ss.subspec "textlayoutmanager" do |sss|
      sss.dependency             "Folly", folly_version
      sss.compiler_flags       = folly_compiler_flags
      sss.source_files         = "ReactCommon/ABI33_0_0fabric/textlayoutmanager/**/*.{cpp,h,mm}"
      sss.exclude_files        = "**/tests/*"
      sss.header_dir           = "ABI33_0_0fabric/textlayoutmanager"
      sss.pod_target_xcconfig  = { "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/ReactCommon\" \"$(PODS_ROOT)/Folly\"" }
    end

    ss.subspec "uimanager" do |sss|
      sss.dependency             "Folly", folly_version
      sss.compiler_flags       = folly_compiler_flags
      sss.source_files         = "ReactCommon/ABI33_0_0fabric/uimanager/**/*.{cpp,h}"
      sss.exclude_files        = "**/tests/*"
      sss.header_dir           = "ABI33_0_0fabric/uimanager"
      sss.pod_target_xcconfig  = { "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/ReactCommon\" \"$(PODS_ROOT)/Folly\"" }
    end

    ss.subspec "view" do |sss|
      sss.dependency             "Folly", folly_version
      sss.dependency             "ABI33_0_0yoga"
      sss.compiler_flags       = folly_compiler_flags
      sss.source_files         = "ReactCommon/ABI33_0_0fabric/view/**/*.{cpp,h}"
      sss.exclude_files        = "**/tests/*"
      sss.header_dir           = "ABI33_0_0fabric/view"
      sss.pod_target_xcconfig  = { "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/ReactCommon\" \"$(PODS_ROOT)/Folly\"" }
    end
  end

  # Fabric sample target for sample app purpose.
  s.subspec "RCTFabricSample" do |ss|
    ss.dependency             "Folly", folly_version
    ss.compiler_flags       = folly_compiler_flags
    ss.source_files         = "ReactCommon/ABI33_0_0fabric/sample/**/*.{cpp,h}"
    ss.exclude_files        = "**/tests/*"
    ss.header_dir           = "ABI33_0_0fabric/sample"
    ss.pod_target_xcconfig  = { "HEADER_SEARCH_PATHS" => "\"$(PODS_TARGET_SRCROOT)/ReactCommon\" \"$(PODS_ROOT)/Folly\"" }
  end

  s.subspec "ART" do |ss|
    ss.dependency             "ReactABI33_0_0/Core"
    ss.source_files         = "Libraries/ART/**/*.{h,m}"
  end

  s.subspec "RCTActionSheet" do |ss|
    ss.dependency             "ReactABI33_0_0/Core"
    ss.source_files         = "Libraries/ActionSheetIOS/*.{h,m}"
  end

  s.subspec "RCTAnimation" do |ss|
    ss.dependency             "ReactABI33_0_0/Core"
    ss.source_files         = "Libraries/NativeAnimation/{Drivers/*,Nodes/*,*}.{h,m}"
    ss.header_dir           = "RCTAnimation"
  end

  s.subspec "RCTBlob" do |ss|
    ss.dependency             "ReactABI33_0_0/Core"
    ss.source_files         = "Libraries/Blob/*.{h,m,mm}"
    ss.preserve_paths       = "Libraries/Blob/*.js"
  end

  s.subspec "RCTCameraRoll" do |ss|
    ss.dependency             "ReactABI33_0_0/Core"
    ss.dependency             'React/RCTImage'
    ss.source_files         = "Libraries/CameraRoll/*.{h,m}"
  end

  s.subspec "RCTGeolocation" do |ss|
    ss.dependency             "ReactABI33_0_0/Core"
    ss.source_files         = "Libraries/Geolocation/*.{h,m}"
  end

  s.subspec "RCTImage" do |ss|
    ss.dependency             "ReactABI33_0_0/Core"
    ss.dependency             "ReactABI33_0_0/RCTNetwork"
    ss.source_files         = "Libraries/Image/*.{h,m}"
  end

  s.subspec "RCTNetwork" do |ss|
    ss.dependency             "ReactABI33_0_0/Core"
    ss.source_files         = "Libraries/Network/*.{h,m,mm}"
  end

  s.subspec "RCTPushNotification" do |ss|
    ss.dependency             "ReactABI33_0_0/Core"
    ss.source_files         = "Libraries/PushNotificationIOS/*.{h,m}"
  end

  s.subspec "RCTSettings" do |ss|
    ss.dependency             "ReactABI33_0_0/Core"
    ss.source_files         = "Libraries/Settings/*.{h,m}"
  end

  s.subspec "RCTText" do |ss|
    ss.dependency             "ReactABI33_0_0/Core"
    ss.source_files         = "Libraries/Text/**/*.{h,m}"
  end

  s.subspec "RCTVibration" do |ss|
    ss.dependency             "ReactABI33_0_0/Core"
    ss.source_files         = "Libraries/Vibration/*.{h,m}"
  end

  s.subspec "RCTWebSocket" do |ss|
    ss.dependency             "ReactABI33_0_0/Core"
    ss.dependency             "ReactABI33_0_0/RCTBlob"
    ss.dependency             "ReactABI33_0_0/fishhook"
    ss.source_files         = "Libraries/WebSocket/*.{h,m}"
  end

  s.subspec "fishhook" do |ss|
    ss.header_dir           = "fishhook"
    ss.source_files         = "Libraries/fishhook/*.{h,c}"
  end

  s.subspec "RCTLinkingIOS" do |ss|
    ss.dependency             "ReactABI33_0_0/Core"
    ss.source_files         = "Libraries/LinkingIOS/*.{h,m}"
  end

  s.subspec "RCTTest" do |ss|
    ss.dependency             "ReactABI33_0_0/Core"
    ss.source_files         = "Libraries/RCTTest/**/*.{h,m}"
    ss.frameworks           = "XCTest"
  end

  s.subspec "_ignore_me_subspec_for_linting_" do |ss|
    ss.dependency             "ReactABI33_0_0/Core"
    ss.dependency             "ReactABI33_0_0/CxxBridge"
  end
end
