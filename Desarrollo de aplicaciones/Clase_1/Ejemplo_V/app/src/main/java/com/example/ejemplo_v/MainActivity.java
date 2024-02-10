package com.example.ejemplo_v;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.Bundle;
import android.view.View;
import android.widget.RelativeLayout;

public class MainActivity extends AppCompatActivity {

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
    }

    public class Micanvas extends View{
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
            //Configure el objeto
            canvas.drawRect(10,70,70,1200,pincel);
            pincel.setTextSize(50); 
            pincel.setStrokeWidth(20);
            pincel.setColor(Color.BLUE);
            canvas.drawText("Hola", 10, 100, pincel);
        }
    }
}