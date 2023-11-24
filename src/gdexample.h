#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

class The_Game : public Node {
        GDCLASS(The_Game, Node)

       void _get_property_list(List<PropertyInfo> *p_list) const;

    static void _bind_methods();
// TODO: it seems like the above thing here is a GDExtension
// specific thing.

    Node *node;
    Node *audioStreamPlayer;

public:
    void _ready();
    void _process(double delta);

    };

class Beta : public Sprite2D {
	GDCLASS(Beta, Sprite2D)

private:
	double time_passed;

protected:
	static void _bind_methods();

public:
	Beta();
	~Beta();

	void _process(double delta);
};

}

#endif
