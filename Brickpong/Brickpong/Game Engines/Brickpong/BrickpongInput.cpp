#include "BrickpongInput.h"
#include "BrickpongGame.h"

BrickpongInput::BrickpongInput(BrickpongGame* agame) {
    _game = agame;
    _pauseBallVelocity = b2Vec2(0.0f, 0.0f);
}

BrickpongInput::~BrickpongInput() {

}

void BrickpongInput::CursorPositionChanged(BrickpongGame* agame, GLFWwindow *awindow, double acursorPosX, double acursorPosY) {
    int windowWidth;
    glfwGetFramebufferSize(awindow, &windowWidth, NULL);
    int halfWindowWidth = windowWidth / 2.0f;
    Cursor* cursor = agame->GetCursor();
    float cursorXOffsetFromMiddle = (acursorPosX - halfWindowWidth) / (halfWindowWidth / cursor->maxOffset);
    if (cursor->damping != 0.0f) {
        cursorXOffsetFromMiddle /= cursor->damping;
    }
    cursor->positionX = glm::clamp(cursorXOffsetFromMiddle, -cursor->maxOffset, cursor->maxOffset);
    agame->GetPad()->SetTransform(b2Vec2(cursor->positionX, agame->GetPad()->GetPosition().y), 0.0f);
#ifdef __Brickpong__DEBUG_LOG__
    std::cout << "Cursor x position: " << cursor.positionX << std::endl;
#endif
}

void BrickpongInput::KeyCallback(BrickpongGame* agame, GLFWwindow *awindow, int akey, int ascancode, int aaction, int amods, GLFWcursorposfun acurrentCursorPosCallback) {
    if (aaction == GLFW_RELEASE && akey == GLFW_KEY_SPACE) {
        b2Vec2 tmp = agame->GetBall()->GetLinearVelocity();
        agame->GetBall()->SetLinearVelocity(_pauseBallVelocity);
        _pauseBallVelocity = tmp;
        if (!agame->IsGamePaused()) {
            agame->SetGamePaused(true);
            glfwSetCursorPosCallback(awindow, NULL);
#ifndef __Brickpong__DEBUG_LOG__
            glfwSetInputMode(awindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            std::cout << "Ball position: " << agame->GetBall()->GetPosition().x << "; " << agame->GetBall()->GetPosition().y << " | ";
            std::cout << "Pad position: " << agame->GetPad()->GetPosition().x << "; " << agame->GetPad()->GetPosition().y << std::endl;
#endif
            std::cout << "Game Paused" << std::endl;
        }
        else {
            agame->SetGamePaused(false);

            glfwSetCursorPosCallback(awindow, acurrentCursorPosCallback);
#ifndef __Brickpong__DEBUG_LOG__
            glfwSetInputMode(awindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
#endif
            std::cout << "Game Resumed" << std::endl;
        }
    }
    if (aaction == GLFW_PRESS || aaction == GLFW_REPEAT) {
        if (akey == GLFW_KEY_A || akey == GLFW_KEY_LEFT) {
            agame->GetCursor()->positionX -= 0.5f;
            b2Vec2 padPosition = agame->GetPad()->GetPosition();
            padPosition.x -= 0.5f;
            agame->GetPad()->SetTransform(padPosition, agame->GetPad()->GetAngle());
        }
        else if (akey == GLFW_KEY_D || akey == GLFW_KEY_RIGHT) {
            agame->GetCursor()->positionX += 0.5f;
            b2Vec2 padPosition = agame->GetPad()->GetPosition();
            padPosition.x += 0.5f;
            agame->GetPad()->SetTransform(padPosition, agame->GetPad()->GetAngle());
        }
        else if (akey == GLFW_KEY_LEFT_BRACKET) {
            agame->GetCursor()->damping -= 0.5f;
            agame->GetCursor()->damping = glm::clamp(agame->GetCursor()->damping, 0.0f, 4.0f);
        }
        else if (akey == GLFW_KEY_RIGHT_BRACKET) {
            agame->GetCursor()->damping += 0.5f;
            agame->GetCursor()->damping = glm::clamp(agame->GetCursor()->damping, 0.0f, 4.0f);
        }
    }
    if (aaction == GLFW_PRESS && akey == GLFW_KEY_R) {
        agame->ResetGame();
    }
}

b2Vec2 BrickpongInput::GetPauseBallVelocity() {
    return _pauseBallVelocity;
}
void BrickpongInput::SetBallPauseVelocity(b2Vec2 apauseBallVelocity) {
    _pauseBallVelocity = apauseBallVelocity;
}