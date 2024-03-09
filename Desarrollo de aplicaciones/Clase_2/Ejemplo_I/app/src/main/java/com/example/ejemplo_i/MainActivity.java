package com.example.ejemplo_i;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.StrictMode;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetSocketAddress;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {
    private EditText Tx1;
    private EditText Tx2;
    private Button Bt1;
    private Button Bt2;
    private Button Bt3;
    private Button Bt4;
    //Estas variables asocian el socket al codigo
    private Socket clientSocket;
    private PrintWriter socketOut;
    private int port = 1234;
    private final String ip = "192.168.104.54";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //Enlace de variables
        Tx1=(EditText) findViewById(R.id.editText);
        Tx2=(EditText) findViewById(R.id.editText2);
        Bt1=(Button) findViewById(R.id.button);
        Bt2=(Button) findViewById(R.id.button2);
        Bt3=(Button) findViewById(R.id.button4);
        //Politica de uso del buffer
        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);
        //Oyente 1 -Conexión-
        Bt1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                try{
                    clientSocket = new Socket();
                    clientSocket.connect(new InetSocketAddress(ip,port),2000);
                    socketOut = new PrintWriter(clientSocket.getOutputStream(), true);
                    Tx2.setText("Conectado");
                }catch(Exception e){
                    e.printStackTrace();
                    Tx2.setText("No conectado");
                }
            }
        });
        //Oyente 2 -Enviar-
        Bt2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                socketOut.println(Tx1.getText());
            }
        });
        //Oyente 4 -Cerrar comunicación-
        Bt3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (clientSocket != null) {
                    try {
                        socketOut.println("cerrar");
                        clientSocket.close();
                        Tx2.setText("Termino comunicación");
                    } catch (IOException e) {
                        Tx2.setText("Error al cerrar");
                    }
                }
            }
        });
    }
}