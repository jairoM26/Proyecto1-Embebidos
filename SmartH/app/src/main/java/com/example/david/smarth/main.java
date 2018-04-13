package com.example.david.smarth;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.io.IOException;
import java.util.concurrent.TimeUnit;

public class main extends AppCompatActivity {
    boolean flag = true;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final String host= new config().gethostname();





        final Handler RefreshHandler;
        RefreshHandler = new Handler() {

            @Override
            public void handleMessage(Message msg) {
                TextView t_lg = (TextView)findViewById(R.id.textView_lg);
                TextView t_ls = (TextView)findViewById(R.id.textView_ls);
                TextView t_lc = (TextView)findViewById(R.id.textView_lc);
                TextView t_lc1 = (TextView)findViewById(R.id.textView_lc1);
                TextView t_lc2 = (TextView)findViewById(R.id.textView_lc2);
                TextView t_pg = (TextView)findViewById(R.id.textView_pg);
                TextView t_ps = (TextView)findViewById(R.id.textView_ps);
                TextView t_pc2 = (TextView)findViewById(R.id.textView_pc2);
                TextView t_pc1 = (TextView)findViewById(R.id.textView_pc1);
                String signals= (String)msg.obj;

                if(signals.substring(0,1).equals("1")){
                    t_lg.setText("ON");
                }
                if(signals.substring(0,1).equals("0")){
                    t_lg.setText("OFF");
                }
                if(signals.substring(1,2).equals("1")){
                    t_ls.setText("ON");
                }
                if(signals.substring(1,2).equals("0")){
                    t_ls.setText("OFF");
                }
                if(signals.substring(2,3).equals("1")){
                    t_lc.setText("ON");
                }
                if(signals.substring(2,3).equals("0")){
                    t_lc.setText("OFF");
                }
                if(signals.substring(3,4).equals("1")){
                    t_lc2.setText("ON");
                }
                if(signals.substring(3,4).equals("0")){
                    t_lc2.setText("OFF");
                }
                if(signals.substring(4,5).equals("1")){
                    t_lc1.setText("ON");
                }
                if(signals.substring(4,5).equals("0")){
                    t_lc1.setText("OFF");
                }
                if(signals.substring(5,6).equals("1")){
                    t_pg.setText("Abierta");
                }
                if(signals.substring(5,6).equals("0")){
                    t_pg.setText("Cerrada");
                }
                if(signals.substring(6,7).equals("1")){
                    t_ps.setText("Abierta");
                }
                if(signals.substring(6,7).equals("0")){
                    t_ps.setText("Cerrada");
                }
                if(signals.substring(7,8).equals("1")){
                    t_pc2.setText("Abierta");
                }
                if(signals.substring(7,8).equals("0")){
                    t_pc2.setText("Cerrada");
                }
                if(signals.substring(8,9).equals("1")){
                    t_pc1.setText("Abierta");
                }
                if(signals.substring(8,9).equals("0")){
                    t_pc1.setText("Cerrada");
                }




            }
        };
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
        new Thread(new Runnable(){
            public void run(){
                Client client = new Client(host, 22000);

                try {
                    client.connect();
                    client.readResponse();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                while(true && flag ==true) {

                    try {

                        client.sendDataForSignals();
                        String sig = client.readResponse();
                        System.out.println("Signals  " + sig);
                        String message = sig;
                        Message msg = Message.obtain(); // Creates an new Message instance
                        msg.obj = message; // Put the string into Message, into "obj" field.
                        msg.setTarget(RefreshHandler); // Set the Handler
                        msg.sendToTarget();





                    } catch (IOException e) {
                        e.printStackTrace();
                    }

                    try {
                        TimeUnit.MILLISECONDS.sleep(200);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }).start();

            }
        });

        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                final Button button = findViewById(R.id.button_image);
                button.setOnClickListener(new View.OnClickListener() {
                    public void onClick(View v) {
                        flag = false;
                        main.this.finish();
                        Intent intent = new Intent(main.this, display_image.class);
                        main.this.startActivity(intent);

                    }
                });

                final Button button_lg = findViewById(R.id.button_g);
                button_lg.setOnClickListener(new View.OnClickListener() {
                    public void onClick(View v) {
                        new Thread(new Runnable(){
                            public void run(){
                                Client client = new Client(host, 22000);
                                try {
                                    client.connect();
                                    client.readResponse();
                                    client.sendDataForLights("1");

                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                            }
                        }).start();
                    }
                });

                final Button button_ls = findViewById(R.id.button_s);
                button_ls.setOnClickListener(new View.OnClickListener() {
                    public void onClick(View v) {
                        new Thread(new Runnable(){
                            public void run(){
                                Client client = new Client(host, 22000);
                                try {
                                    client.connect();
                                    client.readResponse();
                                    client.sendDataForLights("2");

                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                            }
                        }).start();
                    }
                });

                final Button button_lc = findViewById(R.id.button_c);
                button_lc.setOnClickListener(new View.OnClickListener() {
                    public void onClick(View v) {
                        new Thread(new Runnable(){
                            public void run(){
                                Client client = new Client(host, 22000);
                                try {
                                    client.connect();
                                    client.readResponse();
                                    client.sendDataForLights("3");

                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                            }
                        }).start();
                    }
                });

                final Button button_c2 = findViewById(R.id.button_c2);
                button_c2.setOnClickListener(new View.OnClickListener() {
                    public void onClick(View v) {
                        new Thread(new Runnable(){
                            public void run(){
                                Client client = new Client(host, 22000);
                                try {
                                    client.connect();
                                    client.readResponse();
                                    client.sendDataForLights("4");

                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                            }
                        }).start();
                    }
                });

                final Button button_c1 = findViewById(R.id.button_c1);
                button_c1.setOnClickListener(new View.OnClickListener() {
                    public void onClick(View v) {
                        new Thread(new Runnable(){
                            public void run(){
                                Client client = new Client(host, 22000);
                                try {
                                    client.connect();
                                    client.readResponse();
                                    client.sendDataForLights("5");

                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                            }
                        }).start();
                    }
                });
            }
        });

    }
}
