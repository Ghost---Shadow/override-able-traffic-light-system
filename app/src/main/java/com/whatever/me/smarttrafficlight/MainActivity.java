package com.whatever.me.smarttrafficlight;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.ParcelUuid;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.reflect.InvocationTargetException;
import java.util.Set;

public class MainActivity extends AppCompatActivity {

    private EditText etPassword;
    private Button bToggle;
    private TextView tvLog;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        etPassword = (EditText) findViewById(R.id.etPassword);
        bToggle = (Button) findViewById(R.id.bToggle);
        tvLog = (TextView)findViewById(R.id.tvLog);

        bToggle.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String passwordString = etPassword.getText().toString();
                sendStringOverBt(passwordString);
            }
        });
    }

    private void sendStringOverBt(String str){
        OutputStream outputStream;
        //InputStream inStream;
        BluetoothAdapter blueAdapter = BluetoothAdapter.getDefaultAdapter();
        if (blueAdapter != null) {
            if (blueAdapter.isEnabled()) {
                Set<BluetoothDevice> bondedDevices = blueAdapter.getBondedDevices();
                try {
                    if (bondedDevices.size() > 0) {
                        Object[] devices = bondedDevices.toArray();
                        BluetoothDevice device = (BluetoothDevice) devices[0];
                        ParcelUuid[] uuids = device.getUuids();
                        Log.i("info",device.getName());
                        BluetoothSocket socket = null;
                        try {
                            socket = device.createRfcommSocketToServiceRecord(uuids[0].getUuid());
                            socket.connect();
                        }catch (IOException e){
                            try {
                                Log.i("error","Using alternative");
                                socket = (BluetoothSocket) device.getClass().getMethod("createRfcommSocket", new Class[]{int.class}).invoke(device, 1);
                                socket.connect();
                            } catch (NoSuchMethodException e1) {
                                e1.printStackTrace();
                            } catch (IllegalAccessException e1) {
                                e1.printStackTrace();
                            } catch (InvocationTargetException e1) {
                                e1.printStackTrace();
                            }
                        }
                        //BluetoothSocket socket =(BluetoothSocket) device.getClass().getMethod("createRfcommSocket", new Class[] {int.class}).invoke(device,1);
                        //BluetoothSocket socket = device.createInsecureRfcommSocketToServiceRecord(uuids[0].getUuid());
                        if(socket == null)
                            throw new IOException();

                        outputStream = socket.getOutputStream();
                        //inStream = socket.getInputStream();
                        outputStream.write(str.getBytes());
                        outputStream.close();
                        socket.close();
                        tvLog.setText(R.string.MessageSent);
                    } else {
                        Log.e("error", "No appropriate paired devices.");
                        tvLog.setText(R.string.NoPairedDeviceError);
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                    tvLog.setText(R.string.IOExceptionLog);
                }


            } else {
                Log.e("error", "Bluetooth is disabled.");
                tvLog.setText(R.string.BtDisabledError);
            }
        }
    }
}
