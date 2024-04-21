from NotesData import Note
from data import Data
import pprint

song1 = Data(Note)

lanes = song1.get_lanes()

for lane in lanes:
    print("NEW LANE: ")
    pprint.pprint(lane)

song1.write_to_file("Lost_Woods")
