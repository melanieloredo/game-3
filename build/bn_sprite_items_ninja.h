#ifndef BN_SPRITE_ITEMS_NINJA_H
#define BN_SPRITE_ITEMS_NINJA_H

#include "bn_sprite_item.h"

//{{BLOCK(ninja_bn_gfx)

//======================================================================
//
//	ninja_bn_gfx, 32x512@4, 
//	+ palette 16 entries, not compressed
//	+ 256 tiles not compressed
//	Total size: 32 + 8192 = 8224
//
//	Time-stamp: 2025-02-26, 03:13:03
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_NINJA_BN_GFX_H
#define GRIT_NINJA_BN_GFX_H

#define ninja_bn_gfxTilesLen 8192
extern const bn::tile ninja_bn_gfxTiles[256];

#define ninja_bn_gfxPalLen 32
extern const bn::color ninja_bn_gfxPal[16];

#endif // GRIT_NINJA_BN_GFX_H

//}}BLOCK(ninja_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item ninja(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(ninja_bn_gfxTiles, 256), bpp_mode::BPP_4, compression_type::NONE, 16), 
            sprite_palette_item(span<const color>(ninja_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

