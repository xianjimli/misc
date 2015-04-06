package org.broncho.servicecontainer;

import android.app.Service;
import java.lang.Thread;
import java.lang.Runnable;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;
import java.lang.System;
import android.os.ServiceManager;

public class ServiceContainerService extends Service
{
	static final String TAG="ServiceContainerService";

	@Override
	public IBinder onBind(Intent intent) {
		return null;
	}

	@Override
	public void onCreate() 
	{
		super.onCreate();
		ServiceManager.addService(FakeInputService.NAME, new FakeInputService());

		return;
	}

	@Override
	public void onDestroy() 
	{
		super.onDestroy();
	}

};
