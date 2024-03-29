{
  "targets": [
    {
      "target_name": "GetFanInfo",
      "cflags!": [ "-fno-exceptions"],
      "cflags_cc!": [ "-fno-exceptions"],
      "sources": [ "NodeBinding.cc" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
      'libraries': ["<!@(node -p \"require('./path.js').getFanInfoLib\")"]
    }
  ]
}