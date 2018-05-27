const np = require("./build/Release/binding.node");

export enum PlayerName {
    WLM,
    AIMP,
    CAD,
    FOOBAR,
    ITUNES,
    MEDIAMONKEY,
    SPOTIFY,
    WINAMP,
    WMP,
}

export interface NowPlayingConfig {
    getCover?: boolean;
    player: PlayerName;
    playerPath?: string;
}

export class NowPlaying {
    private instance: any;
    constructor(config: NowPlayingConfig) {
        if (config.getCover === undefined) {
            config.getCover = false;
        }
        this.instance = new np.NowPlaying(config);
    }

    /**
     * Closes the player.
     */
    public closePlayer(): void {
        this.instance.closePlayer();
    };

    /**
     * Current album.
     */
    public getAlbum(): string {
        return this.instance.getAlbum();
    };

    /**
     * Track artist.
     */
    public getArtist(): string {
        return this.instance.getArtist();
    };

    /**
     * Path to cover art.
     */
    public getCoverPath(): string {
        return this.instance.getCoverPath();
    };

    /**
     * Total length of track in seconds.
     */
    public getDuration(): number {
        return this.instance.getDuration();
    };

    /**
     * Path to the playing media file.
     */
    public getFilePath(): string {
        return this.instance.getFilePath();
    };

    /**
     * Track genre.
     */
    public getGenre(): string {
        return this.instance.getGenre();
    };

    /**
     * Track number.
     */
    public getNumber(): number {
        return this.instance.getNumber();
    };

    /**
     * Current position in track in seconds.
     */
    public getPosition(): number {
        return this.instance.getPosition();
    };

    /**
     * Percentage of track completed.
     */
    public getProgress(): number {
        return this.instance.getProgress();
    };

    /**
     * Rating of current track (0 to 5).
     */
    public getRating(): number {
        return this.instance.getRating();
    };

    /**
     * `false` if repeat/loop track is off, `true` if on.
     */
    public getRepeat(): boolean {
        return this.instance.getRepeat();
    };

    /**
     * `false` if shuffle/random tracks is off, `true` if on.
     */
    public getShuffle(): boolean {
        return this.instance.getShuffle();
    };

    /**
     * `0` for stopped, `1` for playing, and `2` for paused.
     */
    public getState(): number {
        return this.instance.getState();
    };

    /**
     * `false` for inactive (player closed) and `true` for active (player open).
     */
    public getStatus(): boolean {
        return this.instance.getStatus();
    };

    /**
     * Track title.
     */
    public getTitle(): string {
        return this.instance.getTitle();
    };

    /**
     * From 0 to 100.
     */
    public getVolume(): number {
        return this.instance.getVolume();
    };

    /**
     * Track year.
     */
    public getYear(): number {
        return this.instance.getYear();
    };

    /**
     * Change to next track.
     */
    public next(): void {
        this.instance.next();
    };

    /**
     * Opens the player. If already open, the player will be brought to the top.
     */
    public openPlayer(): void {
        this.instance.openPlayer();
    };

    /**
     * Pause current track.
     */
    public pause(): void {
        this.instance.pause();
    };

    /**
     * Play current track.
     */
    public play(): void {
        this.instance.play();
    };

    /**
     * Change to previous track.
     */
    public previous(): void {
        this.instance.previous();
    };

    /**
     * Change track position.
     * @param position in second
     */
    public setPosition(position: number): void {
        this.instance.setPosition(position);
    };

    /**
     * Change track rating.
     * @param rating  `0` (no rating) to `5` (maximum rating)
     */
    public setRating(rating: number): void {
        this.instance.setRating(rating);
    };

    /**
     * Change player repeat state.
     * @param isRepeat `true`: repeat on. `false`: repeat off.
     */
    public setRepeat(isRepeat: boolean): void {
        this.instance.setRepeat(isRepeat);
    };

    /**
     * Change player shuffle state.
     * @param isShuffle `true`: shuffle on. `false`: shuffle off.
     */
    public setShuffle(isShuffle: boolean): void {
        this.instance.setShuffle(isShuffle);
    };

    /**
     * Change player volume level.
     * @param level 0 to 100.
     */
    public setVolume(level: number): void {
        this.instance.setVolume(level);
    };

    /**
     * Stop current track.
     */
    public stop(): void {
        this.instance.stop();
    };

    /**
     * Update all information. Call this method before get any information.
     */
    public update(): void {
        this.instance.update();
    };
}
