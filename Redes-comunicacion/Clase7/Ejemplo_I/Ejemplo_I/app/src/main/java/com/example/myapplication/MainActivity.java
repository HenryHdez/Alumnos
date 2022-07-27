package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {
    private EditText In1,In2, Re;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //Inicie las clases y asigne el id correspondiente.
        In1=(EditText)findViewById(R.id.Entrada1);
        In2=(EditText)findViewById(R.id.Entrada2);
        Re=(EditText)findViewById(R.id.Resultado);
    }

    //Metodo a asignar al boton
    public void Funcion_clic(View view){
        //Leer de un campo de texto
        String N1=In1.getText().toString();
        String N2=In2.getText().toString();
        //Convetir texto a numero
        double Valor1=Double.parseDouble(N1);
        double Valor2=Double.parseDouble(N2);
        double Valor3=Valor1+Valor2;
        //Convetir numero a String
        String Salida=String.valueOf(Valor3);
        //Publicar en campo de salida
        Re.setText(Salida);
    }

}