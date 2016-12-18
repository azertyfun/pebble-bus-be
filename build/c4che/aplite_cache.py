AR = 'arm-none-eabi-ar'
ARFLAGS = 'rcs'
AS = 'arm-none-eabi-gcc'
BINDIR = '/usr/local/bin'
BLOCK_MESSAGE_KEYS = []
BUILD_DIR = 'aplite'
BUILD_TYPE = 'app'
BUNDLE_BIN_DIR = 'aplite'
BUNDLE_NAME = 'app.pbw'
CC = ['arm-none-eabi-gcc']
CCLNK_SRC_F = []
CCLNK_TGT_F = ['-o']
CC_NAME = 'gcc'
CC_SRC_F = []
CC_TGT_F = ['-c', '-o']
CC_VERSION = ('4', '7', '2')
CFLAGS = ['-std=c99', '-mcpu=cortex-m3', '-mthumb', '-ffunction-sections', '-fdata-sections', '-g', '-fPIE', '-Os', '-D_TIME_H_', '-Wall', '-Wextra', '-Werror', '-Wno-unused-parameter', '-Wno-error=unused-function', '-Wno-error=unused-variable']
CFLAGS_MACBUNDLE = ['-fPIC']
CFLAGS_cshlib = ['-fPIC']
CPPPATH_ST = '-I%s'
DEFINES = ['RELEASE', 'PBL_PLATFORM_APLITE', 'PBL_BW', 'PBL_RECT', 'PBL_COMPASS', 'PBL_DISPLAY_WIDTH=144', 'PBL_DISPLAY_HEIGHT=168', 'PBL_SDK_3']
DEFINES_ST = '-D%s'
DEST_BINFMT = 'elf'
DEST_CPU = 'arm'
DEST_OS = 'linux'
INCLUDES = ['aplite']
LD = 'arm-none-eabi-ld'
LIBDIR = '/usr/local/lib'
LIBPATH_ST = '-L%s'
LIB_DIR = 'node_modules'
LIB_JSON = [{u'gitHead': u'09c82b6f23ee1781434904669583f5ef194217ee', u'_location': u'/@smallstoneapps/scroll-text-layer', u'dist': {u'tarball': u'https://registry.npmjs.org/@smallstoneapps/scroll-text-layer/-/scroll-text-layer-1.3.0.tgz', u'shasum': u'bf3f1ad25ec3e9fe4681705f0d041d36c650154f'}, u'_spec': u'@smallstoneapps/scroll-text-layer', u'_npmOperationalInternal': {u'tmp': u'tmp/scroll-text-layer-1.3.0.tgz_1477627145248_0.3947755233384669', u'host': u'packages-18-east.internal.npmjs.com'}, u'keywords': [u'pebble-package'], u'devDependencies': {}, u'_from': u'@smallstoneapps/scroll-text-layer@latest', u'pebble': {u'sdkVersion': u'3', u'projectType': u'package', u'targetPlatforms': [u'aplite', u'basalt', u'chalk', u'diorite', u'emery']}, u'_inCache': True, u'_phantomChildren': {}, u'_args': [[{u'name': u'@smallstoneapps/scroll-text-layer', u'escapedName': u'@smallstoneapps%2fscroll-text-layer', u'rawSpec': u'', u'raw': u'@smallstoneapps/scroll-text-layer', u'scope': u'@smallstoneapps', u'type': u'tag', u'spec': u'latest'}, u'/home/nathan/src/bus-wallonia/app']], u'_nodeVersion': u'6.9.1', u'version': u'1.3.0', u'_resolved': u'https://registry.npmjs.org/@smallstoneapps/scroll-text-layer/-/scroll-text-layer-1.3.0.tgz', u'readme': u'ERROR: No README data found!', u'main': u'src/c/scroll-text-layer.c', u'homepage': u'https://github.com/smallstoneapps/scroll-text-layer#readme', u'files': [u'dist.zip'], u'_npmVersion': u'3.10.8', u'_requested': {u'name': u'@smallstoneapps/scroll-text-layer', u'escapedName': u'@smallstoneapps%2fscroll-text-layer', u'rawSpec': u'', u'raw': u'@smallstoneapps/scroll-text-layer', u'scope': u'@smallstoneapps', u'type': u'tag', u'spec': u'latest'}, u'description': u'Pebble library for easily adding a scrollable text layer to your app.', u'repository': {u'url': u'git+https://github.com/smallstoneapps/scroll-text-layer.git', u'type': u'git'}, u'optionalDependencies': {}, u'_requiredBy': [u'#USER', u'/'], u'maintainers': [{u'name': u'smallstoneapps', u'email': u'pebble@matthewtole.com'}], u'dependencies': {}, u'scripts': {}, 'path': 'node_modules/@smallstoneapps/scroll-text-layer/dist', u'_shrinkwrap': None, u'name': u'@smallstoneapps/scroll-text-layer', u'license': u'MIT', u'directories': {}, u'author': {u'name': u'Matthew Tole', u'email': u'pebble@matthewtole.com'}, u'bugs': {u'url': u'https://github.com/smallstoneapps/scroll-text-layer/issues'}, u'_npmUser': {u'name': u'smallstoneapps', u'email': u'pebble@matthewtole.com'}, u'_where': u'/home/nathan/src/bus-wallonia/app', u'_id': u'@smallstoneapps/scroll-text-layer@1.3.0', u'_shasum': u'bf3f1ad25ec3e9fe4681705f0d041d36c650154f'}, {u'gitHead': u'2f21b520cc6c0c9dc8b6e9af531d0ce9780f5ab9', u'_location': u'/@smallstoneapps/bitmap-loader', u'dist': {u'tarball': u'https://registry.npmjs.org/@smallstoneapps/bitmap-loader/-/bitmap-loader-1.3.0.tgz', u'shasum': u'ff509bede5e2bd45230c0c2b2edd574d1657e025'}, u'_spec': u'@smallstoneapps/bitmap-loader@^1.3.0', u'_npmOperationalInternal': {u'tmp': u'tmp/bitmap-loader-1.3.0.tgz_1477589074220_0.9935465389862657', u'host': u'packages-12-west.internal.npmjs.com'}, u'keywords': [u'pebble-package'], u'devDependencies': {}, u'_from': u'@smallstoneapps/bitmap-loader@>=1.3.0 <2.0.0', u'pebble': {u'sdkVersion': u'3', u'projectType': u'package', u'targetPlatforms': [u'aplite', u'basalt', u'chalk', u'diorite', u'emery']}, u'_inCache': True, u'_phantomChildren': {}, u'_args': [[{u'name': u'@smallstoneapps/bitmap-loader', u'escapedName': u'@smallstoneapps%2fbitmap-loader', u'rawSpec': u'^1.3.0', u'raw': u'@smallstoneapps/bitmap-loader@^1.3.0', u'scope': u'@smallstoneapps', u'type': u'range', u'spec': u'>=1.3.0 <2.0.0'}, u'/home/nathan/src/bus-wallonia/app']], u'_nodeVersion': u'6.9.1', u'version': u'1.3.0', u'_resolved': u'https://registry.npmjs.org/@smallstoneapps/bitmap-loader/-/bitmap-loader-1.3.0.tgz', u'readme': u'ERROR: No README data found!', u'main': u'src/c/bitmap-loader.c', u'homepage': u'https://github.com/smallstoneapps/bitmap-loader#readme', u'files': [u'dist.zip'], u'_npmVersion': u'3.10.8', u'_requested': {u'name': u'@smallstoneapps/bitmap-loader', u'escapedName': u'@smallstoneapps%2fbitmap-loader', u'rawSpec': u'^1.3.0', u'raw': u'@smallstoneapps/bitmap-loader@^1.3.0', u'scope': u'@smallstoneapps', u'type': u'range', u'spec': u'>=1.3.0 <2.0.0'}, u'description': u'Pebble library to do lazy loading of bitmaps from resources', u'repository': {u'url': u'git+https://github.com/smallstoneapps/bitmap-loader.git', u'type': u'git'}, u'optionalDependencies': {}, u'_requiredBy': [u'#USER', u'/'], u'maintainers': [{u'name': u'smallstoneapps', u'email': u'pebble@matthewtole.com'}], u'dependencies': {u'@smallstoneapps/linked-list': u'^1.4.0'}, u'scripts': {u'test': u'make'}, 'path': 'node_modules/@smallstoneapps/bitmap-loader/dist', u'_shrinkwrap': None, u'name': u'@smallstoneapps/bitmap-loader', u'license': u'MIT', u'directories': {u'test': u'tests'}, u'author': {u'name': u'Matthew Tole', u'email': u'pebble@matthewtole.com'}, u'bugs': {u'url': u'https://github.com/smallstoneapps/bitmap-loader/issues'}, u'_npmUser': {u'name': u'smallstoneapps', u'email': u'pebble@matthewtole.com'}, u'_where': u'/home/nathan/src/bus-wallonia/app', u'_id': u'@smallstoneapps/bitmap-loader@1.3.0', u'_shasum': u'ff509bede5e2bd45230c0c2b2edd574d1657e025'}, {u'gitHead': u'4b575a4fae9f575ec978e0ac66dc84fea3e2e965', u'_location': u'/@smallstoneapps/linked-list', u'dist': {u'tarball': u'https://registry.npmjs.org/@smallstoneapps/linked-list/-/linked-list-1.4.0.tgz', u'shasum': u'33ab0472202899b07e0ba318d49daf86770319d9'}, u'_spec': u'@smallstoneapps/linked-list@^1.4.0', u'_npmOperationalInternal': {u'tmp': u'tmp/linked-list-1.4.0.tgz_1476813130672_0.23447094927541912', u'host': u'packages-12-west.internal.npmjs.com'}, u'keywords': [u'pebble-package'], u'devDependencies': {}, u'_from': u'@smallstoneapps/linked-list@>=1.4.0 <2.0.0', u'pebble': {u'sdkVersion': u'3', u'projectType': u'package', u'targetPlatforms': [u'aplite', u'basalt', u'chalk', u'diorite', u'emery']}, u'_inCache': True, u'_phantomChildren': {}, u'_args': [[{u'name': u'@smallstoneapps/linked-list', u'escapedName': u'@smallstoneapps%2flinked-list', u'rawSpec': u'^1.4.0', u'raw': u'@smallstoneapps/linked-list@^1.4.0', u'scope': u'@smallstoneapps', u'type': u'range', u'spec': u'>=1.4.0 <2.0.0'}, u'/home/nathan/src/bus-wallonia/app/node_modules/@smallstoneapps/bitmap-loader']], u'_nodeVersion': u'6.8.1', u'version': u'1.4.0', u'_resolved': u'https://registry.npmjs.org/@smallstoneapps/linked-list/-/linked-list-1.4.0.tgz', u'readme': u'ERROR: No README data found!', u'main': u'src/c/linked-list.c', u'homepage': u'https://github.com/smallstoneapps/linked-list#readme', u'files': [u'dist.zip', u'src/', u'include/'], u'_npmVersion': u'3.10.8', u'_requested': {u'name': u'@smallstoneapps/linked-list', u'escapedName': u'@smallstoneapps%2flinked-list', u'rawSpec': u'^1.4.0', u'raw': u'@smallstoneapps/linked-list@^1.4.0', u'scope': u'@smallstoneapps', u'type': u'range', u'spec': u'>=1.4.0 <2.0.0'}, u'description': u'Pebble library for doing linked lists', u'repository': {u'url': u'git+https://github.com/smallstoneapps/linked-list.git', u'type': u'git'}, u'optionalDependencies': {}, u'_requiredBy': [u'/@smallstoneapps/bitmap-loader'], u'maintainers': [{u'name': u'smallstoneapps', u'email': u'pebble@matthewtole.com'}], u'dependencies': {}, u'scripts': {u'test': u'make'}, 'path': 'node_modules/@smallstoneapps/linked-list/dist', u'_shrinkwrap': None, u'name': u'@smallstoneapps/linked-list', u'license': u'MIT', u'directories': {u'test': u'tests'}, u'author': {u'name': u'Matthew Tole', u'email': u'pebble@matthewtole.com'}, u'bugs': {u'url': u'https://github.com/smallstoneapps/linked-list/issues'}, u'_npmUser': {u'name': u'smallstoneapps', u'email': u'pebble@matthewtole.com'}, u'_where': u'/home/nathan/src/bus-wallonia/app/node_modules/@smallstoneapps/bitmap-loader', u'_id': u'@smallstoneapps/linked-list@1.4.0', u'_shasum': u'33ab0472202899b07e0ba318d49daf86770319d9'}]
LIB_RESOURCES_JSON = {u'@smallstoneapps/scroll-text-layer': {}, u'@smallstoneapps/linked-list': {}, u'@smallstoneapps/bitmap-loader': {}}
LIB_ST = '-l%s'
LINKFLAGS = ['-mcpu=cortex-m3', '-mthumb', '-Wl,--gc-sections', '-Wl,--warn-common', '-fPIE', '-Os']
LINKFLAGS_MACBUNDLE = ['-bundle', '-undefined', 'dynamic_lookup']
LINKFLAGS_cshlib = ['-shared']
LINKFLAGS_cstlib = ['-Wl,-Bstatic']
LINK_CC = ['arm-none-eabi-gcc']
MESSAGE_KEYS = {u'ADD_STOP_LINE': 2, u'MESSAGE': 0, u'ADD_STOP': 1, u'ADD_STOP_SECOND_NEXT': 4, u'ADD_STOP_NEXT': 3}
MESSAGE_KEYS_DEFINITION = '/home/nathan/src/bus-wallonia/app/build/src/message_keys.auto.c'
MESSAGE_KEYS_HEADER = '/home/nathan/src/bus-wallonia/app/build/include/message_keys.auto.h'
MESSAGE_KEYS_JSON = '/home/nathan/src/bus-wallonia/app/build/js/message_keys.json'
NODE_PATH = '/home/nathan/.pebble-sdk/SDKs/current/node_modules'
PEBBLE_SDK_COMMON = '/home/nathan/.pebble-sdk/SDKs/current/sdk-core/pebble/common'
PEBBLE_SDK_PLATFORM = '/home/nathan/.pebble-sdk/SDKs/current/sdk-core/pebble/aplite'
PEBBLE_SDK_ROOT = '/home/nathan/.pebble-sdk/SDKs/current/sdk-core/pebble'
PLATFORM = {'TAGS': ['aplite', 'bw', 'rect', 'compass', '144w', '168h'], 'MAX_FONT_GLYPH_SIZE': 256, 'ADDITIONAL_TEXT_LINES_FOR_PEBBLE_H': [], 'MAX_APP_BINARY_SIZE': 65536, 'MAX_RESOURCES_SIZE': 524288, 'MAX_APP_MEMORY_SIZE': 24576, 'MAX_WORKER_MEMORY_SIZE': 10240, 'NAME': 'aplite', 'BUNDLE_BIN_DIR': 'aplite', 'BUILD_DIR': 'aplite', 'MAX_RESOURCES_SIZE_APPSTORE_2_X': 98304, 'MAX_RESOURCES_SIZE_APPSTORE': 131072, 'DEFINES': ['PBL_PLATFORM_APLITE', 'PBL_BW', 'PBL_RECT', 'PBL_COMPASS', 'PBL_DISPLAY_WIDTH=144', 'PBL_DISPLAY_HEIGHT=168']}
PLATFORM_NAME = 'aplite'
PREFIX = '/usr/local'
PROJECT_INFO = {'appKeys': {u'ADD_STOP_LINE': 2, u'MESSAGE': 0, u'ADD_STOP': 1, u'ADD_STOP_SECOND_NEXT': 4, u'ADD_STOP_NEXT': 3}, u'sdkVersion': u'3', u'projectType': u'native', u'uuid': u'1e9a4732-184e-4eb1-a17e-c4dd04e1f6a6', u'messageKeys': {u'ADD_STOP_LINE': 2, u'MESSAGE': 0, u'ADD_STOP': 1, u'ADD_STOP_SECOND_NEXT': 4, u'ADD_STOP_NEXT': 3}, 'companyName': u'Azertyfun', u'enableMultiJS': True, u'targetPlatforms': [u'aplite', u'basalt', u'chalk', u'diorite', u'emery'], u'capabilities': [u'location'], 'versionLabel': u'1.0', 'longName': u'Bus Belgium', u'displayName': u'Bus Belgium', 'shortName': u'Bus Belgium', u'watchapp': {u'watchface': False}, u'resources': {u'media': [{u'menuIcon': True, u'type': u'png', u'name': u'ICON', u'file': u'images/icon.png'}]}, 'name': u'bus-belgium'}
REQUESTED_PLATFORMS = [u'aplite', u'basalt', u'chalk', u'diorite', u'emery']
RESOURCES_JSON = [{u'menuIcon': True, u'type': u'png', u'name': u'ICON', u'file': u'images/icon.png'}]
RPATH_ST = '-Wl,-rpath,%s'
SANDBOX = False
SDK_VERSION_MAJOR = 5
SDK_VERSION_MINOR = 78
SHLIB_MARKER = None
SIZE = 'arm-none-eabi-size'
SONAME_ST = '-Wl,-h,%s'
STLIBPATH_ST = '-L%s'
STLIB_MARKER = None
STLIB_ST = '-l%s'
SUPPORTED_PLATFORMS = ['chalk', 'basalt', 'diorite', 'aplite', 'emery']
TARGET_PLATFORMS = ['emery', 'diorite', 'chalk', 'basalt', 'aplite']
TIMESTAMP = 1482096117
USE_GROUPS = True
VERBOSE = 0
WEBPACK = '/home/nathan/.pebble-sdk/SDKs/current/node_modules/.bin/webpack'
cprogram_PATTERN = '%s'
cshlib_PATTERN = 'lib%s.so'
cstlib_PATTERN = 'lib%s.a'
macbundle_PATTERN = '%s.bundle'
