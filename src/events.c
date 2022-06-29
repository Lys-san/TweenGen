#include "events.h"

State initState() {
	State new;
	new.onionSkin = 1;
	new.editMode = 1;

	return new;
}

int hasSelectedPoint(int xMouse, int yMouse, Armature armature, CtrlPoint *point) {
	int i;

	for (i = 0; i < armature.nPoints; i++) {
		if (xMouse > armature.points[i].x - CTRL_POINT_RADIUS
			&& xMouse < armature.points[i].x + CTRL_POINT_RADIUS
			&& yMouse > armature.points[i].y - CTRL_POINT_RADIUS
			&& yMouse < armature.points[i].y + CTRL_POINT_RADIUS) {
			
			*point = armature.points[i];
			return 1;
		}
	}
	return 0;
}


int getAndApplyEvent(unsigned int windowWidth, unsigned int windowHeight, FrameSeq *frame, State *s) {

	MLV_Keyboard_button sym   = MLV_KEYBOARD_NONE;
	MLV_Keyboard_modifier mod = MLV_KEYBOARD_KMOD_NONE;
	MLV_Input_box *input_box  = NULL;
	char* texte               = NULL;
	MLV_Button_state state;
	int x, y;

	int workspace_x = MARGIN_RATIO * windowWidth;
	int workspace_y = MENU_RATIO * windowHeight;

	CtrlPoint selectedPoint;

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
						onionSkin(*frame, s->onionSkin);
						drawArmature((*frame)->armature, CRT_FRAME, 255);
						return 1;

					/* NEXT FRAME */
					case MLV_KEYBOARD_RIGHT :
						goToFrame((*frame)->index + 1, frame);
						drawFrame(*frame, windowWidth, windowHeight);
						onionSkin(*frame, s->onionSkin);
						drawArmature((*frame)->armature, CRT_FRAME, 255);

						return 1;

					/* NEW FRAME (for tests & debug) */
					case MLV_KEYBOARD_n :
						printf("Adding a new frame...\n");
						FrameSeq new = createEmptyFrame();
						insertFrameHere(new, frame);
						drawFrame(*frame, windowWidth, windowHeight);
						printf("New frame successfully added !\n");

						return 1;

					/* GENERATE INBETWEENS (interpolation) */
					case MLV_KEYBOARD_SPACE :
						printf("Generating inbetweens...\n");
						interpolateSeq(frame, &INTERPOL_FUNC);
						printf("Inbetweeens generated !\n");
						printFrameSeq(*frame);
						drawFrame(*frame, windowWidth, windowHeight);
						drawArmature((*frame)->armature, CRT_FRAME, 255);

						return 1;

					/* GENERATE INBETWEENS from bones (interpolation) */
					case MLV_KEYBOARD_b :
						printf("Generating inbetweens...\n");
						interpolateSeqFromBones(frame, &boneInterpol);
						printf("Inbetweeens generated !\n");
						printFrameSeq(*frame);
						drawFrame(*frame, windowWidth, windowHeight);
						drawArmature((*frame)->armature, CRT_FRAME, 255);

						return 1;
					/* AVERAGE SEQUENCE */
					case MLV_KEYBOARD_t :
						printf("Generating inbetweens...\n");
						averageSeq(frame);
						printf("Inbetweeens generated !\n");
						printFrameSeq(*frame);
						drawFrame(*frame, windowWidth, windowHeight);
						drawArmature((*frame)->armature, CRT_FRAME, 255);

						return 1;

					/* ONION SKIN */
					case MLV_KEYBOARD_o :
						s->onionSkin++;
						s->onionSkin %= MAX_ONIONSKIN_LEVEL;
						/* upadting display */
						drawFrame(*frame, windowWidth, windowHeight);

						onionSkin(*frame, s->onionSkin);
						drawArmature((*frame)->armature, CRT_FRAME, 255);
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
						if (s->editMode) {
							if (hasSelectedPoint(x, y, (*frame)->armature, &selectedPoint)) {
								printf("[DEBUG] Clicked on a point\n");
								drawPointSelection(selectedPoint); /* highlighting selected point */
								MLV_actualise_window();
								CtrlPoint otherSelectedPoint;

								/* wait until end of edit */
								while(1) {
									MLV_wait_mouse(&x, &y);

									/* didn't clicked on a point : updating point position */
									if (!hasSelectedPoint(x, y, (*frame)->armature, &otherSelectedPoint)) {
										printf("Updating position.\n");
										printCtrlPoint((*frame)->armature.points[isContained((*frame)->armature, selectedPoint)]);
										/*updatePointWithNewCoords(&selectedPoint, x, y);*/
										updatePointWithNewCoords(&((*frame)->armature.points[isContained((*frame)->armature, selectedPoint)]), x, y);
										
										drawFrame(*frame, windowWidth, windowHeight);
										drawArmature((*frame)->armature, CRT_FRAME, 255);

										return 1;
									}
									/* clicked on another point */
									else {
										/* cancel selection */
										if(areSamePoints(selectedPoint, otherSelectedPoint)) {
											drawCtrlPoint(selectedPoint, CRT_FRAME, 255);
											MLV_actualise_window();
											printf("Cancelled selection.\n");
											return 0;
										}

										/* connect points */
										if((*frame)->armature.nPoints > 1) {											
											Bone newBone = createBone(selectedPoint, otherSelectedPoint);
											addBoneToArmature(&((*frame)->armature), newBone);

											drawBone(newBone, CRT_FRAME, 255);
											drawCtrlPoint(selectedPoint, CRT_FRAME, 255);

											printf("(Info) Connected points successfully.\n");
											printf("[DEBUG] Armature has now %d bones.\n", (*frame)->armature.nBones);
											return 1;
										}
									}

								}

								
							}
							else {
								CtrlPoint new = createCtrlPoint("new point", x, y);
								addCtrlPointToArmature(&((*frame)->armature), new);
								printArmature((*frame)->armature);
								/* we just have to draw the new point */
								drawCtrlPoint(new, CRT_FRAME, 255);
								return 1;
							}

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