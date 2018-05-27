#include <node.h>
#include <node_buffer.h>
#include <node_object_wrap.h>
#include "Player.h"

using v8::Function;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::Persistent;
using v8::Value;

// Do not hover mouse over v8::FunctionTemplate to read description, Visual
// Studio will freeze.
#define FUNCTIONTEMPLATE v8::FunctionTemplate
#define FBVALUE v8::FunctionCallbackInfo<v8::Value>

class NowPlaying : public node::ObjectWrap {
public:
  static void Init(Local<Object> exports);
  static Persistent<Function> constructor;
  static void New(const FBVALUE &args);
  static void Update(const FBVALUE &args);
  static void GetState(const FBVALUE &args);
  static void GetArtist(const FBVALUE &args);
  static void GetAlbum(const FBVALUE &args);
  static void GetTitle(const FBVALUE &args);
  static void GetGenre(const FBVALUE &args);
  static void GetCoverPath(const FBVALUE &args);
  static void GetFilePath(const FBVALUE &args);
  static void GetDuration(const FBVALUE &args);
  static void GetPosition(const FBVALUE &args);
  static void GetProgress(const FBVALUE &args);
  static void GetRating(const FBVALUE &args);
  static void GetVolume(const FBVALUE &args);
  static void GetNumber(const FBVALUE &args);
  static void GetYear(const FBVALUE &args);
  static void GetShuffle(const FBVALUE &args);
  static void GetRepeat(const FBVALUE &args);
  static void GetStatus(const FBVALUE &args);
  static void Pause(const FBVALUE &args);
  static void Play(const FBVALUE &args);
  static void Stop(const FBVALUE &args);
  static void Next(const FBVALUE &args);
  static void Previous(const FBVALUE &args);
  static void SetPosition(const FBVALUE &args);
  static void SetRating(const FBVALUE &args);
  static void SetVolume(const FBVALUE &args);
  static void SetShuffle(const FBVALUE &args);
  static void SetRepeat(const FBVALUE &args);
  static void OpenPlayer(const FBVALUE &args);
  static void ClosePlayer(const FBVALUE &args);

  Player *_player;

  UINT trackCount;
  bool trackChanged;
  std::wstring playerPath;

private:
  explicit NowPlaying(Player *player, std::wstring playerPath);
  ~NowPlaying();
};