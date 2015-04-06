#include <trace.h>

static void irq_real_dispach(void)
{
	return;
}

void irq_dispach(void)
{
	os_trace(__func__, __LINE__, "irq enter");
	irq_real_dispach();
	os_trace(__func__, __LINE__, "irq leave");

	return;
}

void firq_dispatch(void)
{
	os_trace(__func__, __LINE__, "irq enter");
	irq_real_dispach();
	os_trace(__func__, __LINE__, "irq leave");
	
	return;
}
