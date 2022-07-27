package com.example.ejemplo_iv;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.TextView;
import android.view.View;

public class MainActivity extends AppCompatActivity {
    private TextView In1, In2, Res;
    private RadioButton R1, R2;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        In1=(EditText) findViewById(R.id.editText);
        In2=(EditText) findViewById(R.id.editText2);
        Res=(EditText) findViewById(R.id.editText3);
        R1=(RadioButton) findViewById(R.id.radioButton);
        R2=(RadioButton) findViewById(R.id.radioButton2);
    }

    public void calcular(View view){
        String N1=In1.getText().toString();
        String N2=In2.getText().toString();
        double Valor1=Double.parseDouble(N1);
        double Valor2=Double.parseDouble(N2);
        double Res3=0;
        //Verifica si el radiobutton 1 esta pulsado
        if(R1.isChecked()){
            Res3=Valor1+Valor2;
        }
        //Verifica si el radiobutton 2 esta pulsado
        if(R2.isChecked()){
            Res3=Valor1-Valor2;
        }
        String Salida=String.valueOf(Res3);
        Res.setText(Salida);
    }
}
