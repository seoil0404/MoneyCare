#include "Extentions.h"
#include "WindowManager.h"
#include "Coroutine.h"
#include "DebugLog.h"
#include "Global.h"

std::shared_ptr<sf::RectangleShapeEx> sf::RectangleShapeEx::Create(sf::Vector2f size, sf::Vector2f position)
{
    std::shared_ptr<sf::RectangleShapeEx> tempObject(new sf::RectangleShapeEx(size, position));

    tempObject->UpdateObject();

    return tempObject;
}

sf::RectangleShapeEx::RectangleShapeEx(sf::Vector2f size, sf::Vector2f position) : sf::RectangleShape(size)
{
    // set origin to middle of the object
    this->setOrigin(sf::Vector2f(this->getSize().x / 2, this->getSize().y / 2));

    // set position
    this->setPosition(position);
    
    // set animation state to origin
    this->position_animation = sf::Vector2f(this->getPosition());
    this->position_animation_speed_rate = 0;

    this->scale_animation = sf::Vector2f(1, 1);
    this->scale_animation_speed_rate = 0;
}

void sf::RectangleShapeEx::UpdateObject()
{
    UpdateAnimation();

    WindowManager::window.draw(*this);

    Coroutine::SafeAddCoroutine(
        get_weak(this),
        [&]() {UpdateObject();}
    );
}

void sf::RectangleShapeEx::UpdateAnimation()
{
    UpdatePositionAnimation();
    UpdateScaleAnimation();
}

void sf::RectangleShapeEx::UpdatePositionAnimation()
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

void sf::RectangleShapeEx::UpdateScaleAnimation()
{
    float toX, toY;

    toX = getScale().x
        + (scale_animation.x - getScale().x)
        / MAX_ANIMATION_SPEED_RATE
        * scale_animation_speed_rate
        * Global::DeltaTime();

    toY = getScale().y
        + (scale_animation.y - getScale().y)
        / MAX_ANIMATION_SPEED_RATE
        * scale_animation_speed_rate
        * Global::DeltaTime();

    setScale(toX, toY);
}

void sf::RectangleShapeEx::Translate(sf::Vector2f toPos, float speedRate)
{
    position_animation = position_animation + toPos;

    if (speedRate > MAX_ANIMATION_SPEED_RATE) speedRate = MAX_ANIMATION_SPEED_RATE;
    position_animation_speed_rate = speedRate;
}

void sf::RectangleShapeEx::Resize(sf::Vector2f toScale, float speedRate)
{
    scale_animation = toScale;

    if (speedRate > MAX_ANIMATION_SPEED_RATE) speedRate = MAX_ANIMATION_SPEED_RATE;
    scale_animation_speed_rate = speedRate;
}