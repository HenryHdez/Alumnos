package com.example.ejemplo_iv;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.CountDownTimer;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    TextView Tx1;
    CountDownTimer Conta1;
    int t=0;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Tx1=(TextView) findViewById(R.id.textView);
        //tiempos
        int tiempo_finaliza=10000;
        int tiempo_paso=1000;

        Conta1=new CountDownTimer(tiempo_finaliza,tiempo_paso) {
            @Override
            public void onTick(long millisUntilFinished) {
                Tx1.setText(Integer.toString(t));
                t++;
            }

            @Override
            public void onFinish() {
                t=0;
                Conta1.start();
            }
        };
    }
    public void Iniciar(View view){
        Conta1.start();
    };
    public void Parar(View view){
        Conta1.cancel();
    };
}