all:
	gcc -g show_inputdev_info.c -o show_inputdev_info_test
	gcc -g uinput.c -DHAS_LINUX_UINPUT_H -DUINPUT_TEST -o uinput_test
	gcc -g dump_inputdev.c -o  dump_inputdev_test
clean:
	rm -f *test
