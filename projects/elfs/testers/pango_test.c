#include <stdio.h>
#include <pango/pango.h>

int main(int argc, char* argv[])
{
	const char* font_name = argc == 1? "Sans 12" : argv[1];

	g_type_init();
	PangoFontDescription* font_desc = pango_font_description_from_string (font_name);
 
 	printf("%s %d\n", 
 		pango_font_description_get_family (font_desc), 
 		pango_font_description_get_size (font_desc));


    return 0;
}
