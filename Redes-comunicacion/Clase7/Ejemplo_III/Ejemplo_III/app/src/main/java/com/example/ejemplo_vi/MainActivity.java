package com.example.ejemplo_vi;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.RelativeLayout;

public class MainActivity extends AppCompatActivity {
    //Definición de variables globales
    int x=50;
    int y=50;
    ImageButton bt1;
    ImageButton bt2;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //Inicie la clase encargada de pintar en el contructor
        final Mi_Canvas fondo = new Mi_Canvas(this);
        setContentView(fondo);
        setContentView(R.layout.activity_main);
        RelativeLayout lienzo = (RelativeLayout) findViewById(R.id.lienzo);
        lienzo.addView(fondo);
        //Agregue funciones a los botones mediante un oyente
        bt1=(ImageButton) findViewById(R.id.imageButton);
        bt1.setOnClickListener(
                new View.OnClickListener() { // hago clic en el botón
                    @Override
                    public void onClick(View v) {
                        fondo.Aumentar(v);
                    }});
        bt2=(ImageButton) findViewById(R.id.imageButton2);
        bt2.setOnClickListener(
                new View.OnClickListener() { // hago clic en el botón
                    @Override
                    public void onClick(View v) {
                        fondo.Disminuir(v);
                    }});

        lienzo.setOnTouchListener(new View.OnTouchListener() {
                                     @Override
                                     public boolean onTouch(View v, MotionEvent event) {
                                         x=(int)event.getX();
                                         y=(int)event.getY();
                                         fondo.invalidate();
                                         return false;
                                     }
                                 }
        );
    }
    

    public class Mi_Canvas extends View {
        public Mi_Canvas (Context context){super(context);}
        @Override
        protected void onDraw(Canvas canvas) {
            //Cree el objeto que va a dibujar
            Paint pincel=new Paint();
            //Configure el estilo del objeto
            pincel.setStyle(Paint.Style.FILL);
            pincel.setColor(Color.YELLOW);
            //Dibuje sobre el lienzo
            int ancho=canvas.getWidth();
            int alto=canvas.getHeight();
            canvas.drawRect(0,20,ancho,alto/2,pincel);
            pincel.setStyle(Paint.Style.FILL);
            pincel.setColor(Color.RED);
            canvas.drawCircle(x,y, 10,pincel);

        }
        public void Aumentar(View view){
            x=x+10;
            postInvalidate();
        }
        public void Disminuir(View view){
            x=x-10;
            postInvalidate();
        }
    }
}
