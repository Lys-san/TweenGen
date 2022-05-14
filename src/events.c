#include "events.h"

Event getEvent(unsigned int windowWidth, unsigned int windowHeight) {

    MLV_Keyboard_button sym   = MLV_KEYBOARD_NONE;
    MLV_Keyboard_modifier mod = MLV_KEYBOARD_KMOD_NONE;
    MLV_Input_box *input_box  = NULL;
    char* texte               = NULL;
    MLV_Button_state state;
    int x, y;

    int workspace_x = MARGIN_RATIO * windowWidth;
	int workspace_y = MENU_RATIO * windowHeight;

    /* getting the event */
    MLV_Event ev = MLV_get_event( 
            &sym, &mod, NULL,
            &texte, &input_box,
            &x, &y, NULL,
            &state
    );

    /* checking the event */
    switch( ev ) {
    	/* keyboard event */
    	case MLV_KEY :
    		if(state == MLV_PRESSED) {
    			switch( sym ) {

    				case MLV_KEYBOARD_ESCAPE :
    					return QUIT;

    				case MLV_KEYBOARD_LEFT :
    					return PREV_FRAME;

    				case MLV_KEYBOARD_RIGHT :
    					return NEXT_FRAME;

    				case MLV_KEYBOARD_s :
    					return SAVE;

    				default :
    					break;
    			}
    		}

    	/* mouse event */
    	case MLV_MOUSE_BUTTON :
    		if(state == MLV_PRESSED) {
    			/* menu */
                if(y < workspace_y)
                    return MENU;

                /* toolbar */
                if(x < workspace_x)
                	return TOOLBAR;
    		}
            break;

    	/* no event */
    	case MLV_NONE :
    		return NONE;

    	default :
    		return NONE;
    }
    return NONE;
}

int doAction(Event ev, FrameSeq *frame, unsigned int windowWidth, unsigned int windowHeight) {
    switch( ev ) {

        case TOOLBAR :
            return 1;

        case MENU :
            return 1;

        case NEXT_FRAME:
        	goToFrame((*frame)->index + 1, frame);
        	drawFrame(*frame, windowWidth, windowHeight);
        	return 1;

        case PREV_FRAME:
        	goToFrame((*frame)->index - 1, frame);
        	drawFrame(*frame, windowWidth, windowHeight);
        	return 1;

        case QUIT :
            return -1;

        default :
            return 0;
    }
}