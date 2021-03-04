# Message Standards

## Standard 0.6 - 14/06/20

Messages

### Led Segment Message Indicies
1. Led Segments Key
2. Number of Segments
#### For each Segment
3. Index Min
4. Index Max
5. Segment Type
6. PosA.x
7. PosA.y
8. PosA.z
#### For Line Segment
9. PosB.x
10. PosB.y
11. PosB.z
#### For Circle Segment
9. Normal.x
10. Normal.y
11. Normal.z
12. radius

### Led Pattern Message Indicies
1. Led Patterns Key
2. Number of Patterns
- For each Pattern
	3. Pattern Type
	4. Brightness
- For Solid Pattern
	5. Color.R
	6. Color.G
	7. Color.B
	8. Color.W
- For Rainbow Pattern
	5. Shape
	7. Frequency
	8. Speed
	9. Whiteness
- For Dual Color Pattern
	5. Shape
	4. Frequency
	5. Speed
	4. ColorA.R
	5. ColorA.G
	6. ColorA.B
	6. ColorA.W
	4. ColorB.R
	5. ColorB.G
	6. ColorB.B
	6. ColorB.W
## Standard 0.2 - 17/01/20

All messages are sent as JSON arrays of integers. Values marked as floats will be serialized and deserialized as integers by scaling by a certain amount (100).

### Message Keys

all message fields are non compulsory

|                       name |             Description | Param 1 |     Param 2 | Param 3 | Param 4 | Param 5 | Param 6 | Param 7 | Param 8 |
| -------------------------: | ----------------------: | ------: | ----------: | ------: | ------: | ------: | ------: | ------: | ------: |
|       MKEY_CONNECTION_IDLE |       Connection - Idle |         |             |         |         |         |         |         |         |
| MKEY_CONNECTION_CONNECTING | Connection - Connecting |         |             |         |         |         |         |         |         |
|  MKEY_CONNECTION_CONNECTED |  Connection - Connected |         |             |         |         |         |         |         |         |
|     MKEY_CONNECTION_FAILED |     Connection - Failed |         |             |         |         |         |         |         |         |
|              MKEY_LED_MODE |      Led Animation Mode | Segment |        Mode |         |         |         |         |         |         |
|          MKEY_LED_INDICIES |    Led Segment Indicies | Segment |         min |     max |         |         |         |         |         |
|        MKEY_LED_BRIGHTNESS |          Led Brightness | Segment |  brightness |         |         |         |         |         |         |
|         MKEY_LED_WHITENESS |   Led minimum whiteness | Segment |   whiteness |         |         |         |         |         |         |
|             MKEY_LED_SPEED |     led animation speed | Segment |       speed |         |         |         |         |         |         |
|            MKEY_LED_PERIOD | led pattern repetitions | Segment |      period |         |         |         |         |         |         |
|       MKEY_LED_COLOR_COUNT | led pattern color count | Segment | color count |         |         |         |         |         |         |
|         MKEY_LED_SET_COLOR |              led colors | Segment | color index |     red |   green |    blue |   white |         |         |


### Parameter Info

|                Name | Value Type |         Range |                                                                           Notes |
| ------------------: | ---------: | ------------: | ------------------------------------------------------------------------------: |
|             Segment |       uint |           0,4 |                                          Max extended by setting constant CONST |
|            Led Mode | uint(enum) | AnimationMode |                                                                  Animation Mode |
|       Led Index Min |       uint |         0,127 |                   Max extended by setting constant CONST (may increase latency) |
|       Led Index Max |       uint |         0,127 |                   Max extended by setting constant CONST (may increase latency) |
|      Led Brightness |      float |           0,1 |                               All colors are scaled by this value before render |
|       Led Whiteness |       byte |         0,255 |                       This value is overriden by colors with a higher whiteness |
|           Led Speed |      float |        -99,99 |                                                                 Animation speed |
|          Led Period |      float |        -99,99 |                                      Number of repetitions of the color pattern |
|     Led Color Count |       uint |           0,4 | Number of colors in the pattern, max can be increased by setting constant CONST |
| Led Set Color Index |       uint |           0,4 |                                                        Index of color to be set |
|             Led Red |       byte |         0,255 |                                                                             red |
|           Led Green |       byte |         0,255 |                                                                           green |
|            Led Blue |       byte |         0,255 |                                                                            blue |
|           Led White |       byte |         0,255 |                                                                           white |


### Enums

```js
```



## Standard 0.1 - 02/01/20


Json standard for communication

### Message Keys

all message fields are non compulsory

| index |     name |    type | Description |
| ----: | -------: | ------: | ----------: |
|     0 | metadata |  object |             |
| 1-128 |  message | various |     message |


### Message Parameters
|    Message Type | Index |         Value/Type |           Meaning |                           Description |
| --------------: | ----: | -----------------: | ----------------: | ------------------------------------: |
| CONNECTION DATA |       |                    |                   |                                       |
|                 |     1 |                100 | connection status |         update to a connection status |
|                 |     2 |                  0 |       wifi client |                                       |
|                 |     2 |                  2 |         wifi host |                                       |
|                 |     2 |                  3 |  bluetooth client |                                       |
|                 |     2 |                  4 |    bluetooth host |                                       |
|                 |     3 |                    |              IDLE |             not attempting connection |
|                 |     3 |                    |        CONNECTING |                 attempting connection |
|                 |     3 |                    |         CONNECTED |                 connection successful |
|                 |     3 |                    |            FAILED | connection unsuccessful, no reattempt |
|                 |       |                    |                   |                                       |
|                 |       |                    |                   |                                       |
|        LED DATA |       |                    |                   |                                       |
|                 |       |                    |                   |                                       |
|                 |     1 |                210 |              mode |                        animation mode |
|                 |     2 |                int |           segment |                 targetd segment index |
|                 |     3 |                  0 |          ANIM_OFF |                         do not update |
|                 |     3 |                  1 |        ANIM_BLACK |                          set to black |
|                 |     3 |                  2 |      ANIM_RAINBOW |                        set to rainbow |
|                 |     3 |                  3 |        ANIM_SOLID |                   set to solid colors |
|                 |     3 |                  4 |         ANIM_FADE |                    set to fade colors |
|                 |       |                    |                   |                                       |
|                 |     1 |                211 |          indicies |                                       |
|                 |     2 |               uint |               min |                         min led index |
|                 |     3 |               uint |               max |                         max led index |
|                 |       |                    |                   |                                       |
|                 |     1 |                212 |        brightness |                                       |
|                 |     2 |      float - (0,1) |        brightness |                      total brightness |
|                 |       |                    |                   |                                       |
|                 |     1 |                213 |         whiteness |                                       |
|                 |     2 |               byte |         whiteness |                     minimum whiteness |
|                 |       |                    |                   |                                       |
|                 |     1 |                214 |             speed |                                       |
|                 |     2 | float - (-999,999) |       speed value |      movement of led color per second |
|                 |       |                    |                   |                                       |
|                 |     1 |                215 |            period |                                       |
|                 |     2 |    float - (0,999) |      period value |         number of variations in strip |
|                 |       |                    |                   |                                       |
|                 |     1 |                220 |       color count |                                       |
|                 |     2 |        int - (1,4) |        colorCount |                 number of colors used |
|                 |       |                    |                   |                                       |
|                 |     1 |                221 |         set color |                                       |
|                 |     2 |        int - (0,3) |       color index |          index of the color to change |
|                 |     3 |               byte |               red |                    red value of color |
|                 |     4 |               byte |             green |                  green value of color |
|                 |     5 |               byte |              blue |                   blue value of color |
|                 |     6 |               byte |             white |          minimum white value of color |
|                 |       |                    |                   |                                       |
|                 |       |                    |                   |                                       |
|                 |       |                    |                   |                                       |