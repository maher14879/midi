
## How to read a MIDI?

#### A MIDI **Header Chunk** has the following structure:

| Field        | Size      | Description                |
|--------------|-----------|-------------               |
| `chunk_type` | 32-bit    | Always ASCII `'MThd'`      |
| `length`     | 32-bit    | Always 6                   |
| `format`     | 16-bit    | MIDI format: 1, 2, or 3    |
| `ntrks`      | 16-bit    | Number of tracks           |
| `division`   | 16-bit    | Timing division            |

#### Division
If **bit 15 = 0**, stores number of ticks per quarter note (PPQN). <br> - If **bit 15 = 1**, uses SMPTE time code: <br> &nbsp;&nbsp;* Bits 14–8: negative two’s complement number of frames per second (-24, -25, -29, -30; -29 = 30 drop frame). <br> &nbsp;&nbsp;* Bits 7–0: resolution within a frame (ticks per frame). 

#### A MIDI **Track Chunk** has the following structure:

| Field        | Size      | Description            |
|--------------|-----------|-------------           |
| `chunk type` | 32-bit    | Always ASCII `'MThd'`  |
| `length`     | 32-bit    | The lenght of track    |
| `MTrk event` | VLQ       | One or more            |

#### A MIDI **MTrk event** has the following structure:

| Field        | Size      | Description                        |
|--------------|-----------|-------------                       |
| `delta-time` | VLQ       | Ticks before first event of track  |
| `event`      | 32-bit    |                                    |

#### A MIDI **event** has the following structure:

| Field        | Size      | Description            |
|--------------|-----------|-------------           |
| `MIDI event` | 32-bit    | Always ASCII `'MThd'`  |
| `sysex event`| 32-bit    | Always                 |
| `meta-event` | 32-bit    | Always 6               |
