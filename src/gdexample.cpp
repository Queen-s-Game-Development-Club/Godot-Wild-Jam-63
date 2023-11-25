#include "gdexample.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Beta::_bind_methods() {
}

Beta::Beta() {
	// Initialize any variables here.
	time_passed = 0.0;
}

Beta::~Beta() {
	// Add your cleanup here.
}

void Beta::_process(double delta) {
	time_passed += delta;

	Vector2 new_position = Vector2(10.0 + (10.0 * sin(time_passed * 2.0)), 10.0 + (10.0 * cos(time_passed * 2.0)));

	set_position(new_position);

    // have I hit the thing ?

// get by tag




}

void The_Game::_bind_methods()
{}

void The_Game::_get_property_list(List<PropertyInfo> *p_list) const
{

	p_list->push_back(
        PropertyInfo(Variant::INT, "My Property", PROPERTY_HINT_RANGE, "0,30,1", PROPERTY_USAGE_EDITOR));
    
}

void The_Game::_ready()
{
    obstacle = get_node<Node>("Obstacle");
    node = get_node<Node>("printer_node");
    audioStreamPlayer = get_node<Node>("AudioStreamPlayer");
    player = get_node<Node>("player");
    camera = get_node<Node>("camera");
    audioStreamPlayer->call("play");
}

void The_Game::_input(const Ref<InputEvent> &event)
{
    
#if 0
const InputEventKey *key_event = Object::cast_to<const InputEventKey>(*event);	
if (key_event) {
		emit_custom_signal(String("_input: ") + key_event->get_key_label(), key_event->get_unicode());
	}
#endif

const InputEventMouseButton *mouseBttnEvent = Object::cast_to<const InputEventMouseButton>(*event);

if (mouseBttnEvent){
        node->call( "my_print", "mouse button event" ); 
}

#if 0
   elif event is InputEventMouseMotion:
	   print("Mouse Motion at: ", event.position)

           // Print the size of the viewport.
   print("Viewport Resolution is: ", get_viewport().get_visible_rect().size)
#endif

}

void The_Game::_process(double delta)
{
    runningTime += delta;

    if (runningTime > 1.f)
    {
        // do something interesting.
        const char *str = "we rich";        
        double something = 5.1;
        static int d = 3;
//        printf( "%s, %f, %d", str, something, d++ );

// can we get into a debugger?
        node->call( "my_print", "Hello, World!" ); 


      runningTime = 0.f;
    }

    Vector2 newCameraPos = Vector2((10.0 * sin(runningTime)), (10.0 * -cos(runningTime)));
    camera->call("set_position", newCameraPos);

	Vector2 new_position = Vector2(10.0 + (10.0 * sin(runningTime * 2.0)), 10.0 + (10.0 * cos(runningTime * 2.0)));

	player->call("set_position", new_position);//  set_position(new_position);

}

