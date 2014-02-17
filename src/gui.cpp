#include "gui.hpp"

/* Initialize GTK.
 */
void initGuiWindow(const char* name) {
  GtkBuilder *builder;
  GtkWidget *window;

  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, name, (GError**)NULL);
  window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
  gtk_builder_connect_signals (builder, NULL);
  
  gtk_widget_show(window);
}

/* Initializes the glade gui.
   input:
   argc: number of string items in argv.
   argv: command line arguments as a string array.
*/
void guiInit(int *argc, char** argv) {
  gtk_init(argc, &argv);
}

/* Calls a single GTK main loop iteration to process 
 * events (non-blocking).
 */
void guiMainIteration(void) {
  gtk_main_iteration_do(0);
}