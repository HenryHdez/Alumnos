package com.example.ejemplo_ii;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.TextView;
import android.view.View;

public class MainActivity extends AppCompatActivity {
    private EditText In1, In2, Sal;
    private RadioButton R1, R2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        In1=(EditText) findViewById(R.id.editTextText);
        In2=(EditText) findViewById(R.id.editTextText2);
        Sal=(EditText) findViewById(R.id.editTextText3);
        R1=(RadioButton) findViewById(R.id.radioButton);
        R2=(RadioButton) findViewById(R.id.radioButton2);
    }
    public void Calcular(View view){
        double N1=Double.parseDouble(In1.getText().toString());
        double N2=Double.parseDouble(In2.getText().toString());
        double Resul=0;
        if(R1.isChecked()){
            Resul=N1+N2;
            R1.setChecked(false);
        }
        else if(R2.isChecked()){
            Resul=N1-N2;
        }
        else{
            Resul=0;
        }
        Sal.setText(String.valueOf(Resul));
        R1.setChecked(false);
        R2.setChecked(false);
    }
}