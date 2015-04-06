package org.broncho.servicecontainer;

import android.widget.Toast;
import android.content.Context;
import android.content.Intent;
import android.content.BroadcastReceiver;

public class BootCompleteReceiver extends BroadcastReceiver 
{
	static final String ACTION = "android.intent.action.BOOT_COMPLETED";

	public void onReceive(Context context, Intent intent)
	{
		if(intent.getAction().equals(ACTION))
		{
			context.startService(new Intent(context, ServiceContainerService.class));
		}
	}
}
