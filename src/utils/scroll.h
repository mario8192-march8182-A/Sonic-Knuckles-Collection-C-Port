#ifndef SKC_SCROLLUTIL_H
#define SKC_SCROLLUTIL_H

#define TILE_SIZE_PIXELS 8
#define BLOCK_SIZE_TILES 2
#define SCREEN_SIZE_BLOCKS 8
#define PLANE_WIDTH_TILES 64
#define PLANE_HEIGHT_TILES 32

#define BLOCK_SIZE_PIXELS (BLOCK_SIZE_TILES * TILE_SIZE_PIXELS)
#define SCREEN_SIZE_PIXELS (SCREEN_SIZE_BLOCKS * BLOCK_SIZE_PIXELS)
#define PLANE_WIDTH_PIXELS (PLANE_WIDTH_TILES * TILE_SIZE_PIXELS)
#define PLANE_HEIGHT_PIXELS (PLANE_HEIGHT_TILES * TILE_SIZE_PIXELS)
#define PLANE_WIDTH_BLOCKS (PLANE_WIDTH_TILES / BLOCK_SIZE_TILES)

inline short to_tiles(short posi) {
  return posi / TILE_SIZE_PIXELS;
}
inline short to_blocks(short posi) {
  return posi / BLOCK_SIZE_PIXELS;
}
inline short to_screens(short posi) {
  return posi / SCREEN_SIZE_PIXELS;
}
inline short to_blocks_in_screen(short posi) {
  return to_blocks(posi) % SCREEN_SIZE_BLOCKS;
}
inline short to_htiles_in_plane(short xposi) {
  return to_tiles(xposi) % PLANE_WIDTH_TILES;
}
inline short to_vtiles_in_plane(short yposi) {
  return to_tiles(yposi) % PLANE_HEIGHT_TILES;
}
inline short to_hblocks_in_plane(short xposi) {
  return to_blocks(yposi) % PLANE_WIDTH_BLOCKS;
}
