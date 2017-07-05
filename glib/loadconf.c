/******************************************************************************
 *   soloapple   2017年07月03日 00时27分38秒
 *	
 *	 only do some read config test.
 *****************************************************************************/
#include <glib-2.0/glib.h>
#include <locale.h>
#include <stdio.h>

static GKeyFile *
load_config(const char *file)
{
	GError *err = NULL;
	GKeyFile *keyfile;
	keyfile = g_key_file_new();
	g_key_file_set_list_separator(keyfile, ',');

	if (!g_key_file_load_from_file(keyfile, file, 0, &err)) {
		error("Parsing %s failed: %s", file, err->message);
		g_error_free(err);
		g_key_file_free(keyfile);
		return NULL;
	}
	return keyfile;
}

int main(int argc, int **argv)
{
	char *str;
	int val1, val2;
	GError* err = NULL;
	GKeyFile* keyfile;

	keyfile = load_config("main.conf");
	str = g_key_file_get_string(keyfile, "General", "OffMode", &err);

	if (err) {
		printf("%s",err->message);
		g_clear_error(&err);
	}
	val1 = g_key_file_get_integer(keyfile, "General", "PageTimeout", &err);
	if (err) {
		printf("%s",err->message);
		g_clear_error(&err);
	}
	val2 = g_key_file_get_integer(keyfile, "test", "age", &err);
	if (err) {
		printf("%s",err->message);
		g_clear_error(&err);
	}

	printf("offmode = %s\n",str);
	printf("pagetimeout = %d\n",val1);
	printf("age = %d\n",val2);

	return 0;
}
