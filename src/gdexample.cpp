#include "gdexample.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

// TODO: In a real game what we might do would be
// to create scripts that sit on the player
// and the obstacles, so that the game is descending down
// the tree here.
// make those "objects" themselves do the descending.

float sign(float a)
{
    return a > 0 ? 1.f :  -1.f;
}


void The_Game::_bind_methods()
{}

bool The_Game::_set(const StringName &p_name, const Variant &p_value)
{

        char buffer[256];
        sprintf(buffer, "we rich2: %d", int32_t(p_value));
        node->call( "my_print", buffer);


    if (values.has(p_name)) {
			values[p_name] = p_value;


			return true;
		}

		return false;
}

#define CAMERA_SPEED_PROP "Camera Speed"

bool The_Game::_get(const StringName &p_name, Variant &r_ret) const {
		if (values.has(p_name)) {
			r_ret = values[p_name];
			return true;
		}

		return false;
	}

void The_Game::_get_property_list(List<PropertyInfo> *p_list) const
{

	p_list->push_back(
        PropertyInfo(Variant::INT, CAMERA_SPEED_PROP, PROPERTY_HINT_RANGE, "0,100,1", PROPERTY_USAGE_EDITOR));
    
}

// TODO: find the way where we can hook the very start of the game
// each time the play bttn is pressed.

void The_Game::_ready()
{

// add the editor properties
    {
        values.insert(CAMERA_SPEED_PROP, Variant(10));
    }


    obstacle = get_node<Node2D>("Obstacle");
    node = get_node<Node>("printer_node");
    audioStreamPlayer = get_node<Node>("AudioStreamPlayer");
    player = get_node<Node2D>("player");
    camera = get_node<Node>("camera");

    jumpPlayer = get_node<Node>("AudioStreamPlayer2");


//    audioStreamPlayer->call("play");



// TODO: log the shits here if we can't find the stuff.
    if (obstacle)
    {
        int width;
        int height;
        Sprite2D *sprite = obstacle->get_node<Sprite2D>("Sprite2D");
        if (sprite)
        {
            Ref<Texture2D> texture = sprite->get_texture();
            if (texture.is_valid())
            {
                width = texture->get_width();
                height = texture->get_height();
            }
        }

        CollisionShape2D *shape = obstacle->get_node<CollisionShape2D>("CollisionShape2D");

        if (shape)
        {
// create a shape 2d.
            groundPlaneColBox.set_size(Vector2(width, height));
            groundPlaneRef = Ref<Shape2D>(&groundPlaneColBox);
            shape->set_shape(groundPlaneRef);
        }

    }

    Node *canvas = get_node<Node>("CanvasLayer");
    if (canvas)
        scoreLabel = canvas->get_node<Label>("Label");

// TODO: is there any way that we can just quit game if we can't get
// any of these things? that's the sensible thing to do.

// Set the init player velocity.
    player->set_position(Vector2(0,0));
//    playerVelocity = Vector2(0.f, -20.f);;
    playerVelocity = Vector2(0,0);

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

// TODO: we could hide the mouse cursor and animate a sprite to follow
// where the user is pointing their mouse. that way, we can have a sort
// of animated mouse. I imagine this to be where it rotates the cursor
// such that when hovering over a button or something is selected,
// it points always like an arrow to that thing.

// TODO: when the window size is adjusted, adjust the primary window.
// TODO: prob. want to do some sort of singleton design pattern idea.

void The_Game::_process(double delta)
{
    runningTime += delta;
    runningTime_noReset += delta;

    if (runningTime > 5.f)
    {
        // do something interesting.
        const char *str = "we rich";        
        double something = 5.1;
        static int d = 3;
//        printf( "%s, %f, %d", str, something, d++ );

        char buffer[256];
        sprintf(buffer, "we rich: %f", runningTime_noReset);
        node->call( "my_print", buffer);


// can we get into a debugger?
        node->call( "my_print", "Jump!" ); 

    jumpPlayer->call("play");

//    playerVelocity += Vector2(0.f, 23.f);;

      runningTime = 0.f;
    }

    if (Engine::get_singleton()->is_editor_hint())
    {
        // do nothing
    }
    else
    {

        static char scoreText[256]; 

        if (scoreLabel)
        {
            sprintf(scoreText, "SCORE: %f", runningTime_noReset);
            scoreLabel->set_text(scoreText);
                }

//        Vector2 newCameraPos = Vector2( runningTime_noReset/10.f+(10.0 * sin(runningTime)), runningTime_noReset/10.f+(10.0 * -cos(runningTime)));


// TODO: E.g. constants like this should be exposed in the editor window.
// we actually already began something like that. how do we continue
// to complete that thing?

        Vector2 newCameraPos = Vector2( 0.f, runningTime_noReset* int32_t(values[CAMERA_SPEED_PROP]) );
    camera->call("set_position", newCameraPos);

	Vector2 new_position = player->get_position() + playerVelocity * delta;

    float speedX = abs(playerVelocity.x);
    float speedY = abs(playerVelocity.y);

    // apply drag.
    playerVelocity.x += 0.1f * speedX * speedX * -sign(playerVelocity.x);
    playerVelocity.y += 0.1f * speedY * speedY * -sign(playerVelocity.y);

    player->set_position(new_position);

//Vector2(10.0 + (10.0 * sin(runningTime * 2.0)), 10.0 + (10.0 * cos(runningTime * 2.0)));

//	player->call("set_position", new_position);//  set_position(new_position);
    }


}

