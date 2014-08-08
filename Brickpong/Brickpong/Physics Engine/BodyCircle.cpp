#include "BodyCircle.h"
#include "BodyAABB.h"
#include "Collision.h"

BodyCircle::BodyCircle() : Body() {
    _colliderType = 2;
    _collider = Circle();
}

BodyCircle::BodyCircle(glm::vec2 position, glm::vec2 velocity, PhysicsMaterial& physicsMaterial, float mass, bool isStatic, float gravityScale, Circle collider) : Body(position, velocity, physicsMaterial, mass, isStatic, gravityScale) {
    _colliderType = 2;
    _collider = collider;
}

BodyCircle::~BodyCircle() {
}

void BodyCircle::setPosition(glm::vec2 position) {
    _collider.setPosition(position);
    _position = _collider.getPosition();
}

glm::vec2 BodyCircle::getPosition() {
    return _collider.getPosition();
}

Circle& BodyCircle::getCollider() {
    return _collider;
}

void BodyCircle::setCollider(Circle collider) {
    _collider = collider;
}

bool BodyCircle::checkCollision(BodyCircle& other, Collision* collision) {
    if (_collider.checkCollision(other.getCollider())) {
        collision = new Collision(this, &other);

        glm::vec2 n = other.getPosition() - _position;

        float r = _collider.getRadius() + other.getCollider().getRadius();
        float d = glm::length(n);

        if (d > r) {
            return false;
        }

        if (d != 0) {
            collision->setPenetration(r - d);
            collision->setNormal(n / d);
        }
        else {
            collision->setPenetration(getCollider().getRadius());
            collision->setNormal(glm::vec2(1.0f, 0.0f));
        }
        return true;
    }
    return false;
}

bool BodyCircle::checkCollisionCrosstype(BodyAABB& other, Collision* collision) {
    if (_collider.checkCollisionCrosstype(other.getCollider())) {
        collision = new Collision(this, &other);

        glm::vec2 n = other.getPosition() - _position;
        glm::vec2 closest = n;
        float x_extent = (other.getCollider().getMax().x - other.getCollider().getWidth()) / 2.0f;
        float y_extent = (other.getCollider().getMax().y - other.getCollider().getHeight()) / 2.0f;
        closest.x = glm::clamp(-x_extent, x_extent, closest.x);
        closest.y = glm::clamp(-y_extent, y_extent, closest.y);
        bool inside = false;
        if (n == closest) {
            inside = true;
            if (glm::abs(n.x) > glm::abs(n.y)) {
                if (closest.x > 0) {
                    closest.x = x_extent;
                }
                else {
                    closest.x = -x_extent;
                }
            }
            else {
                if (closest.y > 0) {
                    closest.y = y_extent;
                }
                else {
                    closest.y = -y_extent;
                }
            }
        }
        glm::vec2 normal = n - closest;
        int d = normal.length();
        int r = _collider.getRadius();

        if (d > r&&!inside) {
            return false;
        }
        if (inside) {
            collision->setNormal(-n);
        }
        else {
            collision->setNormal(n);
        }
        collision->setPenetration(r + d);
        return true;
    }
    return false;
}
