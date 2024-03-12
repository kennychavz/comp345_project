#include <vector>

class Observer;

class Observable {
public:
    virtual void addObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notifyObservers() = 0;
};

class Observer {
public:
    virtual void update() = 0;
};
