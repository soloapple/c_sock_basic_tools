glib:
	gcc glib.c -o myglib `pkg-config --cflags --libs glib-2.0 gthread-2.0`	
	gcc GOptionContext.c -o context `pkg-config --cflags --libs glib-2.0 gthread-2.0`	
	gcc loadconf.c -o loadconf `pkg-config --cflags --libs glib-2.0 gthread-2.0`	

clean:
	rm -rf a.out myglib
