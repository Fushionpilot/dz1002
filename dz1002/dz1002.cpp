
#include "httplib.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace httplib;
using namespace std;

class Car {
public:
    string brand;
    string model;
    int year;

    Car(string brand, string model, int year): brand(brand), model(model), year(year) {}
};

int main()
{
	Server server;

    server.Get("/car", [](const Request& req, Response& res) {

        if (!req.has_param("brand")) {

            ifstream file("car.html");

            string content((istreambuf_iterator<char>(file)),istreambuf_iterator<char>());
            res.set_content(content, "text/html");
            return;
        }

        string brand = req.get_param_value("brand");
        string model = req.get_param_value("model");
        int year = stoi(req.get_param_value("year"));

        Car car(brand, model, year);
        string response = "Brand: " + car.brand + " Model: " + car.model + " Year: " + to_string(car.year);
        res.set_content(response, "text/plain");
        });


    cout << "Server is running" << endl;
    server.listen("0.0.0.0", 8080);
    cout << "Server stopped" << endl;
}

