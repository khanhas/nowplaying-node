export declare enum PlayerName {
    WLM = 0,
    AIMP = 1,
    CAD = 2,
    FOOBAR = 3,
    ITUNES = 4,
    MEDIAMONKEY = 5,
    SPOTIFY = 6,
    WINAMP = 7,
    WMP = 8,
}
export interface NowPlayingConfig {
    getCover?: boolean;
    player: PlayerName;
    playerPath?: string;
}
export declare class NowPlaying {
    private instance;
    constructor(config: NowPlayingConfig);
    /**
     * Closes the player.
     */
    closePlayer(): void;
    /**
     * Current album.
     */
    getAlbum(): string;
    /**
     * Track artist.
     */
    getArtist(): string;
    /**
     * Path to cover art.
     */
    getCoverPath(): string;
    /**
     * Total length of track in seconds.
     */
    getDuration(): number;
    /**
     * Path to the playing media file.
     */
    getFilePath(): string;
    /**
     * Track genre.
     */
    getGenre(): string;
    /**
     * Track number.
     */
    getNumber(): number;
    /**
     * Current position in track in seconds.
     */
    getPosition(): number;
    /**
     * Percentage of track completed.
     */
    getProgress(): number;
    /**
     * Rating of current track (0 to 5).
     */
    getRating(): number;
    /**
     * `false` if repeat/loop track is off, `true` if on.
     */
    getRepeat(): boolean;
    /**
     * `false` if shuffle/random tracks is off, `true` if on.
     */
    getShuffle(): boolean;
    /**
     * `0` for stopped, `1` for playing, and `2` for paused.
     */
    getState(): number;
    /**
     * `false` for inactive (player closed) and `true` for active (player open).
     */
    getStatus(): boolean;
    /**
     * Track title.
     */
    getTitle(): string;
    /**
     * From 0 to 100.
     */
    getVolume(): number;
    /**
     * Track year.
     */
    getYear(): number;
    /**
     * Change to next track.
     */
    next(): void;
    /**
     * Opens the player. If already open, the player will be brought to the top.
     */
    openPlayer(): void;
    /**
     * Pause current track.
     */
    pause(): void;
    /**
     * Play current track.
     */
    play(): void;
    /**
     * Change to previous track.
     */
    previous(): void;
    /**
     * Change track position.
     * @param position in second
     */
    setPosition(position: number): void;
    /**
     * Change track rating.
     * @param rating  `0` (no rating) to `5` (maximum rating)
     */
    setRating(rating: number): void;
    /**
     * Change player repeat state.
     * @param isRepeat `true`: repeat on. `false`: repeat off.
     */
    setRepeat(isRepeat: boolean): void;
    /**
     * Change player shuffle state.
     * @param isShuffle `true`: shuffle on. `false`: shuffle off.
     */
    setShuffle(isShuffle: boolean): void;
    /**
     * Change player volume level.
     * @param level 0 to 100.
     */
    setVolume(level: number): void;
    /**
     * Stop current track.
     */
    stop(): void;
    /**
     * Update all information. Call this method before get any information.
     */
    update(): void;
}
