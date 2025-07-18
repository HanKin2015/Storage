#include <vector>
#include <algorithm>

class Observer {
public:
    virtual void update(int state) = 0;
    virtual ~Observer() = default;
};

class Subject {
private:
    std::vector<Observer*> observers;
    int state;
public:
    void attach(Observer* o) { observers.push_back(o); }
    void detach(Observer* o) {
        observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
    }
    void notify() {
        for (auto o : observers) {
            o->update(state);
        }
    }
    void setState(int s) {
        state = s;
        notify();
    }
};

class ConcreteObserver : public Observer {
private:
    int observerState;
public:
    void update(int state) override { observerState = state; }
};