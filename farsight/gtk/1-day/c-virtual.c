#include <stdio.h>
#include <stdlib.h>

struct _Printer;
typedef struct _Printer Printer;

typedef void (*PrinterPrintFunc)(Printer* thiz, const char* str);
typedef void (*PrinterDestroyFunc)(Printer* thiz);

struct _Printer
{
	PrinterPrintFunc print;
	PrinterDestroyFunc destroy;
};

/////////////////////////////////////////////
typedef struct _ConsolePrinter
{
	Printer parent;
}ConsolePrinter;

static void console_printer_print(Printer* thiz, const char* str)
{
	printf("%s", str);

	return ;
}

static void console_printer_destroy(Printer* thiz)
{
	free(thiz);

	return;
}

Printer* console_printer_create(void)
{
	ConsolePrinter* thiz = (ConsolePrinter*)calloc(1, sizeof(ConsolePrinter));

	thiz->parent.print = console_printer_print;
	thiz->parent.destroy = console_printer_destroy;

	return (Printer*)thiz;
}

/////////////////////////////////////////////
typedef struct _FilePrinter
{
	Printer parent;
	FILE* fp;
}FilePrinter;

static void file_printer_print(Printer* thiz, const char* str)
{
	FilePrinter* printer = (FilePrinter*)thiz;

	fprintf(printer->fp, "%s", str);

	return ;
}

static void file_printer_destroy(Printer* thiz)
{
	FilePrinter* printer = (FilePrinter*)thiz;
	fclose(printer->fp);

	free(thiz);

	return;
}

Printer* file_printer_create(const char* filename)
{
	FILE* fp = NULL;
	FilePrinter* thiz = NULL;

	if((fp = fopen(filename, "wb+")) == NULL)
	{
		return NULL;
	}

	thiz = (FilePrinter*)calloc(1, sizeof(FilePrinter));
	thiz->parent.print = file_printer_print;
	thiz->parent.destroy = file_printer_destroy;
	thiz->fp = fp;

	return (Printer*)thiz;
}

int main(int argc, char* argv[])
{
	Printer* printer = NULL;
	Printer* console_printer = console_printer_create();
	Printer* file_printer = file_printer_create("./log.txt");

	printer = console_printer;
	printer->print(printer, "hello world!\n");
	printer->destroy(printer);

	printer = file_printer;
	printer->print(printer, "hello world!\n");
	printer->destroy(printer);

	return 0;
}
