/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: GoptionContext.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年07月02日 12时58分30秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年07月02日                  build this moudle  
 *****************************************************************************/
#include <glib-2.0/glib.h>
#include <locale.h>

#define GETTEXT_PACKAGE "test"

static gint repeats = 2;  
static gint max_size = 8;  
static gboolean verbose = FALSE;  
static gboolean beep = FALSE;  
static gboolean xrand = FALSE;  
static gchar *string;  

static GOptionEntry entries[] =  
{  
	{ "repeats", 'r', 0, G_OPTION_ARG_INT, &repeats, "Average over N repetitions", "N" },  
	{ "max-size", 'm', 0, G_OPTION_ARG_INT, &max_size, "Test up to 2^M items", "M" },  
	{ "verbose", 'v', 0, G_OPTION_ARG_NONE, &verbose, "Be verbose", NULL },  
	{ "beep", 'b', 0, G_OPTION_ARG_NONE, &beep, "Beep when done", NULL },  
	{ "xrand", 0, 0, G_OPTION_ARG_NONE, &xrand, "xrandomize the data", NULL },  
	{ "str_test", 's', 0, G_OPTION_ARG_STRING, &string, "test the stirng", NULL},  
	{ NULL }  
};  
	
int  
main (int argc, char *argv[])  
{  
	GError *error = NULL;  
	GOptionContext *context;  
	context = g_option_context_new ("- test tree model performance");  
	g_option_context_add_main_entries (context, entries, GETTEXT_PACKAGE);  
//	 g_option_context_add_group (context, gtk_get_option_group (TRUE));  
	if (!g_option_context_parse (context, &argc, &argv, &error))  
	{  
		g_print ("option parsing failed: %s/n", error->message);  
		return 0;
	}  
	g_option_context_free(context);
}  
