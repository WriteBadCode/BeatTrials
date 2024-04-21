import pprint


class Data:
    def __init__(self, notes, *, lanes=4):
        self.lane_numbers = lanes
        self.lanes = [[] for i in range(lanes)]
        # defaulted this way to make life easier.
        self.highest_pitch = 0
        self.lowest_pitch = 100000
        self.total_notes = 0
        self.difference = 0
        self.tones = []
        self.ticks_per_second = notes["beatsPerMinute"] / notes["ticksPerBeat"] * notes["ticksPerBeat"]

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

    def get_lanes(self):
        return self.lanes

    def write_to_file(self, song_name):
        file_path = fr".\Game\RythmGame\NoteMainFrame\ParsedSongs\{song_name}.txt"
        with open(file_path, "w") as f:
            final_content = f"tick_per_second: {self.ticks_per_second}\n"
            for lane in self.lanes:
                line = ""
                for note in lane:
                    line += f"{note['pitches'][0]}-{note['points'][0]['tick']}:{note['points'][1]['tick']},"
                final_content += line + "\n"

            f.write(final_content)