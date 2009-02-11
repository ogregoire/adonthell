#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include "label.h"
#include "input/input.h"

namespace gui
{
	typedef void (*clickevent)(bool down, void* arg);
	class button:public label
	{
	protected:
		const gfx::surface * imgdown;
		bool clicked;
		clickevent clickit;
		input::keyboard_event::key_type downkey;
		int clickpush;
	public:
		button(const char* upimg, const char* downimg, clickevent c, void* a=NULL, int o=5):label(upimg),imgdown(gfx::surfaces->get_surface_only((downimg))),clicked(false),clickit(c),clickpush(o),arg(a) {centerH(true);centerV(true);}
		~button() {if (imgdown) gfx::surfaces->free_surface(imgdown);}


		virtual void draw(int x, int y, gfx::surface* s);
		virtual bool keyup(input::keyboard_event& k);
		virtual bool keydown(input::keyboard_event&k);
//not till we get a mouse_event class
//		virtual bool mouseup(SDL_MouseButtonEvent & m);
//		virtual bool mousedown(SDL_MouseButtonEvent & m);
		virtual bool focus() {return true;}
		virtual void unfocus() {clicked = false;}

		virtual void activate() {clickit(clicked, arg);}
		//so we can change the argument later
		void* arg;
	};
};


#endif//GUI_LABEL_H
