#include "NowPlaying.h"
#include <node.h>

void InitAll(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
  NowPlaying::Init(exports);
};

NODE_MODULE(NODE_GYP_MODULE_NAME, InitAll)