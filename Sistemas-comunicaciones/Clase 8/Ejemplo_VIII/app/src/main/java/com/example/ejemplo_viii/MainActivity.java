package com.example.ejemplo_viii;

import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.viewmodel.CreationExtras;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.widget.EditText;

import java.util.List;

public class MainActivity extends AppCompatActivity implements SensorEventListener {
    EditText Tx1, Tx2, Tx3, Tx4, Tx5, Tx6;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Tx1=(EditText) findViewById(R.id.editTextText);
        Tx2=(EditText) findViewById(R.id.editTextText2);
        Tx3=(EditText) findViewById(R.id.editTextText3);
        Tx4=(EditText) findViewById(R.id.editTextText4);
        Tx5=(EditText) findViewById(R.id.editTextText5);
        Tx6=(EditText) findViewById(R.id.editTextText6);
        SensorManager Administrador = (SensorManager) getSystemService(SENSOR_SERVICE);

        //Activación de los oyentes del sensor
        List Listasensores = Administrador.getSensorList(Sensor.TYPE_GYROSCOPE);
        if(!Listasensores.isEmpty()){
            Sensor orientacion = (Sensor) Listasensores.get(0);
            Administrador.registerListener(this,orientacion,SensorManager.SENSOR_DELAY_UI);
        }

        Listasensores = Administrador.getSensorList(Sensor.TYPE_ACCELEROMETER);
        if(!Listasensores.isEmpty()){
            Sensor acelerometro = (Sensor) Listasensores.get(0);
            Administrador.registerListener(this,acelerometro,SensorManager.SENSOR_DELAY_UI);
        }
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        switch(event.sensor.getType()){
            case Sensor.TYPE_ACCELEROMETER:
                Tx1.setText("X: "+ event.values[0]);
                Tx2.setText("Y: "+ event.values[1]);
                Tx3.setText("Z: "+ event.values[2]);
                break;
            case Sensor.TYPE_GYROSCOPE:
                Tx4.setText("X: "+ event.values[0]);
                Tx5.setText("Y: "+ event.values[1]);
                Tx6.setText("Z: "+ event.values[2]);
                break;
            default:
                Tx1.setText("X: 0");
                Tx2.setText("Y: 0");
                Tx3.setText("Z: 0");
                Tx4.setText("X: 0");
                Tx5.setText("Y: 0");
                Tx6.setText("Z: 0");
                break;
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }
}