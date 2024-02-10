package com.example.ejemplo_vii;

import androidx.appcompat.app.AppCompatActivity;

import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.widget.TextView;

import java.util.List;

public class MainActivity extends AppCompatActivity {
    TextView Tx1;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Tx1=(TextView) findViewById(R.id.textView2);
        //Gestor de sensores
        SensorManager Administrador = (SensorManager) getSystemService(SENSOR_SERVICE);
        List Listasensores = Administrador.getSensorList(Sensor.TYPE_ALL);

        //Leer sensores
        for(int i=0;i<Listasensores.size();i++){
            Sensor var_sensor=(Sensor) Listasensores.get(i);
            Tx1.append(String.valueOf(var_sensor.getName())+'\n');
        }
    }
}