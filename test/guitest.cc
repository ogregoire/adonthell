#include <iostream>
#include <sstream>
#include <string>
using std::string;
#include "base/base.h"
#include "gfx/gfx.h"
#include "input/input.h"
#include "gui/gui.h"
#include "main/adonthell.h"
#include "gui/draw.h"

class InputHandler {
private:
public:
  
  bool letsexit ;
  gui::base* widgetbase;
  
  InputHandler (gui::widget* wb = NULL) : letsexit (false), widgetbase(wb) {};
  
  bool handle_keys (input::keyboard_event *ev) {
    // On escape, the global variable letsexit will be set to 1
    if (ev->key() == input::keyboard_event::ESCAPE_KEY) {
      letsexit = true;
      std::cout << "Escape pressed, leaving..." << std::endl;
      return true;
    } else if (ev->type() == input::keyboard_event::KEY_PUSHED) {
		if (widgetbase) widgetbase->keydown(*ev);
	} else if (ev->type() == input::keyboard_event::KEY_RELEASED) {
		if (widgetbase) widgetbase->keyup(*ev);
	}
    return false;
  }
};


class GuiTest : public adonthell::app {
  static void changelabel(bool down, void* arg) {
    gui::label* l = (gui::label*)arg;
	std::stringstream s; 
	static int count = 0;
	count++;
	s << "Click " << count;
	l->setString(s.str());
  }
  static void print(bool down, void* arg) {
    char* s = (char*) arg;
	std::cout << s << ":" << (down?"down":"up") << "\n";
  }
  int main () {
    
    InputHandler ih;
    
    // Initialize the gfx and input systems
    init_modules (GFX | INPUT);
    
    // Set us a nice window
	gfx::screen::set_fullscreen(false);
    gfx::screen::set_video_mode(512,512);
    
    // Create our input_listener and connect the callback
    // to handle keyboard events
    input::listener il;
    il.connect_keyboard_function(base::make_functor_ret(ih, &InputHandler::handle_keys));
    input::manager::add (&il);
    
    /*************************************************************************/
    /*************************************************************************/
    /*************************************************************************/
    /*************************************************************************/
    /*************************************************************************/
    /*************************************************************************/
	//find the images we need
	string testbg1 = "data/gfx/gui/testbg1.png";
	base::Paths.find_in_path(testbg1);
	string testbuttondown = "data/gfx/gui/testbuttondown.png";
	base::Paths.find_in_path(testbuttondown);
	string testbuttonup = "data/gfx/gui/testbuttonup.png";
	base::Paths.find_in_path(testbuttonup);

	gui::font f;
	gui::label l(200, 30);
	l.setString("This is a Label");
	gui::label label_with_bg(testbg1.c_str());
	label_with_bg.setString("Is this readable?");

	gui::button b(testbuttonup.c_str(), testbuttondown.c_str(), changelabel, &l, 2);
	b.setString("Click Me");
	gui::button b2(testbuttonup.c_str(), testbuttondown.c_str(), print, (void*)"button 2", 1);
	b2.setString("Button 2");
	gui::button b3(testbuttonup.c_str(), testbuttondown.c_str(), print, (void*)"button 3", 1);
	b3.setString("Button 3");
	gui::option o1(testbuttonup.c_str(), testbuttondown.c_str(), print, (void*)"option 1", 1);
	o1.setString("Option 1");

	gui::textbox t1(400, 30);
	
		
	/* arrange them in a freeform layout object */
	gui::layout widgets;
	widgets.addchild( b, 10, 10);
	widgets.addchild(b2, 10, 50);
	widgets.addchild(b3, 10, 90);
	widgets.addchild(o1, 10,130);
	widgets.addchild(t1, 10,170);
	widgets.focus();

	ih.widgetbase = &widgets;
    /*************************************************************************/
    /*************************************************************************/
    /*************************************************************************/
    /*************************************************************************/
    /*************************************************************************/
    /*************************************************************************/

    // Run this loop until letsexit is set to 1 by the
    // callback function. Every time a key event is raised,
    // the input manager will send it to the listeners it handles
    // (that is, only the one we've connected) which will call the
    // callback function that has been connected to handle keyboard events.
	gfx::surface * screen = gfx::screen::get_surface();
    while (!ih.letsexit) {
      ::base::Timer.update ();
      ::input::manager::update();
	  	
		screen->fillrect(0, 0, screen->length(), screen->height(), 0);
		f.render("Hello World", -10, 5, screen);
		f.render("Hello World", -10, 520, screen);
		f.render("Hello World", 470, 520, screen);
		f.render("Hello World", 470, 5, screen);
      	l.draw(10, 50, screen);
		label_with_bg.draw(10, 80, screen);
		widgets.draw(10, 120, screen);

		u_int32 c = 0xff0000b0;
		gui::box(345, 5, 30, 50, c, screen);
		gui::border(340, 5, 40, 55, screen);
		gui::vertLine(350, 10, 50, c, screen);
		gui::vertLine(351, 10, 50, c, screen);
		gui::vertLine(352, 10, 50, c, screen);
		gui::vertLine(353, 10, 50, c, screen);
		gui::vertLine(354, 10, 50, c, screen);
		gui::vertLine(355, 10, 50, c, screen);
		gui::vertLine(356, 10, 50, c, screen);
		gui::vertLine(357, 10, 50, c, screen);
		gui::vertLine(358, 10, 50, c, screen);
		gui::vertLine(359, 10, 50, c, screen);
		gui::vertLine(360, 10, 50, c, screen);
		gui::vertLine(361, 10, 50, c, screen);
		gui::vertLine(362, 10, 50, c, screen);
		gui::vertLine(363, 10, 50, c, screen);
		gui::vertLine(364, 10, 50, c, screen);
		gui::vertLine(365, 10, 50, c, screen);
		gui::vertLine(366, 10, 50, c, screen);
		gui::vertLine(367, 10, 50, c, screen);
		gui::vertLine(368, 10, 50, c, screen);
		gui::vertLine(369, 10, 50, c, screen);

		gfx::screen::update ();
    }
    
    // Do some cleanup, and we're ready to exit!

    return 0;
  }
} theApp;
