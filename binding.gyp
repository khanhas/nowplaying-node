{
  "targets": [
    {
      "target_name": "binding",
      "sources": [
        "<!@(node list-sources.js)",
        "src/taglib/TagLibUnity_ape.cpp",
        "src/taglib/TagLibUnity_asf.cpp",
        "src/taglib/TagLibUnity_flac.cpp",
        "src/taglib/TagLibUnity_mp4.cpp",
        "src/taglib/TagLibUnity_mpeg_id3v2.cpp",
        "src/taglib/TagLibUnity_mpeg.cpp",
        "src/taglib/TagLibUnity_ogg.cpp",
        "src/taglib/TagLibUnity_toolkit.cpp",
        "src/taglib/TagLibUnity.cpp",
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "<(module_root_dir)",
        "<(module_root_dir)/src/",
        "<(module_root_dir)/src/SDKs/",
        "<(module_root_dir)/src/taglib",
        "<(module_root_dir)/src/taglib/ape",
        "<(module_root_dir)/src/taglib/asf",
        "<(module_root_dir)/src/taglib/flac",
        "<(module_root_dir)/src/taglib/mp4",
        "<(module_root_dir)/src/taglib/mpc",
        "<(module_root_dir)/src/taglib/mpeg",
        "<(module_root_dir)/src/taglib/mpeg/id3v1",
        "<(module_root_dir)/src/taglib/mpeg/id3v2",
        "<(module_root_dir)/src/taglib/mpeg/id3v2/frames",
        "<(module_root_dir)/src/taglib/ogg",
        "<(module_root_dir)/src/taglib/ogg/flac",
        "<(module_root_dir)/src/taglib/ogg/vorbis",
        "<(module_root_dir)/src/taglib/toolkit",
        "<(module_root_dir)/src/taglib/wavpack",
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "defines": [
        "NAPI_CPP_EXCEPTIONS",
        "UNICODE",
      ]
    }
  ]
}