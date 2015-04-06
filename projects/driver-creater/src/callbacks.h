#include <gtk/gtk.h>


void
on_new_activate                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_open_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_save_as_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_exit_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_menuitem_general_activate           (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_menuitem_module_parameters_activate (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_about1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
window_general_on_button_ok_clicked    (gpointer user_data, GtkButton       *button);

void
window_general_on_button_cancel_clicked(gpointer user_data, GtkButton       *button);
