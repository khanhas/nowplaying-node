#include "NowPlaying.h"

#include "Player.h"
#include "PlayerAIMP.h"
#include "PlayerCAD.h"
#include "PlayerITunes.h"
#include "PlayerSpotify.h"
#include "PlayerWLM.h"
#include "PlayerWMP.h"
#include "PlayerWinamp.h"

HINSTANCE g_Instance = nullptr;

using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::Persistent;
using v8::Value;

enum PlayerName {
  WLM,
  AIMP,
  CAD,
  FOOBAR,
  ITUNES,
  MEDIAMONKEY,
  SPOTIFY,
  WINAMP,
  WMP
};

int GetInt(Isolate *isolate, Local<Object> &obj, LPCSTR key, int defVal) {
  Local<Value> val = obj->Get(v8::String::NewFromUtf8(isolate, key));
  return val->IsUndefined() ? defVal : (int)val->ToInteger()->Value();
}

bool GetBoolean(Isolate *isolate, Local<Object> &obj, LPCSTR key, bool defVal) {
  Local<Value> val = obj->Get(v8::String::NewFromUtf8(isolate, key));
  return val->IsUndefined() ? defVal : val->ToBoolean()->Value();
}

Persistent<Function> NowPlaying::constructor;

NowPlaying::NowPlaying(Player *player, std::wstring playerPath)
    : _player(player), trackCount(0), trackChanged(false),
      playerPath(playerPath) {
  //_player = player;
}

NowPlaying::~NowPlaying() { printf("Deleted"); }

void NowPlaying::New(const FBVALUE &args) {
  Isolate *isolate = args.GetIsolate();
  if (args.IsConstructCall()) {
    // Invoked as constructor: `new NowPlaying(...)`
    if (args[0]->IsUndefined()) {
      args.GetReturnValue().Set(v8::Undefined(isolate));
      return;
    }

    Player *player = nullptr;

    Local<Object> setting = args[0].As<Object>();

    int playerName = GetInt(isolate, setting, "player", 0);
    if (playerName == PlayerName::AIMP) {
      player = PlayerAIMP::Create();
    } else if (playerName == PlayerName::CAD) {
      player = PlayerCAD::Create();
    } else if (playerName == PlayerName::FOOBAR) {
      HWND fooWindow = FindWindow(L"foo_rainmeter_class", nullptr);
      if (fooWindow) {
        const WCHAR *error = L"Your foobar2000 plugin is out of date.\n\nDo "
                             L"you want to update the plugin now?";
        if (MessageBox(nullptr, error, L"NowPlayingJS",
                       MB_YESNO | MB_ICONINFORMATION | MB_TOPMOST) == IDYES) {
          ShellExecute(nullptr, L"open",
                       L"http://github.com/poiru/foo-cad#readme", nullptr,
                       nullptr, SW_SHOWNORMAL);
        }
      }

      player = PlayerCAD::Create();
    } else if (playerName == PlayerName::ITUNES) {
      player = PlayerITunes::Create();
    } else if (playerName == PlayerName::MEDIAMONKEY) {
      player = PlayerWinamp::Create(WA_MEDIAMONKEY);
    } else if (playerName == PlayerName::SPOTIFY) {
      player = PlayerSpotify::Create();
    } else if (playerName == PlayerName::WINAMP) {
      player = PlayerWinamp::Create(WA_WINAMP);
    } else if (playerName == PlayerName::WMP) {
      player = PlayerWMP::Create();
    } else {
      player = PlayerWLM::Create();

      if (playerName != PlayerName::WLM) {
        printf("Invalid player option. Fallback to WLM.");
      }
    }

    bool getCover = GetBoolean(isolate, setting, "getCover", false);
    player->m_getCover = getCover;

    Local<Value> playerPathVal =
        setting->Get(v8::String::NewFromUtf8(isolate, "playerPath"));
    std::wstring playerPath;
    if (!playerPathVal->IsUndefined()) {
      uint16_t buffer[MAX_PATH];
      playerPathVal->ToString()->Write(buffer, 0, -1, 4);
      playerPath = (LPCWSTR)buffer;
    }

    NowPlaying *np = new NowPlaying(player, playerPath);

    np->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  }
}

void NowPlaying::Update(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  np->_player->UpdateMeasure();
}

void NowPlaying::GetState(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  args.GetReturnValue().Set(
      v8::Integer::New(args.GetIsolate(), np->_player->GetState()));
}

void NowPlaying::GetArtist(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  uint16_t *coverted = (uint16_t *)np->_player->GetArtist();
  args.GetReturnValue().Set(
      v8::String::NewFromTwoByte(args.GetIsolate(), coverted));
}

void NowPlaying::GetAlbum(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  uint16_t *coverted = (uint16_t *)np->_player->GetAlbum();
  args.GetReturnValue().Set(
      v8::String::NewFromTwoByte(args.GetIsolate(), coverted));
}

void NowPlaying::GetTitle(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  uint16_t *coverted = (uint16_t *)np->_player->GetTitle();
  args.GetReturnValue().Set(
      v8::String::NewFromTwoByte(args.GetIsolate(), coverted));
}

void NowPlaying::GetGenre(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  uint16_t *coverted = (uint16_t *)np->_player->GetGenre();
  args.GetReturnValue().Set(
      v8::String::NewFromTwoByte(args.GetIsolate(), coverted));
}

void NowPlaying::GetCoverPath(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  uint16_t *coverted = (uint16_t *)np->_player->GetCoverPath();
  args.GetReturnValue().Set(
      v8::String::NewFromTwoByte(args.GetIsolate(), coverted));
}

void NowPlaying::GetFilePath(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  uint16_t *coverted = (uint16_t *)np->_player->GetFilePath();
  args.GetReturnValue().Set(
      v8::String::NewFromTwoByte(args.GetIsolate(), coverted));
}

void NowPlaying::GetProgress(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  double value = (double)np->_player->GetPosition() * 100.0 /
                 (double)np->_player->GetDuration();
  args.GetReturnValue().Set(v8::Number::New(args.GetIsolate(), value));
}

void NowPlaying::GetDuration(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  args.GetReturnValue().Set(
      v8::Integer::New(args.GetIsolate(), np->_player->GetDuration()));
}

void NowPlaying::GetPosition(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  args.GetReturnValue().Set(
      v8::Integer::New(args.GetIsolate(), np->_player->GetPosition()));
}

void NowPlaying::GetRating(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  args.GetReturnValue().Set(
      v8::Integer::New(args.GetIsolate(), np->_player->GetRating()));
}

void NowPlaying::GetVolume(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  args.GetReturnValue().Set(
      v8::Integer::New(args.GetIsolate(), np->_player->GetVolume()));
}

void NowPlaying::GetNumber(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  args.GetReturnValue().Set(
      v8::Integer::New(args.GetIsolate(), np->_player->GetNumber()));
}

void NowPlaying::GetYear(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  args.GetReturnValue().Set(
      v8::Integer::New(args.GetIsolate(), np->_player->GetYear()));
}

void NowPlaying::GetShuffle(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  args.GetReturnValue().Set(
      v8::Boolean::New(args.GetIsolate(), np->_player->GetShuffle()));
}

void NowPlaying::GetRepeat(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  args.GetReturnValue().Set(
      v8::Boolean::New(args.GetIsolate(), np->_player->GetRepeat()));
}

void NowPlaying::GetStatus(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  args.GetReturnValue().Set(
      v8::Boolean::New(args.GetIsolate(), np->_player->IsInitialized()));
}

void NowPlaying::Pause(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  np->_player->Pause();
}
void NowPlaying::Play(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  np->_player->Play();
}
void NowPlaying::Stop(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  np->_player->Stop();
}
void NowPlaying::Next(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  np->_player->Next();
}
void NowPlaying::Previous(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  np->_player->Previous();
}
void NowPlaying::SetPosition(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  if (args[0]->IsNumber()) {
    int val = (int)args[0]->ToInteger()->Value();
    np->_player->SetPosition(val);
  }
}
void NowPlaying::SetRating(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  if (args[0]->IsNumber()) {
    int val = (int)args[0]->ToInteger()->Value();
    np->_player->SetRating(val);
  }
}
void NowPlaying::SetVolume(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  if (args[0]->IsNumber()) {
    int val = (int)args[0]->ToInteger()->Value();
    np->_player->SetVolume(val);
  }
}
void NowPlaying::SetShuffle(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  if (args[0]->IsBoolean()) {
    bool val = args[0]->ToBoolean()->Value();
    np->_player->SetShuffle(val);
  }
}
void NowPlaying::SetRepeat(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  if (args[0]->IsBoolean()) {
    bool val = args[0]->ToBoolean()->Value();
    np->_player->SetRepeat(val);
  }
}
void NowPlaying::OpenPlayer(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  np->_player->OpenPlayer(np->playerPath);
}
void NowPlaying::ClosePlayer(const FBVALUE &args) {
  NowPlaying *np = ObjectWrap::Unwrap<NowPlaying>(args.This());
  np->_player->ClosePlayer();
}

void NowPlaying::Init(Local<Object> exports) {
  Isolate *isolate = exports->GetIsolate();
  printf("Initing");
  // Prepare constructor template
  Local<FUNCTIONTEMPLATE> tpl = FUNCTIONTEMPLATE::New(isolate, New);
  tpl->SetClassName(v8::String::NewFromUtf8(isolate, "NowPlaying"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl, "update", Update);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getState", GetState);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getArtist", GetArtist);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getAlbum", GetAlbum);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getTitle", GetTitle);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getGenre", GetGenre);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getCoverPath", GetCoverPath);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getFilePath", GetFilePath);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getDuration", GetDuration);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getPosition", GetPosition);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getProgress", GetProgress);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getRating", GetRating);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getVolume", GetVolume);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getNumber", GetNumber);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getYear", GetYear);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getShuffle", GetShuffle);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getRepeat", GetRepeat);
  NODE_SET_PROTOTYPE_METHOD(tpl, "getStatus", GetStatus);
  NODE_SET_PROTOTYPE_METHOD(tpl, "pause", Pause);
  NODE_SET_PROTOTYPE_METHOD(tpl, "play", Play);
  NODE_SET_PROTOTYPE_METHOD(tpl, "stop", Stop);
  NODE_SET_PROTOTYPE_METHOD(tpl, "next", Next);
  NODE_SET_PROTOTYPE_METHOD(tpl, "previous", Previous);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setPosition", SetPosition);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRating", SetRating);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setVolume", SetVolume);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setShuffle", SetShuffle);
  NODE_SET_PROTOTYPE_METHOD(tpl, "setRepeat", SetRepeat);
  NODE_SET_PROTOTYPE_METHOD(tpl, "openPlayer", OpenPlayer);
  NODE_SET_PROTOTYPE_METHOD(tpl, "closePlayer", ClosePlayer);

  constructor.Reset(isolate, tpl->GetFunction());

  exports->Set(v8::String::NewFromUtf8(isolate, "NowPlaying"),
               tpl->GetFunction());
}