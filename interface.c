#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "interface.h"


static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    /* If you return FALSE in the "delete-event" signal handler,
     * GTK will emit the "destroy" signal. Returning TRUE means
     * you don't want the window to be destroyed.
     * This is useful for popping up 'are you sure you want to quit?'
     * type dialogs. */

    g_print ("delete event occurred\n");

    /* Change TRUE to FALSE and the main window will be destroyed with
     * a "delete-event". */

    return FALSE;
}

/* Another callback */
static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
}

static void button_test (){
	g_print("Test button clicked");
}

/* Get the selected filename and print it to the console */
static void file_ok_sel( GtkWidget        *w,
                         GtkFileSelection *fs )
{
	char filename[400];

    g_print ("%s\n", gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs)));


    strcpy( filename, gtk_file_selection_get_filename(GTK_FILE_SELECTION(fs)));

    printf("%s\n", filename );

}



void call_interface() {
	

	GtkWidget *window;
	GtkWidget *button;
    GtkWidget *filew;
    
 	gtk_init (NULL, NULL);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

    /*Close Events */
    g_signal_connect (window, "delete-event", G_CALLBACK (delete_event), NULL);
    g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);
    
    /*Size of the window*/
    gtk_container_set_border_width (GTK_CONTAINER (window), 250);


	/* Button */
    button = gtk_button_new_with_label ("Hello World");
    g_signal_connect (button, "clicked", G_CALLBACK (button_test), NULL);


    /*Select a file*/
    filew = gtk_file_selection_new ("File selection");
    /* Connect the ok_button to file_ok_sel function */
    g_signal_connect (GTK_FILE_SELECTION (filew)->ok_button,
		      "clicked", G_CALLBACK (file_ok_sel), (gpointer) filew);
    
    /* Connect the cancel_button to destroy the widget */
    g_signal_connect_swapped (GTK_FILE_SELECTION (filew)->cancel_button,
	                      "clicked", G_CALLBACK (gtk_widget_destroy),
			      filew);
    
    /* Lets set the filename, as if this were a save dialog, and we are giving
     a default filename */
    gtk_file_selection_set_filename (GTK_FILE_SELECTION(filew), 
				     "penguin.png");
    
    gtk_widget_show (filew);


    /*Add the button to window*/
    gtk_container_add (GTK_CONTAINER (window), button);
    gtk_widget_show (button);

    gtk_widget_show  (window);
    
    gtk_main ();

}