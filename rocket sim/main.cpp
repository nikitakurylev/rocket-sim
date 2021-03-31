#include <iostream>
#include <string>

#define G 6.67e-11
#define PI 3.14159265359
#define EARTH_RADIUS 6356752.3142

int main()
{
    double angle = 89, rocketMass = 33750000, fuelMass = 273900000, gasSpeed = 6470, fuelRate = 500000, earthMass = 5.972E24, x = 0, y = 0, vx = 0, vy = 0;
    using std::cout;
    using std::cin;
    using std::string;
    using std::to_string;

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

    angle = angle / 180 * PI;


    while (!(fuelMass == 0 && y == 0))
    {
        double acceleration = 0;
        if (fuelMass > 0) {
            double tmp = fuelMass;
            fuelMass -= fuelRate;
            if (fuelMass < 0)
                fuelMass = 0;
            acceleration = gasSpeed * (tmp - fuelMass) / (rocketMass + fuelMass); //Calculate jet force

        }
        double g = G * earthMass / pow(EARTH_RADIUS + y, 2); //Calculate gravitational acceleration

        //Apply acceleration
        vy += acceleration * sin(angle) - g;
        vx += acceleration * cos(angle);
        y += vy;
        if (y <= 0) {
            y = 0;
            vy = 0;
        }
        else
            x += vx;

        string output = "Position:\n   x: " + to_string(x / 1000) + " km\n   y: " + to_string(y / 1000) + " km\n";
        output += "Velocity:\n   x: " + to_string(vx / 1000) + " km/s\n   y: " + to_string(vy / 1000) + " km/s\n   module: " + to_string(sqrt(vy * vy + vx * vx) / 1000) + " km/s\n";
        output += "Fuel: " + to_string(fuelMass) + "\n";
        cout << output;
    }

    return 0;
}