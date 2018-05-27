"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const np = require("./build/Release/binding.node");
var PlayerName;
(function (PlayerName) {
    PlayerName[PlayerName["WLM"] = 0] = "WLM";
    PlayerName[PlayerName["AIMP"] = 1] = "AIMP";
    PlayerName[PlayerName["CAD"] = 2] = "CAD";
    PlayerName[PlayerName["FOOBAR"] = 3] = "FOOBAR";
    PlayerName[PlayerName["ITUNES"] = 4] = "ITUNES";
    PlayerName[PlayerName["MEDIAMONKEY"] = 5] = "MEDIAMONKEY";
    PlayerName[PlayerName["SPOTIFY"] = 6] = "SPOTIFY";
    PlayerName[PlayerName["WINAMP"] = 7] = "WINAMP";
    PlayerName[PlayerName["WMP"] = 8] = "WMP";
})(PlayerName = exports.PlayerName || (exports.PlayerName = {}));
class NowPlaying {
    constructor(config) {
        if (config.getCover === undefined) {
            config.getCover = false;
        }
        this.instance = new np.NowPlaying(config);
    }
    /**
     * Closes the player.
     */
    closePlayer() {
        this.instance.closePlayer();
    }
    ;
    /**
     * Current album.
     */
    getAlbum() {
        return this.instance.getAlbum();
    }
    ;
    /**
     * Track artist.
     */
    getArtist() {
        return this.instance.getArtist();
    }
    ;
    /**
     * Path to cover art.
     */
    getCoverPath() {
        return this.instance.getCoverPath();
    }
    ;
    /**
     * Total length of track in seconds.
     */
    getDuration() {
        return this.instance.getDuration();
    }
    ;
    /**
     * Path to the playing media file.
     */
    getFilePath() {
        return this.instance.getFilePath();
    }
    ;
    /**
     * Track genre.
     */
    getGenre() {
        return this.instance.getGenre();
    }
    ;
    /**
     * Track number.
     */
    getNumber() {
        return this.instance.getNumber();
    }
    ;
    /**
     * Current position in track in seconds.
     */
    getPosition() {
        return this.instance.getPosition();
    }
    ;
    /**
     * Percentage of track completed.
     */
    getProgress() {
        return this.instance.getProgress();
    }
    ;
    /**
     * Rating of current track (0 to 5).
     */
    getRating() {
        return this.instance.getRating();
    }
    ;
    /**
     * `false` if repeat/loop track is off, `true` if on.
     */
    getRepeat() {
        return this.instance.getRepeat();
    }
    ;
    /**
     * `false` if shuffle/random tracks is off, `true` if on.
     */
    getShuffle() {
        return this.instance.getShuffle();
    }
    ;
    /**
     * `0` for stopped, `1` for playing, and `2` for paused.
     */
    getState() {
        return this.instance.getState();
    }
    ;
    /**
     * `false` for inactive (player closed) and `true` for active (player open).
     */
    getStatus() {
        return this.instance.getStatus();
    }
    ;
    /**
     * Track title.
     */
    getTitle() {
        return this.instance.getTitle();
    }
    ;
    /**
     * From 0 to 100.
     */
    getVolume() {
        return this.instance.getVolume();
    }
    ;
    /**
     * Track year.
     */
    getYear() {
        return this.instance.getYear();
    }
    ;
    /**
     * Change to next track.
     */
    next() {
        this.instance.next();
    }
    ;
    /**
     * Opens the player. If already open, the player will be brought to the top.
     */
    openPlayer() {
        this.instance.openPlayer();
    }
    ;
    /**
     * Pause current track.
     */
    pause() {
        this.instance.pause();
    }
    ;
    /**
     * Play current track.
     */
    play() {
        this.instance.play();
    }
    ;
    /**
     * Change to previous track.
     */
    previous() {
        this.instance.previous();
    }
    ;
    /**
     * Change track position.
     * @param position in second
     */
    setPosition(position) {
        this.instance.setPosition(position);
    }
    ;
    /**
     * Change track rating.
     * @param rating  `0` (no rating) to `5` (maximum rating)
     */
    setRating(rating) {
        this.instance.setRating(rating);
    }
    ;
    /**
     * Change player repeat state.
     * @param isRepeat `true`: repeat on. `false`: repeat off.
     */
    setRepeat(isRepeat) {
        this.instance.setRepeat(isRepeat);
    }
    ;
    /**
     * Change player shuffle state.
     * @param isShuffle `true`: shuffle on. `false`: shuffle off.
     */
    setShuffle(isShuffle) {
        this.instance.setShuffle(isShuffle);
    }
    ;
    /**
     * Change player volume level.
     * @param level 0 to 100.
     */
    setVolume(level) {
        this.instance.setVolume(level);
    }
    ;
    /**
     * Stop current track.
     */
    stop() {
        this.instance.stop();
    }
    ;
    /**
     * Update all information. Call this method before get any information.
     */
    update() {
        this.instance.update();
    }
    ;
}
exports.NowPlaying = NowPlaying;
//# sourceMappingURL=index.js.map