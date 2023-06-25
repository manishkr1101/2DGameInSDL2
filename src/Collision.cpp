#include "Collision.h"
#include "ECS/Components.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
    if (
        recA.x + recA.w >= recB.x &&
        recB.x + recB.w >= recA.x &&
        recA.y + recA.h >= recB.y &&
        recB.y + recB.h >= recA.y
    ) {
        return true;
    }
    return false;
}

bool Collision::AABB(const Entity& entityA, const Entity& entityB)
{
    return AABB(
        entityA.getComponent<ColliderComponent>().collider,
        entityB.getComponent<ColliderComponent>().collider
        );
}