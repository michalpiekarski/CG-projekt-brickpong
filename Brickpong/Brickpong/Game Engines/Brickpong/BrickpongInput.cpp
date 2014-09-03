#include "BrickpongInput.h"
#include "BrickpongGame.h"

BrickpongInput::BrickpongInput(BrickpongGame* agame) {
    _game = agame;
    _pauseBallVelocity = b2Vec2(0.0f, 0.0f);
    _debugMode = 0;
}

BrickpongInput::BrickpongInput(BrickpongGame* agame, unsigned short adebugMode) : BrickpongInput(agame) {
    _debugMode = adebugMode;
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

    if (_debugMode > 1) {
        std::cout << "Cursor x position: " << cursor->positionX << std::endl;
    }
}

void BrickpongInput::KeyCallback(BrickpongGame* agame, GLFWwindow *awindow, int akey, int ascancode, int aaction, int amods, GLFWcursorposfun acurrentCursorPosCallback) {
    if (aaction == GLFW_RELEASE) {
        if (akey == GLFW_KEY_SPACE) {
            b2Vec2 tmp = agame->GetBall()->GetLinearVelocity();
            agame->GetBall()->SetLinearVelocity(_pauseBallVelocity);
            _pauseBallVelocity = tmp;
            if (!agame->IsGamePaused()) {
                agame->SetGamePaused(true);
                glfwSetCursorPosCallback(awindow, NULL);
                glfwSetInputMode(awindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

                if (_debugMode > 1) {
                    std::cout << "Ball position: " << agame->GetBall()->GetPosition().x << "; " << agame->GetBall()->GetPosition().y << " | ";
                    std::cout << "Pad position: " << agame->GetPad()->GetPosition().x << "; " << agame->GetPad()->GetPosition().y << std::endl;
                }

                std::cout << "--Game Paused--" << std::endl;
            }
            else {
                agame->SetGamePaused(false);

                glfwSetCursorPosCallback(awindow, acurrentCursorPosCallback);
                glfwSetInputMode(awindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

                std::cout << "--Game Resumed--" << std::endl;
            }
        }
        else if(akey == GLFW_KEY_1) {
            BrickpongBall* tmpBall = agame->GetBall();
            float tmpVelMulti = tmpBall->GetLinearVelocityMultiplier();
            if (tmpVelMulti > 1.0) {
                tmpVelMulti = 1.0f;
            }
            tmpBall->SetLinearVelocityMultiplier(tmpVelMulti*0.75f);

            if (_debugMode > 0) {
                std::cout << "Ball speed dencreased to level: " << tmpBall->GetLinearVelocityMultiplier() << std::endl;
            }
        }
        else if (akey == GLFW_KEY_2) {
            BrickpongBall* tmpBall = agame->GetBall();
            float tmpVelMulti = tmpBall->GetLinearVelocityMultiplier();
            if (tmpVelMulti < 1.0) {
                tmpVelMulti = 1.0f;
            }
            tmpBall->SetLinearVelocityMultiplier(tmpVelMulti*1.25f);

            if (_debugMode > 0) {
                std::cout << "Ball speed increased to level: " << tmpBall->GetLinearVelocityMultiplier() << std::endl;
            }
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