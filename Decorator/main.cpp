/*
#include <string>
#include <iostream>
using namespace std;

class Car //Our Abstract base class 车的抽象基类
{
        protected:
                string _str;
        public:
                Car()
                {
                        _str = "Unknown Car";
                }

                virtual string getDescription()
                {
                        return _str;
                }

                virtual double getCost() = 0;

                virtual ~Car()
                {
                        cout << "~Car()\n";
                }
};

class OptionsDecorator : public Car //Decorator Base class 装饰选项基类
{
        public:
                virtual string getDescription() = 0;

                virtual ~OptionsDecorator()
                {
                        cout<<"~OptionsDecorator()\n";
                }
};


class CarModel1 : public Car //定义一种车型
{
        public:
                CarModel1()
                {
                        _str = "CarModel1";
                }
                virtual double getCost()
                {
                        return 31000.23;
                }

                ~CarModel1()
                {
                        cout<<"~CarModel1()\n";
                }
};


class Navigation: public OptionsDecorator // 导航 装饰 ，在这个类中重写装饰类中的方法， 给车加一个导航的方法
{
                Car *_b;
        public:
                Navigation(Car *b)
                {
                        _b = b;
                }
                string getDescription()
                {
                        return _b->getDescription() + ", Navigation";
                }

                double getCost()
                {
                        return 300.56 + _b->getCost();
                }
                ~Navigation()
                {
                        cout << "~Navigation()\n";
                        delete _b;
                }
};

class PremiumSoundSystem: public OptionsDecorator //高级音响系统
{
                Car *_b;
        public:
                PremiumSoundSystem(Car *b)
                {
                        _b = b;
                }
                string getDescription()
                {
                        return _b->getDescription() + ", PremiumSoundSystem";
                }

                double getCost()
                {
                        return 0.30 + _b->getCost();
                }
                ~PremiumSoundSystem()
                {
                        cout << "~PremiumSoundSystem()\n";
                        delete _b;
                }
};

class ManualTransmission: public OptionsDecorator //手动变速器
{
                Car *_b;
        public:
                ManualTransmission(Car *b)
                {
                        _b = b;
                }
                string getDescription()
                {
                return _b->getDescription()+ ", ManualTransmission";
                }

                double getCost()
                {
                        return 0.30 + _b->getCost();
                }
                ~ManualTransmission()
                {
                        cout << "~ManualTransmission()\n";
                        delete _b;
                }
};

int main()
{
        //Create our Car that we want to buy
        Car *b = new CarModel1();

        cout << "Base model of " << b->getDescription() << " costs $" << b->getCost() << "\n";

        //Who wants base model let's add some more features

        b = new Navigation(b);
        cout << b->getDescription() << " will cost you $" << b->getCost() << "\n";
        b = new PremiumSoundSystem(b);
        b = new ManualTransmission(b);
        cout << b->getDescription() << " will cost you $" << b->getCost() << "\n";

        // WARNING! Here we leak the CarModel1, Navigation and PremiumSoundSystem objects!
        // Either we delete them explicitly or rewrite the Decorators to take
        // ownership and delete their Cars when destroyed.
        delete b;

        return 0;
}
*/

#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Interface {
    public:
        virtual ~Interface() { }
        virtual void write (std::string&) = 0;
};

class Core : public Interface {
    public:
        ~Core() {std::cout << "Core destructor called.\n";}
        virtual void write (std::string& text) override {};  // Do nothing.
};

class Decorator : public Interface {
    private:
        std::unique_ptr<Interface> interface;
    public:
        Decorator (std::unique_ptr<Interface> c) {interface = std::move(c);}
        virtual void write (std::string& text) override {interface->write(text);}
};

class MessengerWithSalutation : public Decorator {
    private:
        std::string salutation;
    public:
        MessengerWithSalutation (std::unique_ptr<Interface> c, const std::string& str) : Decorator(std::move(c)), salutation(str) {}
        ~MessengerWithSalutation() {std::cout << "Messenger destructor called.\n";}
        virtual void write (std::string& text) override {
            text = salutation + "\n\n" + text;
            Decorator::write(text);
        }
};

class MessengerWithValediction : public Decorator {
    private:
        std::string valediction;
    public:
        MessengerWithValediction (std::unique_ptr<Interface> c, const std::string& str) : Decorator(std::move(c)), valediction(str) {}
        ~MessengerWithValediction() {std::cout << "MessengerWithValediction destructor called.\n";}
        virtual void write (std::string& text) override {
            Decorator::write(text);
            text += "\n\n" + valediction;
        }
};

int main() {
    const std::string salutation = "Greetings,";
    const std::string valediction = "Sincerly, Andy";
    std::string message1 = "This message is not decorated.";
    std::string message2 = "This message is decorated with a salutation.";
    std::string message3 = "This message is decorated with a valediction.";
    std::string message4 = "This message is decorated with a salutation and a valediction.";

    std::unique_ptr<Interface> messenger1 = std::make_unique<Core>();
    std::unique_ptr<Interface> messenger2 = std::make_unique<MessengerWithSalutation> (std::make_unique<Core>(), salutation);
    std::unique_ptr<Interface> messenger3 = std::make_unique<MessengerWithValediction> (std::make_unique<Core>(), valediction);
    std::unique_ptr<Interface> messenger4 = std::make_unique<MessengerWithValediction> (std::make_unique<MessengerWithSalutation>
                                          (std::make_unique<Core>(), salutation), valediction);

    messenger1->write(message1);
    std::cout << message1 << '\n';
    std::cout << "\n------------------------------\n\n";

    messenger2->write(message2);
    std::cout << message2 << '\n';
    std::cout << "\n------------------------------\n\n";

    messenger3->write(message3);
    std::cout << message3 << '\n';
    std::cout << "\n------------------------------\n\n";

    messenger4->write(message4);
    std::cout << message4 << '\n';
    std::cout << "\n------------------------------\n\n";
}
