#include <SFML/Graphics.hpp>
#include <iostream>

#define G 6.67e-11
#define PI 3.14159265359
#define EARTH_RADIUS 6356752.3142

int main()
{
    double angle = 60, rocketMass = 33750000, fuelMass = 273900000, gasSpeed = 6470, fuelRate = 500000, earthMass = 5.972E24, x = 0, y = 0, vx = 0, vy = 0;
    using std::cout;
    using std::cin;
    using std::string;
    using std::to_string;

    /* Input. Uncomment if needed
    cout << "Angle: ";
    cin >> angle;
    cout << "Rocket mass: ";
    cin >> rocketMass;
    cout << "Fuel mass: ";
    cin >> fuelMass;
    cout << "Gas speed: ";
    cin >> gasSpeed;
    cout << "Fuel rate: ";
    cin >> fuelRate;
    cout << "Earth mass: ";
    cin >> earthMass;
    */

    float rocketSize = 30;
    int scale = 70000;
    int time = 0;

    rocketSize /= scale;
    if (rocketSize < 12)
        rocketSize = 12;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Rocket sim");
    sf::ConvexShape rocketShape(3);
    rocketShape.setPoint(0, sf::Vector2f(-rocketSize / 4, 0.f));
    rocketShape.setPoint(1, sf::Vector2f(.0f, -rocketSize));
    rocketShape.setRotation(angle);
    rocketShape.setPoint(2, sf::Vector2f(rocketSize / 4, 0.f));
    rocketShape.setFillColor(sf::Color::Magenta);
    sf::Vector2f offset(-(float)window.getSize().x / 2, (float)window.getSize().y);
    //rocketShape.setOrigin(-(float)window.getSize().x/2, -(float)window.getSize().y );

    sf::RectangleShape startShape(sf::Vector2f(rocketSize/6.0f,rocketSize));
    startShape.setFillColor(sf::Color::Green);
    startShape.setOrigin(-(float)window.getSize().x / 2, -(float)window.getSize().y + rocketSize);


    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    angle = angle / 180 * PI;

    while (window.isOpen())
    {
        time++;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        double acceleration = 0;
        if (fuelMass > 0) {
            double tmp = fuelMass;
            fuelMass -= fuelRate;
            if (fuelMass < 0)
                fuelMass = 0;
            acceleration = gasSpeed * (tmp-fuelMass) / (rocketMass + fuelMass);

        }
        double g = G * earthMass / pow(EARTH_RADIUS + y, 2);

        //Apply acceleration
        vy += acceleration * sin(angle) - g;
        vx += acceleration * cos(angle);
        y += vy;
        if (y <= 0) {
            y = 0;
            vy = 0;
        }
        else {
            x += vx;
            rocketShape.setPosition(-offset.x, -y / scale + offset.y);
        }

        string output = "Position:\n   x: " + to_string(x / 1000) + " km\n   y: " + to_string(y / 1000)+" km\n";
        output += "Velocity:\n   x: " + to_string(vx / 1000) + " km/s\n   y: " + to_string(vy / 1000) + " km/s\n   module: " + to_string(sqrt(vy*vy+vx*vx) / 1000) + " km/s\n";
        output += "Fuel: " + to_string(fuelMass)+"\n";
        cout << output;
        text.setString(output);

        //Draw stuff
        startShape.setPosition(-x / scale, 0);
        rocketShape.setRotation(atan2(vx, vy)/PI*180);
        window.clear();
        window.draw(startShape);
        window.draw(rocketShape);
        window.draw(text);
        window.display();

        //Delay
        sf::sleep(sf::milliseconds(1));
    }

    return 0;
}

