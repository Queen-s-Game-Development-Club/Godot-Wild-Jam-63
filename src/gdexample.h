#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/input_event_mouse.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/rectangle_shape2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>


namespace godot {

class The_Game : public Node {
        GDCLASS(The_Game, Node)

       void _get_property_list(List<PropertyInfo> *p_list) const;

    static void _bind_methods();
// TODO: it seems like the above thing here is a GDExtension
// specific thing.

    Node *node;
    Node *audioStreamPlayer;

// TODO: this is not a scalable solution.
    Node *jumpPlayer;

    Node2D *player;
    Node2D *obstacle;

    Vector2 playerVelocity;

    double runningTime = 0.f;

    Node *camera;

    RectangleShape2D groundPlaneColBox;
    Ref<Shape2D> groundPlaneRef;

public:
    void _ready();
    void _process(double delta);
    void _input(const Ref<InputEvent> &event);

    };


} // end namespace.

#endif
