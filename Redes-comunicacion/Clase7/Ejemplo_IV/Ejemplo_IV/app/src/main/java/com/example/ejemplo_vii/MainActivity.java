package com.example.ejemplo_vii;

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
        Tx1=(TextView)findViewById(R.id.textView);
        int Tiempo_Finaliza=10000;
        int Tiempo_paso=1000;
        Conta1 = new CountDownTimer(Tiempo_Finaliza,Tiempo_paso) {
            public void onTick(long millisUntilFinished) {
                //Actividad a realizar cada Tiempo_paso
                Tx1.setText(Integer.toString(t));
                t++;
            }
            public void onFinish() {
                t=0;
                Conta1.start();
            }
        };

    }

    //Funciones para asignar a los botones e iniciar el tempo
    public void iniciar(View view){
        Conta1.start();
    }
    public void parar(View view){
        Conta1.cancel();
    }
}
