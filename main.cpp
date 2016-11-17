#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <iostream>

void draw(bool** change, bool** state);
void setState(bool** &change, bool** &state);

int main(int argc, char** argv) {

	//----INIT----

	bool isStarted = false;
	bool** change = new bool*[1920 / 2];
	bool** state = new bool*[1920 / 2];

	for (int n = 0; n < 1920 / 2; n++) {
		change[n] = new bool[1080 / 2];
		state[n] = new bool[1080 / 2];
		for (int m = 0; m < 1080 / 2; m++) {
			change[n][m] = false;
			state[n][m] = false;
		}
	}

	if (!al_init_primitives_addon())
		al_show_native_message_box(al_create_display(400,500),"Warning!","Initialization error!","Couldnt initialize primitives addon.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	al_init();
	al_install_keyboard();
	al_install_mouse();

	ALLEGRO_TIMER* timer = al_create_timer(1.0/60);//FPS
	ALLEGRO_KEYBOARD_STATE keyb;
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	ALLEGRO_EVENT event;
	ALLEGRO_DISPLAY* window = al_create_display(1920,1080);
	al_set_window_title(window, "Game of Life Conoway Edition");
	al_get_keyboard_state(&keyb);//set state to false(otherwise it will instantly close)
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(window));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	//----Main loop of the game----

	while (!al_key_down(&keyb, ALLEGRO_KEY_ESCAPE)) {
		al_get_keyboard_state(&keyb);
		al_clear_to_color(al_map_rgb(0,0,0));
		al_get_next_event(queue, &event);

		if (al_key_down(&keyb, ALLEGRO_KEY_SPACE))
			isStarted = true; //start
		
		if (!isStarted && event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && event.mouse.button == 1) { 
			state[event.mouse.x/2][event.mouse.y/2] = true;
		}

		setState(change,state);
		draw(change, state);
		
		al_flip_display();
	}

	//----Cleanup----
	al_destroy_display(window);
	al_shutdown_primitives_addon();

	return 0;
}

void draw(bool** change, bool** state) {

	for (int n = 0; n < 1920 / 2; n++) {
		for (int m = 0; m < 1080 / 2; m++) {
			if (state[n][m])
				al_draw_filled_rectangle(n*2,m*2,n*2+2,m*2+2,al_map_rgb(255,255,255));
		}
	}
}

void setState(bool** &change, bool** &state) {
	/*for (int n = 0; n < 1920 / 2; n++) {
		for (int m = 0; m < 1080 / 2; m++) {

		}
	}*/
}