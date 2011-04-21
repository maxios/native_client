# -*- python -*-
# Copyright 2011 (c) The Native Client Authors. All rights reserved.  Use
# of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
{
  'includes': [
    '../../../build/common.gypi',
  ],
  'target_defaults': {
    'variables':{
      'target_base': 'none',
    },
    'target_conditions': [
      ['target_base=="simple_service"', {
        'sources': [
          'nacl_simple_ltd_service.h',
          'nacl_simple_rservice.h',
          'nacl_simple_service.h',

          'nacl_simple_ltd_service.c',
          'nacl_simple_rservice.c',
          'nacl_simple_service.c',
        ],
        'xcode_settings': {
          'WARNING_CFLAGS': [
            '-Wno-missing-field-initializers'
          ]
        },
      },
    ]],
  },
  'conditions': [
    ['OS=="linux"', {
      'defines': [
        'XP_UNIX',
      ],
    }],
    ['OS=="mac"', {
      'defines': [
        'XP_MACOSX',
        'XP_UNIX',
        'TARGET_API_MAC_CARBON=1',
        'NO_X11',
        'USE_SYSTEM_CONSOLE',
      ],
    }],
    ['OS=="win"', {
      'defines': [
        'XP_WIN',
        'WIN32',
        '_WINDOWS'
      ],
      'targets': [
        {
          'target_name': 'simple_service64',
          'type': 'static_library',
          'variables': {
            'target_base': 'simple_service',
          },
          'configurations': {
            'Common_Base': {
              'msvs_target_platform': 'x64',
            },
          },
          'dependencies': [
            '<(DEPTH)/native_client/src/shared/platform/platform.gyp:platform64',
            '<(DEPTH)/native_client/src/trusted/desc/desc.gyp:nrd_xfer64',
            '<(DEPTH)/native_client/src/trusted/nacl_base/nacl_base.gyp:nacl_base64',
          ],
        },
      ],
    }],
  ],
  'targets': [
    {
      'target_name': 'simple_service',
      'type': 'static_library', # 'dynamic_library', ?!?
      'variables': {
        'target_base': 'simple_service',
      },
      'dependencies': [
        '<(DEPTH)/native_client/src/shared/platform/platform.gyp:platform',
        '<(DEPTH)/native_client/src/trusted/desc/desc.gyp:nrd_xfer',
        '<(DEPTH)/native_client/src/trusted/nacl_base/nacl_base.gyp:nacl_base',
      ],
    },
  ],
}
