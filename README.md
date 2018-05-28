# nowplaying-node

![build](https://ci.appveyor.com/api/projects/status/drbuy98474cs9rcf?svg=true)

Currently investigating foobar and WMP player freezing cause.

## Install
You need windows-build-tools to build native module:  
```
npm --add-python-to-path install --global windows-build-tools
```

then run:  
```
npm install nowplaying-node
```

## Electron

If you're making electron app, you might need to install `electron-rebuild`:  
```
npm install --save-dev electron-rebuild
```
then run:
```
.\node_modules\.bin\electron-rebuild
```
to rebuild usable module for your current Electron's Node version

# How to use:
Import NowPlaying:  
```js
import { NowPlaying, PlayerName } from "nowplaying-node";
```

Create player interface:
```js
const myAIMP = new NowPlaying({
    fetchCover: true,
    player: PlayerName.AIMP,
});
```

Get information:
```js
myAIMP.update();
console.log("%s - %s", myAIMP.getArtist(), myAIMP.getTitle())
```

Track info only is updated when `.update()` is called, so put them in an interval to always have most recent info:
```js
setInterval(() => {
    myAIMP.update();
    console.log("%s - %s", myAIMP.getArtist(), myAIMP.getTitle())
    console.log(myAIMP.getPosition());
    console.log(myAIMP.getCoverPath());
}, 1000);
```


 List of supported players:

- AIMP:  
```js
player = PlayerName.AIMP
```  
Fully supported. 
- foobar2000:  
```js
player = PlayerName.CAD
```  
Fully supported. The [foo_cad plugin (download)](http://poiru.github.com/foo-cad/) needs to be installed.  
- iTunes:  
```js
player = PlayerName.ITUNES
```  
Fully supported. Tested with iTunes 10.2.  
- J. River Media Center and Media Jukebox:  
```js
player = PlayerName.CAD
```  
Fully supported through the CAD interface with Media Center 19 and later. More information [here](http://yabb.jriver.com/interact/index.php?topic=84508.0).  
- MediaMonkey:  
```js
player = PlayerName.MEDIAMONKEY
```  
Fully supported. Tested with MediaMonkey 3.2.5.  
- MusicBee:  
```js
player = PlayerName.CAD
```  
Fully supported. MusicBee 1.2 (or higher) is required.  
- Winamp:  
```js
player = PlayerName.WINAMP
```  
Fully supported.  
- WMP:  
```js
player = PlayerName.WMP
```  
Fully supported, except for the `.getRepeat()` / `.getShuffle()`.

- Spotify:  
```js
player = PlayerName.SPOTIFY
```  
Partially supported. Only the `.getArtist()`, `.getTitle()` information and `.play()`, `.pause()`, `.stop()`, `.next()`, and `.previous()` controls are available.
- Last.fm Client, TTPlayer, OpenPandora, Zune:  
```js
player = PlayerName.WLM
```  
Partially supported. Even in the best case, only the types `.getTitle()`, `.getArtist()`, `.getAlbum()` information and `.play()`, `.pause()`, `.stop()`, `.next()`, and `.previous()` are supported.
