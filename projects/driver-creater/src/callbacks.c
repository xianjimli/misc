#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "driver_info.h"

void
on_new_activate                        (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget* window = gtk_widget_get_toplevel(GTK_WIDGET(menuitem));
	DriverInfo* info = g_object_get_data(G_OBJECT(window), "driver_info");

	if(info != NULL)
	{
		driver_info_destroy(info);
	}

	info = driver_info_new();
	g_object_set_data(G_OBJECT(window), "driver_info", info);

	return;
}


void
on_open_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_save_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget* window = gtk_widget_get_toplevel(menuitem);
	DriverInfo* info = g_object_get_data(G_OBJECT(window), "driver_info");
	
	if(info != NULL && info->name != NULL)
	{
		driver_info_save(info, info->name);
	}

	return;
}


void
on_save_as_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_exit_activate                       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_menuitem_general_activate           (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	DriverInfo* info = (DriverInfo*)g_object_get_data(G_OBJECT(gtk_widget_get_toplevel(GTK_WIDGET(menuitem))), "driver_info");
	GtkWidget* window = create_window_general();

	g_object_set_data(G_OBJECT(window), "driver_info", info);
	gtk_widget_show(window);

	return;
}


void
on_menuitem_module_parameters_activate (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	DriverInfo* info = (DriverInfo*)g_object_get_data(G_OBJECT(gtk_widget_get_toplevel(GTK_WIDGET(menuitem))), "driver_info");
	GtkWidget* window = create_window_module_parameters();

	g_object_set_data(G_OBJECT(window), "driver_info", info);
	gtk_widget_show(window);

	return;
}


void
on_about1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}

#define GET_ENTRY_TEXT(window, name) g_strdup(gtk_entry_get_text((GtkEntry*)lookup_widget(window, name)))
void
window_general_on_button_ok_clicked    (gpointer user_data, GtkButton       *button)
{
	DriverInfo* info = (DriverInfo*)g_object_get_data(G_OBJECT(user_data), "driver_info");
	GtkWidget* window = GTK_WIDGET(user_data);
	if(info != NULL)
	{
		SET_STR(info->name, GET_ENTRY_TEXT(window, "entry_module"));
		SET_STR(info->author, GET_ENTRY_TEXT(window, "entry_author"));
		SET_STR(info->email, GET_ENTRY_TEXT(window, "entry_email"));
		SET_STR(info->description, GET_ENTRY_TEXT(window, "entry_description"));
		SET_STR(info->license, GET_ENTRY_TEXT(window, "entry_license"));
	}

	gtk_widget_destroy(window);

	return;
}


void
window_general_on_button_cancel_clicked(gpointer user_data, GtkButton *button)
{
	GtkWidget* window = GTK_WIDGET(user_data);
	gtk_widget_destroy(window);

	return;
}

