package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.media.Image;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;
import android.widget.RelativeLayout;

public class MainActivity extends AppCompatActivity {
    int x=500;
    int y=200;
    ImageButton B1;
    ImageButton B2;
    ImageButton B3;
    ImageButton B4;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //Iniciar la clase. Primero hay que crearla.
        Micanvas fondo = new Micanvas (this);
        setContentView(fondo);
        setContentView(R.layout.activity_main);
        RelativeLayout lienzo = (RelativeLayout) findViewById(R.id.Lienzo);
        lienzo.addView(fondo);

        B1=(ImageButton) findViewById(R.id.imageButton2);
        B1.setOnClickListener(
                new View.OnClickListener(){
                    @Override
                    public void onClick(View v) {
                        fondo.Aumentar(v);
                    }
                }
        );

        B2=(ImageButton) findViewById(R.id.imageButton3);
        B2.setOnClickListener(
                new View.OnClickListener(){
                    @Override
                    public void onClick(View v) {
                        fondo.Disminuir(v);
                    }
                }
        );

        B3= (ImageButton) findViewById(R.id.imageButton5);
        B3.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View view) {
                        fondo.Izquierda(view);
                    }
                }
        );

        B4= (ImageButton) findViewById(R.id.imageButton6);
        B4.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View view) {
                        fondo.Derecha(view);
                    }
                }
        );

    }

    public class Micanvas extends View {
        public Micanvas(Context context) {
            super(context);
        }
        @Override
        protected void onDraw(Canvas canvas) {
            //Cree objeto para dibujar
            Paint pincel = new Paint();
            pincel.setStyle(Paint.Style.STROKE);
            pincel.setStrokeWidth(5);
            pincel.setColor(Color.RED);
            //Seleccionar del objeto
            int ancho=canvas.getWidth();
            int alto=canvas.getHeight();
            canvas.drawRect(0,20,ancho,alto/2,pincel);
            //Otras caracteristicas
            pincel.setStyle(Paint.Style.FILL);
            pincel.setColor(Color.RED);
            canvas.drawCircle(x,y,30,pincel);
        }
        public void Aumentar(View view){
            x=x+10;
            postInvalidate();
        }
        public void Disminuir(View view){
            x=x-10;
            postInvalidate();
        }

        public void Izquierda(View view){
            y=y-10;
            postInvalidate();
        }

        public void Derecha(View view){
            y=y+10;
            postInvalidate();
        }
    }



}