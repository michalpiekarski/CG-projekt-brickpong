#include "BodyAABB.h"
#include "BodyCircle.h"
#include "Collision.h"

BodyAABB::BodyAABB() : Body() {
    _collider = AABB();
}

BodyAABB::BodyAABB(glm::vec2 position, glm::vec2 velocity, float mass, PhysicsMaterial physicsMaterial, AABB collider) : Body::Body(position, velocity, mass, physicsMaterial) {
    _collider = collider;
}

BodyAABB::~BodyAABB() {
}

AABB BodyAABB::getCollider() {
    return _collider;
}

void BodyAABB::setCollider(AABB collider) {
    _collider = collider;
}

bool BodyAABB::checkCollision(BodyAABB& other, Collision* collision) {
    if (_collider.checkCollision(other.getCollider())) {
        collision = new Collision(this, &other);

        glm::vec2 n = other.getPosition() - _position;

        float a_extent_x = (_collider.getMax().x - _collider.getWidth()) / 2.0f;
        float b_extent_x = (other.getCollider().getMax().x - other.getCollider().getWidth()) / 2.0f;

        float x_overlap = a_extent_x + b_extent_x - glm::abs(n.x);

        if (x_overlap > 0) {
            float a_extent_y = (_collider.getMax().y - _collider.getHeight()) / 2.0f;
            float b_extent_y = (other.getCollider().getMax().y - other.getCollider().getHeight()) / 2.0f;

            float y_overlap = a_extent_y + b_extent_y - glm::abs(n.y);

            if (y_overlap > 0) {
                if (x_overlap > y_overlap) {
                    if (n.x < 0) {
                        collision->setNormal(glm::vec2(-1, 0));
                    }
                    else {
                        collision->setNormal(glm::vec2(0, 0));
                    }
                    collision->setPenetration(x_overlap);
                }
                else {
                    if (n.y < 0) {
                        collision->setNormal(glm::vec2(0, -1));
                    }
                    else {
                        collision->setNormal(glm::vec2(0, 1));
                    }
                    collision->setPenetration(y_overlap);
                }
                return true;
            }
        }
    }
    return false;
}

bool BodyAABB::checkCollisionCrosstype(BodyCircle& other, Collision* collision) {
    if (_collider.checkCollisionCrosstype(other.getCollider())) {
        // TODO: Genereate AABBCircle collision object
    }
}
