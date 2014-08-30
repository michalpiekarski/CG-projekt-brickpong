#include "BrickpongGame.h"

BrickpongGame::BrickpongGame() {
    cursor.positionX = 0.0f;
    cursor.maxOffset = 9.0f;
    cursor.damping = 1.0f;

    PauseBallVelocity = b2Vec2(0.0f, 0.0f);
    Points = 0;
    gamePaused = false;

    ballBrickContactListener = new BallBrickContactListener(&contacts);
}

BrickpongGame::~BrickpongGame() {
    delete ballBrickContactListener;
}

void BrickpongGame::CreateGame() {
    CreateWorld(b2Vec2(0.0f, -10.0f));
    CreateWorldBounds(16.5f, 10.0f, b2Vec2(0.0f, -4.0f));
    CreateBall();
    CreatePad();
    CreateManyBricks(b2Vec2(-7.0f, -3.0f), b2Vec2(7.0f, 0.5f), b2Vec2(1.0f, 0.5f), b2Vec2(0.1f, 0.1f));
    ConnectContactListenerToWorld();
}

void BrickpongGame::DestroyGame() {
    DestroyWorld();
    DestroyContactListener();
}

void BrickpongGame::CreateWorld(b2Vec2 agravity) {
    world = new b2World(agravity);
}

void BrickpongGame::DestroyWorld() {
    delete world;
}

void BrickpongGame::CreateWorldBounds(float32 worldWidth, float32 worldHeight, b2Vec2 worldCenterOffset) {
    b2BodyDef wbBDef;
    wbBDef.type = b2_kinematicBody;
    wbBDef.position.SetZero();
    worldBounds = world->CreateBody(&wbBDef);

    float32 leftWindowEdge = -worldWidth / 2.0 + worldCenterOffset.x;
    float32 rightWindowEdge = worldWidth / 2.0 + worldCenterOffset.x;
    float32 topWindowEdge = worldHeight / 2.0 + worldCenterOffset.y;
    float32 bottomWindowEdge = -worldHeight / 2.0 + worldCenterOffset.y;

    b2Vec2 wbShapePoints[4] = {
        b2Vec2(leftWindowEdge, bottomWindowEdge),
        b2Vec2(leftWindowEdge, topWindowEdge),
        b2Vec2(rightWindowEdge, topWindowEdge),
        b2Vec2(rightWindowEdge, bottomWindowEdge),
    };

    b2ChainShape wbShape;
    wbShape.CreateChain(wbShapePoints, 4);
    worldBounds->CreateFixture(&wbShape, 0.0f);
}

void BrickpongGame::CreateBall() {
    b2BodyDef ballBDef;
    ballBDef.type = b2_dynamicBody;
    ballBDef.position.Set(1.0f, -5.0f);
    ballBDef.linearVelocity.Set(2.0f, 4.0f);
    ballBDef.gravityScale = 0.0f;
    ballBDef.linearDamping = 0.0f;
    ballBDef.bullet = true;
    ball = world->CreateBody(&ballBDef);
    b2CircleShape ballShape;
    ballShape.m_radius = 0.25f;
    b2FixtureDef ballFDef;
    ballFDef.shape = &ballShape;
    ballFDef.density = 3.0f;
    ballFDef.friction = 0.0f;
    ballFDef.restitution = 1.0f;
    ball->CreateFixture(&ballFDef);
}

void BrickpongGame::CreatePad() {
    b2BodyDef padBDef;
    padBDef.type = b2_kinematicBody;
    padBDef.position.Set(cursor.positionX, -7.5f);
    pad = world->CreateBody(&padBDef);
    b2Vec2 padShapePoints[6] = {
        b2Vec2(-2.0f, -0.25f),
        b2Vec2(-2.0f, -0.1f),
        b2Vec2(-0.05f, +0.25f),
        b2Vec2(+0.05f, +0.25f),
        b2Vec2(+2.0f, -0.1f),
        b2Vec2(+2.0f, -0.25f),
    };
    b2PolygonShape padShape;
    padShape.Set(padShapePoints, 6);
    pad->CreateFixture(&padShape, 0.0f);
}

void BrickpongGame::CreateBrick(b2Body* abrick, b2Vec2 pos, b2Vec2 size) {
    b2BodyDef brickBDef;
    brickBDef.type = b2_staticBody;
    brickBDef.position.Set(pos.x, pos.y);
    abrick = world->CreateBody(&brickBDef);
    b2PolygonShape brickShape;
    brickShape.SetAsBox(size.x / 2.0f, size.y / 2.0f);
    abrick->CreateFixture(&brickShape, 0.0f);
}

void BrickpongGame::CreateManyBricks(b2Vec2 startPos, b2Vec2 endPos, b2Vec2 size, b2Vec2 padding) {
    b2BodyDef brickBDef;
    brickBDef.type = b2_staticBody;
    b2PolygonShape brickShape;
    brickShape.SetAsBox(size.x / 2.0f, size.y / 2.0f);
    b2Body* brick;
    for (float32 x = startPos.x; x <= endPos.x; x += size.x + padding.x) {
        for (float32 y = startPos.y; y <= endPos.y; y += size.y + padding.y) {
            brickBDef.position.Set(x, y);
            brick = world->CreateBody(&brickBDef);
            brick->CreateFixture(&brickShape, 0.0f);
            bricks.push_back(brick);
        }
    }
}

bool BrickpongGame::validBallBrickContact(b2Body* A, b2Body* B) {
    if ((A->GetType() == b2_dynamicBody && B->GetType() == b2_staticBody) ||
        (B->GetType() == b2_dynamicBody && A->GetType() == b2_staticBody)) {
        return true;
    }
    else {
        return false;
    }
}

BrickpongGame::BallBrickContactListener::BallBrickContactListener(std::vector<b2Contact*>* acontacts) {
    contacts = acontacts;
}

void BrickpongGame::BallBrickContactListener::BeginContact(b2Contact* contact) {
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    if (validBallBrickContact(bodyA, bodyB)) {
        contacts->push_back(contact);
    }
}

void BrickpongGame::ConnectContactListenerToWorld() {
    ballBrickContactListener = new BallBrickContactListener(&contacts);
    world->SetContactListener(ballBrickContactListener);
}

void BrickpongGame::DestroyContactListener() {
    delete ballBrickContactListener;
}

void BrickpongGame::DestroyBricks() {
    for (std::vector<b2Contact*>::iterator i = contacts.begin(); i != contacts.end(); i++) {
        b2Body* bodyA = (*i)->GetFixtureA()->GetBody();
        b2Body* bodyB = (*i)->GetFixtureB()->GetBody();
        if (validBallBrickContact(bodyA, bodyB)) {
            b2Vec2 brickPos;
            if (bodyA->GetType() == b2_staticBody) {
                brickPos = bodyA->GetPosition();
                bodyA->SetActive(false);
            }
            else if (bodyB->GetType() == b2_staticBody) {
                brickPos = bodyB->GetPosition();
                bodyB->SetActive(false);
            }
#ifdef __Brickpong__DEBUG_LOG__
            std::cout << "Brick destroyed at: " << brickPos.x << "; " << brickPos.y << std::endl;
#endif
            ++Points;
            std::cout << "Points: " << Points << std::endl;
        }
    }
    contacts.clear();
}

int BrickpongGame::GetPoints() {
    return Points;
}

void BrickpongGame::StepPhysics(float32 timeStep, int32 velocityIterations, int32 positionIterations) {
    world->Step(timeStep, velocityIterations, positionIterations);
}

std::vector<b2Body*> BrickpongGame::GetBricksList() {
    return bricks;
}

Cursor BrickpongGame::GetCursor() {
    return cursor;
}

b2Body* BrickpongGame::GetBall() {
    return ball;
}

void BrickpongGame::CursorPositionChanged(GLFWwindow *window, double x, double y) {
    int windowWidth;
    glfwGetFramebufferSize(window, &windowWidth, NULL);
    int halfWindowWidth = windowWidth / 2.0f;
    float cursorXOffsetFromMiddle = (x - halfWindowWidth) / (halfWindowWidth / cursor.maxOffset);
    if (cursor.damping != 0.0f) {
        cursorXOffsetFromMiddle /= cursor.damping;
    }
    cursor.positionX = glm::clamp(cursorXOffsetFromMiddle, -cursor.maxOffset, cursor.maxOffset);
    pad->SetTransform(b2Vec2(cursor.positionX, pad->GetPosition().y), 0.0f);
#ifdef __Brickpong__DEBUG_LOG__
    std::cout << "Cursor x position: " << cursor.positionX << std::endl;
#endif
}

void BrickpongGame::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods, GLFWcursorposfun currentCursorPosCallback) {
    if (action == GLFW_RELEASE && key == GLFW_KEY_SPACE) {
        b2Vec2 tmp = ball->GetLinearVelocity();
        ball->SetLinearVelocity(PauseBallVelocity);
        PauseBallVelocity = tmp;
        if (!gamePaused) {
            gamePaused = true;
            glfwSetCursorPosCallback(window, NULL);
#ifndef __Brickpong__DEBUG_LOG__
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            std::cout << "Ball position: " << ball->GetPosition().x << "; " << ball->GetPosition().y << " | ";
            std::cout << "Pad position: " << pad->GetPosition().x << "; " << pad->GetPosition().y << std::endl;
#endif
            std::cout << "Game Paused" << std::endl;
        }
        else {
            gamePaused = false;

            glfwSetCursorPosCallback(window, currentCursorPosCallback);
#ifndef __Brickpong__DEBUG_LOG__
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
#endif
            std::cout << "Game Resumed" << std::endl;
        }
    }
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_A || key == GLFW_KEY_LEFT) {
            cursor.positionX -= 0.5f;
            b2Vec2 padPosition = pad->GetPosition();
            padPosition.x -= 0.5f;
            pad->SetTransform(padPosition, pad->GetAngle());
        }
        else if (key == GLFW_KEY_D || key == GLFW_KEY_RIGHT) {
            cursor.positionX += 0.5f;
            b2Vec2 padPosition = pad->GetPosition();
            padPosition.x += 0.5f;
            pad->SetTransform(padPosition, pad->GetAngle());
        }
        else if (key == GLFW_KEY_LEFT_BRACKET) {
            cursor.damping -= 0.5f;
            cursor.damping = glm::clamp(cursor.damping, 0.0f, 4.0f);
        }
        else if (key == GLFW_KEY_RIGHT_BRACKET) {
            cursor.damping += 0.5f;
            cursor.damping = glm::clamp(cursor.damping, 0.0f, 4.0f);
        }
    }
    if (action == GLFW_PRESS && key == GLFW_KEY_R) {
        ResetGame();
    }
}

void BrickpongGame::ResetGame() {
    ball->SetTransform(b2Vec2(1.0f, -6.0f), 0.0f);
    ball->SetLinearVelocity(b2Vec2(2.0f, 4.0f));
    for (std::vector<b2Body*>::iterator i = bricks.begin(); i != bricks.end(); i++) {
        (*i)->SetActive(true);
    }
    Points = 0;
    std::cout << "Points: " << Points << std::endl;
}

void BrickpongGame::CheckBallBelowPad() {
    if (ball->GetPosition().y < -8.0f) {
        std::cout << "##GAME OVER ##" << std::endl << std::endl;
        ResetGame();
    }
}

void BrickpongGame::CheckGameWin() {
    if (Points == bricks.size()) {
        std::cout << "=== YOU WON! ===" << std::endl << std::endl;
        ResetGame();
    }
}