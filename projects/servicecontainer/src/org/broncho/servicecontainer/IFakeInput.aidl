package  org.broncho.servicecontainer;

interface IFakeInput
{
	boolean mouseEvent(int type, int x, int y);
	boolean keyEvent(int type, int code);
}
