from data import Data
import json

file_path = fr".\Game\RythmGame\NoteMainFrame\load_song.json"
with open(file_path, 'r', encoding="utf-8") as f:
    loaded_song = json.loads(f.read())

song = Data(loaded_song)

lanes = song.get_lanes()

song.write_to_file("Lost_Woods")