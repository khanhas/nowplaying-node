import { NowPlaying, PlayerName } from "../index";

const np = new NowPlaying({
    player: PlayerName.AIMP,
    fetchCover: true,
});

setInterval(() => {
    np.update();
    console.log(np.getTitle());
    console.log(np.getArtist());
    console.log(np.getPosition());
    console.log(np.getCoverPath());
}, 1000);
