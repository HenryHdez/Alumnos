package com.example.ejemplo_i;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {
    private EditText Caja1, Caja2, Caja3;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        //Definición del constructor
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Caja1=(EditText) findViewById(R.id.In1);
        Caja2=(EditText) findViewById(R.id.In2);
        Caja3=(EditText) findViewById(R.id.Sal1);
    }
    //Función del botón
    public void Funcionclic(View view){
        String N1=Caja1.getText().toString();
        String N2= Caja2.getText().toString();
        double x= Double.parseDouble(N1);
        double y= Double.parseDouble(N2);
        double z=x+y;
        String Salida=String.valueOf(z);
        Caja3.setText(Salida);
    }
}