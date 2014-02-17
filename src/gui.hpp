#ifndef GUI_HPP
#define GUI_HPP

#include <stdlib.h>
#include <gtk/gtk.h>


/* Initialize GTK.
 */
extern void initGuiWindow(const char*);

/* Initializes the glade gui.
   input:
      argc: number of string items in argv.
      argv: command line arguments as a string array.
 */
extern void guiInit(int *, char**);

/* Calls a single GTK main loop iteration to process 
 * events (non-blocking).
 */
extern void guiMainIteration(void);


#endif  /* MATRIX_HPP */