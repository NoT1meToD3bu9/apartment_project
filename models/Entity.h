#pragma once

class Entity {
protected:
    int id;

public:
    Entity(int id = 0) : id(id) {}
    virtual ~Entity() = default;

    int getId() const { return id; }
    void setId(int value) { id = value; }

    virtual void display() const = 0;
};

