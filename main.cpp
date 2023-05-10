#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <cmath>

class Ball
{
public:
    sf::CircleShape _ball;
    sf::Vector2f pos;
    sf::Vector2f vel;
    float radius { rand() % 5 + 15 };
    float speed { rand() % 100 + 75 };

    Ball();
    sf::CircleShape getShape();
    void update(float elapsedTime, sf::Window& window);
};

Ball::Ball()
{
    _ball.setOutlineThickness(4);
    _ball.setOutlineColor(sf::Color::Black);
    _ball.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
    _ball.setRadius(radius);
}

sf::CircleShape Ball::getShape()
{
    return _ball;
}

void Ball::update(float elapsedTime, sf::Window& window)
{
    // Move the ball
    _ball.move(vel * elapsedTime);

    // Collisions between screen
    sf::Vector2f getPos = _ball.getPosition();
    sf::Vector2u winSize = window.getSize();
    // Collide with Left and Right screen
    if (getPos.x < 0 || getPos.x + radius * 2 > winSize.x)
    {
        vel.x = -vel.x;
    }
    // Collide with Top and Bottom screen
    if (getPos.y < 0 || getPos.y + radius * 2 > winSize.y)
    {
        vel.y = -vel.y;
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    using kb = sf::Keyboard;

    unsigned const int WIDTH { 1200 };
    unsigned const int HEIGHT { 900 };
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML");
    window.setFramerateLimit(75);

    std::vector<Ball> balls;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Exit program if click X
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Input
        // Close window if press Escape button
        if (kb::isKeyPressed(kb::Escape))
        {
            window.close();
        }

        // Spawn Balls if press Space
        if (kb::isKeyPressed(kb::Space))
        {
            Ball ball;
            ball._ball.setPosition(window.getSize().x / 2, window.getSize().y / 2);
            float angle { rand() % 360 / 3.141};
            //ball.vel = sf::Vector2f(ball.speed * (rand() % 10 - 5), ball.speed * (rand() % 10 - 5));
            ball.vel = sf::Vector2f(ball.speed * std::cos(angle), ball.speed * std::sin(angle));
            balls.push_back(ball);
        }

        // Update
        sf::Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();
        for (auto& ball : balls)
        {
            ball.update(dtAsSeconds, window);
        }

        // Draw
        window.clear(sf::Color(40, 40, 100));
        for (auto& ball : balls)
        {
            window.draw(ball.getShape());
        }
        window.display();
    }

    return 0;
}
