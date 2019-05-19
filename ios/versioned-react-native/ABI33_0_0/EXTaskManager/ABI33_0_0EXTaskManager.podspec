require 'json'

package = JSON.parse(File.read(File.join(__dir__, 'package.json')))

Pod::Spec.new do |s|
  s.name           = 'ABI33_0_0EXTaskManager'
  s.version        = package['version']
  s.summary        = package['description']
  s.description    = package['description']
  s.license        = package['license']
  s.author         = package['author']
  s.homepage       = package['homepage']
  s.platform       = :ios, '10.0'
  s.source         = { git: 'https://github.com/expo/expo-task-manager.git' }
  s.source_files   = 'ABI33_0_0EXTaskManager/**/*.{h,m}'
  s.preserve_paths = 'ABI33_0_0EXTaskManager/**/*.{h,m}'
  s.requires_arc   = true

  s.dependency 'ABI33_0_0UMCore'
  s.dependency 'ABI33_0_0UMConstantsInterface'
  s.dependency 'ABI33_0_0UMTaskManagerInterface'
  s.dependency 'ABI33_0_0EXAppLoaderProvider'
end
