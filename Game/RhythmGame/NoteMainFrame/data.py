import pprint


class Data:
    def __init__(self, notes, *, lanes=4):  # lanes are defaulted to 4 lanes
        self.lane_numbers = lanes
        self.lanes = [[] for i in range(lanes)]
        # defaulted this way to make life easier.
        self.highest_pitch = 0
        self.lowest_pitch = 100000
        self.total_notes = 0
        self.difference = 0
        self.tones = []
        self.ticks_per_second = notes["ticksPerBeat"] * (notes["beatsPerMinute"] / 60)

        self.init_data(notes)
        self.parse_to_lanes()

    def init_data(self, notes):
        for pitches in notes["channels"]:
            for tones in pitches["patterns"]:
                if tones["notes"]:
                    for tone in tones["notes"]:
                        self.tones.append(tone)
                        if tone["pitches"][0] < self.lowest_pitch:
                            self.lowest_pitch = tone["pitches"][0]
                        if tone["pitches"][0] > self.highest_pitch:
                            self.highest_pitch = tone["pitches"][0]
                        self.total_notes += 1

        self.difference = self.highest_pitch - self.lowest_pitch

    def parse_to_lanes(self):
        # range between highest and lowest pitches
        lane_width = self.difference / self.lane_numbers
        for note in self.tones:
            # the current note pitch
            target = note["pitches"][0]
            for lane_number in range(self.lane_numbers):
                if target <= (lane_width * (lane_number + 1)) + self.lowest_pitch:
                    self.lanes[lane_number - 1].append(note)
                    break

    def cleanse_lanes(self):
        final_content = ""
        for lane in self.lanes:
            prev_end = -1
            line = ""
            for note in lane:
                crnt_start = note['points'][0]['tick']
                crnt_end = note['points'][1]['tick']
                if (prev_end > crnt_start):
                    prev_end += crnt_start
                    line += f"{prev_end}:{prev_end + crnt_end - crnt_start},"
                    # line += f"{prev_end + crnt_end - crnt_start}:{prev_end},"
                else:
                    prev_end = crnt_end
                    line += f"{crnt_start}:{crnt_end}," 
                    # line += f"{crnt_end}:{crnt_start},"
            final_content += line[:-1] + "\n"
        return final_content


    def get_lanes(self):
        return self.lanes

    def write_to_file(self, song_name):
        file_path = fr".\Game\RhythmGame\NoteMainFrame\ParsedSongs\{song_name}.txt"
        with open(file_path, "w") as f:
            final_content = f"{self.lane_numbers}\n{self.ticks_per_second}\n"
            final_content += self.cleanse_lanes()

            f.write(final_content)