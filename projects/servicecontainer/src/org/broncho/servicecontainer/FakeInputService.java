package org.broncho.servicecontainer;

class FakeInputService extends IFakeInput.Stub
{
	static public final String NAME="FakeInputService";

	public boolean mouseEvent(int type, int x, int y) throws android.os.RemoteException
	{
		return true;	
	}

	public boolean keyEvent(int type, int code) throws android.os.RemoteException
	{
		return true;
	}
}
