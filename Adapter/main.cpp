#include <iostream>

class Hindu {  // Abstract Target 印度教
        public:
            virtual ~Hindu() = default;
            virtual void performsHinduRitual() const = 0;
};

class HinduFemale : public Hindu {  // Concrete Target 印度教女
        public:
            virtual void performsHinduRitual() const override {std::cout << "Hindu girl performs Hindu ritual." << std::endl;}
};

class Muslim {  // Abstract Adaptee 穆斯林
        public:
            virtual ~Muslim() = default;
            virtual void performsMuslimRitual() const = 0;
};

class MuslimFemale : public Muslim {  // Concrete Adaptee 穆斯林女
        public:
            virtual void performsMuslimRitual() const override {std::cout << "Muslim girl performs Muslim ritual." << std::endl;}
};

class HinduRitual { //印度教仪式
        public:
            void carryOutRitual (Hindu* hindu) {
                std::cout << "On with the Hindu rituals!" << std::endl;
                hindu->performsHinduRitual();
            }
};

class HinduAdapter : public Hindu {  // Adapter 印度教适配器
    private:
        Muslim* muslim;
    public:
        HinduAdapter (Muslim* m) : muslim(m) {}
        virtual void performsHinduRitual() const override {muslim->performsMuslimRitual();}
};

int main() {  // Client code
    HinduFemale* hinduGirl = new HinduFemale; //创建印度教女的
    MuslimFemale* muslimGirl = new MuslimFemale; //创建穆斯林女的
    HinduRitual hinduRitual; //创建印度教宗教仪式
//	hinduRitual.carryOutRitual (muslimGirl);  // Will not compile of course since the parameter must be of type Hindu*.
    //穆斯林女孩经过印度教的适配转换变成一个印度适配者这时他们是同样一个人
    HinduAdapter* adaptedMuslim = new HinduAdapter (muslimGirl);  // muslimGirl has adapted to become a Hindu!

    hinduRitual.carryOutRitual (hinduGirl);
    hinduRitual.carryOutRitual (adaptedMuslim);  // So now muslimGirl, in the form of adaptedMuslim, participates in the hinduRitual!
                // Note that muslimGirl is carrying out her own type of ritual in hinduRitual though.

    delete adaptedMuslim;  // adaptedMuslim is not needed anymore
    delete muslimGirl; // muslimGirl is not needed anymore
    delete hinduGirl; // hinduGirl is not needed anymore, too
    return 0;
}
