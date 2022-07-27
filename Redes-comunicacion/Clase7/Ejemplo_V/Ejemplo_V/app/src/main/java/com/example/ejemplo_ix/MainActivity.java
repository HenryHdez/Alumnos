package com.example.ejemplo_ix;

import androidx.appcompat.app.AppCompatActivity;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.widget.TextView;

import java.util.List;

public class MainActivity extends AppCompatActivity implements
        SensorEventListener {
    TextView Tx1;
    TextView Tx2;
    TextView Tx3;
    TextView Tx4;
    TextView Tx5;
    TextView Tx6;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Tx1=(TextView)findViewById(R.id.textView);
        Tx2=(TextView)findViewById(R.id.textView2);
        Tx3=(TextView)findViewById(R.id.textView3);
        Tx4=(TextView)findViewById(R.id.textView10);
        Tx5=(TextView)findViewById(R.id.textView11);
        Tx6=(TextView)findViewById(R.id.textView12);
        //Inicialice el servicio para determinar la disponibilidad de los sensores
        SensorManager sensorAdmin = (SensorManager)getSystemService(SENSOR_SERVICE);
        //Almacene la cantidad de sensores disponible
        List listaSensores = sensorAdmin.getSensorList(Sensor.TYPE_ALL);
        //Seleccione el sensor de la lista
        listaSensores = sensorAdmin.getSensorList(Sensor.TYPE_GYROSCOPE);
        if(!listaSensores.isEmpty()){
            Sensor orientationSensor = (Sensor) listaSensores.get(0);
            sensorAdmin.registerListener(this,orientationSensor,
                    SensorManager.SENSOR_DELAY_UI);
        }
        listaSensores = sensorAdmin.getSensorList(Sensor.TYPE_ACCELEROMETER);
        if(!listaSensores.isEmpty()){
            Sensor acelerometroSensor = (Sensor) listaSensores.get(0);
            sensorAdmin.registerListener(this,acelerometroSensor,
                    SensorManager.SENSOR_DELAY_UI);
        }
    }

    private void log(String cadena){
        Tx1.append(cadena + "\n");
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        switch(event.sensor.getType()){
            case Sensor.TYPE_ACCELEROMETER:
                Tx1.setText("X = "+event.values[0]);
                Tx2.setText("Y = "+event.values[1]);
                Tx3.setText("Z = "+event.values[2]);
                break;
            case Sensor.TYPE_GYROSCOPE:
                Tx4.setText("X = "+event.values[0]);
                Tx5.setText("Y = "+event.values[1]);
                Tx6.setText("Z = "+event.values[2]);
                break;
            default:
                break;
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }
}
