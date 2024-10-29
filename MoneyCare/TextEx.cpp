#include "Extentions.h"
#include "WindowManager.h"
#include "Coroutine.h"
#include "DebugLog.h"
#include "Global.h"

std::shared_ptr<sf::TextEx> sf::TextEx::Create(sf::Font font, std::string contents, unsigned int size, sf::Vector2f position)
{
    std::shared_ptr<sf::TextEx> tempObject(new sf::TextEx(font, contents, size, position));

    tempObject->UpdateObject();

    return tempObject;
}

sf::TextEx::TextEx(sf::Font font, std::string contents, unsigned int size, sf::Vector2f position)
{
    
    this->setCharacterSize(size);
    this->setFont(font);

    // set origin to middle of the object
    this->setOrigin(sf::Vector2f(this->getGlobalBounds().width / 2, this->getGlobalBounds().height / 2));

    // set position
    this->setPosition(position);

    // set animation state to origin
    this->position_animation = sf::Vector2f(this->getPosition());
    this->position_animation_speed_rate = 0;
}

void sf::TextEx::UpdateObject()
{
    UpdateAnimation();
    WindowManager::window.draw(*this);

    Coroutine::SafeAddCoroutine(
        static_cast<std::weak_ptr<sf::TextEx>>(shared_from_this()),
        [&]() {UpdateObject();}
    );
}

void sf::TextEx::UpdateAnimation()
{
    UpdatePositionAnimation();
}

void sf::TextEx::Translate(sf::Vector2f toPos, float speedRate)
{
    position_animation = toPos;

    if (speedRate > MAX_ANIMATION_SPEED_RATE) speedRate = MAX_ANIMATION_SPEED_RATE;
    position_animation_speed_rate = speedRate;
}

void sf::TextEx::UpdatePositionAnimation()
{
    float toX, toY;

    toX = getPosition().x
        + (position_animation.x - getPosition().x)
        / MAX_ANIMATION_SPEED_RATE
        * position_animation_speed_rate
        * Global::DeltaTime();

    toY = getPosition().y
        + (position_animation.y - getPosition().y)
        / MAX_ANIMATION_SPEED_RATE
        * position_animation_speed_rate
        * Global::DeltaTime();

    setPosition(toX, toY);
}