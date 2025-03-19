#include "../include/cloak.h"
#include "bn_math.h"

Cloak::Cloak(int x, int y, const bn::sprite_item& item)
    : sprite(item.create_sprite(x, y)), hitbox{x, y, 16, 16}, last_direction(3), score(0), animation(bn::nullopt) {}

void Cloak::update(const bn::sprite_ptr& target, const bn::vector<Hitbox, 10>& obstacles) {
    bn::fixed dx = target.x() - sprite.x();
    bn::fixed dy = target.y() - sprite.y();

    bn::fixed distance = bn::sqrt(dx * dx + dy * dy);
    if (distance < 1) return;

    bn::fixed move_speed = 0.8;
    dx = (dx / distance) * move_speed;
    dy = (dy / distance) * move_speed;

    Hitbox new_position = {sprite.x() + dx, sprite.y() + dy, hitbox.width, hitbox.height};

    if (!new_position.collides_any(obstacles)) {
        sprite.set_x(new_position.x);
        sprite.set_y(new_position.y);
        hitbox.x = sprite.x();
        hitbox.y = sprite.y();

        int new_direction = (bn::abs(dx) > bn::abs(dy)) ? ((dx > 0) ? 1 : 0) 
                                                        : ((dy > 0) ? 3 : 2);

        if (new_direction != last_direction || !animation.has_value()) {
            int start_frame = (new_direction == 0) ? 8
                            : (new_direction == 1) ? 12
                            : (new_direction == 2) ? 4
                            : 0;

            animation = bn::create_sprite_animate_action_forever(
                sprite, 8, bn::sprite_items::cloak.tiles_item(),
                start_frame, start_frame + 1, start_frame + 2, start_frame + 3
            );

            last_direction = new_direction;
        }
        animation->update();
    } else {
        animation.reset();
        int idle_frame = (last_direction == 0) ? 8
                       : (last_direction == 1) ? 12
                       : (last_direction == 2) ? 4
                       : 0;
        sprite.set_tiles(bn::sprite_items::cloak.tiles_item(), idle_frame);
    }
}

Hitbox Cloak::get_hitbox() const {
    return hitbox;
}

void Cloak::increase_score() {
    score++;
}
