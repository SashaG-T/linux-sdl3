#include "usersprite.h"
#include "texture.h"
#include "global.h"

/*

This is supposed to load 8x8 sprites from rawSprite array.
It's meant to be a way for me to load images without needing to do
pixel art in a separate program.

Example:

struct Sprite* sprite = UserSprite_Create(SQUARE);
Object_SetParent(sprite, parent);

*/


//We'll replace COLOUR with another table that loads from a 256 value colour table.
#define COLOUR(colour_id) ColourTable[(colour_id)]

typedef char RawSprite_t[64];

unsigned int ColourTable[256] = {
  [' '] = 0x00000000,
  ['.'] = 0x00000000,
  ['R'] = 0xff0000ff,
  ['W'] = 0xffffffff,
  ['w'] = 0xff7c7c7c,
  ['0'] = 0xffaaffaa,
  ['1'] = 0xff7cff7c,
  ['2'] = 0xff55ff55,
  ['3'] = 0xff007c00,
  ['B'] = 0xffff0000,
  ['c'] = 0xffdddddd
};

RawSprite_t rawSprite[USERSPRITE_COUNT] = {

[CURSOR1]=
"....www."
"...wWWw."
"...wWWww"
"...wWWWw"
"....wWWW"
"....wWWW"
".....wWW"
".wwwwwWW", 

[CURSOR2]=
"........"
"........"
"........"
"www....."
"wWWwww.."
"WWWWWWw."
"WWwWWwWw"
"WWwWWwWw",

[CURSOR3]=
"wwWWwwWW"
"wWWWWwWW"
".wwWWWWW"
"...wwWWW"
".....wWw"
"......wW"
"......ww"
".......w",

[CURSOR4]=
"WWWWWWWw"
"WWWWWWww"
"WWwwwww."
"wwWWWWww"
"WWWwwWWw"
"WwwWWWww"
"WWWWwww."
"wwww....",

[CURSOR5]=
"........"
"........"
"....wwww"
"...wWWWw"
"..wWWWWW"
"..wWWwWW"
"..wWWwWW"
"..wwwwWW", 

[CURSOR6]=
"..wWWwWW"
"..wWWwWW"
"...wWWWW"
"....wWWW"
".....wWw"
"......wW"
"......ww"
".......w",


  [SQUARE1]=
  "        "
  " www  ww"
  " w      "
  " w      "
  "        "
  "        "
  " w      "
  " w      ",

  [SQUARE2]=
  "        "
  "ww  www "
  "      w "
  "      w "
  "        "
  "        "
  "      w "
  "      w ",

  [SQUARE3]=
  " w      "
  " w      "
  "        "
  "        "
  " w      "
  " w      "
  " www  ww"
  "        ",

  [SQUARE4]=
  "      w "
  "      w "
  "        "
  "        "
  "      w "
  "      w "
  "ww  www "
  "        ",


  [TREE]=
  "        "
  "   22   "
  "  2222  "
  "   22   "
  " 222222 "
  "   22   "
  "   22   "
  "        ",

  [MOUNTA]=
  "11111111"
  "21111110"
  "22111100"
  "222  000"
  "222  000"
  "22333300"
  "23333330"
  "33333333",

  [GOBLIN]=
  "        "
  "   222  "
  "  2R2R2 "
  "   222  "
  " 2222222"
  "   BBB  "
  "   B B  "
  "   2 2  ",

  [CARD_BLANK]=
  " wwwwwww"
  "wWWWWWWW"
  "wWcccccc"
  "wWcccccc"
  "wWcccccc"
  "wWcccccc"
  "wWcccccc"
  "wWcccccc",

  [CARD_BLANK_2]=
  "wwwwwww "
  "WWWWWWWw"
  "ccccccWw"
  "ccccccWw"
  "ccccccWw"
  "ccccccWw"
  "ccccccWw"
  "ccccccWw",

  [CARD_BLANK_3]=
  "wWcccccc"
  "wWcccccc"
  "wWcccccc"
  "wWcccccc"
  "wWcccccc"
  "wWcccccc"
  "wWWWWWWW"
  " wwwwwww",

  [CARD_BLANK_4]=
  "ccccccWw"
  "ccccccWw"
  "ccccccWw"
  "ccccccWw"
  "ccccccWw"
  "ccccccWw"
  "WWWWWWWw"
  "wwwwwww ",

  [CARD_HOUSE]=
  " wwwwwww"
  "wWWWWWWW"
  "wWcccccc"
  "wWcccccR"
  "wWccccRR"
  "wWcccRRR"
  "wWccRRRR"
  "wWcRRRRR",

  [CARD_HOUSE_2]=
  "wwwwwww "
  "WWWWWWWw"
  "ccccccWw"
  "RcccccWw"
  "RRccccWw"
  "RRRcccWw"
  "RRRRccWw"
  "RRRRRcWw",

  [CARD_HOUSE_3]=
  "wWRRRRRR"
  "wWccRRRR"
  "wWccRRRR"
  "wWccRRRR"
  "wWccRRRR"
  "wWcccccc"
  "wWWWWWWW"
  " wwwwwww",

  [CARD_HOUSE_4]=
  "RRRRRRWw"
  "RRRRccWw"
  "RRRRccWw"
  "RRRRccWw"
  "RRRRccWw"
  "ccccccWw"
  "WWWWWWWw"
  "wwwwwww ",
  
  [CARD_FIELD]=
  " wwwwwww"
  "wWWWWWWW"
  "wW000000"
  "wW000000"
  "wW000000"
  "wW000000"
  "wW000000"
  "wW000000",

  [CARD_FIELD_2]=
  "wwwwwww "
  "WWWWWWWw"
  "000000Ww"
  "000000Ww"
  "000000Ww"
  "000000Ww"
  "000000Ww"
  "000000Ww",

  [CARD_FIELD_3]=
  "wW000000"
  "wW000000"
  "wW000000"
  "wW000000"
  "wW000000"
  "wW000000"
  "wWWWWWWW"
  " wwwwwww",

  [CARD_FIELD_4]=
  "000000Ww"
  "000000Ww"
  "000000Ww"
  "000000Ww"
  "000000Ww"
  "000000Ww"
  "WWWWWWWw"
  "wwwwwww ",

/*
....RRR. ........
...R..R. ........
...R..R. ........
....R..R RRR.....
....R... R..RRR..
.....R.. ......R.
.....R.. ..R..R.R
......R. ..R..R.R

.RRR..R. .......R
R...RR.. .......R
RRR..... .....RR.
...RR... .......R
.....RR. RRR.R..R
....R..R .......R
....R... .....RR.
.....RRR RRRRR...

........ ........
........ ........
........ ........
..RRRRRR RRR.....
.R...... R..RRR..
R..RR... ......R.
R....R.. ..R..R.R
RRRR..R. ..R..R.R

R..R..R. .......R
.R..RR.. .......R
..R..... .....RR.
...RR... .......R
.....RR. RRR.R..R
....R..R .......R
....R... .....RR.
.....RRR RRRRR...
*/

};

unsigned int spritePerWidth = 1;

struct Texture* texture = 0;

void UserSprite_DebugDraw() {
  unsigned int width = spritePerWidth * 8 * 8;
  SDL_FRect dest = {0, 0, (float)width, (float)width};
  SDL_RenderTexture(renderer, texture->texture, NULL, &dest);
}

void LoadPixelData(unsigned int x, unsigned int y, unsigned int* p) {
  unsigned int id = x + y * spritePerWidth;
  if(id >= USERSPRITE_COUNT) {
    return;
  }

  unsigned int spriteSize = sizeof(RawSprite_t);
  unsigned int spriteWidth = 8;

  unsigned int rw = spritePerWidth * spriteSize;
  unsigned int rs = spritePerWidth * spriteWidth;

  for(int oy = 0; oy < spriteWidth; oy++) {
    for(int ox = 0; ox < spriteWidth; ox++) {
      p[(x * spriteWidth + ox) + (oy * rs + y * rw)] = COLOUR(rawSprite[id][ox + oy * spriteWidth]);
    }
  }  
}

void load(struct Texture* texture) {
  for(spritePerWidth = 1; (spritePerWidth)*(spritePerWidth) < USERSPRITE_COUNT; spritePerWidth *= 2);

  unsigned int pixelCount = spritePerWidth * spritePerWidth * sizeof(RawSprite_t);
  unsigned int* pixelData = malloc(pixelCount * sizeof(unsigned int));
  
  int c = 0;
  for(int y = 0; y < spritePerWidth; y++) {
    for(int x = 0; x < spritePerWidth; x++) {
      LoadPixelData(x, y, pixelData);
    }
  }

  unsigned int spriteSize = sizeof(RawSprite_t);
  unsigned int spriteWidth = 8;
  unsigned int width = spritePerWidth * spriteWidth;

  SDL_Surface* surface = SDL_CreateSurfaceFrom(width, width, SDL_PIXELFORMAT_RGBA32, pixelData, width * sizeof(unsigned int));
  PrintError(!surface);
  SDL_Texture* t = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_SetTextureScaleMode(t, SDL_SCALEMODE_NEAREST);
  SDL_DestroySurface(surface);
  free(pixelData);

  texture->texture = t;
}

void destroy(struct Texture* texture) {
  SDL_DestroyTexture(texture->texture);
  texture->texture = 0;
}

/*** Public ***/

struct Sprite* UserSprite_Create(int id) {
  if(!texture) {
    texture = Texture_Generate(0, load, destroy);
  }
  //use id to set Sprite texture SRC and DEST.
  unsigned int x, y;
  id = id % (spritePerWidth * spritePerWidth);
  x = (id % spritePerWidth) * 8;
  y = (id / spritePerWidth) * 8;
  struct Sprite* sprite = Sprite_Create(texture, x, y, 8, 8, 32, 32);
  return sprite;
}
