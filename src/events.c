#include "events.h"

int getAndApplyEvent(unsigned int windowWidth, unsigned int windowHeight, FrameSeq *frame) {

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
					/* QUIT */
					case MLV_KEYBOARD_ESCAPE :
						return -1;

					/* PREV FRAME */
					case MLV_KEYBOARD_LEFT :
						goToFrame((*frame)->index - 1, frame);
						drawFrame(*frame, windowWidth, windowHeight);
							drawArmature((*frame)->armature, CRT_FRAME);

						return 1;

					/* NEXT FRAME */
					case MLV_KEYBOARD_RIGHT :
						goToFrame((*frame)->index + 1, frame);
						drawFrame(*frame, windowWidth, windowHeight);
						drawArmature((*frame)->armature, CRT_FRAME);

						return 1;

					/* SAVE */
					case MLV_KEYBOARD_s :
						return 1;

					default :
						break;
				}
			}

		/* mouse event */
		case MLV_MOUSE_BUTTON :
			if(state == MLV_PRESSED) {
				/* MENU */
				if(y < workspace_y)
					return 1;

				/* TOOLBAR */
				else {
					if(x < workspace_x)
						return 1;

					/* WORKSPACE */
					else {
						if (EDIT_MODE) {
							CtrlPoint new = createCtrlPoint("a", x, y);
							addCtrlPointToArmature(&((*frame)->armature), new);
							printArmature((*frame)->armature);
							/* we just have to draw the new point */
							drawCtrlPoint(new, CRT_FRAME);
							return 1;
						}
					}
				}
			}
			break;

		/* no event */
		case MLV_NONE :
			return 0;

		default :
			return 0;
	}
	return 0;
}