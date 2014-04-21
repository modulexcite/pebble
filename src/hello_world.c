#include <pebble.h>

Window *window;
TextLayer *text_layer;
TextLayer *date_layer;
TextLayer *bruno_layer;
InverterLayer *inverter_layer;

void handle_timechanges(struct tm *tick_time, TimeUnits units_changed){
  static char time_buffer[10];
  static char date_buffer[10];

  // format and display time
  strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", tick_time);
  text_layer_set_text(text_layer, time_buffer);

  // format and display date
  strftime(date_buffer, sizeof(date_buffer), "%b %e", tick_time);
  text_layer_set_text(date_layer, date_buffer);
}

void handle_init(void) {
	// Create a window and text layer
	window = window_create();
	text_layer = text_layer_create(GRect(0, 0, 144, 154));
	
	// Set the text, font, and text alignment
	text_layer_set_text(text_layer, "Hi, I'm El Bruno!");
	text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
	
	// Add the text layer to the window
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));

  // add layer for date at the bottom with 1/3 total size of the watch
  //date_layer = text_layer_create(GRect(x, y, width, height));
  date_layer = text_layer_create(GRect(0, 112, 144, 56));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(date_layer));
	text_layer_set_text_alignment(date_layer, GTextAlignmentCenter);
  text_layer_set_font(date_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT));
	tick_timer_service_subscribe(SECOND_UNIT, handle_timechanges);
  
  // init inverter layer for the date at the bottom
  inverter_layer = inverter_layer_create(GRect(0, 112, 144, 56));
	layer_add_child(window_get_root_layer(window), inverter_layer_get_layer(inverter_layer));

  // add bruno layer for middle title with 1/3 total size of the watch
  bruno_layer = text_layer_create(GRect(0, 56, 144, 56));
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(bruno_layer));
	text_layer_set_text_alignment(bruno_layer, GTextAlignmentCenter);
  text_layer_set_font(bruno_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text(bruno_layer, "El Bruno");
	  
	// Push the window
	window_stack_push(window, true);
	
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Hi Log from el Bruno!");
}

void handle_deinit(void) {
	// Destroy the text layer
	text_layer_destroy(text_layer);
	text_layer_destroy(date_layer);
	
  // destroy the inverter layer
  inverter_layer_destroy(inverter_layer);
  
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}
