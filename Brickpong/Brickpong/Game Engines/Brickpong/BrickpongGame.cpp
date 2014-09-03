#include "BrickpongGame.h"

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

BrickpongGame::BrickpongGame() {
    _cursor.positionX = 0.0f;
    _cursor.maxOffset = 9.0f;
    _cursor.damping = 1.0f;

    _pauseBallVelocity = b2Vec2(0.0f, 0.0f);
    _points = 0;
    _gamePaused = false;

    _ballBrickContactListener = new BallBrickContactListener(&_contacts);
}

BrickpongGame::~BrickpongGame() {
}

void BrickpongGame::CreateGame(ShaderProgram* aballShaderProgram, GLint aballPositionAttribLoc, GLint aballColorAttribLoc, ShaderProgram* apadShaderProgram, GLint apadPositionAttribLoc, GLint apadColorAttribLoc, ShaderProgram* abrickShaderProgram, GLint abrickPositionAttribLoc, GLint abrickColorAttribLoc) {
    _world = new BrickpongWorld(b2Vec2(0.0f, -10.0f));
    _worldBounds = new BrickpongWorldBounds(_world->GetWorld(), 19.0f, 11.0f, b2Vec2(0.0f, -3.0f));
    _ball = new BrickpongBall(_world->GetWorld(), 0.25f, b2Vec2(2.0f, 4.0f), 1.0f, 3.0f, aballShaderProgram, aballPositionAttribLoc, aballColorAttribLoc);
    _pad = new BrickpongPad(_world->GetWorld(), 4.0f, 0.5f, _cursor.positionX, apadShaderProgram, apadPositionAttribLoc, apadColorAttribLoc);
        //CreateBricksFromGrid(b2Vec2(-7.0f, -3.0f), b2Vec2(7.0f, 0.5f), 1.0f, 0.5f, b2Vec2(0.1f, 0.1f), abrickShaderProgram);

        // tymczasowa implementacja wywołania CreateManyBricksFromLayout()
    std::vector<BrickpongBrickLayout*> bricksLayout;
    bricksLayout.push_back(new BrickpongBrickLayout(b2Vec2(-6.0f, -2.5f), b2Vec2(2.0f, 1.0f)));
    bricksLayout.push_back(new BrickpongBrickLayout(b2Vec2(-2.0f, -2.5f), b2Vec2(2.0f, 1.0f)));
    bricksLayout.push_back(new BrickpongBrickLayout(b2Vec2(2.0f, -2.5f), b2Vec2(2.0f, 1.0f)));
    bricksLayout.push_back(new BrickpongBrickLayout(b2Vec2(6.0f, -2.5), b2Vec2(2.0f, 1.0f)));
    bricksLayout.push_back(new BrickpongBrickLayout(b2Vec2(-6.0f, -1.5f), b2Vec2(4.0f, 1.0f)));
    bricksLayout.push_back(new BrickpongBrickLayout(b2Vec2(-2.0f, -1.5f), b2Vec2(4.0f, 1.0f)));
    bricksLayout.push_back(new BrickpongBrickLayout(b2Vec2(2.0f, -1.5f), b2Vec2(4.0f, 1.0f)));
    bricksLayout.push_back(new BrickpongBrickLayout(b2Vec2(6.0f, -1.5f), b2Vec2(4.0f, 1.0f)));
    bricksLayout.push_back(new BrickpongBrickLayout(b2Vec2(-4.0f, 0.0f), b2Vec2(8.0f, 2.0f)));
    bricksLayout.push_back(new BrickpongBrickLayout(b2Vec2(4.0f, 0.0f), b2Vec2(8.0f, 2.0f)));
    CreateBricksFromLayout(bricksLayout, abrickShaderProgram, abrickPositionAttribLoc, abrickColorAttribLoc);
    ConnectContactListenerToWorld();
    _input = new BrickpongInput(this);
}

void BrickpongGame::DestroyGame() {
    delete _input;
    DestroyContactListener();
    delete _pad;
    delete _ball;
    delete _worldBounds;
    delete _world;
}

void BrickpongGame::CreateBricksFromGrid(b2Vec2 astartPos, b2Vec2 aendPos, float awidth, float aheight, b2Vec2 apadding, ShaderProgram* ashaderProgram, GLint apositionAttribLoc, GLint acolorAttribLoc) {
    for (float32 x = astartPos.x; x <= aendPos.x; x += awidth + apadding.x) {
        for (float32 y = astartPos.y; y <= aendPos.y; y += aheight + apadding.y) {
            _bricks.push_back(new BrickpongBrick(_world->GetWorld(), b2Vec2(x, y), awidth, aheight, ashaderProgram, apositionAttribLoc, acolorAttribLoc));
        }
    }
}

void BrickpongGame::CreateBricksFromLayout(std::vector<BrickpongBrickLayout*> alayout, ShaderProgram* ashaderProgram, GLint apositionAttribLoc, GLint acolorAttribLoc) {
    for (std::vector<BrickpongBrickLayout*>::iterator i = alayout.begin(); i != alayout.end(); i++) {
        _bricks.push_back(new BrickpongBrick(_world->GetWorld(), (*i)->GetPosition(), (*i)->GetSize().x, (*i)->GetSize().y, ashaderProgram, apositionAttribLoc, acolorAttribLoc));
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

void BrickpongGame::DestroyBricks() {
    for (std::vector<b2Contact*>::iterator i = _contacts.begin(); i != _contacts.end(); i++) {
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
            ++_points;
            std::cout << "Points: " << _points << std::endl;
        }
    }
    _contacts.clear();
}

int BrickpongGame::GetPoints() {
    return _points;
}

std::vector<BrickpongBrick*> BrickpongGame::GetBricksList() {
    return _bricks;
}

Cursor* BrickpongGame::GetCursor() {
    return &_cursor;
}

BrickpongBall* BrickpongGame::GetBall() {
    return _ball;
}

void BrickpongGame::ConnectContactListenerToWorld() {
    _ballBrickContactListener = new BallBrickContactListener(&_contacts);
    _world->SetContactListener(_ballBrickContactListener);
}

void BrickpongGame::DestroyContactListener() {
    delete _ballBrickContactListener;
}

void BrickpongGame::ResetGame() {
    _ball->SetTransform(b2Vec2(1.0f, -6.0f), 0.0f);
    _ball->SetLinearVelocityMultiplier(1.0f);
    _ball->SetLinearVelocity(b2Vec2(2.0f, 4.0f));
    for (std::vector<BrickpongBrick*>::iterator i = _bricks.begin(); i != _bricks.end(); i++) {
        (*i)->SetActive(true);
    }
    _points = 0;
    std::cout << "Points: " << _points << std::endl;
}

void BrickpongGame::CheckGameOver() {
    if (_ball->GetPosition().y < -8.0f) {
        std::cout << "##GAME OVER ##" << std::endl << std::endl;
        ResetGame();
    }
}

void BrickpongGame::CheckGameWin() {
    if (_points == _bricks.size()) {
        std::cout << "=== YOU WON! ===" << std::endl << std::endl;
        ResetGame();
    }
}

BrickpongPad* BrickpongGame::GetPad() {
    return _pad;
}

bool BrickpongGame::IsGamePaused() {
    return _gamePaused;
}

void BrickpongGame::SetGamePaused(bool agamePaused) {
    _gamePaused = agamePaused;
}

BrickpongWorld* BrickpongGame::GetWorld() {
    return _world;
}

BrickpongInput* BrickpongGame::GetInput() {
    return _input;
}

void BrickpongGame::CheckGameResult() {
    CheckGameOver();
    CheckGameWin();
}

void BrickpongGame::DrawBricks(glm::mat4 Model, glm::mat4 View, glm::mat4 Projection, GLuint MVP_ID) {
    for (std::vector<BrickpongBrick*>::iterator i = _bricks.begin(); i != _bricks.end(); i++) {
        if ((*i)->IsActive()) {
            (*i)->Draw(Model, View, Projection, MVP_ID);
        }
    }
}
